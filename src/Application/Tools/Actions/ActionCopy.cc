/*
 For more information, please see: http://software.sci.utah.edu

 The MIT License

 Copyright (c) 2009 Scientific Computing and Imaging Institute,
 University of Utah.


 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

#include <Core/Action/ActionFactory.h>
#include <Core/Volume/MaskVolumeSlice.h>

#include <Application/Clipboard/Clipboard.h>
#include <Application/Clipboard/ClipboardUndoBufferItem.h>
#include <Application/Tools/Actions/ActionCopy.h>
#include <Application/Layer/MaskLayer.h>
#include <Application/Layer/LayerManager.h>
#include <Application/ProjectManager/ProjectManager.h>
#include <Application/UndoBuffer/UndoBuffer.h>
#include <Application/ViewerManager/ViewerManager.h>

CORE_REGISTER_ACTION( Seg3D, Copy )

namespace Seg3D
{

class ActionCopyPrivate
{
public:
	std::string target_layer_id_;
	int slice_type_;
	size_t slice_number_;
	SandboxID sandbox_;

	Core::MaskLayerHandle target_layer_;
	Core::MaskVolumeSliceHandle vol_slice_;

	bool deduce_params_;
};

ActionCopy::ActionCopy() :
	private_( new ActionCopyPrivate )
{
	this->add_layer_id( this->private_->target_layer_id_ );
	this->add_parameter( this->private_->slice_type_ );
	this->add_parameter( this->private_->slice_number_ );
	this->add_parameter( this->private_->sandbox_ );

	this->private_->deduce_params_ = false;
}

bool ActionCopy::validate( Core::ActionContextHandle& context )
{
	// Make sure that the sandbox exists
	if ( !LayerManager::CheckSandboxExistence( this->private_->sandbox_, context ) )
	{
		return false;
	}

	if ( this->private_->deduce_params_ )
	{
		size_t active_viewer_id = static_cast< size_t >( ViewerManager::Instance()->
			active_viewer_state_->get() );
		ViewerHandle viewer = ViewerManager::Instance()->get_viewer( active_viewer_id );
		if ( viewer->is_volume_view() )
		{
			context->report_error( "Can't copy from a volume view" );
			return false;
		}
		
		LayerHandle active_layer = LayerManager::Instance()->get_active_layer();

		if ( !active_layer || active_layer->get_type() != Core::VolumeType::MASK_E )
		{
			context->report_error( "Nothing to copy from" );
			return false;
		}
		
		Core::VolumeSliceHandle vol_slice = viewer->get_active_volume_slice();
		this->private_->target_layer_ = boost::dynamic_pointer_cast< MaskLayer >( active_layer );
		this->private_->target_layer_id_ = active_layer->get_layer_id();
		this->private_->slice_number_ = vol_slice->get_slice_number();
		this->private_->slice_type_ = vol_slice->get_slice_type();

		// Need to translate the action again because the parameters weren't ready
		if ( !this->translate( context ) ) return false;

		// Set the deduce_params_ flag to false so if the action is re-run (by the undo buffer),
		// it won't need to go through the process again. 
		this->private_->deduce_params_ = false;
	}
	
	// Check whether the layer exists and is of the right type and return an
	// error if not
	if ( !( LayerManager::CheckLayerExistenceAndType( this->private_->target_layer_id_,
		Core::VolumeType::MASK_E, context, this->private_->sandbox_ ) ) ) return false;

	// Check whether the layer is available for read access.
	if ( !( LayerManager::CheckLayerAvailabilityForUse( this->private_->target_layer_id_, 
		context, this->private_->sandbox_ ) ) ) return false;
	
	this->private_->target_layer_ = LayerManager::FindMaskLayer( 
		this->private_->target_layer_id_, this->private_->sandbox_ );
	
	if ( this->private_->slice_type_ != Core::VolumeSliceType::AXIAL_E &&
		this->private_->slice_type_ != Core::VolumeSliceType::CORONAL_E &&
		this->private_->slice_type_ != Core::VolumeSliceType::SAGITTAL_E )
	{
		context->report_error( "Invalid slice type" );
		return false;
	}
	
	Core::VolumeSliceType slice_type = static_cast< Core::VolumeSliceType::enum_type >(
		this->private_->slice_type_ );
		
	Core::MaskVolumeSliceHandle volume_slice( new Core::MaskVolumeSlice(
		this->private_->target_layer_->get_mask_volume(), slice_type ) );
	if ( this->private_->slice_number_ >= volume_slice->number_of_slices() )
	{
		context->report_error( "Slice number is out of range." );
		return false;
	}

	volume_slice->set_slice_number( this->private_->slice_number_ );
	this->private_->vol_slice_ = volume_slice;
		
	return true;
}

bool ActionCopy::run( Core::ActionContextHandle& context, Core::ActionResultHandle& result )
{
	// Only create provenance and undo record if the action is not running in a sandbox
	if ( this->private_->sandbox_ == -1 )
	{
		ClipboardItemConstHandle old_item = Clipboard::Instance()->get_item();
		ClipboardItemHandle checkpoint;
		ProvenanceID old_prov_id = -1;
		if ( old_item )
		{
			checkpoint = old_item->clone();
			old_prov_id = old_item->get_provenance_id();
		}
		ProvenanceStep* prov_step = new ProvenanceStep;
		prov_step->set_input_provenance_ids( this->get_input_provenance_ids() );
		prov_step->set_output_provenance_ids( this->get_output_provenance_ids( 1 ) );
		if ( old_prov_id != -1 )
		{
			prov_step->set_replaced_provenance_ids( ProvenanceIDList( 1, old_prov_id ) );
		}
		prov_step->set_action_name( this->get_type() );
		prov_step->set_action_params( this->export_params_to_provenance_string() );
		ProvenanceStepID step_id = ProjectManager::Instance()->get_current_project()->
			add_provenance_record( ProvenanceStepHandle( prov_step ) );

		ClipboardUndoBufferItemHandle undo_item( new ClipboardUndoBufferItem( "Copy",
			checkpoint ) );
		undo_item->set_redo_action( this->shared_from_this() );
		undo_item->set_provenance_step_id( step_id );
		UndoBuffer::Instance()->insert_undo_item( context, undo_item );
	}
	
	size_t nx = this->private_->vol_slice_->nx();
	size_t ny = this->private_->vol_slice_->ny();

	ClipboardItemHandle clipboard_item = Clipboard::Instance()->get_item( nx, ny,
		Core::DataType::UCHAR_E, this->private_->sandbox_ );
	 this->private_->vol_slice_->copy_slice_data( reinterpret_cast< unsigned char* >( 
		clipboard_item->get_buffer() ) );
	 clipboard_item->set_provenance_id( this->get_output_provenance_id() );

	return true;
}

void ActionCopy::clear_cache()
{
	this->private_->target_layer_.reset();
	this->private_->vol_slice_.reset();
}

void ActionCopy::Dispatch( Core::ActionContextHandle context )
{
	ActionCopy* action = new ActionCopy;
	action->private_->deduce_params_ = true;

	Core::ActionDispatcher::PostAction( Core::ActionHandle( action ), context );
}

void ActionCopy::Dispatch( Core::ActionContextHandle context, 
						  const std::string& layer_id, int slice_type, size_t slice_number )
{
	ActionCopy* action = new ActionCopy;
	action->private_->deduce_params_ = false;
	action->private_->target_layer_id_ = layer_id;
	action->private_->slice_type_ = slice_type;
	action->private_->slice_number_ = slice_number;

	Core::ActionDispatcher::PostAction( Core::ActionHandle( action ), context );
}

} // end namespace Seg3D
