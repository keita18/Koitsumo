//! @file 		AdditionalTimeDrawer.cpp
//! @author 	Keita Tanji
//! @breif		

#include "AdditionalTimeDrawer.h"
//#import "Text.h"

namespace Puzzle {
	/*static*/ const float AdditionalTimeDrawer::DRAW_TIME = 2.0f;
	
	//@TODO

	AdditionalTimeDrawer::AdditionalTimeDrawer( int time )
	//: text_( nil )
	: x_( 0 )
	, y_( 0 )
	, drawTime_( 0 )
	{
		const int ADD_TIME_TEXT_SIZE = 16;
		// NSString* addTimeStr = [NSString stringWithFormat:@"+%d", time];
		// text_ = [[Text alloc] initWithString:addTimeStr Size:ADD_TIME_TEXT_SIZE Alignment:UITextAlignmentLeft];
	}
	
	void AdditionalTimeDrawer::calc( float delta )
	{
		drawTime_ += delta;
		x_ = 100;
		y_ = 60 - 20*(drawTime_/DRAW_TIME);
	}
	
	void AdditionalTimeDrawer::draw()
	{
		// [text_ draw_x:x_ y:y_ ];
	}
	
}/*namespace Puzzle*/
