//! @file 		TitleUnit.cpp
//! @author 	Keita Tanji
//! @breif		

#include "TitleUnit.h"
#include "../../Graphics/2D/Sprite.h"
#include "Classes/Routine/UI/UI_GameMain.h"

//=============================================================================
TitleUnit::TitleUnit()
: _coinModel(NULL)
, _spr_logo(NULL)
, _spr_bestscore(NULL)
, _spr_scoreNumber(NULL)
, _spr_teamlogo(NULL)
, _spr_menubar(NULL)
, _bestScore(1234)
{
	_spr_logo = new Sprite("title_logo.png", 512, 256);
	_spr_bestscore = new Sprite("best.png", 128, 32);
	_spr_scoreNumber = new Sprite("Score.png", 64, 85);
	_spr_teamlogo = new Sprite("teamlogo.png", 128, 64);
	_spr_menubar = new Sprite("TitleMenu.png", 320, 128);

	_coinModel = UserInterface::UI_GameMain::makeCoinModel("10.png", 64);
}
//=============================================================================
TitleUnit::~TitleUnit()
{
	SAFE_DELETE(_spr_logo);
	SAFE_DELETE(_spr_bestscore);
	SAFE_DELETE(_spr_scoreNumber);
	SAFE_DELETE(_spr_teamlogo);
	SAFE_DELETE(_spr_menubar);
}
//=============================================================================
void TitleUnit::calc()
{

}
//=============================================================================
void TitleUnit::draw()
{
#define TITLE_SCORE_POS_X        70
#define TITLE_SCORE_POS_Y       380
#define TITLE_LOGO_POS_Y         50
#define TITLE_TEAMLOGO_POS_Y    435
#define TITLE_MENUBAR_POS_Y     250
#define TITLE_MENUINFO_POS_X     30

	_spr_bestscore->drawWithFrame(0, TITLE_SCORE_POS_X, TITLE_SCORE_POS_Y, 64, 16);
	_spr_scoreNumber->drawWithFrame(0, TITLE_SCORE_POS_X+66, TITLE_SCORE_POS_Y, 16, 16);
	for (int i=0; i<7; i++) {
		_spr_scoreNumber->drawWithFrame( 
			(_bestScore/((int)pow(10, 6-i)))%10, TITLE_SCORE_POS_X+80+i*12, TITLE_SCORE_POS_Y, 16, 16);
	}

	_spr_logo->drawWithFrame(0, 0, TITLE_LOGO_POS_Y, 320, 160);
	_spr_teamlogo->drawWithFrame(0, 240, TITLE_TEAMLOGO_POS_Y, 64, 32);

	//test描画
	// _spr_logo->drawBox();
}
