//! @file 		PuzzleUnit.cpp
//! @author 	Keita Tanji
//! @breif		
#include "PuzzleUnit.h"
#include "Parameter.h"
#include "Block.h"
#include "Result.h"
#include "AdditionalTimeDrawer.h"
#include "Classes/Routine/Base/FrameTime.h"
#include "Classes/Routine/SaveData/SaveData.h"
#include "Classes/Graphics/2D/Draw.h"
#include "Classes/Graphics/2D/Text.h"
#include "Classes/Graphics/2D/Sprite.h"
#include "Classes/Math/Functions.h"

namespace Puzzle
{
/*static*/ PuzzleUnit* PuzzleUnit::instance_  = NULL;

//=============================================================================
/*static*/ void PuzzleUnit::onDecideScreenRatio(int ratio)
{
	Parameter::onDecideScreenRatio(ratio);
	Stage::onDecideScreenRatio(ratio);
	Block::onDecideScreenRatio(ratio);	//Stageより後にする
}

//=============================================================================
PuzzleUnit::PuzzleUnit(bool isTimeLimit)
	: ui_()
	, stage_()
	, blockContainer_()
	, fallBlocks_()
	, nextBlockContainer_()
	, result_(NULL)
	, addTimeDrawer_() 
	, score_(0)
	, time_(0)
	, timeLimit_(0)
	, state_(STATE_NORMAL)
	, preState_(STATE_NORMAL)
	, beginTp_()
	, currentTp_()
	, maxTpx_(0)
	, minTpx_(0)
	, maxTpy_(0)
	, minTpy_(0)
	, deviceAngle_(0)
	, waitNextPopTime_(0)
	, waitGameOverTime_(0)
	, blockMovingTime_(0)	
	, chainCount_(0)
	, flag_(0)
{
	assert( instance_ == NULL );
	instance_ = this;
	if( !isTimeLimit ){
		setFlag(FLAG_NO_TIMELIMIT);
	}

	Math::initRand();
	ui_.init();
	ui_.setBestScore( getCurrentHighScore() );
	Block::uiGameMain = &ui_;
	blockBackup_[0] = blockBackup_[1] = NULL;
	
	// 暫定Textで
	//@TODO
	// NSString* timeStr = [NSString stringWithFormat:@"Time  %d", timeLimit_];
	// timeText_ = [[Text alloc] initWithString:timeStr Size:TIME_TEXT_SIZE Alignment:UITextAlignmentLeft];

	//@TODO
	// SaveData* save = SaveData::getInstance();
	// if( save->isFirstTime() ){
	// 	save->setIsFirstTime( false );
	// 	save->save();
	// }

	//@TODO    
    //広告表示
 //    MgameAppDelegate *appDelegate = (MgameAppDelegate *)[[UIApplication sharedApplication] delegate];
	// MgameViewController* vc = appDelegate.viewController;
 //    [vc setVisibleBanner:YES];
}

//=============================================================================
PuzzleUnit::~PuzzleUnit()
{
	//@TODO

    //時間制限なしの場合は終了時にハイスコア記録
    // if( testFlag(FLAG_NO_TIMELIMIT) ){
    //     SaveData::SaveData* save = SaveData::SaveData::getInstance();
    //     if( save && score_ > save->getHighScoreWithoutTimeLimit() ){
    //         save->setHighScoreWithoutTimeLimit(score_);
    //         save->save();
    //     }
    // }
    
	// デバイス向きを戻す
	// MgameAppDelegate *appDelegate = (MgameAppDelegate *)[[UIApplication sharedApplication] delegate];
	// MgameViewController* vc = appDelegate.viewController;
	// UIDeviceOrientation preOrientation = getDeviceOrientationByAngle( getDeviceAngle() );
	// [vc rotate_preOrientation:preOrientation curOrientation:UIDeviceOrientationPortrait];

 //    [vc setVisibleBanner:NO];

	// [timeText_ release];
	
	if( result_ ){
		delete result_;
		ui_.setPrize( NULL );
		result_ = NULL;
	}
	
	if( addTimeDrawer_ ){
		delete addTimeDrawer_;
		addTimeDrawer_ = NULL;
	}
	
	instance_ = NULL;
	ui_.term();
}
//=============================================================================
void PuzzleUnit::calc()
{
	//オリジナルのPuzzleUnitとCPuzzleUnitのつなぎ吸収用に一個ラップ
	calc_();
}
//-----------------------------------------------------------------------------
void PuzzleUnit::calc_()
{
	Base::FrameTime* frameTime = Base::FrameTime::getSystemFrameTime();
	float dt = 1e-6f * frameTime->getDeltaTime();
	
	//NSLog( @"dt = %f\n", dt ); 
	
	// calc for UI
	ui_.setLimitTime(timeLimit_);
	ui_.setTime(timeLimit_ - time_);
	ui_.setScore(score_);
	ui_.calc();

	if(score_ > getCurrentHighScore()) {
        ui_.setBestScore(score_);
        if (!ui_.isNewRecord()) ui_.setNewRecord(true);
    }
	// 
	if( addTimeDrawer_ ){
		addTimeDrawer_->calc( dt );
		if( addTimeDrawer_->isDrawEnd() ){
			delete addTimeDrawer_;
			addTimeDrawer_ = NULL;
		}
	}
	
	// 状態遷移
	switch( state_ ){
		case STATE_NORMAL:
			// 全ブロック固定されたらグループ作成
			if( fallBlocks_.isEmpty() && !blockContainer_.isExistFreeBlock() ){
				for (int i=0;i<2;i++)
					if (blockBackup_[i]) { 
						blockBackup_[i]->getUI()->popEffectOn();
						popNeighborBlock(blockBackup_[i], 0);
						blockBackup_[i] = 0;
					}
				if( blockContainer_.makeGroup() ){///<消えた
					setFlag(FLAG_BLOCK_MOVING);
					resetBlockMovingTime_();
				}
				else{///<もう消えない
					setState( STATE_WAIT_NEXT_POP );
					resetWaitNextPopTime();
				}

				// グループ作っても詰まってたらゲームオーバー
				if( blockContainer_.isOverFlowed() ){
					setState( STATE_GAME_OVER_IDLE );
				}
			}
			
			if( testFlag(FLAG_BLOCK_MOVING) ){
				updateBlockMovingTime_(dt);
			}
			break;
		case STATE_WAIT_NEXT_POP:
            if( timeLimit_ - static_cast<int>(time_) <= 0 ){
				setState( STATE_RESULT_IDLE );
				result_ = new Result( score_ );
				
				SaveData* save = SaveData::getInstance();
				if( score_ > save->getHighScore() ){
					save->setHighScore( score_ );
                    ui_.setHighScoreInDialog(true);
					save->save();
				}
			}

			waitNextPopTime_ += dt;
			
			//移動エフェクト終わってたら回転OK
			if( testFlag(FLAG_BLOCK_MOVING) ){
				updateBlockMovingTime_(dt);
			}
			else {
				if( applyDeviceOrientation() ){
					setState( STATE_DEVICE_ROTATE_END );
				}
				else {
					if( waitNextPopTime_ > WAIT_NEXT_POP_TIME ){
						setState( STATE_NORMAL );
						setFlag( FLAG_PUSH_NEXT_BLOCK );
						resetWaitNextPopTime();
					}
				}
			}
			break;
		case STATE_DEVICE_ROTATE_END:
			//@memo 回転後のコインポップにも待ち時間入れる？
			
			if( !blockContainer_.isExistFreeBlock() ){
				if( blockContainer_.makeGroup() ){///<消えた
					setFlag(FLAG_BLOCK_MOVING);
					resetBlockMovingTime_();
				}
				else {///<もう消えない
					if( !testFlag(FLAG_BLOCK_MOVING) ){
						setState( STATE_NORMAL );
						setFlag(FLAG_PUSH_NEXT_BLOCK);
					}
				}
			}
			// blockが消えてエフェクトで動いてる
			if( testFlag(FLAG_BLOCK_MOVING) ){
				updateBlockMovingTime_(dt);
			}
			break;
		case STATE_RESULT_IDLE:
			waitGameOverTime_ += dt;
			if( waitGameOverTime_ > WAIT_GAME_OVER_TIME ){
				setState( STATE_RESULT );
				setHint();
				ui_.setPrize( result_->getSprite() );
				ui_.showResultDialog();
				waitGameOverTime_ = 0.0f;
			}
			break;
		case STATE_RESULT:
			// resultからgameoverへ
			if( result_ ){
				setState(STATE_PAUSE);
			}
			break;
		case STATE_GAME_OVER_IDLE:
			waitGameOverTime_ += dt;
			if( waitGameOverTime_ > WAIT_GAME_OVER_TIME ){
				setState( STATE_GAME_OVER );
				setHint();
				ui_.showGameOverDialog();
				waitGameOverTime_ = 0.0f;
			}
			break;
		case STATE_GAME_OVER:
			setState( STATE_PAUSE );
			break;
		default:
			break;			
	}

	// ゲームの更新処理を省略する
	if( !isPlaying() ){
		return;
	}
    if( !testFlag(FLAG_NO_TIMELIMIT) 
#ifdef DEBUG	
	&& ![[DebugMenu getInstance] testOption:DEBUG_FLAG_IGNORE_TIME]
#endif
	){
		if( !fallBlocks_.isEmpty() ){
			calcTime( dt );
		}
	}
    
	if( nextBlockContainer_.getSize() < 12 ){
		Block* base = NULL;
		Block* sub = NULL;
		BlockSet::createRandom( &base, &sub );
		nextBlockContainer_.pushBlock( base );
		nextBlockContainer_.pushBlock( sub );
	}

	nextBlockContainer_.calc();

	// 落ちブロックの設定
	if( testFlag(FLAG_PUSH_NEXT_BLOCK) && getState() == STATE_NORMAL ){
		if( nextBlockContainer_.isReady() ){
			nextBlockContainer_.pop( &fallBlocks_ );
			blockBackup_[0] = fallBlocks_.getBlock(0);
			blockBackup_[1] = fallBlocks_.getBlock(1);
			fallBlocks_.beginFall();
			resetFlag(FLAG_PUSH_NEXT_BLOCK);
			addChainEffect();
		}
	}
	if( fallBlocks_.isLocked() ){
		fallBlocks_.setEmpty();
	}
	if( !fallBlocks_.isEmpty() ){
		fallBlocks_.calc( dt );
	}

	// 固定ブロックの更新
	blockContainer_.calc(dt);
}
//=============================================================================
void PuzzleUnit::draw()
{
	//stage_.draw();

	ui_.draw(testFlag(FLAG_NO_TIMELIMIT));
	
	if( addTimeDrawer_ ){
		addTimeDrawer_->draw();
	}
}
//=============================================================================
void PuzzleUnit::touchedBegin(CGPoint tp)
{
	beginTp_ = tp;
	currentTp_ = tp;
	maxTpx_ = minTpx_ = tp.x;
	maxTpy_ = minTpy_ = tp.y;

	// pause
	if( getState() == STATE_NORMAL || getState() == STATE_WAIT_NEXT_POP ){
		if( ui_.isPauseTouched( tp ) ){
			//ui_.touchBeginPause();
		}
	}
}
//=============================================================================
void PuzzleUnit::touchedMoved(CGPoint tp)
{
	if( getState() == STATE_NORMAL || getState() == STATE_WAIT_NEXT_POP ){
		//block移動
		int moveX = 0;
		if( tp.x - currentTp_.x > TOUCHX_PER_MOVE ){
			moveX = Block::WIDTH;
			currentTp_.x = tp.x;
		}
		else if( tp.x - currentTp_.x < -TOUCHX_PER_MOVE ){
			moveX = -Block::WIDTH;
			currentTp_.x = tp.x;
		}
		
		if( !fallBlocks_.isEmpty() && moveX != 0 ){
			fallBlocks_.move( (float)moveX, 0.0f );
		}
		
		// y方向
		int difY = tp.y - currentTp_.y;
		if( !fallBlocks_.isEmpty() && difY > TOUCHY_PER_MOVE ){
			fallBlocks_.setSpeed( BLOCK_ACCELATED_SPEED );
			currentTp_.y = tp.y;
		}
	}

	if( tp.x > maxTpx_ ) { maxTpx_ = tp.x; }
	if( tp.x < minTpx_ ) { minTpx_ = tp.x; }
	
	if( tp.y > maxTpy_ ) { maxTpy_ = tp.y; }
	if( tp.y < minTpy_ ) { minTpy_ = tp.y; }
}
//=============================================================================
void PuzzleUnit::touchedEnded(CGPoint tp)
{
	// pause
	if( getState() == STATE_NORMAL || getState() == STATE_WAIT_NEXT_POP ){
		if( ui_.isPauseTouched( tp ) ){
			setState( STATE_PAUSE );
			ui_.showPauseDialog();
			setHint();
			return;
		}
		
		// block
		if( !fallBlocks_.isEmpty() ){
			if( maxTpx_ - minTpx_ < 20  && 
			   maxTpy_ - minTpy_ < 20 ){
				fallBlocks_.rotate( BlockSet::X );
			}
			
			float preSpeed = fallBlocks_.canControl() ? Block::FALL_SPEED : Block::FIXED_FALL_SPEED;
			fallBlocks_.setSpeed( preSpeed );
		}
	}
	
	// pause中
	if( getState() == STATE_PAUSE ){
		if( ui_.isEndPauseTouched( tp ) ){
			setState( preState_ );
			ui_.hideDialog();
		}
		else if( ui_.isRetryTouched( tp ) ){
			setFlag( FLAG_RETRY );
		}
		else if( ui_.isReturnToTitleTouched( tp ) ){
			setFlag( FLAG_RETURN_TO_TITLE );
		}
	}
}
//=============================================================================
/*static*/ void PuzzleUnit::setState(State state)
{ 
	instance_->preState_ = instance_->state_;
	instance_->state_ = state;
	
	switch (state) {
		case STATE_RESULT_IDLE:
			for(int y=0;y<9;y++) {
				for(int x=0;x<9;x++) {
					Block *b = BlockContainer::get(y, x);
					if (b) {
						b->getUI()->setState(UserInterface::UI_GameMain::Coin::STATE_CLEAR);
						b->getUI()->setWaitFrame(y*3);
					}
				}
			}
			if( !instance_->fallBlocks_.isEmpty() ){
				for( int i = 0; i < 2; ++i ){
					Block *b = instance_->fallBlocks_.getBlock(i);
					if (b) {
						b->getUI()->setState(UserInterface::UI_GameMain::Coin::STATE_CLEAR);
						int row = b->getRowNumber();
						b->getUI()->setWaitFrame(row*3);
					}
				}
			}
			break;
		case STATE_GAME_OVER_IDLE:
			for(int y=0;y<9;y++) {
				for(int x=0;x<9;x++) {
					Block *b = BlockContainer::get(y, x);
					if (b) {
						b->getUI()->setState(UserInterface::UI_GameMain::Coin::STATE_OVER_FALL);
						b->getUI()->setWaitFrame(y*3);
					}
				}
			}
			break;
        default:
            break;
	}
}
//=============================================================================
/*static*/ void PuzzleUnit::addScore( int value, const Math::Vector2 &pos )
{
    int preSpeedLv = instance_->score_ / ADD_SPEED_INTERVAL_SCORE;
	instance_->score_ += value;
    instance_->getUI()->addScorePlus(value, pos);
    //時間無制限時は加速処理
    if( testFlag(FLAG_NO_TIMELIMIT) ){
        int speedLv = instance_->score_ / ADD_SPEED_INTERVAL_SCORE;
        if( speedLv > preSpeedLv ){
            Block::FALL_SPEED = BLOCK_DEFAULT_SPEED + (float)speedLv * ADD_SPEED;
            Block::FIXED_FALL_SPEED = BLOCK_FIXED_FALL_SPEED + (float)speedLv * ADD_SPEED;
        }
    }
}
//=============================================================================
/*static*/ void PuzzleUnit::addTimeByGroupNum( int nbGroup )
{
	instance_->addTimeByGroupNum_( nbGroup );
}
//=============================================================================
void PuzzleUnit::addTimeByGroupNum_( int nbGroup )
{
	int timePlus = 0;

	if( chainCount_ == 0 ){
		timePlus = ADD_TIME * nbGroup;
	}
	else {
		timePlus = ADD_TIME_WITH_CHAIN * nbGroup;
	}

	if (!testFlag(FLAG_NO_TIMELIMIT)) {
		ui_.addTimePlus(timePlus);
	}
	
	time_ -= timePlus;

	if( time_ < 0 ){
		time_ = 0;
	}

	//NSLog( @"time = %f, timeLimit = %f\n", time_, timeLimit_ );
}
//=============================================================================
/*static*/ int PuzzleUnit::getPinchLevel()
{
	int nbRow3 = instance_->blockContainer_.getSize( 3 );
	int nbRow4 = instance_->blockContainer_.getSize( 4 );
	return ( nbRow3 > nbRow4 ) ? nbRow3 : nbRow4; 
}
//=============================================================================
/*static*/ int PuzzleUnit::getTimeLimit() 
{ 
	return instance_ ? (int)(instance_->timeLimit_) : TIME_LIMIT; 
}
//=============================================================================
/*static*/ int PuzzleUnit::getScore()
{
	return instance_ ? instance_->score_ : 0;
}
//=============================================================================
UIDeviceOrientation PuzzleUnit::getDeviceOrientationByAngle( int angle )
{
	switch( angle ){
		case 0:
			return UIDeviceOrientationPortrait; break;
		case 90:
			return UIDeviceOrientationLandscapeLeft; break;
		case 180:
			return UIDeviceOrientationPortraitUpsideDown; break;
		case 270:
			return UIDeviceOrientationLandscapeRight; break;
		default:
			assert( !"invalid angle used" );break;
	}
	return UIDeviceOrientationUnknown;
}
//=============================================================================
void PuzzleUnit::calcTime( float dt )
{
	// とりあえずdeltatimeで経過時間計算。（誤差がでるかも）
	//int preTime = static_cast<int>(time_);
	time_ += dt;
	if( time_ > timeLimit_ ){
		time_ = timeLimit_;
	}
	//int curTime = static_cast<int>(time_);
}
//=============================================================================
void PuzzleUnit::addChainEffect()
{
	// 最終的な連鎖の数で何か与えるのは今のところない
	
	chainCount_ = 0;
}
//=============================================================================
void PuzzleUnit::updateBlockMovingTime_( float dt )
{
	blockMovingTime_ += dt;
	if( blockMovingTime_ > BLOCK_MOVING_TIME ){
		resetBlockMovingTime_();
		resetFlag(FLAG_BLOCK_MOVING);
	}
}
//=============================================================================
void PuzzleUnit::popNeighborBlock( Block *b, Block *p )
{
	if (!b || b == p || (p && p->getValue() != b->getValue())) return;
	if (p && p->getValue() == b->getValue()) {
		b->getUI()->popEffectOn();
	}
	Block *neighbor[] = {
		blockContainer_.get(b->getRowNumber()+1, b->getColumnNumber()),
		blockContainer_.get(b->getRowNumber()-1, b->getColumnNumber()),
		blockContainer_.get(b->getRowNumber(),   b->getColumnNumber()+1),
		blockContainer_.get(b->getRowNumber(),   b->getColumnNumber()-1),
	};
	for (int i=0;i<4;i++)
		if (neighbor[i] && neighbor[i] != p && !neighbor[i]->getUI()->isPopEffectOn() && b->getValue() == neighbor[i]->getValue()) 
			popNeighborBlock(neighbor[i], b);
}
//=============================================================================
bool PuzzleUnit::isPlaying() const
{
	if(getState() == STATE_PAUSE || 
		getState() == STATE_GAME_OVER || 
		getState() == STATE_GAME_OVER_IDLE ||
		getState() == STATE_RESULT_IDLE ||
		getState() == STATE_RESULT ){
		return false;
	}
	return true;
}
//=============================================================================
void PuzzleUnit::setHint()
{
	//@TODO
// #include "Hint.h"
// 	ui_.setHintText( HINT_TEXTS[currentHint] );
// 	currentHint = ( currentHint + 1 ) % NB_HINT;
}
//=============================================================================
int PuzzleUnit::getCurrentHighScore() const
{
	SaveData* save = SaveData::getInstance();
	if( testFlag(FLAG_NO_TIMELIMIT) ){
		return save->getHighScoreWithoutTimeLimit();
	}
	else {
		return save->getHighScore();
	}
}


}