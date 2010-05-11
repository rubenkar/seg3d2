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

#include <Core/Volume/MaskVolume.h>
#include <Core/DataBlock/MaskDataBlockManager.h>

namespace Core
{

MaskVolume::MaskVolume( const GridTransform& grid_transform, 
					   const MaskDataBlockHandle& mask_data_block ) :
	Volume( grid_transform ),
	mask_data_block_( mask_data_block )
{
}

MaskVolume::MaskVolume( const GridTransform& grid_transform ) :
	Volume( grid_transform )
{
    MaskDataBlockManager::Instance()->create( get_nx(), get_ny(), get_nz(), mask_data_block_ );
}

VolumeType MaskVolume::get_type() const
{
	return VolumeType::MASK_E;
}

MaskDataBlockHandle MaskVolume::mask_data_block() const
{
	return this->mask_data_block_;
}

} // end namespace Core