//! @file 		TitleUnit.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "../Unit.h"
#include "Classes/Routine/UI/UI_GameMain.h"
#include "Classes/Graphics/3D/model.h"
#include "Classes/Math/Vector3.h"

class Sprite;

class TitleUnit : public Unit
{
public:
	TitleUnit();
	~TitleUnit();
	virtual void calc();
	virtual void draw();	

	void touchedBegin(CGPoint tp);
	void touchedMoved(CGPoint tp);
	void touchedEnded(CGPoint tp);

private:
	UserInterface::UI_GameMain::BackGround	_bg;
	Graphics::Model*	_coinModel;

	Sprite* 	_spr_logo;
	Sprite*		_spr_bestscore;
	Sprite*		_spr_scoreNumber;
	Sprite*		_spr_teamlogo;
	Sprite*		_spr_menubar;

	//@TODO 	text系

	unsigned int 	_bestScore;

	bool 		_coinTouched;	//!<コイン操作中か
	int 		_coinCounter;	//!<コインを触っていない時間
	int 		_coinTouchTimer;	//!<コインを触っている時間（速度計算用）
	Math::Vector3 	_coinMoveStart;	//!<コインを動かした地点
	Math::Vector3 	_coinMoveEnd;	//!<コインを離した地点
	float 		_coinSpeed;			//!<コインの移動スピード
};