//! @file 		UI_GameMain.cpp
//! @author 	Keita Tanji
//! @breif		
#include "UI_GameMain.h"
#include "pch.h"
#include "Classes/Graphics/2D/Draw.h"
using namespace UserInterface;


//=============================================================================
UI_GameMain::UI_GameMain()
{}
//=============================================================================
UI_GameMain::~UI_GameMain()
{}
//=============================================================================
/*static*/ Graphics::Model* UI_GameMain::makeCoinModel(const char* imageFileName, int divine)
{
#define COIN_MODEL_HEIGHT	0.1f
#define COIN_TEX_SIZE 		1.0f
	unsigned int size = divine * 3 * 4;
	Graphics::Model::VERTEX		vtx[size];
		for (int i=0; i < divine; i++) {
		vtx[i * 3 + 0].x = vtx[i * 3 + 2 + divine * 3].x = sinf(i * 2 * PI / divine);
		vtx[i * 3 + 0].y = vtx[i * 3 + 2 + divine * 3].y = cosf(i * 2 * PI / divine);
		vtx[i * 3 + 2].x = vtx[i * 3 + 0 + divine * 3].x = sinf((i + 1) * 2 * PI / divine);
		vtx[i * 3 + 2].y = vtx[i * 3 + 0 + divine * 3].y = cosf((i + 1) * 2 * PI / divine);
		vtx[i * 3 + 1].x = vtx[i * 3 + 1].y = vtx[i * 3 + 1 + divine * 3].x = vtx[i * 3 + 1 + divine * 3].y = 0;
		vtx[i * 3 + 0].z = vtx[i * 3 + 1].z = vtx[i * 3 + 2].z = COIN_MODEL_HEIGHT;
		vtx[i * 3 + 0 + divine * 3].z = vtx[i * 3 + 1 + divine * 3].z = vtx[i * 3 + 2 + divine * 3].z =-COIN_MODEL_HEIGHT;
        
		vtx[i * 3 + 0].u = vtx[i * 3 + 2 + divine * 3].u = vtx[i * 3 + 0].x / 2 + 0.5f;
		vtx[i * 3 + 0].v = vtx[i * 3 + 2 + divine * 3].v = vtx[i * 3 + 0].y / 2 + 0.5f;
		vtx[i * 3 + 2].u = vtx[i * 3 + 0 + divine * 3].u = vtx[i * 3 + 2].x / 2 + 0.5f;
		vtx[i * 3 + 2].v = vtx[i * 3 + 0 + divine * 3].v = vtx[i * 3 + 2].y / 2 + 0.5f;
		vtx[i * 3 + 1].u = vtx[i * 3 + 1 + divine * 3].u = 0.5f;
		vtx[i * 3 + 1].v = vtx[i * 3 + 1 + divine * 3].v = 0.5f;
		
		vtx[i * 6 + 0 + divine * 6].x = vtx[i * 6 + 2 + divine * 6].x = vtx[i * 6 + 4 + divine * 6].x = sinf(i * 2 * PI / divine);
		vtx[i * 6 + 0 + divine * 6].y = vtx[i * 6 + 2 + divine * 6].y = vtx[i * 6 + 4 + divine * 6].y = cosf(i * 2 * PI / divine);
		vtx[i * 6 + 1 + divine * 6].x = vtx[i * 6 + 3 + divine * 6].x = vtx[i * 6 + 5 + divine * 6].x = sinf((i + 1) * 2 * PI / divine);
		vtx[i * 6 + 1 + divine * 6].y = vtx[i * 6 + 3 + divine * 6].y = vtx[i * 6 + 5 + divine * 6].y = cosf((i + 1) * 2 * PI / divine);
		vtx[i * 6 + 0 + divine * 6].z = vtx[i * 6 + 4 + divine * 6].z = vtx[i * 6 + 5 + divine * 6].z =-COIN_MODEL_HEIGHT;
		vtx[i * 6 + 1 + divine * 6].z = vtx[i * 6 + 2 + divine * 6].z = vtx[i * 6 + 3 + divine * 6].z = COIN_MODEL_HEIGHT;
		vtx[i * 6 + 0 + divine * 6].u = vtx[i * 6 + 4 + divine * 6].u = 0;
		vtx[i * 6 + 0 + divine * 6].v = vtx[i * 6 + 4 + divine * 6].v = 0;
		vtx[i * 6 + 2 + divine * 6].u = 0.1f;
		vtx[i * 6 + 2 + divine * 6].v = 0;
		vtx[i * 6 + 1 + divine * 6].u = vtx[i * 6 + 3 + divine * 6].u = 0.1f;
		vtx[i * 6 + 1 + divine * 6].v = vtx[i * 6 + 3 + divine * 6].v = 0.1f;
		vtx[i * 6 + 2 + divine * 6].u = 0;
		vtx[i * 6 + 2 + divine * 6].v = 0.1f;
	}

	for (int i=0;i<size;i++) {
		vtx[i].r = vtx[i].g = vtx[i].b = vtx[i].a = 0xff;
	}
	
    Graphics::Model *output = new Graphics::Model();
	output->SetVertexBuffer(vtx, size);
	output->SetTexture(imageFileName);
    return output;
}

// ---------------------------------
// UI_GameMain::BackGround
// ---------------------------------
//=============================================================================
#define UI_GAMEMAIN_BACKGROUND_SCALEBASE	15.0f
UI_GameMain::BackGround::BackGround()
: _sprite0(NULL)
, _sprite1(NULL)
, _orientation(ORIENTATION_PORTRAIT_UP)
, _pos(Math::Vector2(0,0))
, _sclframe(0)
, _scl(UI_GAMEMAIN_BACKGROUND_SCALEBASE)
{
	_sprite0 = new Sprite("point.png", 32, 32);
	_sprite1 = new Sprite("point.png", 32, 32);

	_sprite0->setColor(255, 255, 255, 80);
	_sprite1->setColor(193, 236, 245, 255);
}
//=============================================================================
/*virtual*/ UI_GameMain::BackGround::~BackGround()
{
	SAFE_DELETE(_sprite0);
	SAFE_DELETE(_sprite1);
}
//=============================================================================
void UI_GameMain::BackGround::calc()
{
#define UI_GAMEMAIN_BACKGROUND_CALC_FRAMEPLUS	0.01f
#define UI_GAMEMAIN_BACKGROUND_CALC_SCALEPLUS	5.0f
	static const int DOT_MOVE_INTERVAL = 64 * Screen::RATIO;
	//使ってなさそう
	_pos += Math::Vector2(-1, -0.5f);
	if (_pos.x < -DOT_MOVE_INTERVAL) _pos.x += DOT_MOVE_INTERVAL;
	if (_pos.y < -DOT_MOVE_INTERVAL) _pos.y += DOT_MOVE_INTERVAL;
	_sclframe += UI_GAMEMAIN_BACKGROUND_CALC_FRAMEPLUS;
	if(_sclframe > PI * 2) _sclframe -= PI * 2;
	_scl = UI_GAMEMAIN_BACKGROUND_SCALEBASE + UI_GAMEMAIN_BACKGROUND_CALC_SCALEPLUS * sinf(_sclframe);

	//LOGI("BackGround::pos.x = %3.3f, pos.y = %3.3f", _pos.x, _pos.y );
}
//=============================================================================
void UI_GameMain::BackGround::draw()
{
	int width, height;
	switch(_orientation) {
		case ORIENTATION_PORTRAIT_UP:
		case ORIENTATION_PORTRAIT_DOWN:
			width  = Screen::WIDTH;
			height = Screen::HEIGHT;
			break;
		case ORIENTATION_LANDSCAPE_LEFT:
		case ORIENTATION_LANDSCAPE_RIGHT:
			width  = Screen::HEIGHT;
			height = Screen::WIDTH;
			break;
	}

	Draw::singleton()->setColor(255, 255, 255, 255);
	Draw::singleton()->setColorWithSide(DrawColorSideLeftBottom, 45, 158, 216, 255);
	Draw::singleton()->setColorWithSide(DrawColorSideRightBottom, 45, 158, 216, 255);
	Draw::singleton()->drawBox(0, 0, width, height);

	//解像度吸収定数定義
	static const int DOT_HEIGHT_MAX = height + 30 * Screen::RATIO;
	static const int DOT_HEIGHT_INTERVAL = 32 * Screen::RATIO;
	static const int DOT_WIDTH_MAX = width + 30 * Screen::RATIO;
	static const int DOT_WIDTH_INTERVAL = 32 * Screen::RATIO;
	static const int DOT_SIZE_X = 20 * Screen::RATIO;
	static const int DOT_SIZE_Y = 20 * Screen::RATIO;
	//dotをまばらに描く
	int ycount = 0;
	for(int y=(int)_pos.y; y < DOT_HEIGHT_MAX; y+=DOT_HEIGHT_INTERVAL){
		int xcount = ycount%2;
		for(int x = (int)_pos.x; x < DOT_WIDTH_MAX; x+=DOT_WIDTH_INTERVAL){
			_sprite0->drawWithFrame(0, x, y, DOT_SIZE_X, DOT_SIZE_Y);
			xcount++;
		}
	}
}