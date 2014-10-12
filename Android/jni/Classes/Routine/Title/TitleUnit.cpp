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
	static const float MODEL_SCALE = 32.f * Screen::RATIO;
	static const float MODEL_X = 160.0f * Screen::RATIO;
	static const float MODEL_Y = 218.0f * Screen::RATIO;

	_coinModel->SetScale(Math::Vector3(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
	_coinModel->SetPosition(Math::Vector3(MODEL_X, MODEL_Y, 0));

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

	static const float COIN_POS_X_TH_MAX = 360 * Screen::RATIO;
	static const float COIN_POS_X_TH_MIN = -40 * Screen::RATIO;
	static const float COIN_FALL_SPEED = 4 * Screen::RATIO;
	static const float COIN_FALL_MAX_Y = 282 * Screen::RATIO;
	static const float COIN_AUTO_MOVE_X_SPEED = 160.0f * Screen::RATIO;

	Math::Vector3 coinpos = _coinModel->GetPosition();
	if (coinpos.y < COIN_FALL_MAX_Y) coinpos.y += COIN_FALL_SPEED;
	if (_coinCounter == 0) coinpos.x -= (coinpos.x - COIN_AUTO_MOVE_X_SPEED) * 0.03f;
	else {
		if (abs(_coinSpeed) > 1.0f) {
			_coinSpeed -= _coinSpeed * 0.1f;
		} else {
			_coinSpeed = 0;
		}
		coinpos.x += _coinSpeed;
	}
	_coinModel->SetPosition(coinpos);
	_coinModel->SetRotation(Math::Vector3(0, 0, (coinpos.x - COIN_AUTO_MOVE_X_SPEED) * 2.0f));

	if (coinpos.x > COIN_POS_X_TH_MAX) {
		SetEnd(true);
		SetNextID(UNIT_PUZZLE_NO_TIMELIMIT);
	} else if (coinpos.x < COIN_POS_X_TH_MIN) {
		SetEnd(true);
		SetNextID(UNIT_PUZZLE);
	}

	if (!_coinTouched && _coinCounter > 0) _coinCounter--;
}
//=============================================================================
void TitleUnit::draw()
{
//解像度差吸収のためにすべての直値をラベル化
#define TITLE_SCORE_POS_X        (70 * Screen::RATIO)
#define TITLE_SCORE_POS_Y       (380 * Screen::RATIO)
#define TITLE_LOGO_POS_Y         (50 * Screen::RATIO)
#define TITLE_LOGO_SIZE_X         (320 * Screen::RATIO)
#define TITLE_LOGO_SIZE_Y         (160 * Screen::RATIO)
#define TITLE_TEAMLOGO_POS_X    (240 * Screen::RATIO)
#define TITLE_TEAMLOGO_POS_Y    (435 * Screen::RATIO)
#define TITLE_TEAMLOGO_SIZE_X    (64 * Screen::RATIO)
#define TITLE_TEAMLOGO_SIZE_Y    (32 * Screen::RATIO)
#define TITLE_MENUBAR_POS_X     (160 * Screen::RATIO)
#define TITLE_MENUBAR_POS_Y     (250 * Screen::RATIO)
#define TITLE_MENUBAR_SIZE_X     (160 * Screen::RATIO)
#define TITLE_MENUBAR_SIZE_Y     (64 * Screen::RATIO)
#define TITLE_MENUINFO_POS_X     (30 * Screen::RATIO)
#define TITLE_SCORE_SIZE_X		(64 * Screen::RATIO)
#define TITLE_SCORE_SIZE_Y		(16 * Screen::RATIO)
#define TITLE_SCORE_NUMBER_SIZE_X		(16 * Screen::RATIO)
#define TITLE_SCORE_NUMBER_SIZE_Y		(16 * Screen::RATIO)
#define TITLE_SCORE_NUMBER_POS_X		(TITLE_SCORE_POS_X + 66 * Screen::RATIO)
#define TITLE_SCORE_NUMBER_OFFSET_X		(12 * Screen::RATIO)
#define TITLE_SCORE_NUMBER_OFFSET_X_2		(80 * Screen::RATIO)


	_bg.draw();
	_spr_bestscore->drawWithFrame(0, TITLE_SCORE_POS_X, TITLE_SCORE_POS_Y, TITLE_SCORE_SIZE_X, TITLE_SCORE_SIZE_Y);
	_spr_scoreNumber->drawWithFrame(0, TITLE_SCORE_NUMBER_POS_X, TITLE_SCORE_POS_Y, TITLE_SCORE_NUMBER_SIZE_X, TITLE_SCORE_NUMBER_SIZE_Y);
	for (int i=0; i<7; i++) {
		_spr_scoreNumber->drawWithFrame( 
			(_bestScore/((int)pow(10.0f, 6.0f-(float)i)))%10, 
			TITLE_SCORE_POS_X+TITLE_SCORE_NUMBER_OFFSET_X_2+i*TITLE_SCORE_NUMBER_OFFSET_X, 
			TITLE_SCORE_POS_Y, TITLE_SCORE_NUMBER_SIZE_X, TITLE_SCORE_NUMBER_SIZE_Y);
	}

	//@TODO stencilとか
	_spr_menubar->drawWithFrame(0, 0, TITLE_MENUBAR_POS_Y, TITLE_MENUBAR_SIZE_X, TITLE_MENUBAR_SIZE_Y);
	_spr_menubar->drawWithFrame(1, TITLE_MENUBAR_POS_X, TITLE_MENUBAR_POS_Y, TITLE_MENUBAR_SIZE_X, TITLE_MENUBAR_SIZE_Y);

	// _spr_menubar->drawWithFrame(0, 0, TITLE_MENUBAR_POS_Y, 160, 64);
	// _spr_menubar->drawWithFrame(0, 0, TITLE_MENUBAR_POS_Y, 160, 64);

	_coinModel->Draw();

	_spr_logo->drawWithFrame(0, 0, TITLE_LOGO_POS_Y, TITLE_LOGO_SIZE_X, TITLE_LOGO_SIZE_Y);
	_spr_teamlogo->drawWithFrame(0, TITLE_TEAMLOGO_POS_X, TITLE_TEAMLOGO_POS_Y, TITLE_TEAMLOGO_SIZE_X, TITLE_TEAMLOGO_SIZE_Y);

	//test描画
	// _spr_logo->drawBox();
}

//=============================================================================
void TitleUnit::touchedBegin(CGPoint tp)
{
#define TITLE_COIN_COUNTER	30
	static const int TOUCH_WIDTH = 32 * Screen::RATIO;

	Math::Vector3 coinpos = _coinModel->GetPosition();

	LOGI("coinPos=%3.3f, %3.3f, %3.3f, tp=%3.3f, %3.3f", coinpos.x, coinpos.y, coinpos.z, tp.x, tp.y);

	if ( coinpos.x - TOUCH_WIDTH < tp.x && tp.x < coinpos.x + TOUCH_WIDTH && 
		 coinpos.y - TOUCH_WIDTH < tp.y && tp.y < coinpos.y + TOUCH_WIDTH) {
		_coinMoveStart = coinpos;
		_coinTouchTimer = 0;
		_coinTouched = true;
	}
}
//=============================================================================
void TitleUnit::touchedMoved(CGPoint tp)
{
	static const int TOUCH_WIDTH = 32;
	if(_coinTouched)
	{
		Math::Vector3 coinpos = _coinModel->GetPosition();
		if( tp.y < coinpos.y - TOUCH_WIDTH || tp.y > coinpos.y + TOUCH_WIDTH ) {
			_coinSpeed = (_coinMoveEnd.x - _coinMoveStart.x) / _coinTouchTimer;
			_coinTouched = false; 
		}  else {
			_coinTouchTimer++;
			coinpos.x = tp.x;
			_coinModel->SetPosition(coinpos);
		}
	}
}
//=============================================================================
void TitleUnit::touchedEnded(CGPoint tp)
{
	if(_coinTouched) {
		_coinMoveEnd = _coinModel->GetPosition();
		_coinSpeed = (_coinMoveEnd.x - _coinMoveStart.x) / _coinTouchTimer;
		_coinTouched = false;
	}

	LOGI("coinMoveEnd=%3.3f, %3.3f, %3.3f, tp=%3.3f, %3.3f", _coinMoveEnd.x, _coinMoveEnd.y, _coinMoveEnd.z, tp.x, tp.y);
}
