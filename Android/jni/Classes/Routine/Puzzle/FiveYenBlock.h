//! @file 		FiveYenBlock.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "Block.h"

namespace Puzzle {
	
	class FiveYenBlock : public Block
	{		
	public:		
		FiveYenBlock(Math::Vector2 pos);
		virtual ~FiveYenBlock();
		//! エフェクトの実行
		void ExecuteDropEffect();
		void ExecuteMoveEffect();
		void ExecuteRoteteEffect();
		void ExecuteBanishEffect();
		//! グループ編成数の取得
		int getGroupValue() const;
	};
	
}/**/
