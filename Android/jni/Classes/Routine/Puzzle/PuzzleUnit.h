//! @file 		PuzzleUnit.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "../Unit.h"
#include "Stage.h"
#include "BlockContainer.h"
#include "NextBlockContainer.h"
#include "BlockSet.h"
#include "Classes/Math/Vector2.h"
#include "Classes/Routine/UI/UI_GameMain.h"

namespace Puzzle {
	class Block;
	class Result;
	class AdditionalTimeDrawer;

class PuzzleUnit : public Unit
{
public:
	static void onDecideScreenRatio(int ratio);

public:
	enum State{
		STATE_NORMAL,			 ///<通常
		STATE_WAIT_NEXT_POP,     ///<次のポップ待ち(回転はここでのみ受付)
		STATE_DEVICE_ROTATE_END, ///<本体回転した後
		STATE_RESULT_IDLE,		 ///<結果表示までアイドル中
		STATE_RESULT,			 ///<結果表示
		STATE_GAME_OVER_IDLE,	 ///<ゲームオーバーアイドル中
		STATE_GAME_OVER,		 ///<ゲームオーバー 
		STATE_PAUSE,			 ///<ポーズ
	};
	
	enum Flag {
		FLAG_RETURN_TO_TITLE = 0x01 << 0,
		FLAG_RETRY			 = 0x01 << 1,
		FLAG_PUSH_NEXT_BLOCK = 0x01 << 2,
		FLAG_BLOCK_MOVING    = 0x01 << 3,  ///<ブロックが消えてエフェクト中
        FLAG_NO_TIMELIMIT    = 0x01 << 4,
	};

public:
	explicit PuzzleUnit(bool isTimeLimit);
	virtual ~PuzzleUnit();

	virtual void calc();
	virtual void draw();

	virtual void touchedBegin(CGPoint tp);
	virtual void touchedMoved(CGPoint tp);
	virtual void touchedEnded(CGPoint tp);

	//! UI取得
	UserInterface::UI_GameMain* getUI() { return &ui_; }
	//! 本体が回転した瞬間に通知 @TODO
	void notifyRotateDevice() {}
	//! 本体の向きを適用 @TODO
	bool applyDeviceOrientation() { return false; }
	//! ゲームオーバー？
	bool isGameOver() const { return getState() == STATE_GAME_OVER; }

public:
	static NextBlockContainer* getNextBlockContainer() { return &(instance_->nextBlockContainer_); }
	static void setDeviceAngle( int angle ) { instance_->deviceAngle_ = angle; }
	//! @brief  デバイスの向き取得(int)
	static int getDeviceAngle() { return instance_->deviceAngle_; }
	//! @brief  スコア加算
	static void addScore( int value, const Math::Vector2 &pos = Math::Vector2(0, 0) );
	//! @biref  タイム追加.timeLimit_が最大
	static void addTimeByGroupNum( int nbGroup );
	//! @brief  状態遷移
	static void setState( State state );
	//! @brief  状態取得
	static State getState() { return instance_->state_; }
	//! @brief  待ち時間リセット
	static void resetWaitNextPopTime() { instance_->waitNextPopTime_ = 0.0f; }
	//! @brief  ステージ取得
	static Stage& getStage() { return instance_->stage_; }
	//! @brief  連鎖add
	static void addChain( int val = 1 ) { instance_->chainCount_ += val; }
	//! @brief  ピンチかどうか
	static bool isDanger() { return false; }
	//! @biref  ピンチの度合いを返す。[0,7]で7がピンチ最大
	static int getPinchLevel();
	
	//! @brief  フラグ
	static bool testFlag( Flag f ) { return f & instance_->flag_; }
	static void setFlag( Flag f ) { instance_->flag_ |= f; }
	static void resetFlag( Flag f ) { instance_->flag_ = instance_->flag_ & ~f; }
	
	//@TODO 
//#ifdef DEBUG
	//! @brief  デバッグ用タイムリミット設定
	static void setTimeLimit( int time ) { instance_->timeLimit_ = (float)time; }
	static int getTimeLimit();
	//! @brief  デバッグ用スコア設定
	static void setScore( int score ) { instance_->score_ = score; }
	static int getScore();
//#endif

private:
	UIDeviceOrientation getDeviceOrientationByAngle( int angle );
	void calcTime( float dt );
	//! @brief  時間延長
	void addTimeLimit( float time ) { timeLimit_ += time; }
	//! @brief  連鎖効果適用
	void addChainEffect();
	//! @brief	PopEffectのための関数
	void popNeighborBlock( Block *b, Block *p );
	//! @brief  できたグループの数に応じてタイム加算
	void addTimeByGroupNum_( int nbGroup );
	//! @brief  ブロックが動いてる時間カウント
	void resetBlockMovingTime_() { blockMovingTime_ = 0; }
	void updateBlockMovingTime_( float dt );
	
	//! @brief  プレイ中?
	bool isPlaying() const;
	
	//! @brief  ヒント設定
	void setHint();
    
    //! @brief  現在のモードのハイスコア
    int getCurrentHighScore() const;

private:
	void calc_();
	
private:
	UserInterface::UI_GameMain 	ui_;
	Stage 		stage_;
	BlockContainer 	blockContainer_;
	BlockSet 	fallBlocks_;
	Block*		blockBackup_[2];
	NextBlockContainer	nextBlockContainer_;
	Result* result_;
	AdditionalTimeDrawer*	addTimeDrawer_;

	int   score_;
	float time_; ///<@brief 経過時間
	float timeLimit_;
	
	State state_;     ///<state
	State preState_; ///<一時保存用(pause中など)
	
	CGPoint beginTp_;
	CGPoint currentTp_;
	int maxTpx_; ///<@brief 一度のタッチの間の最大x
	int minTpx_; ///<@brief 一度のタッチの間の最小x
	int maxTpy_;
	int minTpy_;
	
	int deviceAngle_; ///<デバイスの向き
	
	float waitNextPopTime_; ///<回転
	float waitGameOverTime_; ///<ゲームオーバーアイドル時間
	float blockMovingTime_;  ///<blockが動いてるの待ち時間
	
	int chainCount_;
	
	unsigned int flag_;

private:
	static PuzzleUnit* instance_;
};

}