//! @file 		FiveYenBlock.cpp
//! @author 	Keita Tanji
//! @breif		

#include "FiveYenBlock.h"
#include "Classes/Graphics/2D/Sprite.h"
// #include "SoundDriver.h"

namespace Puzzle { 
	
	FiveYenBlock::FiveYenBlock( Math::Vector2 pos )
	: Block( 5, "5", pos )
	{
	}
	
	FiveYenBlock::~FiveYenBlock()
	{
	}
	
	void FiveYenBlock::ExecuteDropEffect()
	{
		//! 着地　発音
		// [[SoundDriver getInstance] play:2];
	}
	
	void FiveYenBlock::ExecuteMoveEffect()
	{
		//! 移動音　発音
		// [[SoundDriver getInstance] play:1];
	}
	
	void FiveYenBlock::ExecuteRoteteEffect()
	{
		//! 回転音　発音
		// [[SoundDriver getInstance] play:3];
	}
	
	void FiveYenBlock::ExecuteBanishEffect()
	{
		//! 消滅音　発音
		// [[SoundDriver getInstance] play:0];
	}
	
	int FiveYenBlock::getGroupValue() const
	{
		return value_ * 2;
	}
	
}/*namespace Puzzle*/
