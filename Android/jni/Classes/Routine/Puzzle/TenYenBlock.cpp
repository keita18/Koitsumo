//! @file 		TenYenBlock.cpp
//! @author 	Keita Tanji
//! @breif		

#include "TenYenBlock.h"
#include "Classes/Graphics/2D/Sprite.h"
// #include "SoundDriver.h"

namespace Puzzle { 

	TenYenBlock::TenYenBlock( Math::Vector2 pos )
	: Block( 10, "10", pos )
	{
	}

	TenYenBlock::~TenYenBlock()
	{
	}

	void TenYenBlock::ExecuteDropEffect()
	{
		//! 着地　発音
		// [[SoundDriver getInstance] play:2];
	}

	void TenYenBlock::ExecuteMoveEffect()
	{
		//! 移動音　発音
		// [[SoundDriver getInstance] play:1];
	}

	void TenYenBlock::ExecuteRoteteEffect()
	{
		//! 回転音　発音
		// [[SoundDriver getInstance] play:3];
	}

	void TenYenBlock::ExecuteBanishEffect()
	{
		//! 消滅音　発音
		// [[SoundDriver getInstance] play:0];
	}

	int TenYenBlock::getGroupValue() const
	{
		return value_ * 5;
	}

}/*namespace Puzzle*/