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

//Boost Includes
#include <boost/lexical_cast.hpp>

//Core Includes - for logging
#include <Core/Utils/Log.h>

//QtUtils Includes
#include <QtUtils/Bridge/QtBridge.h>

//Interface Includes
#include <Interface/AppInterface/LayerGroupWidget.h>
#include <Interface/AppInterface/StyleSheet.h>
#include <Interface/AppInterface/DropSpaceWidget.h>
#include <Interface/AppInterface/OverlayWidget.h>
#include <Interface/AppInterface/PushDragButton.h>

//UI Includes
#include "ui_LayerGroupWidget.h"

//Application Includes
#include <Application/Layer/DataLayer.h>
#include <Application/Layer/MaskLayer.h>
#include <Application/Layer/LayerGroup.h>
#include <Application/LayerManager/Actions/ActionDeleteLayers.h>
#include <Application/LayerManager/Actions/ActionNewMaskLayer.h>
#include <Application/LayerManager/Actions/ActionMoveGroupAbove.h>


namespace Seg3D
{
	
class LayerGroupWidgetPrivate
{
public:
	Ui::LayerGroupWidget ui_;
	
	QtUtils::QtSliderDoubleCombo* center_x_adjuster_crop_;
	QtUtils::QtSliderDoubleCombo* center_y_adjuster_crop_;
	QtUtils::QtSliderDoubleCombo* center_z_adjuster_crop_;
	
	QtUtils::QtSliderDoubleCombo* size_width_adjuster_crop_;
	QtUtils::QtSliderDoubleCombo* size_height_adjuster_crop_;
	QtUtils::QtSliderDoubleCombo* size_depth_adjuster_crop_;
	
	PushDragButton* activate_button_;
    QtUtils::QtSliderDoubleCombo* scale_adjuster_;
	DropSpaceWidget* drop_space_;
	OverlayWidget* overlay_;

	int group_height;
};
	
LayerGroupWidget::LayerGroupWidget( QWidget* parent, LayerHandle layer ) :
	QWidget( parent ),
	private_( new LayerGroupWidgetPrivate ),
	group_menus_open_( false ),
	picked_up_( false ),
	drop_group_set_( false )
{	
    LayerGroupHandle group = layer->get_layer_group();

	this->private_->ui_.setupUi( this );
	
	this->group_id_ = group->get_group_id();
	
	// Set up the Drag and Drop
	this->setAcceptDrops( true );

	// hide the tool bars 
	this->private_->ui_.roi_->hide();
	this->private_->ui_.resample_->hide();
	this->private_->ui_.flip_rotate_->hide();
	this->private_->ui_.transform_->hide();
	this->private_->ui_.delete_->hide();
	this->private_->ui_.delete_button_->setEnabled( false );

	//add the PushDragButton
	this->private_->activate_button_ = new PushDragButton( this->private_->ui_.group_header_ );
	this->private_->activate_button_->setObjectName( QString::fromUtf8( "activate_button_" ) );
	this->private_->activate_button_->setStyleSheet( StyleSheet::GROUP_PUSHDRAGBUTTON_C );
	QSizePolicy sizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed );
	sizePolicy.setHeightForWidth( this->private_->activate_button_->sizePolicy().hasHeightForWidth() );
    this->private_->activate_button_->setSizePolicy( sizePolicy );
    this->private_->activate_button_->setMinimumSize( QSize( 152, 21 ) );
    this->private_->activate_button_->setCheckable( false );
    this->private_->activate_button_->setFlat( true );
	this->private_->ui_.horizontalLayout->insertWidget( 1, this->private_->activate_button_ );

	// set some values of the GUI
	std::string group_name = Core::ExportToString( group->get_grid_transform().get_nx() ) + " x " +
		Core::ExportToString( group->get_grid_transform().get_ny() ) + " x " +
		Core::ExportToString( group->get_grid_transform().get_nz() );
	this->private_->activate_button_->setText( QString::fromStdString( group_name ) );


	// add the slider spinner combo's for the crop
	this->private_->center_x_adjuster_crop_ = new QtUtils::QtSliderDoubleCombo( this->private_->ui_.widget );
	this->private_->ui_.horizontalLayout_11->addWidget( this->private_->center_x_adjuster_crop_ );
	this->private_->center_x_adjuster_crop_->setObjectName( QString::fromUtf8( "center_x_adjuster_crop_" ) );
	
	this->private_->center_y_adjuster_crop_ = new QtUtils::QtSliderDoubleCombo( this->private_->ui_.widget_2 );
	this->private_->ui_.horizontalLayout_12->addWidget( this->private_->center_y_adjuster_crop_ );
	this->private_->center_y_adjuster_crop_->setObjectName( QString::fromUtf8( "center_y_adjuster_crop_" ) );
	
	this->private_->center_z_adjuster_crop_ = new QtUtils::QtSliderDoubleCombo( this->private_->ui_.widget_3 );
	this->private_->ui_.horizontalLayout_14->addWidget( this->private_->center_z_adjuster_crop_ );
	this->private_->center_z_adjuster_crop_->setObjectName( QString::fromUtf8( "center_z_adjuster_crop_" ) );
	
	this->private_->size_height_adjuster_crop_ = new QtUtils::QtSliderDoubleCombo( this->private_->ui_.widget_4 );
	this->private_->ui_.horizontalLayout_7->addWidget( this->private_->size_height_adjuster_crop_ );
	this->private_->size_height_adjuster_crop_->setObjectName( QString::fromUtf8( "size_height_adjuster_crop_" ) );
	
	this->private_->size_width_adjuster_crop_ = new QtUtils::QtSliderDoubleCombo( this->private_->ui_.widget_5 );
	this->private_->ui_.horizontalLayout_9->addWidget( this->private_->size_width_adjuster_crop_ );
	this->private_->size_width_adjuster_crop_->setObjectName( QString::fromUtf8( "size_width_adjuster_crop_" ) );
	
	this->private_->size_depth_adjuster_crop_ = new QtUtils::QtSliderDoubleCombo( this->private_->ui_.widget_6 );
	this->private_->ui_.horizontalLayout_10->addWidget( this->private_->size_depth_adjuster_crop_ );
	this->private_->size_depth_adjuster_crop_->setObjectName( QString::fromUtf8( "size_depth_adjuster_crop_" ) );
	
	this->private_->scale_adjuster_ = new QtUtils::QtSliderDoubleCombo( this->private_->ui_.widget_7 );
	this->private_->ui_.horizontalLayout_15->addWidget( this->private_->scale_adjuster_ );
	this->private_->scale_adjuster_->setObjectName( QString::fromUtf8( "scale_adjuster_" ) );
	
	this->private_->drop_space_ = new DropSpaceWidget( this, 105 );
	this->private_->ui_.verticalLayout_12->insertWidget( 0, this->private_->drop_space_ );
	
	this->private_->drop_space_->hide();
	
	// set some local values for the current size
	this->current_width_ = static_cast<int>( group->get_grid_transform().get_nx() );
	this->current_height_ = static_cast<int>( group->get_grid_transform().get_ny() );
	this->current_depth_ = static_cast<int>( group->get_grid_transform().get_nz() );

	//  connect the gui signals and slots
    connect( this->private_->scale_adjuster_, SIGNAL( valueAdjusted( double ) ), this, SLOT( adjust_new_size_labels( double )) );
	connect( this->private_->ui_.open_button_, SIGNAL( toggled( bool ) ), this, SLOT( show_layers( bool )) );
	connect( this->private_->ui_.group_resample_button_, SIGNAL( clicked( bool ) ), this, SLOT( show_resample( bool )) );
	connect( this->private_->ui_.group_crop_button_, SIGNAL( clicked( bool ) ), this, SLOT( show_crop( bool )) );
	connect( this->private_->ui_.group_transform_button_, SIGNAL( clicked( bool ) ), this, SLOT( show_transform( bool )) );
	connect( this->private_->ui_.group_flip_rotate_button_, SIGNAL( clicked ( bool ) ), this, SLOT( show_flip_rotate( bool )) );
	connect( this->private_->ui_.group_delete_button_, SIGNAL( clicked ( bool ) ), this, SLOT( show_delete( bool )) );
	connect( this->private_->ui_.confirm_delete_checkbox_, SIGNAL( clicked ( bool ) ), this, SLOT( enable_delete_button( bool )) );
	connect( this->private_->ui_.delete_button_, SIGNAL( clicked () ), this, SLOT( uncheck_delete_confirm() ) );
	
	// Add the current layer to the new group
	this->insert_layer( layer, -1 );

	
	//Set the defaulf values for the Group UI and make the connections to the state engine
	    // --- GENERAL ---
    
	    QtUtils::QtBridge::Connect( this->private_->ui_.open_button_, group->show_layers_state_ );
	    QtUtils::QtBridge::Connect( this->private_->ui_.group_visibility_button_, 
			group->visibility_state_ );
	    QtUtils::QtBridge::Connect( this->private_->ui_.delete_button_, 
			boost::bind( &ActionDeleteLayers::Dispatch, 
				Core::Interface::GetWidgetActionContext(), group ) );
		QtUtils::QtBridge::Connect( this->private_->ui_.group_new_button_, 
			boost::bind( &ActionNewMaskLayer::Dispatch, 
				Core::Interface::GetWidgetActionContext(), group ) );
	
	    // --- RESAMPLE ---
	    // = set the default values
	    this->private_->ui_.x_axis_label_current_->setText( QString::fromUtf8("X: ") + 
			QString::number( group->get_grid_transform().get_nx()) );
	    this->private_->ui_.y_axis_label_current_->setText( QString::fromUtf8("Y: ") + 
			QString::number( group->get_grid_transform().get_ny()) );
	    this->private_->ui_.z_axis_label_current_->setText( QString::fromUtf8("Z: ") + 
			QString::number( group->get_grid_transform().get_nz()) );
	    
	    this->private_->ui_.x_axis_label_new_->setText( QString::fromUtf8("X: ") + 
			QString::number( group->get_grid_transform().get_nx()) );
	    this->private_->ui_.y_axis_label_new_->setText( QString::fromUtf8("Y: ") + 
			QString::number( group->get_grid_transform().get_ny()) );
	    this->private_->ui_.z_axis_label_new_->setText( QString::fromUtf8("Z: ") + 
			QString::number( group->get_grid_transform().get_nz()) );
	    
	    QFont font;
        font.setPointSize( 10 );
        this->private_->ui_.x_axis_label_current_->setFont( font );
        this->private_->ui_.y_axis_label_current_->setFont( font );
        this->private_->ui_.z_axis_label_current_->setFont( font );
        
        font.setBold( true );
        this->private_->ui_.x_axis_label_new_->setFont( font );
        this->private_->ui_.y_axis_label_new_->setFont( font );
        this->private_->ui_.z_axis_label_new_->setFont( font );
        
        
        // = make the connections
        QtUtils::QtBridge::Connect( this->private_->scale_adjuster_, group->resample_factor_state_ );
	    QtUtils::QtBridge::Connect( this->private_->ui_.resample_replace_checkBox_, 
			group->resample_replace_state_ );
        

        // --- CROP ---
        // = set the default values
        this->private_->size_width_adjuster_crop_->setRange( 0, 
			group->get_grid_transform().get_nx() );
        this->private_->size_height_adjuster_crop_->setRange( 0, 
			group->get_grid_transform().get_ny() );
        this->private_->size_depth_adjuster_crop_->setRange( 0, 
			group->get_grid_transform().get_nz() );
  
// TODO: Need to migrate this to the application thread		      
//		group->crop_size_width_state_->set( group->get_grid_transform().get_nx() );
//		group->crop_size_height_state_->set( group->get_grid_transform().get_ny() );
//		group->crop_size_depth_state_->set( group->get_grid_transform().get_nz() );
	
        this->private_->center_x_adjuster_crop_->setRange( 0, group->get_grid_transform().get_nx() );
        this->private_->center_y_adjuster_crop_->setRange( 0, group->get_grid_transform().get_ny() );
        this->private_->center_z_adjuster_crop_->setRange( 0, group->get_grid_transform().get_nz() );
        
        // = make the connections
        QtUtils::QtBridge::Connect( this->private_->size_width_adjuster_crop_, group->crop_size_width_state_ );
        QtUtils::QtBridge::Connect( this->private_->size_height_adjuster_crop_, group->crop_size_height_state_ );
        QtUtils::QtBridge::Connect( this->private_->size_depth_adjuster_crop_, group->crop_size_depth_state_ );
        
        QtUtils::QtBridge::Connect( this->private_->center_x_adjuster_crop_, group->crop_center_x_state_ );
        QtUtils::QtBridge::Connect( this->private_->center_y_adjuster_crop_, group->crop_center_y_state_ );
        QtUtils::QtBridge::Connect( this->private_->center_z_adjuster_crop_, group->crop_center_z_state_ );
        
        QtUtils::QtBridge::Connect( this->private_->ui_.crop_replace_checkBox_, group->crop_replace_state_ );
        
        
        // --- TRANSFORM ---
        // = set the default values
        
		// TODO: Being called from the wrong thread needs to be migrated to application thread
		//group->transform_spacing_x_state_->set( group->get_grid_transform().spacing_x() );
        //group->transform_spacing_y_state_->set( group->get_grid_transform().spacing_y() );
        //group->transform_spacing_z_state_->set( group->get_grid_transform().spacing_z() );
        
        // = make the connections
	    QtUtils::QtBridge::Connect( this->private_->ui_.origin_x_spinbox_, group->transform_origin_x_state_ );
	    QtUtils::QtBridge::Connect( this->private_->ui_.origin_y_spinbox_, group->transform_origin_y_state_ );
	    QtUtils::QtBridge::Connect( this->private_->ui_.origin_z_spinbox_, group->transform_origin_z_state_ );
	    
	    QtUtils::QtBridge::Connect( this->private_->ui_.spacing_x_spinbox_, group->transform_spacing_x_state_ );
	    QtUtils::QtBridge::Connect( this->private_->ui_.spacing_y_spinbox_, group->transform_spacing_y_state_ );
	    QtUtils::QtBridge::Connect( this->private_->ui_.spacing_z_spinbox_, group->transform_spacing_z_state_ );
        
        QtUtils::QtBridge::Connect( this->private_->ui_.transform_replace_checkBox_, group->transform_replace_state_ );

	this->private_->ui_.group_frame_layout_->setAlignment( Qt::AlignTop );
	this->private_->ui_.verticalLayout_13->setAlignment( Qt::AlignTop );

	this->private_->overlay_ = new OverlayWidget( this );
	this->private_->overlay_->setStyleSheet( QString::fromUtf8( "background-color: rgba( 255, 0, 0, 200 )" ) );
	this->private_->overlay_->hide();	

	this->private_->ui_.fake_widget_->setMinimumHeight( 0 );
	this->private_->ui_.fake_widget_->hide();
	
	this->private_->ui_.group_dummy_->hide();

	this->private_->group_height = this->private_->ui_.tools_and_layers_widget_->height();
	
}

LayerGroupWidget::~LayerGroupWidget()
{
}

void LayerGroupWidget::mousePressEvent( QMouseEvent *event )
{
	// Exit immediately if they are no longer holding the button the press event isnt valid
	if( event->button() != Qt::LeftButton )
	{ 
		return;
	}

	if( this->group_menus_open_ )
		return;

	QPoint hotSpot = event->pos();

	// Make up some mimedata containing the layer_id of the layer
	QMimeData *mimeData = new QMimeData;
	mimeData->setText(QString::fromStdString( std::string( "group|" ) +  this->get_group_id() ) );

	// Create a drag object and insert the hotspot
	QDrag *drag = new QDrag( this );
	drag->setMimeData( mimeData );

	// here we add basically a screenshot of the widget
	drag->setPixmap( QPixmap::grabWidget( this ));
	drag->setHotSpot( hotSpot );

	// Next we hide the LayerWidget that we are going to be dragging.
	this->setMinimumHeight( this->height() );
	this->seethrough( true );
	this->picked_up_ = true;

	Q_EMIT prep_groups_for_drag_and_drop_signal_( true );
	Q_EMIT picked_up_group_size_signal_( this->height() );
	
	// Finally if our drag was aborted then we reset the layers styles to be visible
	if( ( ( drag->exec(Qt::MoveAction, Qt::MoveAction) ) == Qt::MoveAction ) && this->drop_group_set_ )
	{
		ActionMoveGroupAbove::Dispatch( Core::Interface::GetWidgetActionContext(), 
			this->get_group_id(), this->drop_group_->get_group_id() );
	}
	
	this->setMinimumHeight( 0 );
	this->drop_group_set_ = false;
	this->seethrough( false );
	this->private_->overlay_->hide();
	
	Q_EMIT prep_groups_for_drag_and_drop_signal_( false );
	this->picked_up_ = false;
}

void LayerGroupWidget::set_drop_target( LayerGroupWidget* target_group)
{
	this->drop_group_ = target_group;
	this->drop_group_set_ = true;
}


void LayerGroupWidget::dropEvent( QDropEvent* event )
{
	std::vector<std::string> mime_data = 
		Core::SplitString( event->mimeData()->text().toStdString(), "|" );
	
	if( mime_data.size() < 2 ) return;

	if( ( this->get_group_id() == mime_data[ 1 ] ) || ( mime_data[ 0 ] != "group" ) )
	{
		event->ignore();
		return;
	}

	if( this->group_menus_open_ )
		return;
	
	this->set_drop( false );
	this->private_->overlay_->hide();

	dynamic_cast< LayerGroupWidget* >( event->source() )->set_drop_target( this ); 
	event->setDropAction(Qt::MoveAction);
	event->accept();
}

void LayerGroupWidget::dragEnterEvent( QDragEnterEvent* event)
{
	this->private_->overlay_->show();

	std::vector<std::string> mime_data = 
		Core::SplitString( event->mimeData()->text().toStdString(), "|" );
	
	if( mime_data.size() < 2 ) return;

	if( ( this->get_group_id() != mime_data[ 0 ] ) && ( mime_data[ 0 ] == "group" ) )
	{
		this->set_drop( true );
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else
	{
		this->set_drop( false );
		this->private_->overlay_->hide();
		event->ignore();
	}
}

void LayerGroupWidget::dragLeaveEvent( QDragLeaveEvent* event )
{
	this->set_drop( false );
	this->private_->overlay_->hide();
}

void LayerGroupWidget::seethrough( bool see )
{
	this->set_picked_up( see );

	if( see )
	{
		this->private_->ui_.base_->hide();
	}
	else
	{
		this->private_->ui_.base_->show();
	}
	
	this->repaint();
}

void LayerGroupWidget::set_drop( bool drop )
{
	this->private_->drop_space_->set_height( this->picked_up_group_height_ + 4 );
	
	if( this->picked_up_ )
	{
		return;
	}
	
	if( drop )
	{
		this->private_->drop_space_->show();
	}
	else
	{
		this->private_->drop_space_->hide();
	}
	this->repaint();
}	
	
void LayerGroupWidget::insert_layer( LayerHandle layer, int index )
{
	LayerWidgetQHandle new_layer_handle( new LayerWidget(this->private_->ui_.group_frame_, layer ) );
	
	if( index == -1 )
	{
		// If the layer is a data layer, put it on the bottom.
		if( new_layer_handle->get_volume_type() == Core::VolumeType::DATA_E )
			this->private_->ui_.group_frame_layout_->insertWidget( -1, new_layer_handle.data() );
		else
			this->private_->ui_.group_frame_layout_->insertWidget( 0, new_layer_handle.data() );
	}
	else
	{
		this->private_->ui_.group_frame_layout_->insertWidget( index, new_layer_handle.data() );
	}
	this->layer_list_.push_back( new_layer_handle );
	this->repaint();
	
	connect( new_layer_handle.data(), SIGNAL( prep_for_drag_and_drop( bool ) ), 
		this, SLOT( notify_layer_manager_widget( bool ) ) );

}

	
bool LayerGroupWidget::delete_layer( LayerHandle layer )
{	
	for( QVector< LayerWidgetQHandle >::iterator i = this->layer_list_.begin(); i != 
		this->layer_list_.end(); ++i)
	{
		if( ( *i )->get_layer_id() == layer->get_layer_id() )
		{
			( *i )->deleteLater();
			this->layer_list_.erase( i );
			this->repaint();
			return true;
		}
	}
	return false;  
}
	
LayerWidgetQWeakHandle LayerGroupWidget::set_active_layer( LayerHandle layer )
{
	std::string layer_id = layer->get_layer_id();
    for( int i = 0; i < this->layer_list_.size(); ++i)
	{
	    if( layer_id == this->layer_list_[i]->get_layer_id() )
	    {
	        this->layer_list_[i]->set_active( true );
			return this->layer_list_[i];
	    }
	}
	return LayerWidgetQWeakHandle();
}

const std::string& LayerGroupWidget::get_group_id()
{
	return this->group_id_;
}

	
void LayerGroupWidget::show_selection_checkboxes( bool show )
{
	for( int i = 0; i < this->layer_list_.size(); ++i)
	{
		this->layer_list_[i]->show_selection_checkbox( show );
		this->layer_list_[i]->set_group_menu_status( show );
		this->layer_list_[i]->setAcceptDrops( !show ); 
	}
	this->group_menus_open_ = show;
}

void LayerGroupWidget::adjust_new_size_labels( double scale_factor )
{
    this->private_->ui_.x_axis_label_new_->setText( QString::fromUtf8("X: ") + 
		QString::number( this->current_width_ * scale_factor ) );
	this->private_->ui_.y_axis_label_new_->setText( QString::fromUtf8("Y: ") + 
		QString::number( this->current_height_ * scale_factor ) );
	this->private_->ui_.z_axis_label_new_->setText( QString::fromUtf8("Z: ") + 
		QString::number( this->current_depth_ * scale_factor ) );
}
	
	
void LayerGroupWidget::enable_delete_button( bool enable )
{
	this->private_->ui_.delete_button_->setEnabled( enable );
}

void LayerGroupWidget::uncheck_delete_confirm()
{
    this->private_->ui_.confirm_delete_checkbox_->setChecked( false );
    this->private_->ui_.delete_button_->setEnabled( false );
    show_delete( false );
}

void LayerGroupWidget::show_layers( bool show )
{
	if( show ) 
	{
		if( this->private_->ui_.tools_and_layers_widget_->isHidden() )
		{
			if( this->private_->ui_.fake_widget_->isHidden() )
			{
				this->private_->ui_.fake_widget_->setMinimumHeight( 0 );
				this->private_->ui_.fake_widget_->setFixedHeight( 0 );
				this->private_->ui_.fake_widget_->show();
			}
			
			QPropertyAnimation *animation = new QPropertyAnimation( 
				this->private_->ui_.fake_widget_, "minimumHeight" );
 			animation->setDuration( 500 );
 			animation->setEndValue( this->private_->group_height );
			animation->setEasingCurve( QEasingCurve::OutQuad );
			connect( animation, SIGNAL( finished() ), this, SLOT( show_group() ) );
 			animation->start();
		}
	}
	else
	{
		this->private_->group_height = this->private_->ui_.tools_and_layers_widget_->height();
		this->private_->ui_.tools_and_layers_widget_->hide();
		this->private_->ui_.fake_widget_->setMinimumHeight( 0 );
	}
}
	
void LayerGroupWidget::show_group()
{
	this->private_->ui_.fake_widget_->hide();
	this->private_->ui_.tools_and_layers_widget_->show();
}

void LayerGroupWidget::hide_group()
{
	this->private_->ui_.fake_widget_->hide();
}
	

void LayerGroupWidget::show_resample( bool show )
{
	if( show ) 
	{
		this->private_->ui_.resample_->show();
		
		this->private_->ui_.roi_->hide();
		this->private_->ui_.group_crop_button_->setChecked( false );
		
		this->private_->ui_.delete_->hide();
		this->private_->ui_.group_delete_button_->setChecked( false );
		
		this->private_->ui_.flip_rotate_->hide();
		this->private_->ui_.group_flip_rotate_button_->setChecked( false );
		
		this->private_->ui_.transform_->hide();
		this->private_->ui_.group_transform_button_->setChecked( false );
	}
	else
	{
		this->private_->ui_.resample_->hide();
		this->private_->ui_.group_resample_button_->setChecked( false );
	}
	show_selection_checkboxes( show );
	this->parentWidget()->resize( this->parentWidget()->width(), this->parentWidget()->height() );
	this->repaint();
}

void LayerGroupWidget::show_transform( bool show )
{
	if(show) 
	{
		this->private_->ui_.transform_->show();
		
		this->private_->ui_.roi_->hide();
		this->private_->ui_.group_crop_button_->setChecked( false );
		
		this->private_->ui_.delete_->hide();
		this->private_->ui_.group_delete_button_->setChecked( false );
		
		this->private_->ui_.flip_rotate_->hide();
		this->private_->ui_.group_flip_rotate_button_->setChecked( false );
		
		this->private_->ui_.resample_->hide();
		this->private_->ui_.group_resample_button_->setChecked( false );
	}
	else
	{
		this->private_->ui_.transform_->hide();
		this->private_->ui_.group_transform_button_->setChecked( false );
	}
	show_selection_checkboxes( show );
	this->repaint();
}

void LayerGroupWidget::show_crop( bool show )
{
	if(show) 
	{
		this->private_->ui_.roi_->show();
		
		this->private_->ui_.transform_->hide();
		this->private_->ui_.group_transform_button_->setChecked( false );
		
		this->private_->ui_.delete_->hide();
		this->private_->ui_.group_delete_button_->setChecked( false );
		
		this->private_->ui_.flip_rotate_->hide();
		this->private_->ui_.group_flip_rotate_button_->setChecked( false );
		
		this->private_->ui_.resample_->hide();
		this->private_->ui_.group_resample_button_->setChecked( false );
	}
	else
	{
		this->private_->ui_.roi_->hide();
		this->private_->ui_.group_crop_button_->setChecked( false );
	}
	show_selection_checkboxes( show );
	this->repaint();
}

void LayerGroupWidget::show_flip_rotate( bool show )
{
	if(show) 
	{
		this->private_->ui_.flip_rotate_->show();
		
		this->private_->ui_.transform_->hide();
		this->private_->ui_.group_transform_button_->setChecked( false );
		
		this->private_->ui_.delete_->hide();
		this->private_->ui_.group_delete_button_->setChecked( false );
		
		this->private_->ui_.roi_->hide();
		this->private_->ui_.group_crop_button_->setChecked( false );
		
		this->private_->ui_.resample_->hide();
		this->private_->ui_.group_resample_button_->setChecked( false );
	}
	else
	{
		this->private_->ui_.group_flip_rotate_button_->setChecked( false );
		this->private_->ui_.flip_rotate_->hide();
	}
	show_selection_checkboxes( show );
	this->repaint();
}

void LayerGroupWidget::show_delete( bool show )
{
	if(show) 
	{
		this->private_->ui_.delete_->show();
		
		this->private_->ui_.transform_->hide();
		this->private_->ui_.group_transform_button_->setChecked( false );
		
		this->private_->ui_.flip_rotate_->hide();
		this->private_->ui_.group_flip_rotate_button_->setChecked( false );
		
		this->private_->ui_.roi_->hide();
		this->private_->ui_.group_crop_button_->setChecked( false );
		
		this->private_->ui_.resample_->hide();
		this->private_->ui_.group_resample_button_->setChecked( false );
	}
	else
	{
		this->private_->ui_.delete_->hide();
		this->private_->ui_.group_delete_button_->setChecked( false );
	}
	show_selection_checkboxes( show );
	this->repaint();
}
	
void LayerGroupWidget::resizeEvent( QResizeEvent *event )
{
	this->private_->overlay_->resize( event->size() );
	event->accept();
}
	
void LayerGroupWidget::notify_layer_manager_widget( bool move_time )
{
	Q_EMIT prep_layers_for_drag_and_drop_signal_( move_time );
}

void LayerGroupWidget::prep_layers_for_drag_and_drop( bool move_time )
{
	for( int i = 0; i < this->layer_list_.size(); ++i)
	{
		this->layer_list_[i]->prep_for_animation( move_time );
	}
}

void LayerGroupWidget::prep_for_animation( bool move_time )
{
	if( this->picked_up_ )
		return;
	
	if( move_time )
	{
		this->private_->ui_.group_dummy_->setMinimumHeight( this->private_->ui_.base_->height() );
		this->private_->ui_.group_dummy_->setMinimumWidth( this->private_->ui_.base_->width() );
		this->private_->ui_.group_dummy_->setPixmap( QPixmap::grabWidget( this->private_->ui_.base_ ) );
		this->private_->ui_.base_->hide();
		this->private_->ui_.group_dummy_->show();
	}
	else
	{
		this->private_->ui_.group_dummy_->hide();
		this->private_->ui_.base_->show();
	}
}
	
void LayerGroupWidget::set_picked_up_group_size( int group_height )
{
	this->picked_up_group_height_ = group_height;
}
	
}  //end namespace Seg3D