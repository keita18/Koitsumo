//! @file 		Result.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

class Sprite;

namespace Puzzle {
	
	//! @brief  PuzzleUnitで表示する結果
	class Result
	{
	public:
		enum ResultId{
			RESULT_1,
			RESULT_5,
			RESULT_10,
			RESULT_50,
			RESULT_100,
			RESULT_500,
			RESULT_1000,
			RESULT_2000,
			RESULT_5000,
			RESULT_10000,
			NB_RESULT,
		};
		// 仮の結果画像サイズ
		const static int COIN_WIDTH = 256;
		const static int COIN_HEIGHT = 256;
		const static int PAPER_WIDTH = 256;
		const static int PAPER_HEIGHT = 128;
		
	public:
		Result( int score );
		~Result();
		void calc( float dt );
		void draw();
		
		bool isAnimEnd() const { return isAnimEnd_; }
		
		Sprite* getSprite() { return sprite_; }
		
	private:
		int resultId_;
		Sprite* sprite_;
		int x_;
		int y_;
		int y0_;
		int yMax_;
		float v0_;
		float a_;
		float t_;
		float e_;
		
		bool isAnimEnd_;
		
	};

}/*namespace Puzzle*/
