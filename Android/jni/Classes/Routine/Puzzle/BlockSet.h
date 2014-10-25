//! @file 		BlockSet.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "pch.h"

namespace Puzzle {

class Block;
	
class BlockSet
{
public:
	enum RotDirect{
		X,
		INV_X,
	};
	
public:
	static void createRandom( Block** base, Block** sub );
	
public:
	BlockSet();
	virtual ~BlockSet();
	void calc( float dt );
	void draw();
	bool isLocked() const;
	
	Block* getBlock( int index );
	void setBlock( Block* block, int index );
	int getNbBlocks() const;
	
	void move( float x, float y );
	void rotate( RotDirect dir );
	bool canControl() const { return canControl_; }
	void setSpeed( float speed );
	//! @brief 落下開始
	void beginFall();
	
	//! @brief 空にする
	void setEmpty() { baseBlock_ = NULL; subBlock_ = NULL; }
	bool isEmpty() const { return baseBlock_ == NULL && subBlock_ == NULL; }
	
private:
	void calcBase( float dt );
	void calcSub( float dt );
	
private:
	Block* baseBlock_;
	Block* subBlock_;
	bool canControl_;
	
public:
	static int PROB_1;
	static int PROB_5;
	static int PROB_10;
	static int PROB_50;
	static int PROB_100;
	static int PROB_500;
	
};
	
}/*namespace Puzzle*/
