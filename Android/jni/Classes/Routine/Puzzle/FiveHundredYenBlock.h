//! @file 		FiveHundredYenBlock.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "Block.h"

namespace Puzzle {
	
	class FiveHundredYenBlock : public Block
	{		
	public:		
		FiveHundredYenBlock(Math::Vector2 pos);
		virtual ~FiveHundredYenBlock();
		//! エフェクトの実行
		void ExecuteDropEffect();
		void ExecuteMoveEffect();
		void ExecuteRoteteEffect();
		void ExecuteBanishEffect();
		//! グループ編成数の取得
		int getGroupValue() const;
	};
	
}/**/
