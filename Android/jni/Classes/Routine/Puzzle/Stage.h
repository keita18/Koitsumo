//! @file 		Stage.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

namespace Puzzle {

class Stage 
{
public:
	// enum {
	// 	LINE_WIDTH = 8,
	// 	WIDTH = 280,
	// 	HEIGHT = 280,
	// };	
	//! 画面サイズ対応で動的に設定
	static int LINE_WIDTH;
	static int WIDTH;
	static int HEIGHT;
	static void onDecideScreenRatio(int ratio);
		
public:
	Stage();
	virtual ~Stage() {};
	void draw();
	void setOffsetByAngle( int angle );
	
	static int getColumnNumber( float x );
	
	int getOffsetX() { return offsetX_; }
	int getOffsetY() { return offsetY_; }
	
private:
	int offsetX_;///<スクリーン上のstageの原点
	int offsetY_;///<スクリーン上のstageの原点

private:
	float angle_;
	
};

}/*namespace Puzzle*/
