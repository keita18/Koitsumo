//! @file 		BlockContainer.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <vector>

namespace Puzzle {

class Block;
	
//! @brief  固定されたブロックのコンテナ
class BlockContainer
{
	typedef std::vector< Block* > BlockArray;
	typedef std::vector< Block* >::iterator BlockIterator;
public:
	enum {
		NB_ROW_MAX = 8,
		NB_COLUMN_MAX = 8,
	};
public:
	BlockContainer();
	virtual ~BlockContainer();
		
	//! @brief  ブロックを列に追加
	//! @param[in]  column  列番号
	//! @param[in]  block  追加するブロック
	static void push( int column, Block* block );
		
    //! @brief  指定した位置のブロックを削除。解放まで行う。
	static void remove( int row, int column );
	static void remove( Block* block );
	static void removeAll();

	//! @brief  指定した位置のブロックを取得
	//! @return  指定した位置のブロック。ない場合nil。
	static Block* get( int row, int column );
	
	//! @brief  指定した列のブロック数を取得
	static int getSize( int column ) { return blockArray_[column].size(); }

	void calc( float dt );
	void draw();
	
	//! @brief  デバイス回転通知
	//! @brief  回転角度（差分）
	static void notifyRotate( int angle );

	//! @brief  グループを作成
	//! @return  グループが作られたらtrue
	static bool makeGroup();
	
	//! @brief  動いてるブロックある？
	static bool isExistFreeBlock();
	
	//! @brief  あふれた？　「あふれた」とは3列目または４列目が満杯になったこと。
	static bool isOverFlowed();

	//! @brief	向き変更に対応（ブロックが震える）
	static void readyToOrientation(bool o);
	
private:	
	//! @brief  グループになってるブロックを消す
	static void eraseGroupedBlocks_();
	//! @brief  位置を整える
	static void validatePosition_();

private:
	static std::vector< Block* > blockArray_[NB_COLUMN_MAX];
	
	static std::vector< Block* > freeBlocks_; ///<! @brief 固定されていないブロックのコンテナ 
};
	
}/**/
