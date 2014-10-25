//! @file 		AdditionalTimeDrawer.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

namespace Puzzle {

	class AdditionalTimeDrawer
	{
	public:
		AdditionalTimeDrawer( int time );
		void calc( float delta );
		void draw();
		bool isDrawEnd() const { return drawTime_ > DRAW_TIME; } 
	private:
		const static float DRAW_TIME;
		// 仮対応
		//@TODO
		//Text* text_;
		float x_;
		float y_;
		float drawTime_;
	};
}
