//! @file 		FiftyYenBlock.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "Block.h"

namespace Puzzle {
	
	class FiftyYenBlock : public Block
	{		
	public:		
		FiftyYenBlock(Math::Vector2 pos);
		virtual ~FiftyYenBlock();
		//! エフェクトの実行
		void ExecuteDropEffect();
		void ExecuteMoveEffect();
		void ExecuteRoteteEffect();
		void ExecuteBanishEffect();
		//! グループ編成数の取得
		int getGroupValue() const;
	};
	
}/**/
