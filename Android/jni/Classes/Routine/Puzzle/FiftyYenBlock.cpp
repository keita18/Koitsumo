//! @file 		FiftyYenBlock.cpp
//! @author 	Keita Tanji
//! @breif		

#include "FiftyYenBlock.h"
#include "Classes/Graphics/2D/Sprite.h"
// #include "SoundDriver.h"

namespace Puzzle { 
	
	FiftyYenBlock::FiftyYenBlock( Math::Vector2 pos )
	: Block( 50, "50", pos )
	{
	}
	
	FiftyYenBlock::~FiftyYenBlock()
	{
	}
	
	
	void FiftyYenBlock::ExecuteDropEffect()
	{
		//! 着地　発音
		// [[SoundDriver getInstance] play:2];
	}
	
	void FiftyYenBlock::ExecuteMoveEffect()
	{
		//! 移動音　発音
		// [[SoundDriver getInstance] play:1];
	}
	
	void FiftyYenBlock::ExecuteRoteteEffect()
	{
		//! 回転音　発音
		// [[SoundDriver getInstance] play:3];
	}
	
	void FiftyYenBlock::ExecuteBanishEffect()
	{
		//! 消滅音　発音
		// [[SoundDriver getInstance] play:0];
	}
	
	int FiftyYenBlock::getGroupValue() const
	{
		return value_ * 2;
	}
	
	
}/*namespace Puzzle*/
