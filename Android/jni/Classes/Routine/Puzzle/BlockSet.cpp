//! @file 		BlockSet.cpp
//! @author 	Keita Tanji
//! @breif		


#include "BlockSet.h"
#include "Block.h"
#include "BlockContainer.h"
#include "Stage.h"
#include "PuzzleUnit.h"
#include "Classes/Math/Vector2.h"
#include "Classes/Math/Matrix23.h"
#include "Classes/Math/Functions.h"
#include "pch.h"
#include "Parameter.h"

using Math::Vector2;
using Math::Matrix23;

namespace Puzzle {
	
/*static*/ int BlockSet::PROB_1 = COIN_PROB_1;
/*static*/ int BlockSet::PROB_5 = COIN_PROB_5;
/*static*/ int BlockSet::PROB_10 = COIN_PROB_10;
/*static*/ int BlockSet::PROB_50 = COIN_PROB_50;
/*static*/ int BlockSet::PROB_100 = COIN_PROB_100;
/*static*/ int BlockSet::PROB_500 = COIN_PROB_500;


/*static*/ void BlockSet::createRandom( Block** base, Block** sub )
{
	const int NB_COIN = 2;
	int values[NB_COIN] = { 0 };
	
	int valTables[] = {
		1, 5, 10, 50, 100, 500 };
	
	//確率合計
	int probSum = PROB_1 
				+ PROB_5
				+ PROB_10
				+ PROB_50
				+ PROB_100
				+ PROB_500;
	
	int probMaxs[] = {
		Puzzle::BlockSet::PROB_1,
		PROB_1 + PROB_5,
		PROB_1 + PROB_5 + PROB_10,
		PROB_1 + PROB_5 + PROB_10 + PROB_50,
		PROB_1 + PROB_5 + PROB_10 + PROB_50 + PROB_100,
		PROB_1 + PROB_5 + PROB_10 + PROB_50 + PROB_100 + PROB_500,
	};
	
	int baseRand = Math::getRand( 0, probSum - 1 );
	int probMin = 0;
	// １枚目
	// randがどの範囲の値かで決定
	for( int i = 0; i < sizeof( probMaxs ) / sizeof( probMaxs[0] ); ++i ){
		if( probMin <= baseRand && baseRand < probMaxs[i] ){
			values[0] = valTables[i];
			break;
		}
		probMin = probMaxs[i];
	}
	
	// ２枚目
	bool decided = false;
	while( !decided ){
		int subRand = Math::getRand( 0, probSum - 1 );
		for( int i = 0; i < sizeof( probMaxs ) / sizeof( probMaxs[0] ); ++i ){
			if( probMin <= subRand && subRand < probMaxs[i] ){
				values[1] = valTables[i];
				decided = true;
				break;
			}
			probMin = probMaxs[i];
		}
		// 5系の場合同じコイン禁止
		if( values[0] == 5 || values[0] == 50 || values[0] == 500 ){
			if( values[0] == values[1] ){
				decided = false;
			}
		}
	}
	*base = Block::create(values[0], -1, 3 );
	*sub = Block::create( values[1], -1, 4 );
}

BlockSet::BlockSet()
	: baseBlock_(NULL)
	, subBlock_(NULL)
	, canControl_(true)
{}

BlockSet::~BlockSet()
{
	if( baseBlock_ ){
		delete baseBlock_;
		baseBlock_ = NULL;
	}
	if( subBlock_ ){
		delete subBlock_;
		subBlock_ = NULL;
	}
}
	
void BlockSet::calc( float dt )
{
	//1こで落ちることはなくなったの２個ある場合のみ
	if( baseBlock_ && !baseBlock_->isLocked() && 
	   subBlock_ && !subBlock_->isLocked() ){
		canControl_ = true;
	}
	
	if( baseBlock_ && !baseBlock_->isLocked() && subBlock_ && !subBlock_->isLocked() ){
		//下のものを先に更新
		if( baseBlock_->getPosition().y > subBlock_->getPosition().y ){
			calcBase( dt );
			calcSub( dt );
		}
		else {
			calcSub( dt );
			calcBase( dt );
		}
	}
	else {
		calcBase( dt );
		calcSub( dt );
	}
}

void BlockSet::calcBase( float dt )
{
	if( baseBlock_ && !baseBlock_->isLocked() ){
		baseBlock_->calc( dt );
		if( baseBlock_->isLocked() ){
			baseBlock_ = NULL;
			canControl_ = false;
			if( subBlock_ ){
				subBlock_->setSpeed(Block::FIXED_FALL_SPEED);
			}
		}
	}
}

void BlockSet::calcSub( float dt )
{
	if( subBlock_ && !subBlock_->isLocked() ){
		subBlock_->calc( dt );
		if( subBlock_->isLocked() ){
			subBlock_ = NULL;
			canControl_ = false;
			if( baseBlock_ ){
				baseBlock_->setSpeed(Block::FIXED_FALL_SPEED);
			}
		}
	}
}

void BlockSet::draw()
{
	if( baseBlock_ && !baseBlock_->isLocked() ){
		baseBlock_->draw();
	}
	if( subBlock_ && !subBlock_->isLocked() ){
		subBlock_->draw();
	}
}

bool BlockSet::isLocked() const
{
	return ( baseBlock_ == NULL || baseBlock_->isLocked() ) && 
			( subBlock_ == NULL || subBlock_->isLocked() );
}

Block* BlockSet::getBlock( int index )
{
	if( index == 0 ){
		return baseBlock_;
	}
	else if( index == 1 ){
		return subBlock_;
	}
	else{
		assert( !"illegal index used" );
	}
}

void BlockSet::setBlock( Block* block, int index )
{
	if( index == 0 ){
		baseBlock_ = block;
		baseBlock_->setColumnNumber( 3 );
	}
	else if( index == 1 ){
		subBlock_ = block;
		subBlock_->setColumnNumber( 4 );
	}
	else{
		assert( !"illegal index used" );
	}
}

int BlockSet::getNbBlocks() const
{
	int count = 0;
	if( baseBlock_ != NULL ){
		count++;
	}
	if( subBlock_ != NULL ){
		count++;
	}
	return count;
}

void BlockSet::move( float x, float y )
{
	if( canControl() ){
		Math::Vector2 basePos;
		if( baseBlock_ ){
			basePos = baseBlock_->getPosition();
			basePos += Math::Vector2( x, y );
		}

		if( baseBlock_ && subBlock_ ){
			Math::Vector2 subPos = subBlock_->getPosition();
			subPos += Math::Vector2( x, y );
			
			//誤差考慮
			if( -0.5f <= basePos.x && basePos.x <= static_cast<float>(Block::MAX_X + 0.5f) &&
			   -0.5f <= subPos.x && subPos.x <= static_cast<float>(Block::MAX_X + 0.5f) ){
				int baseColumn = Stage::getColumnNumber( basePos.x );
				int baseNbRow = BlockContainer::getSize( baseColumn );
				int baseMaxY = Stage::HEIGHT - ((baseNbRow + 1) * Block::HEIGHT);
				
				int subColumn = Stage::getColumnNumber( subPos.x );
				int subNbRow = BlockContainer::getSize( subColumn );
				int subMaxY = Stage::HEIGHT - ((subNbRow + 1) * Block::HEIGHT);
				
				if( -Block::WIDTH <= basePos.y && basePos.y <= baseMaxY &&
				   -Block::WIDTH <= subPos.y && subPos.y <= subMaxY ){
					baseBlock_->setPosition(basePos);
					subBlock_->setPosition(subPos);

					//! とりあえず、ベースが発行する
					baseBlock_->ExecuteMoveEffect();
				}
			}
		}
//			else{
//				if( 0 <= basePos.x && basePos.x <= Block::MAX_X ){
//					int baseColumn = Stage::getColumnNumber( basePos.x );
//					int baseNbRow = BlockContainer::getSize( baseColumn );
//					int baseMaxY = Stage::HEIGHT - ((baseNbRow + 1) * Block::HEIGHT);
//					if( -Block::WIDTH <= basePos.y && basePos.y <= baseMaxY ){ 
//						baseBlock_->setPosition(basePos);
//						//! とりあえず、ベースが発行する
//						baseBlock_->ExecuteMoveEffect();
//					}
//				}
//			}
	}
}

void BlockSet::rotate( RotDirect dir )
{
	if( baseBlock_ && subBlock_ && canControl() ){
		switch( dir ){
			case X:
			{
				Vector2 subPos;
				for( int i = 1; i <= 4; ++i ){
					subPos = subBlock_->getPosition();
					Matrix23 mat;
					Vector2 basePos = baseBlock_->getPosition();
					mat.setTranslation( basePos.x, basePos.y );
					mat.rotate( 90 * i );
					mat.translate( -basePos.x, -basePos.y );
					mat.mul( &subPos, subPos );
				
					int subColumn = Stage::getColumnNumber( subPos.x );
					int subNbRow = BlockContainer::getSize( subColumn );
					int subMaxY = Stage::HEIGHT - ((subNbRow + 1) * Block::HEIGHT);
					// 計算誤差を考慮
					if( -Block::WIDTH/2 <= subPos.x && subPos.x <= Block::MAX_X + Block::WIDTH/2 &&
					   -Block::WIDTH/2 <= subPos.y && subPos.y <= subMaxY + Block::WIDTH/2 ){
						break;
					}
				}
				subBlock_->setPosition( subPos );
				break;
			}
			case INV_X:
				break;
		}
		//! とりあえず、ベースが発行する
		baseBlock_->ExecuteRoteteEffect();
	}
}

void BlockSet::setSpeed( float val )
{
	if( baseBlock_ ){
		baseBlock_->setSpeed( val );
	}
	if( subBlock_ ){
		subBlock_->setSpeed( val );
	}
}

void BlockSet::beginFall()
{	
	//角度０の落ち開始位置
	if( baseBlock_ ){
		//baseBlock_->setPosition( x, y );
		baseBlock_->getUI()->setState(UserInterface::UI_GameMain::Coin::STATE_FALL);
	}
	if( subBlock_ ){
		//subBlock_->setPosition( x + Block::WIDTH, y );
		subBlock_->getUI()->setState(UserInterface::UI_GameMain::Coin::STATE_FALL);
	}
    setSpeed(Block::FALL_SPEED);
}

}/*namespace Puzzle*/
