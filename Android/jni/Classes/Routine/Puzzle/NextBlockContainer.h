//! @file 		NextBlockContainer.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <vector>

namespace Puzzle {

class Block;
class BlockSet;

class NextBlockContainer
{
	typedef std::vector< Block* > BlockArray;
	typedef std::vector< Block* >::iterator BlockIterator;

public:
	NextBlockContainer();
	
	~NextBlockContainer();
	
	void calc();
	
	//! @brief  前から探索して一番始めに空いている位置にBlockを挿入
	void pushBlock( Block* block );

	//! @brief  indexにBlockを挿入
	void insertBlock( Block* block, int index );

	//! @brief  始めのBlockSetをポップ
	void pop( BlockSet* blockSet );
	
	//! @brief 数
	int getSize() const { return nextBlocks_.size(); }
	
	//! @brief  準備完了？
	bool isReady() const;
	
private:	
	BlockArray nextBlocks_;
	bool isReady_;
};

}/*namespace Puzzle*/
