//! @file 		FiveHundredYenBlock.cpp
//! @author 	Keita Tanji
//! @breif		

#include "FiveHundredYenBlock.h"
#include "Classes/Graphics/2D/Sprite.h"
// #include "SoundDriver.h"

namespace Puzzle { 
	
	FiveHundredYenBlock::FiveHundredYenBlock( Math::Vector2 pos )
	: Block( 500, "500", pos )
	{
	}
	
	FiveHundredYenBlock::~FiveHundredYenBlock()
	{
	}
	
	void FiveHundredYenBlock::ExecuteDropEffect()
	{
		//! 着地　発音
		// [[SoundDriver getInstance] play:2];
	}
	
	void FiveHundredYenBlock::ExecuteMoveEffect()
	{
		//! 移動音　発音
		// [[SoundDriver getInstance] play:1];
	}
	
	void FiveHundredYenBlock::ExecuteRoteteEffect()
	{
		//! 回転音　発音
		// [[SoundDriver getInstance] play:3];
	}
	
	void FiveHundredYenBlock::ExecuteBanishEffect()
	{
		//! 消滅音　発音
		// [[SoundDriver getInstance] play:0];
		
		//! 札音　発音
		// [[SoundDriver getInstance] play:4];
	}
	
	int FiveHundredYenBlock::getGroupValue() const
	{
		return value_ * 2;
	}
	
}/*namespace Puzzle*/
