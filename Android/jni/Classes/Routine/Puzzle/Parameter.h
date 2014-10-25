//! @file 		Parameter.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#ifndef ROUTINE_PUZZLE_PARAMETER_H
#define ROUTINE_PUZZLE_PARAMETER_H

namespace Puzzle {

/*const*/ static int TOUCHX_PER_MOVE = 30;  ///< ブロックを1マス動かすタッチ幅
/*const*/ static int TOUCHY_PER_MOVE = 40;  ///< ブロック落下を早めるためのy方向タッチ量
/*const*/ static float BLOCK_DEFAULT_SPEED = 40.0f;		 ///< ブロック落下スピード
/*const*/ static float BLOCK_ACCELATED_SPEED = 400.0f;   ///< 下入力加速落下スピード 
/*const*/ static float BLOCK_FIXED_FALL_SPEED = 200.0f;  ///< 固定後に落下するときのスピード
/*const*/ static float ADD_SPEED = 50.0f;   ///<時間無制限でスピードアップする量
const static float WAIT_NEXT_POP_TIME = 1.0f;        ///< 次のブロックがでてくるまでのアイドル時間
const static float WAIT_GAME_OVER_TIME =     2.0f;	 ///< ゲームオーバーアイドル時間
const static int TIME_LIMIT = 60;		   ///<制限時間[sec]
const static int ADD_TIME = 3;	           ///<１回消したときの１つあたりの追加時間[sec]
const static int ADD_TIME_WITH_CHAIN = 10; ///<連鎖したときの１つあたりの追加時間[sec]
const static float BLOCK_MOVING_TIME = 1.0f; ///<ブロックが消えたときに次のブロックを落とすまでアイドルさせる時間
const static int ADD_SPEED_INTERVAL_SCORE = 5000;  ///<時間無制限でスピードアップする間隔の点数
	
/// コイン出現割合
#define DEBUG_COIN_PROB_MODE  0
#if DEBUG_COIN_PROB_MODE
const static int COIN_PROB_1 =   0;
const static int COIN_PROB_5 =   10;
const static int COIN_PROB_10 =  10;
const static int COIN_PROB_50 =  0;
const static int COIN_PROB_100 = 0;
const static int COIN_PROB_500 = 0;
#else
const static int COIN_PROB_1 =   8;
const static int COIN_PROB_5 =   2;
const static int COIN_PROB_10 =  8;
const static int COIN_PROB_50 =  2;
const static int COIN_PROB_100 = 8;
const static int COIN_PROB_500 = 2;
#endif

//ヒントは Hint.h

namespace Parameter
{
	void onDecideScreenRatio(int ratio);
}
	
}/*namespace*/

#endif
