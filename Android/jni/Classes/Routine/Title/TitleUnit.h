//! @file 		TitleUnit.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "../Unit.h"

class Sprite;

class TitleUnit : public Unit
{
public:
	TitleUnit();
	~TitleUnit();
	virtual void calc();
	virtual void draw();	

private:
	Sprite* 	_spr_logo;
};