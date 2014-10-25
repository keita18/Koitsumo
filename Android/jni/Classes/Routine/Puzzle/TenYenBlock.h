//! @file 		TenYenBlock.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "Block.h"

namespace Puzzle {
	
	class TenYenBlock : public Block
	{		
	public:		
		TenYenBlock(Math::Vector2 pos);
		virtual ~TenYenBlock();
		//! エフェクトの実行
		void ExecuteDropEffect();
		void ExecuteMoveEffect();
		void ExecuteRoteteEffect();
		void ExecuteBanishEffect();
		//! グループ編成数の取得
		int getGroupValue() const;
	};
	
}/**/
