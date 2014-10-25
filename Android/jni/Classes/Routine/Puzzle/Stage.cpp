//! @file 		Stage.cpp
//! @author 	Keita Tanji
//! @breif		

#include "Stage.h"
#include "pch.h"
#include "Classes/Graphics/2D/Draw.h"
#include "Block.h"
#include "PuzzleUnit.h"

namespace Puzzle {

/*static*/ int Stage::LINE_WIDTH = 0;
/*static*/ int Stage::WIDTH = 0;
/*static*/ int Stage::HEIGHT = 0;

/*static*/ void Stage::onDecideScreenRatio(int ratio)
{
	LINE_WIDTH = 8 * ratio;
	WIDTH = 280 * ratio;
	HEIGHT = 280 * ratio;
}

Stage::Stage()
: angle_( 0.0f )
{
	setOffsetByAngle(0);
}
	
void Stage::draw()
{
	Draw* renderer = Draw::singleton();
	//下地
	renderer->drawBox(offsetX_ - LINE_WIDTH, 
		offsetY_, 
		WIDTH + LINE_WIDTH*2, 
		HEIGHT + LINE_WIDTH);
	renderer->setColor(0, 40, 0, 255);
	//ステージ
	renderer->drawBox(offsetX_, offsetY_, WIDTH, HEIGHT);
	renderer->setColor(255, 255, 255, 255);
}

	
void Stage::setOffsetByAngle( int angle )
{
	angle_ = angle;
	if( angle_ == 90 || angle_ == 270 ){
		offsetX_ = (80 * Screen::RATIO) + LINE_WIDTH;
		offsetY_ = 0;
	}
	else {
		offsetX_ = LINE_WIDTH;
		offsetY_ = (80 * Screen::RATIO);
	}
}
	
/*static*/ int Stage::getColumnNumber( float x )
{
	return (int)(x + Block::WIDTH/2) / Block::WIDTH;
}

}//namespace
