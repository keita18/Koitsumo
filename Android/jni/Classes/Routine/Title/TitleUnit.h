//! @file 		TitleUnit.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "../Unit.h"
#include "Classes/Graphics/3D/model.h"

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
	Graphics::Model*	_coinModel;

	Sprite* 	_spr_logo;
	Sprite*		_spr_bestscore;
	Sprite*		_spr_scoreNumber;
	Sprite*		_spr_teamlogo;
	Sprite*		_spr_menubar;

	unsigned int 	_bestScore;
};