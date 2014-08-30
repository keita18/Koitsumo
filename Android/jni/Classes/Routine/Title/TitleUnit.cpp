//! @file 		TitleUnit.cpp
//! @author 	Keita Tanji
//! @breif		

#include "TitleUnit.h"
#include "../../Graphics/2D/Sprite.h"
#include "Classes/Routine/UI/UI_GameMain.h"

//=============================================================================
TitleUnit::TitleUnit()
: _bg()
, _coinModel(NULL)
, _spr_logo(NULL)
, _spr_bestscore(NULL)
, _spr_scoreNumber(NULL)
, _spr_teamlogo(NULL)
, _spr_menubar(NULL)
, _bestScore(1234)
, _coinTouched(false)
, _coinCounter(0)
, _coinTouchTimer(0)
, _coinMoveStart()
, _coinMoveEnd()
, _coinSpeed(0.0f)
{
	_spr_logo = new Sprite("title_logo.png", 512, 256);
	_spr_bestscore = new Sprite("best.png", 128, 32);
	_spr_scoreNumber = new Sprite("Score.png", 64, 85);
	_spr_teamlogo = new Sprite("teamlogo.png", 128, 64);
	_spr_menubar = new Sprite("TitleMenu.png", 320, 128);

	_coinModel = UserInterface::UI_GameMain::makeCoinModel("10.png", 64);
	_coinModel->SetScale(Math::Vector3(32.f, 32.f, 32.f));
	_coinModel->SetPosition(Math::Vector3(160.f, 218.f, 0));

	//@TODO 
	// _bestScore

}
//=============================================================================
TitleUnit::~TitleUnit()
{
	SAFE_DELETE(_spr_logo);
	SAFE_DELETE(_spr_bestscore);
	SAFE_DELETE(_spr_scoreNumber);
	SAFE_DELETE(_spr_teamlogo);
	SAFE_DELETE(_spr_menubar);

	SAFE_DELETE(_coinModel);
}
//=============================================================================
void TitleUnit::calc()
{
	_bg.calc();

	Math::Vector3 coinpos = _coinModel->GetPosition();
	if (coinpos.y < 282) coinpos.y += 4.f;
	if (_coinCounter == 0) coinpos.x -= (coinpos.x - 160.0f) * 0.03f;
	else {
		if (abs(_coinSpeed) > 1.0f) {
			_coinSpeed -= _coinSpeed * 0.1f;
		} else {
			_coinSpeed = 0;
		}
		coinpos.x += _coinSpeed;
	}
	_coinModel->SetPosition(coinpos);
	_coinModel->SetRotation(Math::Vector3(0, 0, (coinpos.x - 160.0f) * 2.0f));

	LOGI("coinPos=%3.3f, %3.3f, %3.3f", coinpos.x, coinpos.y, coinpos.z);

	if (coinpos.x > 360) {
		SetEnd(true);
		SetNextID(UNIT_PUZZLE_NO_TIMELIMIT);
	} else if (coinpos.x < -40) {
		SetEnd(true);
		SetNextID(UNIT_PUZZLE);
	}

	if (!_coinTouched && _coinCounter > 0) _coinCounter--;
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

	_bg.draw();
	_spr_bestscore->drawWithFrame(0, TITLE_SCORE_POS_X, TITLE_SCORE_POS_Y, 64, 16);
	_spr_scoreNumber->drawWithFrame(0, TITLE_SCORE_POS_X+66, TITLE_SCORE_POS_Y, 16, 16);
	for (int i=0; i<7; i++) {
		_spr_scoreNumber->drawWithFrame( 
			(_bestScore/((int)pow(10.0f, 6.0f-(float)i)))%10, TITLE_SCORE_POS_X+80+i*12, TITLE_SCORE_POS_Y, 16, 16);
	}

	//@TODO stencilとか
	_spr_menubar->drawWithFrame(0, 0, TITLE_MENUBAR_POS_Y, 160, 64);
	_spr_menubar->drawWithFrame(1, 160, TITLE_MENUBAR_POS_Y, 160, 64);

	// _spr_menubar->drawWithFrame(0, 0, TITLE_MENUBAR_POS_Y, 160, 64);
	// _spr_menubar->drawWithFrame(0, 0, TITLE_MENUBAR_POS_Y, 160, 64);

	_coinModel->Draw();

	_spr_logo->drawWithFrame(0, 0, TITLE_LOGO_POS_Y, 320, 160);
	_spr_teamlogo->drawWithFrame(0, 240, TITLE_TEAMLOGO_POS_Y, 64, 32);

	//test描画
	// _spr_logo->drawBox();
}

//=============================================================================
void TitleUnit::touchedBegin(CGPoint tp)
{

}
//=============================================================================
void TitleUnit::touchedMoved(CGPoint tp)
{

}
//=============================================================================
void TitleUnit::touchedEnded(CGPoint tp)
{

}
