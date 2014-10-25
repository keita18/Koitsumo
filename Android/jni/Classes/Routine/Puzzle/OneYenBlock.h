//! @file 		OneYenBlock.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "Block.h"

namespace Puzzle {
	
	class OneYenBlock : public Block
	{		
	public:		
		OneYenBlock(Math::Vector2 pos);
		virtual ~OneYenBlock();
		//! エフェクトの実行
		void ExecuteDropEffect();
		void ExecuteMoveEffect();
		void ExecuteRoteteEffect();
		void ExecuteBanishEffect();
		//! グループ編成数の取得
		int getGroupValue() const;
	};
	
}/**/
