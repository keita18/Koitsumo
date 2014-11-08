//! @file 		Parameter.cpp
//! @author 	Keita Tanji
//! @breif		

#include "Parameter.h"

namespace Puzzle {

// externグローバル変数の定義	
int TOUCHX_PER_MOVE = 30;  ///< ブロックを1マス動かすタッチ幅
int TOUCHY_PER_MOVE = 40;  ///< ブロック落下を早めるためのy方向タッチ量
float BLOCK_DEFAULT_SPEED = 40.0f;		 ///< ブロック落下スピード
float BLOCK_ACCELATED_SPEED = 400.0f;   ///< 下入力加速落下スピード 
float BLOCK_FIXED_FALL_SPEED = 200.0f;  ///< 固定後に落下するときのスピード
float ADD_SPEED = 50.0f;   ///<時間無制限でスピードアップする量

namespace Parameter
{
	void onDecideScreenRatio(int ratio)
	{
		TOUCHX_PER_MOVE *= ratio;  ///< ブロックを1マス動かすタッチ幅
		TOUCHY_PER_MOVE *= ratio;  ///< ブロック落下を早めるためのy方向タッチ量
		BLOCK_DEFAULT_SPEED *= ratio;		 ///< ブロック落下スピード
		BLOCK_ACCELATED_SPEED *= ratio;   ///< 下入力加速落下スピード 
		BLOCK_FIXED_FALL_SPEED *= ratio;  ///< 固定後に落下するときのスピード
		ADD_SPEED *= ratio;
	}
}
}