//! @file 		OneYenBlock.cpp
//! @author 	Keita Tanji
//! @breif		

#include "OneYenBlock.h"
#include "Classes/Graphics/2D/Sprite.h"
//#include "SoundDriver.h"

namespace Puzzle { 
	
	OneYenBlock::OneYenBlock( Math::Vector2 pos )
	: Block( 1, "1", pos )
	{
	}
	
	OneYenBlock::~OneYenBlock()
	{
	}
	
	void OneYenBlock::ExecuteDropEffect()
	{
		//! 着地　発音
		// [[SoundDriver getInstance] play:2];
	}
	
	void OneYenBlock::ExecuteMoveEffect()
	{
		//! 移動音　発音
		// [[SoundDriver getInstance] play:1];
	}
	
	void OneYenBlock::ExecuteRoteteEffect()
	{
		//! 回転音　発音
		// [[SoundDriver getInstance] play:3];
	}
	
	void OneYenBlock::ExecuteBanishEffect()
	{
		//! 消滅音　発音
		// [[SoundDriver getInstance] play:0];
	}
	
	int OneYenBlock::getGroupValue() const
	{
		return value_ * 5;
	}
	
}/*namespace Puzzle*/
