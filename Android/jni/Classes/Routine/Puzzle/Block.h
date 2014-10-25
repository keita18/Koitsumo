//! @file 		Block.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "Stage.h"
#include "Classes/Routine/UI/UI_GameMain.h"
#include <vector>

class Sprite;

namespace Puzzle {

class Block
{
public:
	typedef std::vector<Block*> BlockArray;

public:
	// enum Size{
	// 	WIDTH = Stage::WIDTH/8,
	// 	HEIGHT = Stage::HEIGHT/8
	// };
	// enum Area{
	// 	MAX_X = Stage::WIDTH - WIDTH,
	// 	MAX_Y = Stage::HEIGHT - HEIGHT,
	// };
	//! 画面サイズ補正で動的に決定
	static int WIDTH;
	static int HEIGHT;
	static int MAX_X;
	static int MAX_Y;
	static void onDecideScreenRatio(int ratio);

public:
	static Block* create( int value, int row, int col );
	static UserInterface::UI_GameMain *uiGameMain;
    static float FALL_SPEED;        //<通常の落下速度
    static float FIXED_FALL_SPEED;  //<固定後の落下速度
	
public:
	Block( int value, const char* resname, Math::Vector2 pos /*サイズが動的に決まる以上使えない= Math::Vector2(WIDTH * 3, 0.0f)*/ );
	virtual ~Block();
	void calc( float dt );
	void draw();
	int getValue() const { return value_; }
	bool isLocked() const { return isLocked_; }
	void setLocked( bool val ) { isLocked_ = val; }
	Math::Vector2 getPosition() const { return position_; }
	void setPosition( const Math::Vector2& position ) { 
		position_ = position; 
	}
	void setPosition( float x, float y ) { 
		setPosition(Math::Vector2( x, y ));
	}
	
	//! @brief  どの列か
	int getColumnNumber() const;
	void setColumnNumber( int col );
	//! @brief  どの行か
	int getRowNumber() const;

	//! @brief  ２つ以上のリンクができてるか
	bool isLinked() const { return isLinked_; }

	//! @brief  グループのリンクに入れるか
	void setLinked( bool val ) { isLinked_ = val; }
	
	//! @brief  グループ完成してるか
	bool isGroup() const { return isGroup_; }
	
	void setGroup( bool val ) { isGroup_ = val; }
		
	//! @brief  グループ完成形になるか
	//! @param[in]  sumValue  形成中のグループの合計の値
	//! @return  グループ完成するとtrue
	bool checkGroup( int* sumValue, BlockArray* linkBlocks );
	
	//! @brief  落下速度取得
	void setSpeed( float val ) { speed_ = val; }
	
	//! @brief  本体回転による座標変換
	void rotateByDeviceRotation( int angle );

	//! エフェクトの実行
	virtual void ExecuteDropEffect() = 0;
	virtual void ExecuteMoveEffect() = 0;
	virtual void ExecuteRoteteEffect() = 0;
	virtual void ExecuteBanishEffect() = 0;
	
	// for UI
	UserInterface::UI_GameMain::Coin* getUI()		{ return ui_; }
	void moveUItoFront();
	
	//! グループ編成数の取得
	virtual int getGroupValue() const = 0;
	
protected:
	
	int value_;	
	Math::Vector2 position_; //!@brief Stage内のローカル座標
	bool isLocked_;
	bool isLinked_;
	bool isGroup_;
	Sprite* sprite_;
	float speed_;
	
	UserInterface::UI_GameMain::Coin	*ui_;
    
};

}/**/
