//! @file 		HundredYenBlock.cpp
//! @author 	Keita Tanji
//! @breif		

#include "HundredYenBlock.h"
#include "Classes/Graphics/2D/Sprite.h"
// #include "SoundDriver.h"

namespace Puzzle { 
	
	HundredYenBlock::HundredYenBlock( Math::Vector2 pos )
	: Block( 100, "100", pos )
	{
	}

	HundredYenBlock::~HundredYenBlock()
	{
	}
	
	
	void HundredYenBlock::ExecuteDropEffect()
	{
		//! 着地　発音
		// [[SoundDriver getInstance] play:2];
	}
	
	void HundredYenBlock::ExecuteMoveEffect()
	{
		//! 移動音　発音
		// [[SoundDriver getInstance] play:1];
	}
	
	void HundredYenBlock::ExecuteRoteteEffect()
	{
		//! 回転音　発音
		// [[SoundDriver getInstance] play:3];
	}
	
	void HundredYenBlock::ExecuteBanishEffect()
	{
		//! 消滅音　発音
		// [[SoundDriver getInstance] play:0];
	}
	
	int HundredYenBlock::getGroupValue() const
	{
		return value_ * 5;
	}
	

}/*namespace Puzzle*/