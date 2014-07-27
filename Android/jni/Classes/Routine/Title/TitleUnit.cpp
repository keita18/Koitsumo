//! @file 		TitleUnit.cpp
//! @author 	Keita Tanji
//! @breif		

#include "TitleUnit.h"
#include "../../Graphics/2D/Sprite.h"

//=============================================================================
TitleUnit::TitleUnit()
: _spr_logo(NULL)
{
	_spr_logo = new Sprite("title_logo.png", 512, 256);
}
//=============================================================================
TitleUnit::~TitleUnit()
{}
//=============================================================================
void TitleUnit::calc()
{}
//=============================================================================
void TitleUnit::draw()
{
#define TITLE_LOGO_POS_Y         50

	// _spr_logo->drawWithFrame(0, 0, TITLE_LOGO_POS_Y, 320, 160);

	//test描画
	_spr_logo->drawBox();
}
