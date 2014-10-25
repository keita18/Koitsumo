//! @file 		Parameter.cpp
//! @author 	Keita Tanji
//! @breif		

#include "Parameter.h"

namespace Puzzle {

namespace Parameter
{
	void onDecideScreenRatio(int ratio)
	{
		TOUCHX_PER_MOVE = 30 * ratio;  ///< ブロックを1マス動かすタッチ幅
		TOUCHY_PER_MOVE = 40 * ratio;  ///< ブロック落下を早めるためのy方向タッチ量
		BLOCK_DEFAULT_SPEED = 40.0f * ratio;		 ///< ブロック落下スピード
		BLOCK_ACCELATED_SPEED = 400.0f * ratio;   ///< 下入力加速落下スピード 
		BLOCK_FIXED_FALL_SPEED = 200.0f * ratio;  ///< 固定後に落下するときのスピード
		ADD_SPEED = 50.0f * ratio;
	}
}
}