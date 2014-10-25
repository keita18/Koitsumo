//! @file 		Result.cpp
//! @author 	Keita Tanji
//! @breif		
#include "Result.h"
#include "Classes/Graphics/2D/Sprite.h"
#include "PuzzleUnit.h"
#include "Classes/Math/Functions.h"

namespace Puzzle {

	//name と sizeを追加
	const char* resnames[] = {
		"prize_1yen.png",
		"prize_5yen.png",
		"prize_10yen.png",
		"prize_50yen.png",
		"prize_100yen.png",
		"prize_500yen.png",
		"prize_1000yen.png",
		"prize_2000yen.png",
		"prize_5000yen.png",
		"prize_10000yen.png",
	};
	int sizes[][2] = {
		{Result::COIN_WIDTH,Result::COIN_HEIGHT},
		{Result::COIN_WIDTH,Result::COIN_HEIGHT},
		{Result::COIN_WIDTH,Result::COIN_HEIGHT},
		{Result::COIN_WIDTH,Result::COIN_HEIGHT},
		{Result::COIN_WIDTH,Result::COIN_HEIGHT},
		{Result::COIN_WIDTH,Result::COIN_HEIGHT},
		{Result::PAPER_WIDTH,Result::PAPER_HEIGHT},
		{Result::PAPER_WIDTH,Result::PAPER_HEIGHT},
		{Result::PAPER_WIDTH,Result::PAPER_HEIGHT},
		{Result::PAPER_WIDTH,Result::PAPER_HEIGHT},
	};
	
	Result::Result( int score )
		: resultId_( 0 )
		, sprite_( NULL )
		, x_( 0 )
		, y_( 0 )
		, y0_( 0 )
		, yMax_( 0 )
		, v0_( 0 )
		, a_( 0 )
		, t_( 0 )
		, e_( 0.5f )
		, isAnimEnd_( false )
	{
		if( score < 1000 ){
			resultId_ = RESULT_1;
		}
		else if(  1000 <= score && score < 2000 ){
			resultId_ = RESULT_5;
		}
		else if(  2000 <= score && score < 3000 ){
			resultId_ = RESULT_10;
		}
		else if(  3000 <= score && score < 4000 ){
			resultId_ = RESULT_50;
		}
		else if(  4000 <= score && score < 5000 ){
			resultId_ = RESULT_100;
		}
		else if(  5000 <= score && score < 6000 ){
			resultId_ = RESULT_500;
		}
		else if(  6000 <= score && score < 7000 ){
			resultId_ = RESULT_1000;
		}
		else if(  7000 <= score && score < 8000 ){
			resultId_ = RESULT_2000;
		}
		else if(  8000 <= score && score < 9000 ){
			resultId_ = RESULT_5000;
		}
		else if( 9000 <= score ){
			resultId_ = RESULT_10000;
		}
		
		int deviceAngle = PuzzleUnit::getDeviceAngle();
		if( deviceAngle == 90 || deviceAngle == 270 ){
			x_  = 240 - (sizes[resultId_][0] / 2);
			yMax_ = 320 - sizes[resultId_][1];
			y0_ = yMax_ - 600;
			v0_ = 100;
			a_  = 300;
		}
		else {
			x_  = 160 - (sizes[resultId_][0] / 2);
			yMax_ = 400 - sizes[resultId_][1];
			y0_ = yMax_ -600;
			v0_ = 100;
			a_  = 300;
		}
		
		y_ = y0_;
		sprite_ = new Sprite(resnames[resultId_], sizes[resultId_][0], sizes[resultId_][1]);
	}

	Result::~Result()
	{
		SAFE_DELETE(sprite_);
	}

	
	void Result::calc( float dt )
	{
		t_ += dt;
		y_ = y0_ + static_cast<int>(v0_*t_ + a_*t_*t_/2.0f);
		if( y_ > yMax_ ){
			y_ = yMax_;
			
			// 反発運動
			y0_ = y_;
			v0_ = -e_ * ( v0_ + a_*t_ );
			t_ = 0;
			
			if( Math::abs(v0_) <= 25.0f ){
				isAnimEnd_ = true;
			}
		}
	}
	
	void Result::draw()
	{
//		[sprite_ drawWithFrame:0
//							 x:x_
//							 y:y_
//						 width:sizes[resultId_][0]
//						height:sizes[resultId_][1]];
	}
	
}/*namespace Puzzle*/