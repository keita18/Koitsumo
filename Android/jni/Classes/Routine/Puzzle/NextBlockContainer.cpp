//! @file 		NextBlockContainer.cpp
//! @author 	Keita Tanji
//! @breif		

#include "NextBlockContainer.h"
#include "pch.h"
#include "Block.h"
#include "BlockSet.h"
#include "Classes/Routine/UI/UI_GameMain.h"

namespace Puzzle {

//=============================================================================
NextBlockContainer::NextBlockContainer()
: isReady_( false )
{
}

//=============================================================================
NextBlockContainer::~NextBlockContainer()
{
	BlockIterator itr = nextBlocks_.begin();
	for( ; itr != nextBlocks_.end(); ++itr ){
		delete *itr;
	}
	nextBlocks_.clear();
}

//=============================================================================
void NextBlockContainer::calc()
{
	const float BLOCK_SPEED = 0.02f * Screen::RATIO;
	
	isReady_ = false;

	// Set UI
	float prog = -1.0f;
	float unit = BlockProgressUnit;
	for (int l=0;l<nextBlocks_.size();l++){
		Block *b = nextBlocks_[l];
		if (b && b->getUI()) {
			float b_prog = b->getUI()->getProgress();
			if (prog < 0) {
				float max = 1.0f;
				prog = b_prog + BLOCK_SPEED;
				if (prog > max) {
					prog = max;
					isReady_ = true;
				}
				b->getUI()->setProgress(prog);
			}
			else {
				float max = prog - unit;
				if (b_prog + BLOCK_SPEED > max){
					b_prog = max;
					prog = b_prog;
				}
				else {
					b_prog += BLOCK_SPEED;
					prog = b_prog;
				}
                if(prog<0) prog = 0.0f;
				b->getUI()->setProgress(b_prog);
			}
		}
	}
}

//=============================================================================
void NextBlockContainer::pushBlock( Block* block )
{
	nextBlocks_.push_back( block );
//		BlockSetIterator itr = nextArray_.begin();
//		for( ; itr != nextArray_.end(); ++itr ){
//			for( int index = 0; index < 2; index++ ){
//				if( (*itr)->getBlock( index ) == NULL ){
//					(*itr)->setBlock( block, index );
//					return;
//				}
//			}
//		}
//		// 空きがなければBlockSetを作成
//		BlockSet* blockSet = new BlockSet;
//		blockSet->setBlock( block, 0 );
//		pushBlockSet( blockSet );
}

//=============================================================================
void NextBlockContainer::insertBlock( Block* block, int index )
{
	if( index >= getSize() ){
		pushBlock( block );
		return;
	}
	
	BlockIterator itr = nextBlocks_.begin();
	itr = itr + index;
	nextBlocks_.insert( itr, block );
	
//		BlockSet* blockSet = nextArray_[index];
//		for( int i = 0; i < 2; i++ ){
//			if( blockSet->getBlock( i ) == NULL ){
//				blockSet->setBlock( block, i );
//				return;
//			}
//		}
//		
//		BlockSetIterator itr = nextArray_.begin();
//		itr = itr + index;
//		BlockSet* newBlockSet = new BlockSet;
//		newBlockSet->setBlock( block, 0 );
//		itr = nextArray_.insert( itr, newBlockSet );
//		//単体のブロックになった場合は後ろからずらす
//		for( ; itr + 1 != nextArray_.end(); ++itr ){
//			BlockSetIterator nextItr = itr + 1;
//			Block* nextFirst = (*nextItr)->getBlock(0);
//			Block* nextSecond = (*nextItr)->getBlock(1);
//			(*itr)->setBlock( nextFirst, 1 );
//			(*nextItr)->setBlock( nextSecond, 0 );
//		}
}

//=============================================================================
void NextBlockContainer::pop( BlockSet* blockSet )
{
	Block* baseBlock = nextBlocks_.size() > 0 ? nextBlocks_[0] : NULL;
	if( baseBlock ){
		blockSet->setBlock( baseBlock, 0 );
		nextBlocks_.erase( nextBlocks_.begin() );
	}
						  
	Block* subBlock = nextBlocks_.size() > 0 ? nextBlocks_[0] : NULL;
	if( subBlock ){
		blockSet->setBlock( subBlock, 1 );
		nextBlocks_.erase( nextBlocks_.begin());
	}
}

//=============================================================================
bool NextBlockContainer::isReady() const
{
	return isReady_;
}

}/*namespace */
