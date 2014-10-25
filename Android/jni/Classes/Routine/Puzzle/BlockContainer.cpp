//! @file 		BlockContainer.cpp
//! @author 	Keita Tanji
//! @breif		

#include "BlockContainer.h"
#include "pch.h"
#include "Block.h"
#include "PuzzleUnit.h"
#include "NextBlockContainer.h"
#include "Parameter.h"
#include "Classes/Routine/UI/UI_GameMain.h"
#include <algorithm>

namespace Puzzle{
	
/*static*/ std::vector< Block* > BlockContainer::blockArray_[BlockContainer::NB_COLUMN_MAX];
	
/*static*/ std::vector< Block* > BlockContainer::freeBlocks_;

//=============================================================================
BlockContainer::BlockContainer()
{
}
//=============================================================================
BlockContainer::~BlockContainer()
{
	removeAll();
}
//=============================================================================
void BlockContainer::calc( float dt )
{	
	BlockIterator freeItr = freeBlocks_.begin();
	for( ; freeItr != freeBlocks_.end(); ){
		(*freeItr)->calc( dt );
		if( (*freeItr)->isLocked() ){
			freeItr = freeBlocks_.erase( freeItr );
		}
		else{
			++freeItr;
		}
	}	
	
}
//=============================================================================
void BlockContainer::draw()
{
	BlockIterator freeItr = freeBlocks_.begin();
	for( ; freeItr != freeBlocks_.end(); ){
		(*freeItr)->draw();
		++freeItr;
	}
	
	for( int col = 0; col < NB_COLUMN_MAX; ++col ){
		BlockIterator itr = blockArray_[col].begin();
		for( int row = 0; itr != blockArray_[col].end() && row < NB_ROW_MAX; ++itr, ++row ){
			(*itr)->draw();
		}
	}
}
//=============================================================================
/*static*/void BlockContainer::push( int column, Block* block )
{
	blockArray_[column].push_back( block );
}
//=============================================================================
/*static*/void BlockContainer::remove( int row, int column )
{
	if( blockArray_[column].size() < row ){
		return;
	}

	BlockIterator itr = blockArray_[column].begin();
	for( int i = 0; i < row; ++i ){
		itr++;
	}
	Block* removeBlock = *itr;
	blockArray_[column].erase( itr );	
	SAFE_DELETE( removeBlock );
}
//=============================================================================
/*static*/void BlockContainer::remove( Block* block )
{
	for( int col = 0; col < NB_COLUMN_MAX; ++col ){
		BlockIterator itr = blockArray_[col].begin();
		for( ; itr != blockArray_[col].end(); ++itr ){
			if( *itr == block ){
				block->ExecuteBanishEffect();
				blockArray_[col].erase(itr);
				SAFE_DELETE( block );
				return;
			}
		}
	}
}
//=============================================================================
/*static*/void BlockContainer::removeAll()
{
	for( int col = 0; col < NB_COLUMN_MAX; ++col ){
		BlockIterator itr = blockArray_[col].begin();
		for( ; itr != blockArray_[col].end(); ++itr ){
			SAFE_DELETE( *itr );
		}
		blockArray_[col].clear();
	}
}
//=============================================================================
Puzzle::Block* BlockContainer::get( int row, int column )
{
	if( 0 <= column && column < NB_COLUMN_MAX &&
	    blockArray_[column].size() > row ){
			return blockArray_[column][row];
	}
	else{
		return NULL;
	}
}
//=============================================================================
//! @brief  本体の回転通知
void BlockContainer::notifyRotate( int angle )
{
	for( int col = 0; col < NB_COLUMN_MAX; ++col ){
		BlockIterator itr = blockArray_[col].begin();
		for( ; itr != blockArray_[col].end(); ){			
			// 座標変換
			(*itr)->rotateByDeviceRotation( angle );
			
			// フローティング状態にする
			(*itr)->setLocked( false );
			(*itr)->setSpeed( Block::FIXED_FALL_SPEED );
			freeBlocks_.push_back( *itr );
			itr = blockArray_[col].erase( itr ); 
		}
	}
	
}
//=============================================================================
bool BlockContainer::makeGroup()
{
	for( int col = 0; col < NB_COLUMN_MAX; ++col ){
		BlockIterator itr = blockArray_[col].begin();
		for( ; itr != blockArray_[col].end(); ++itr ){
			(*itr)->setLinked( false );
		}
	}

	//左下から順に右と上をチェック(グループのフラグたてるだけ）
	bool isGroupMaked = false;
	int groupCount = 0;
	for( int col = 0; col < NB_COLUMN_MAX; ++col ){
		BlockArray& colBlocks = blockArray_[col];
		for( int row = 0, nbRow = colBlocks.size(); row < nbRow; ++row ){
			Block* block = colBlocks[row];
			int sumValue = block->getValue();

			BlockArray linkBlocks;
			linkBlocks.push_back( block );
			if( block->checkGroup( &sumValue, &linkBlocks ) ){
				isGroupMaked = true;
				BlockIterator linkItr = linkBlocks.begin();
				int groupValue = block->getGroupValue();
                Math::Vector2 coinPos = (*linkItr)->getPosition();
				for( ; linkItr != linkBlocks.end(); ){
					(*linkItr)->setGroup( true );
					if( sumValue < 1000) {
						(*linkItr)->getUI()->setState(UserInterface::UI_GameMain::Coin::STATE_UNION);
					} else {
						(*linkItr)->getUI()->setState(UserInterface::UI_GameMain::Coin::STATE_CLEAR);
					}
					linkItr = linkBlocks.erase( linkItr );
				}
				
				//両替(グループの端数はスコアにそのまま加算)
				int nbGroup = sumValue / groupValue;
				int leftValue = sumValue;
                int scorePlus = 0;
				groupCount += nbGroup;
				for( int i = 0; i < nbGroup; ++i ){
					leftValue -= groupValue;
					if( groupValue == 1000 ){
                        scorePlus += groupValue;
					}
					else {
						Block* block = Block::create( groupValue, -1, 3 );
						block->getUI()->shineEffectOn();
						block->getUI()->setProgress(1.0f);
						block->moveUItoFront();
						PuzzleUnit::getNextBlockContainer()->insertBlock( block, 0 );
					}
				}
				assert( leftValue >= 0 );
                scorePlus += leftValue;
                if(scorePlus > 0) {
                    PuzzleUnit::addScore( scorePlus, coinPos );                    
                }
			}
			// linkリセット
			BlockIterator bitr = linkBlocks.begin();
			for( ; bitr != linkBlocks.end(); bitr++ ){
				(*bitr)->setLinked( false );
			}
			linkBlocks.clear();
		}
	}
	if( isGroupMaked ){
		//グループになったやつ全部消す
		eraseGroupedBlocks_();
		validatePosition_();
		
		PuzzleUnit::addTimeByGroupNum( groupCount );//addChainの前によぶ
		PuzzleUnit::addChain();
		return true;
	}
	return false;
}
//=============================================================================
bool BlockContainer::isExistFreeBlock()
{
	return freeBlocks_.size() > 0;
}
//=============================================================================
bool BlockContainer::isOverFlowed()
{
	// ３列目４列目が満杯かどうか
	if( blockArray_[3].size() >= NB_ROW_MAX || 
	   blockArray_[4].size() >= NB_ROW_MAX ){
		return true;
	}
	return false;
}
//=============================================================================
void BlockContainer::eraseGroupedBlocks_()
{
	BlockArray tempArray;
	// イテレータめんどいので一回ポインタ取得
	for( int col = 0; col < NB_COLUMN_MAX; ++col ){
		BlockArray& colBlocks = blockArray_[col];
		BlockIterator bitr = colBlocks.begin();
		for( ; bitr != colBlocks.end(); ++bitr ){
			if( (*bitr)->isGroup() ){
				tempArray.push_back( *bitr );
			}
		}
	}
	BlockIterator titr = tempArray.begin();
	for( ; titr != tempArray.end(); ++titr ){
		remove( *titr );
	}
}
//=============================================================================
void BlockContainer::validatePosition_()
{
	for( int col = 0; col < NB_COLUMN_MAX; ++col ){
		BlockArray& colBlocks = blockArray_[col];
		BlockIterator bitr = colBlocks.begin();
		for( int row = 0; bitr != colBlocks.end(); row++ ){
			float x = Block::WIDTH * col;
			float y = Stage::HEIGHT - ( Block::HEIGHT * (row + 1) );
			Math::Vector2 pos = (*bitr)->getPosition();
			// 下が空いたらコンテナから除外
			Math::Vector2 dif = pos - Math::Vector2( x, y );
			if( dif.squareLength() > 0.1f ){
				Block* freeBlock = *bitr;
				freeBlock->setLocked( false );
				bitr = colBlocks.erase( bitr );
				if( std::find( freeBlocks_.begin(), freeBlocks_.end(), freeBlock ) == freeBlocks_.end() ){
					freeBlocks_.push_back( freeBlock );
				}
			}
			else{
				bitr++;
			}
		}
	}
}
//=============================================================================
void BlockContainer::readyToOrientation(bool o)
{
	for( int col = 0; col < NB_COLUMN_MAX; ++col ){
		BlockIterator itr = blockArray_[col].begin();
		for( int row = 0; itr != blockArray_[col].end() && row < NB_ROW_MAX; ++itr, ++row ){
			(*itr)->getUI()->setShake( o );
		}
	}
	BlockIterator freeItr = freeBlocks_.begin();
	for( ; freeItr != freeBlocks_.end(); ++freeItr ){
		(*freeItr)->getUI()->setShake( o );
	}
}
	
}/*namespace Puzzle*/