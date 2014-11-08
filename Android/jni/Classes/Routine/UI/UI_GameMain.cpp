//! @file 		UI_GameMain.cpp
//! @author 	Keita Tanji
//! @breif		
#include "UI_GameMain.h"
#include "Classes/Graphics/GraphicsBase.h"
#include "Classes/Graphics/2D/Draw.h"
#include "Classes/Graphics/2D/Text.h"
using namespace UserInterface;

/*static*/ int UI_GameMain::STAGE_WIDTH = 0;
/*static*/ int UI_GameMain::STAGE_VERTICAL_OFFSET_X = 0;
/*static*/ int UI_GameMain::STAGE_VERTICAL_OFFSET_Y = 0;
/*static*/ int UI_GameMain::STAGE_HORIZON_OFFSET_X = 0;
/*static*/ int UI_GameMain::STAGE_HORIZON_OFFSET_Y = 0;

//=============================================================================
/*static*/ void UI_GameMain::onDecideScreenRatio(int ratio)
{
	STAGE_WIDTH = 280 * ratio;
	STAGE_VERTICAL_OFFSET_X = 20 * ratio;
	STAGE_VERTICAL_OFFSET_Y = 100 * ratio;
	STAGE_HORIZON_OFFSET_X = 100 * ratio;
	STAGE_HORIZON_OFFSET_Y = 40 * ratio;

	Coin::onDecideScreenRatio(ratio);
	Dialog::onDecideScreenRatio(ratio);
}

/*static*/ int UI_GameMain::Coin::Width = 0;
//=============================================================================
/*static*/ void UI_GameMain::Coin::onDecideScreenRatio(int ratio)
{
	Width = 35 * ratio;
}

//=============================================================================
UI_GameMain::UI_GameMain()
: _time(0)
, _limitTime(0)
, _score(0)
, _bestScore(0)
, _bg()
, _pipe_portrait(NULL)
, _pipe_portrait_back(NULL) 
, _pipe_landscape(NULL)
, _pipe_landscape_back(NULL)
, _orientation(ORIENTATION_PORTRAIT_UP)
, _path_horizon()
, _path_vertical()
, _miniNumber()
, _miniPaper()
, _newRecord_prog(-1.0f)
, _score_spr(0)
, _best_spr(0)
, _newRecord_spr(0)
, _spr_timebar(0)
{
	_coins.clear();

	const int R = Screen::RATIO;
	_path_horizon << Math::Vector2(125*R, -35*R) << Math::Vector2(125*R, 8*R) << Math::Vector2(285*R, 8*R) << Math::Vector2(285*R, 58*R) << Math::Vector2(125*R, 58*R);
	_path_vertical << Math::Vector2(445*R, -35*R) << Math::Vector2(445*R, 70*R) << Math::Vector2(405*R, 70*R) << Math::Vector2(405*R, 0*R) << Math::Vector2(205*R, 0*R);
}
//=============================================================================
UI_GameMain::~UI_GameMain()
{
	term();
}
//=============================================================================
void UI_GameMain::init()
{
	_score = 0;
	_time = 0;
    _bestScore = 0;

	_pipe_portrait = new Sprite("PIPE_Portrait.png", 70, 70);
	_pipe_landscape = new Sprite("PIPE_LandScape.png", 70, 70);
	_pipe_portrait_back = new Sprite("PIPE_Portrait_Back.png", 70, 70);
	_pipe_landscape_back = new Sprite("PIPE_LandScape_Back.png", 70, 70);
	_score_spr = new Sprite("Score.png", 64, 85);
    _best_spr = new Sprite("best.png", 128, 32);
	_newRecord_spr = new Sprite(_best_spr);
    _spr_timebar = new Sprite("timebar.png", 32, 256);
	
	_coinModels[Coin::Type_1yen] = makeCoinModel("1.png");
	_coinModels[Coin::Type_5yen] = makeCoinModel("5.png");
	_coinModels[Coin::Type_10yen] = makeCoinModel("10.png");
	_coinModels[Coin::Type_50yen] = makeCoinModel("50.png");
	_coinModels[Coin::Type_100yen] = makeCoinModel("100.png");
	_coinModels[Coin::Type_500yen] = makeCoinModel("500.png");
    
    _dialog.setNewRecord(false);
}
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
//=============================================================================
void UI_GameMain::calc()
{
#define BLOCK_REWIND_SPEED      0.1f
#define NEWRECORD_INC           0.01f
	
    _bg.calc();
	_dialog.calc();
    _miniNumber.calc();
    _miniPaper.calc();
    Coin *readyPrev = 0;
    if (_newRecord_prog >= 0.0f && _newRecord_prog < 2.0f) {
        _newRecord_prog += NEWRECORD_INC;
    }
	if(!_dialog.isVisible())
	for (int i=0;i<_coins.size();i++)
	{
		_coins[i]->calc();
		if (_coins[i]->getState() == Coin::STATE_READY) {
			if (readyPrev) {
				if(readyPrev->getProgress() - _coins[i]->getProgress() < BlockProgressUnit)
					_coins[i]->setProgress(_coins[i]->getProgress() - BlockProgressUnit * BLOCK_REWIND_SPEED);
			} else readyPrev = _coins[i];
		} else if (_coins[i]->getState() == Coin::STATE_END) {
			delete _coins[i];
			_coins.erase(_coins.begin() + i);
			i--;
		}
	}
}
//=============================================================================
void UI_GameMain::draw(bool noTime)
{
	const int R = Screen::RATIO;

	_bg.draw();
	LinearPath *path = 0;
	Math::Vector2 offset;
	switch (_orientation) {
		case ORIENTATION_PORTRAIT_UP:
		case ORIENTATION_PORTRAIT_DOWN:
			offset.x = UI_GameMain::STAGE_VERTICAL_OFFSET_X;
			offset.y = UI_GameMain::STAGE_VERTICAL_OFFSET_Y;
			path = &_path_horizon;
			break;
		case ORIENTATION_LANDSCAPE_LEFT:
		case ORIENTATION_LANDSCAPE_RIGHT:
			offset.x = UI_GameMain::STAGE_HORIZON_OFFSET_X;
			offset.y = UI_GameMain::STAGE_HORIZON_OFFSET_Y;
			path = &_path_vertical;
			break;
	}
	
	// Draw Pipe
	const int PBW = 280 * Screen::RATIO;	//Pipe Base Width
	const int PBH = 280 * Screen::RATIO;	//Pipe Base Height
	// const int POX = 20 * Screen::RATIO;
	// const int POY = 

	switch (_orientation) {
		case ORIENTATION_PORTRAIT_UP:
		case ORIENTATION_PORTRAIT_DOWN:
		{
			// draw Background
			Draw::singleton()->setColor(0, 0, 0, 179);
			Draw::singleton()->drawBox(offset.x, offset.y, PBW, PBH);
			
			Graphics::ClearDisplayBuffer(Graphics::DisplayClearModeZBuffer);
			
			// draw Time
            if (!noTime) {
                _score_spr->drawWithFrame(11, (offset.x-20*R), (offset.y-25*R), 20*R, 27*R);
                if (_limitTime <= 0) _limitTime = 60;
                _spr_timebar->setColor(255, 255, 255, 255);
                _spr_timebar->drawImage( (offset.x-20*R), (offset.y+280*R) - (_time * 280*R / _limitTime), 
                                       20*R, (_time * 280 * R / _limitTime),
                                     CGPoint(0, (float)(_limitTime-_time)/_limitTime), CGPoint(1, 1));
                Draw::singleton()->setColor(0, 0, 0, 255);
                Draw::singleton()->drawLine( (offset.x-20*R), (offset.y+1*R), (offset.x-20*R), (offset.y+279*R) );
                Draw::singleton()->drawLine( (offset.x) , (offset.y+1*R), (offset.x), (offset.y+279*R) );
                Draw::singleton()->drawLine( (offset.x-20*R), (offset.y+1*R), (offset.x), (offset.y+1*R) );
                Draw::singleton()->drawLine( (offset.x-20*R), (offset.y+279*R), (offset.x), (offset.y+279*R) );
            }
            
			const int NEWRECORD_OFFSET_Y             = 27 * R;
			const int PORTRAIT_SCORE_WIDTH           = 30 * R;
			const int PORTRAIT_SCORE_HEIGHT          = 30 * R;
			const int PORTRAIT_BEST_SCORE_HEIGHT     = 70 * R;
			const int SCORE_W = 16 * R;
			const int SCORE_H = 21 * R;
			// draw Score
			_score_spr->drawWithFrame( 10, PORTRAIT_SCORE_WIDTH, PORTRAIT_SCORE_HEIGHT, SCORE_W, SCORE_H);
			for (int i=0;i<7;i++)
			{
				_score_spr->drawWithFrame( ((_score / ((int)pow(10.0, i))) % 10), (30*R+(7-i)*11*R), PORTRAIT_SCORE_HEIGHT, SCORE_W, SCORE_H);
			}
			
            // draw Best Score
			_score_spr->drawWithFrame( 10, PORTRAIT_SCORE_WIDTH, PORTRAIT_BEST_SCORE_HEIGHT, SCORE_W, SCORE_H);
			for (int i=0;i<7;i++)
			{
				_score_spr->drawWithFrame( ((_bestScore / ((int)pow(10.0, i))) % 10), (30*R+(7-i)*11*R), PORTRAIT_BEST_SCORE_HEIGHT, SCORE_W, SCORE_H);
			}
            _best_spr->drawWithFrame( 0, 0, PORTRAIT_BEST_SCORE_HEIGHT-10*R, 50*R, 13*R);
            
            // draw New Record
            if (_newRecord_spr && _newRecord_prog > 0.0f && _newRecord_prog < 1.0f) {
                // Draw Hint
                Graphics::SetWriteColorMask(Graphics::WriteColorMaskNone);
                Graphics::SetStencilWriteMode(Graphics::StencilFlagUI);
                Draw::singleton()->drawBox( 40*R, PORTRAIT_BEST_SCORE_HEIGHT, 77*R, 21*R);
                
                Graphics::SetStencilWriteMode(Graphics::StencilFlagNone);
                Graphics::SetWriteColorMask(Graphics::WriteColorMaskAll);
                Graphics::SetStencilFilter(Graphics::StencilFlagUI);

                float y_pos = (pow((_newRecord_prog*2-1), 3.0f)+1.0f)/2.0f;
                _newRecord_spr->drawWithFrame( 1, 40*R, PORTRAIT_BEST_SCORE_HEIGHT+NEWRECORD_OFFSET_Y-y_pos*50*R, 77*R, 20*R);

                Graphics::SetStencilFilter(Graphics::StencilFlagNone);
            }
            
			if (_pipe_portrait_back)
			{
				_pipe_portrait_back->drawWithFrame( 0,  125 * R, 0  * R, 35  * R, 8 * R);
				_pipe_portrait_back->drawWithFrame( 8,  125 * R, 0  * R, 35  * R, 8 * R);
				_pipe_portrait_back->drawWithFrame( 3,  125 * R, 8  * R, 35  * R, 35 * R);
				_pipe_portrait_back->drawWithFrame( 6,  160 * R, 8  * R, 125 * R, 35 * R);
				_pipe_portrait_back->drawWithFrame( 4,  285 * R, 8  * R, 35  * R, 35 * R);
				_pipe_portrait_back->drawWithFrame( 7,  285 * R, 43 * R, 35  * R, 35 * R);
				_pipe_portrait_back->drawWithFrame( 5,  285 * R, 78 * R, 35  * R, 35 * R);
				_pipe_portrait_back->drawWithFrame( 6,  195 * R, 58 * R, (285-195) * R, 35 * R);
				_pipe_portrait_back->drawWithFrame( 1,  125 * R, 58 * R, 35 * R, 35 * R);
				_pipe_portrait_back->drawWithFrame( 2,  160 * R, 58 * R, 35 * R, 35 * R);
				_pipe_portrait_back->drawImage( 125 * R, 93 * R, 70 * R, 7 * R, CGPoint(0, 210.0f/256.0f), CGPoint(140.0f/256.0f, 217.0f/256.0f) );
			} 

			// draw Coins
			LOGI("UI_GameMain, drawcoins size=%d", _coins.size());
			for (int i=0;i<_coins.size();i++) { 
				switch (_coins[i]->getState()) {
					case Coin::STATE_READY: {
						_coins[i]->drawWithPosition(path->getPosition(_coins[i]->getProgress()), _orientation);
					} break;
					case Coin::STATE_FALL:
					case Coin::STATE_CLEAR:
					case Coin::STATE_UNION:
					case Coin::STATE_OVER_FALL:
						_coins[i]->drawWithOffset(offset, _orientation);
						break;
				}
			}
			
			if (_pipe_portrait)
			{
				_pipe_portrait->drawWithFrame( 0, 125 * R, 0  * R, 35  * R, 8 * R);
				_pipe_portrait->drawWithFrame( 8, 125 * R, 0  * R, 35  * R, 8 * R);
				_pipe_portrait->drawWithFrame( 3, 125 * R, 8  * R, 35  * R, 35 * R);
				_pipe_portrait->drawWithFrame( 6, 160 * R, 8  * R, 125 * R, 35 * R);
				_pipe_portrait->drawWithFrame( 4, 285 * R, 8  * R, 35  * R, 35 * R);
				_pipe_portrait->drawWithFrame( 7, 285 * R, 43 * R, 35  * R, 35 * R);
				_pipe_portrait->drawWithFrame( 5, 285 * R, 78 * R, 35  * R, 35 * R);
				_pipe_portrait->drawWithFrame( 6, 195 * R, 58 * R, (285-195) * R, 35 * R);
				_pipe_portrait->drawWithFrame( 1, 125 * R, 58 * R, 35 * R, 35 * R);
				_pipe_portrait->drawWithFrame( 2, 160 * R, 58 * R, 35 * R, 35 * R);
				_pipe_portrait->drawImage( 125*R, 93*R, 70*R, 7*R, CGPoint(0, 210.0f/256.0f), CGPoint(140.0f/256.0f, 217.0f/256.0f) );
			} 
			break;
		}
		case ORIENTATION_LANDSCAPE_LEFT:
		case ORIENTATION_LANDSCAPE_RIGHT:
			/* @TODO
			// draw Background
			[[Draw singleton] setColorWithRed:0 Green:0 Blue:0 Alpha:179];
			[[Draw singleton] drawBox_x:offset.x y:offset.y width:280 height:280];
			
			// draw Time
            if (!noTime) {
                [_score_spr drawWithFrame:11 x:(offset.x-20) y:(offset.y-25) width:20 height:27];
                if (_limitTime <= 0) _limitTime = 60;
                [_spr_timebar setColorWithRed:255 Green:255 Blue:255 Alpha:255];
                [_spr_timebar drawImageWithX:(offset.x-20) Y:(offset.y+280) - (_time * 280 / _limitTime) 
                                       Width:20 Height:(_time * 280 / _limitTime)
                                     LeftTop:CGPointMake(0, (float)(_limitTime-_time)/_limitTime) RightDown:CGPointMake(1, 1)];
                [[Draw singleton] setColorWithRed:0 Green:0 Blue:0 Alpha:255];
                [[Draw singleton] drawLine_x1:(offset.x-20) y1:(offset.y+1) x2:(offset.x-20)  y2:(offset.y+279)];
                [[Draw singleton] drawLine_x1:(offset.x)  y1:(offset.y+1) x2:(offset.x)   y2:(offset.y+279)];
                [[Draw singleton] drawLine_x1:(offset.x-20) y1:(offset.y+1) x2:(offset.x)   y2:(offset.y+1)];
                [[Draw singleton] drawLine_x1:(offset.x-20) y1:(offset.y+279) x2:(offset.x) y2:(offset.y+279)];
            }
			
#define LANDSCAPE_SCORE_HEIGHT          150
#define LANDSCAPE_BEST_SCORE_HEIGHT     200
			// draw Score
			[_score_spr drawWithFrame:10 x:390 y:LANDSCAPE_SCORE_HEIGHT width:16 height:21];
			for (int i=0;i<7;i++)
			{
				[_score_spr drawWithFrame:((_score / ((int)pow(10, i))) % 10) x:(390+(7-i)*11) y:LANDSCAPE_SCORE_HEIGHT width:16 height:21];
			}
			
            // draw Best Score
			[_score_spr drawWithFrame:10 x:390 y:LANDSCAPE_BEST_SCORE_HEIGHT width:16 height:21];
			for (int i=0;i<7;i++)
			{
				[_score_spr drawWithFrame:((_bestScore / ((int)pow(10, i))) % 10) x:(390+(7-i)*11) y:LANDSCAPE_BEST_SCORE_HEIGHT width:16 height:21];
			}
            [_best_spr drawWithFrame:0 x:380 y:LANDSCAPE_BEST_SCORE_HEIGHT-10 width:50 height:13];            
            
            // draw New Record
            if (_newRecord_spr && _newRecord_prog > 0.0f && _newRecord_prog < 1.0f) {
                // Draw Hint
                Graphics::SetWriteColorMask(Graphics::WriteColorMaskNone);
                Graphics::SetStencilWriteMode(Graphics::StencilFlagUI);
                [[Draw singleton] drawBox_x:400 y:LANDSCAPE_BEST_SCORE_HEIGHT width:77 height:21];
                
                Graphics::SetStencilWriteMode(Graphics::StencilFlagNone);
                Graphics::SetWriteColorMask(Graphics::WriteColorMaskAll);
                Graphics::SetStencilFilter(Graphics::StencilFlagUI);
                
                float y_pos = (pow((_newRecord_prog*2-1), 3.0f)+1.0f)/2.0f;
                [_newRecord_spr drawWithFrame:1 x:400 y:LANDSCAPE_BEST_SCORE_HEIGHT+NEWRECORD_OFFSET_Y-y_pos*50 width:77 height:20];
                
                Graphics::SetStencilFilter(Graphics::StencilFlagNone);
            }
            
			if (_pipe_landscape_back)
			{
				[_pipe_landscape_back drawWithFrame:2 x:445 y:0    width:35  height:70];
				[_pipe_landscape_back drawWithFrame:1 x:445 y:70   width:35  height:35];
				[_pipe_landscape_back drawWithFrame:4 x:440 y:70   width:5   height:35];
				[_pipe_landscape_back drawWithFrame:0 x:405 y:70   width:35  height:35];
				[_pipe_landscape_back drawWithFrame:2 x:405 y:35   width:35  height:35];
				[_pipe_landscape_back drawWithFrame:5 x:405 y:0    width:35  height:35];
				[_pipe_landscape_back drawWithFrame:4 x:275 y:0    width:130 height:35];
				[_pipe_landscape_back drawWithFrame:8 x:240 y:0    width:35  height:35];
				[_pipe_landscape_back drawWithFrame:7 x:205 y:0    width:35  height:35];
				[_pipe_landscape_back drawImageWithX:205 Y:35 Width:70 Height:5 LeftTop:CGPointMake(0, 210.0f/256.0f) RightDown:CGPointMake(140.0f/256.0f, 215.0f/256.0f)];
			}

			// draw Coins
			for (int i=0;i<_coins.size();i++) { 
				switch (_coins[i]->getState()) {
					case Coin::STATE_READY: {
						_coins[i]->drawWithPosition(path->getPosition(_coins[i]->getProgress()), _orientation);
					} break;
					case Coin::STATE_FALL:
					case Coin::STATE_CLEAR:
					case Coin::STATE_UNION:
					case Coin::STATE_OVER_FALL:
						_coins[i]->drawWithOffset(offset, _orientation);
						break;
				}
			}
			
			if (_pipe_landscape)
			{
				[_pipe_landscape drawWithFrame:2 x:445 y:0    width:35  height:70];
				[_pipe_landscape drawWithFrame:1 x:445 y:70   width:35  height:35];
				[_pipe_landscape drawWithFrame:4 x:440 y:70   width:5   height:35];
				[_pipe_landscape drawWithFrame:0 x:405 y:70   width:35  height:35];
				[_pipe_landscape drawWithFrame:2 x:405 y:35   width:35  height:35];
				[_pipe_landscape drawWithFrame:5 x:405 y:0    width:35  height:35];
				[_pipe_landscape drawWithFrame:4 x:275 y:0    width:130 height:35];
				[_pipe_landscape drawWithFrame:8 x:240 y:0    width:35  height:35];
				[_pipe_landscape drawWithFrame:7 x:205 y:0    width:35  height:35];
				[_pipe_landscape drawImageWithX:205 Y:35 Width:70 Height:5 LeftTop:CGPointMake(0, 210.0f/256.0f) RightDown:CGPointMake(140.0f/256.0f, 215.0f/256.0f)];
			} 
			*/
			break;
	}
    _miniPaper.draw();
    _miniNumber.draw();	
	_dialog.draw(_orientation);
}

//=============================================================================
void UI_GameMain::term()
{
	SAFE_DELETE(_pipe_portrait);
	SAFE_DELETE(_pipe_landscape);
	SAFE_DELETE(_pipe_portrait_back);
	SAFE_DELETE(_pipe_landscape_back);
    SAFE_DELETE(_spr_timebar);
	SAFE_DELETE(_score_spr);
    SAFE_DELETE(_best_spr);
    SAFE_DELETE(_newRecord_spr);

	for (int i=0;i<_coins.size();i++) { SAFE_DELETE(_coins[i]); }
	_coins.clear();
	SAFE_DELETE(_coinModels[Coin::Type_1yen]);
	SAFE_DELETE(_coinModels[Coin::Type_5yen]);
	SAFE_DELETE(_coinModels[Coin::Type_10yen]);
	SAFE_DELETE(_coinModels[Coin::Type_50yen]);
	SAFE_DELETE(_coinModels[Coin::Type_100yen]);
	SAFE_DELETE(_coinModels[Coin::Type_500yen]);
	_coinModels.clear();
}
//=============================================================================
UI_GameMain::Coin* UI_GameMain::addCoin(Coin::TYPE t)
{
	UI_GameMain::Coin *c = new UI_GameMain::Coin(_coinModels[t], t);
	_coins.push_back(c);
	return c;
}
//=============================================================================
void UI_GameMain::removeCoin(Coin *c)
{
	for (int i=0;i<_coins.size();i++)
		if (_coins[i] == c) 
		{
			delete c;
			_coins.erase(_coins.begin() + i);
			break;
		}
}
//=============================================================================
void UI_GameMain::moveCoinFront(Coin *c)
{
	int i=0;
	for (i=0;i<_coins.size();i++)
		if (_coins[i] == c) 
		{
			_coins.erase(_coins.begin() + i);
			break;
		}
	bool inserted = false;
	for (i=0;i<_coins.size();i++)
		if (_coins[i]->getState() == Coin::STATE_READY) {
			_coins.insert(_coins.begin() + i, c);
            c->setProgress(1.0f);
			inserted = true;
			break;
		}
	if (!inserted) {
		_coins.push_back(c);
	}
}
//=============================================================================
void UI_GameMain::addScorePlus(unsigned int num, const Math::Vector2 &pos)
{
    Math::Vector2 offset;
    if (_orientation == ORIENTATION_PORTRAIT_UP || _orientation == ORIENTATION_PORTRAIT_DOWN) {
        offset.x = UI_GameMain::STAGE_VERTICAL_OFFSET_X;
        offset.y = UI_GameMain::STAGE_VERTICAL_OFFSET_Y;
    } else {
        offset.x = UI_GameMain::STAGE_HORIZON_OFFSET_X;
        offset.y = UI_GameMain::STAGE_HORIZON_OFFSET_Y;        
    }
    offset += pos;
    _miniNumber.addNumber(num, MiniNumber::ITEM_TYPE_POINT, offset, 90);
    if (num >= 1000) {
        _miniPaper.addPaper(offset);
    }
}
//=============================================================================
void UI_GameMain::addTimePlus(unsigned int num)
{ 
	const int R = Screen::RATIO;
    Math::Vector2 pos;
    if (_orientation == ORIENTATION_PORTRAIT_UP || _orientation == ORIENTATION_PORTRAIT_DOWN) {
        pos.x = UI_GameMain::STAGE_VERTICAL_OFFSET_X - 20 * R;
        pos.y = UI_GameMain::STAGE_VERTICAL_OFFSET_Y + 280 * R - (_time * 280 * R / _limitTime);    
    } else {
        pos.x = UI_GameMain::STAGE_HORIZON_OFFSET_X - 20 * R;
        pos.y = UI_GameMain::STAGE_HORIZON_OFFSET_Y + 280 * R - (_time * 280 * R / _limitTime);
    }
    _miniNumber.addNumber(num, MiniNumber::ITEM_TYPE_TIME, pos, 60);
}
//=============================================================================
bool UI_GameMain::isPauseTouched(CGPoint tp)
{
	const int R = Screen::RATIO;

	if (_orientation == ORIENTATION_PORTRAIT_UP || _orientation == ORIENTATION_PORTRAIT_DOWN)
		return ( 20*R < tp.x && tp.x < 100*R && 0 < tp.y && tp.y < 40*R );
	else return ( 100*R < tp.x && tp.x < 180*R && 0 < tp.y && tp.y < 40*R );
}
//=============================================================================
bool UI_GameMain::isEndPauseTouched(CGPoint tp)
{
	return _dialog.getTouchResult(tp, _orientation) == Dialog::DialogButtonResume;
}
//=============================================================================
bool UI_GameMain::isRetryTouched(CGPoint tp)
{
	return _dialog.getTouchResult(tp, _orientation) == Dialog::DialogButtonRetry;
}
//=============================================================================
bool UI_GameMain::isReturnToTitleTouched(CGPoint tp)
{
	return _dialog.getTouchResult(tp, _orientation) == Dialog::DialogButtonExit;
}

// ---------------------------------
// UI_GameMain::MiniNumber
// ---------------------------------
//=============================================================================
UI_GameMain::MiniNumber::MiniNumber()
: _itemCount(0)
, _sprite_time(0)
, _sprite_money(0)
{
    _sprite_time = new Sprite("Number32x40.png" ,32 ,40);
    _sprite_money = new Sprite("Number32x40_.png" ,32 ,40);
    memset(_items, 0, sizeof(ITEM) * ITEM_MAX);
    for(size_t i=0;i<ITEM_MAX;i++) {
        _spr_items_t[i] = new Sprite(_sprite_time);
        _spr_items_m[i] = new Sprite(_sprite_money);
    }
}
//=============================================================================
UI_GameMain::MiniNumber::~MiniNumber()
{
    for(size_t i=0;i<ITEM_MAX;i++) {
        SAFE_DELETE(_spr_items_m[i]);
        SAFE_DELETE(_spr_items_t[i]);
    }
    SAFE_DELETE(_sprite_time);
    SAFE_DELETE(_sprite_money);
}
//=============================================================================
void UI_GameMain::MiniNumber::addNumber(unsigned int n, unsigned int type, const Math::Vector2 &pos, unsigned int t)
{
    for(size_t i=0;i<ITEM_MAX;i++)
        if(_items[i].time <= 0)
        {
            _spr_items_m[i]->setColor(255,255,255,255);
            _spr_items_t[i]->setColor(255,255,255,255);
            _items[i].pos = pos;
            _items[i].type = type;
            _items[i].number = n;
            _items[i].time = t;
            _itemCount++;
            break;
        }
}
//=============================================================================
void UI_GameMain::MiniNumber::calc()
{
    size_t count = 0;
    for(size_t i=0;i<ITEM_MAX;i++){
        if(_items[i].time > 0)
        {
            _items[i].pos.y -= 0.3f * Screen::RATIO;
            _items[i].time--;
            count++;
            if(_itemCount == count) break;
        }
    }
}
//=============================================================================
void UI_GameMain::MiniNumber::draw()
{
	const int WIDTH = 12 * Screen::RATIO;
	const int HEIGHT = 21 * Screen::RATIO;

    size_t count = 0;
    for(size_t i=0;i<ITEM_MAX;i++) {
        if(_items[i].time > 0) {
            Sprite *spr = 0;
            switch (_items[i].type) {
                case ITEM_TYPE_POINT:
                    spr = _spr_items_m[i];
                    break;
                case ITEM_TYPE_TIME:
                    spr = _spr_items_t[i];
                    break;
            }
            if(_items[i].time < 30) {
                spr->setColor(255, 255, 255, _items[i].time*255/30);
            }
            if(_items[i].number > 0) {
                size_t dig = size_t(floor(log10((double)_items[i].number))) + 1;
                int start_x = (dig + 1) * 11 * Screen::RATIO;
                spr->drawWithFrame( 10, _items[i].pos.x, _items[i].pos.y, WIDTH, HEIGHT);
                for (int l=0;l<dig;l++)
                {
                    spr->drawWithFrame( ((_items[i].number / ((int)pow(10.0, l))) % 10), 
                    	_items[i].pos.x+start_x-(l+1)*11*Screen::RATIO, 
                    	_items[i].pos.y, 
                    	WIDTH, HEIGHT);
                }
            }
            count++;
            if(_itemCount == count) break;
        }
    }
}
// ---------------------------------
// UI_GameMain::MiniPaper
// ---------------------------------
//=============================================================================
UI_GameMain::MiniPaper::MiniPaper()
{
    _sprite = new Sprite("1000.png", 64, 64);
    for(size_t i=0;i<ITEM_MAX;i++)
    {
        _items[i].enabled = false;
    }
}
//=============================================================================
UI_GameMain::MiniPaper::~MiniPaper()
{
	SAFE_DELETE(_sprite);
}
//=============================================================================
void UI_GameMain::MiniPaper::addPaper(const Math::Vector2 &pos)
{
#define THROWPOWER_DEFAULT 3.f
    
    for(size_t i=0;i<ITEM_MAX;i++)
    if(!_items[i].enabled)
    {
        _items[i].enabled = true;
        _items[i].pos = pos;
        _items[i].throwPower = Math::Vector2(0, THROWPOWER_DEFAULT);
        _items[i].sinval = .0f;
        break;
    }
}
//=============================================================================
void UI_GameMain::MiniPaper::calc()
{
#define THROWPOWER_MINUS    -0.1f
#define THROWPOWER_LIMIT    -1.5f
#define COSVAL_PLUS 0.07f
    
    for(size_t i=0;i<ITEM_MAX;i++)
    if(_items[i].enabled)
    {
        _items[i].pos -= _items[i].throwPower;
        if(_items[i].throwPower.y > THROWPOWER_LIMIT)
            _items[i].throwPower += Math::Vector2(0, THROWPOWER_MINUS);
        else {
            _items[i].sinval += COSVAL_PLUS;
            if(_items[i].sinval > 2*PI) _items[i].sinval -= 2*PI;
        }
        if(_items[i].pos.y > 480 * Screen::RATIO) {
            _items[i].enabled = false;
        }
    }
}
//=============================================================================
void UI_GameMain::MiniPaper::draw()
{
	const int COSVAL_WIDTH  =  50 * Screen::RATIO;
    const int WIDTH = 32 * Screen::RATIO;
    const int HEIGHT = 32 * Screen::RATIO;

    for(size_t i=0;i<ITEM_MAX;i++)
    if(_items[i].enabled)
    {
        Math::Vector2 pos = _items[i].pos;
        pos.x += sinf(_items[i].sinval) * COSVAL_WIDTH;
        _sprite->drawWithFrame(0, pos.x, pos.y, WIDTH, HEIGHT);
    }
}

// ---------------------------------
// UI_GameMain::Coin
// ---------------------------------
UI_GameMain::Coin::Coin(Graphics::Model *m, TYPE type)
: _model(m), _pos(0), _rot(), _dir()
, _state(STATE_READY), _progress(0), _shake(false)
, _shakeFlag(0), _popScale(0)
, _shineEffect(0), _posorg(0, 0), _waitFrame(0)
, _type(type)
{
}

//=============================================================================
void UI_GameMain::Coin::setState(int s)
{
	_state = s;
	_progress = 0.0f;
	
	switch (_state) {
		case STATE_UNION:
			_posorg = *_pos;
			_pos = &_posorg;
			_dir = Math::Vector2(Width * 3, -Width) - _posorg;
			_dir.normalize();
			_dir *= UnionSpeed;
			break;
		case STATE_CLEAR:
			_posorg = *_pos;
			_pos = &_posorg;
			_dir = Math::Vector2(rand()%10-5, -(rand()%10+10));
			break;
		case STATE_OVER_FALL:
			_dir = Math::Vector2(0, 0);
			break;
	}
}

//=============================================================================
void UI_GameMain::Coin::calc()
{
#define COIN_ROTATE_Y_CLEAR			20.0f
#define COIN_ROTATE_Y_UNION			6.0f
// #define POPRCVSPD					0.5f
	const float POPRCVSPD = 0.5f * Screen::RATIO;
	const int Y_MAX = 480 * Screen::RATIO;

	if (_waitFrame > 0) {
		_waitFrame--;
		return;
	}
	
	if (_popScale > 0){
		_popScale -= POPRCVSPD;
		if (_popScale < 0) _popScale = 0;
	}
	
	switch (_state) {
		case STATE_CLEAR:
			*_pos += _dir;
			_rot.y += COIN_ROTATE_Y_CLEAR;
			if (_rot.y > 360.0f) _rot.y -= 360.0f;
			_dir.y += GForce;
			if (_pos->y > Y_MAX) setState(STATE_END);
			break;
		case STATE_UNION:
			*_pos += _dir;
			_rot.y += COIN_ROTATE_Y_UNION;
			if (_rot.y > 360.0f) _rot.y -= 360.0f;
			if ((*_pos - Math::Vector2(Width * 3, -Width)).length() < UnionSpeed * 2.0f) setState(STATE_END);
			break;
		case STATE_OVER_FALL:
			*_pos += _dir;
			_dir.y += GForce;
			if (_pos->y > Y_MAX) setState(STATE_END);			
			break;
	}
}

//=============================================================================
void UI_GameMain::Coin::drawWithPosition(const Math::Vector2 &position, int orientation)
{
	const float POS_OFFSET = 17.5f * Screen::RATIO;
	const float SCALE_OFFSET = 17.5f * Screen::RATIO;

	float rot_z = 0;
	switch (orientation) {
		case ORIENTATION_PORTRAIT_UP:
			break;
		case ORIENTATION_PORTRAIT_DOWN:
			rot_z = 180.0f;
			break;
		case ORIENTATION_LANDSCAPE_LEFT:
			rot_z = 90.0f;
			break;
		case ORIENTATION_LANDSCAPE_RIGHT:
			rot_z =-90.0f;
			break;
	}
	
	if (_state == STATE_READY) {
		float rot_len = 0.0f;
		if (!_progress) {
			_posorg = position;
			_rolldir = 0;
		} else {
			Math::Vector2 p = position - _posorg;
			_posorg = position;
			rot_len = p.length();
			_rolldir = (p.x > 0)?(1):(-1);
		}
		_rot.z += _rolldir * rot_len * 4.0f;
	}
	Math::Vector3 pos(position.x + POS_OFFSET, position.y + POS_OFFSET, 0);
	Math::Vector3 scl(SCALE_OFFSET, SCALE_OFFSET, SCALE_OFFSET);
	Math::Vector3 rot(_rot.x, _rot.y, _rot.z + rot_z);
	if (_shineEffect) {
		// if (Graphics::EffectManager::getInstance()->isFinishedEffect(_shineEffect)) {
		// 	_shineEffect = 0;
		// } else {
		// 	Graphics::EffectManager::getInstance()->setEffectParameter(_shineEffect, Graphics::Effect_ShineModel::PARAM_POSITION, &pos);
		// 	Graphics::EffectManager::getInstance()->setEffectParameter(_shineEffect, Graphics::Effect_ShineModel::PARAM_SCALE, &scl);
		// }
	}									
	
	LOGI("Coin::drawWithPosition, coin=%d, pos=(%3.1f, %3.1f, %3.1f)", _type, pos.x, pos.y, pos.z);

	_model->SetRotation(rot);
	_model->SetScale(scl);
	_model->SetPosition(pos);
	_model->Draw();
}

//=============================================================================
void UI_GameMain::Coin::drawWithOffset(const Math::Vector2 &offset, int orientation)
{	
	const float POS_OFFSET = 17.5f * Screen::RATIO;
	const float SCALE_OFFSET = 17.5f * Screen::RATIO;

	float rot_z = 0;
	switch (orientation) {
		case ORIENTATION_PORTRAIT_UP:
			break;
		case ORIENTATION_PORTRAIT_DOWN:
			rot_z = 180.0f;
			break;
		case ORIENTATION_LANDSCAPE_LEFT:
			rot_z = 90.0f;
			break;
		case ORIENTATION_LANDSCAPE_RIGHT:
			rot_z =-90.0f;
			break;
	}

	Math::Vector3 pos(_pos->x + offset.x + POS_OFFSET, _pos->y + offset.y + POS_OFFSET, 0);
	Math::Vector3 scl(SCALE_OFFSET + _popScale, SCALE_OFFSET + _popScale, SCALE_OFFSET + _popScale);
	Math::Vector3 shakeVec;
	if (_shake){
		pos += Math::Vector3(_shakeFlag/2-4, 0, 0);
		_shakeFlag = (++_shakeFlag)%9;
	}
	if (_shineEffect) {
		// if (Graphics::EffectManager::getInstance()->isFinishedEffect(_shineEffect)) {
		// 	_shineEffect = 0;
		// } else {
		// 	Graphics::EffectManager::getInstance()->setEffectParameter(_shineEffect, Graphics::Effect_ShineModel::PARAM_POSITION, &pos);
		// 	Graphics::EffectManager::getInstance()->setEffectParameter(_shineEffect, Graphics::Effect_ShineModel::PARAM_SCALE, &scl);
		// }
	}

	LOGI("Coin::drawWithOffset, coin=%d, pos=(%3.1f, %3.1f, %3.1f)", _type, pos.x, pos.y, pos.z);

	Math::Vector3 rot(_rot.x, _rot.y, _rot.z + rot_z);
	_model->SetRotation(rot);
	_model->SetScale(scl);
	_model->SetPosition(pos);
	_model->Draw();
}

//=============================================================================
void UI_GameMain::Coin::shineEffectOn()
{
	// _shineEffect = Graphics::EffectManager::getInstance()->generateEffect(EffectID_ShineModel);
	// int duration = 30, duration_max = 30;
	// Graphics::EffectManager::getInstance()->setEffectParameter(_shineEffect, Graphics::Effect_ShineModel::PARAM_DURATION, &duration);
	// Graphics::EffectManager::getInstance()->setEffectParameter(_shineEffect, Graphics::Effect_ShineModel::PARAM_DURATION_MAX, &duration_max);
	// if (_model) Graphics::EffectManager::getInstance()->setEffectParameter(_shineEffect, Graphics::Effect_ShineModel::PARAM_MODEL, _model);
}

// ---------------------------------
// UI_GameMain::Dialog
// ---------------------------------

/*static*/ int UI_GameMain::Dialog::DIALOG_Y_LIMIT = 0;
/*static*/ int UI_GameMain::Dialog::DIALOG_Y_DOWN_LIMIT_FULL = 0;
/*static*/ int UI_GameMain::Dialog::DIALOG_Y_DOWN_LIMIT_SHORT = 0;
/*static*/ int UI_GameMain::Dialog::DIALOG_FALLSPEED_NORMAL = 0;
/*static*/ int UI_GameMain::Dialog::DIALOG_FALLSPEED_HIGH = 0;
//=============================================================================
/*static*/ void UI_GameMain::Dialog::onDecideScreenRatio(int ratio)
{
	DIALOG_Y_LIMIT = -295 * ratio;
	DIALOG_Y_DOWN_LIMIT_SHORT = -160 * ratio;
	DIALOG_FALLSPEED_NORMAL = 10 * ratio;
	DIALOG_FALLSPEED_HIGH = 50 * ratio;
}
//=============================================================================
UI_GameMain::Dialog::Dialog()
: _spr_bg(0)
, _spr_button(0)
, _spr_title(0)
, _spr_gameover(0)
, _spr_score(0)
, _y(DIALOG_Y_LIMIT)
, _height(320 * Screen::RATIO)
, _visible(false)
, _prizeSprite(0)
, _hintText_x(0)
, _fallSpeed(DIALOG_FALLSPEED_NORMAL)
, _type(DialogTypeNone)
, _score(0)
, _newRecord(0)
, _hintText(NULL)
{
	_spr_bg = new Sprite("PauseDialog.png" ,512 ,256);
	_spr_button = new Sprite("DialogButton.png" ,80 ,80);
	_spr_title = new Sprite("DialogTitle.png" ,256 ,64);
	_spr_gameover = new Sprite("gameover.png" ,512 ,512);
	_spr_score = new Sprite("Score.png" ,64 ,85);
	_newRecord_spr = new Sprite("best.png" ,128 ,32);
	
	//_hintText = [[Text alloc] initWithString:@"テストなんだけど、流れるようにしてみた" Size:10 Alignment:UITextAlignmentLeft];
}
//=============================================================================
UI_GameMain::Dialog::~Dialog()
{
	SAFE_DELETE(_spr_bg);
	SAFE_DELETE(_spr_button);
	SAFE_DELETE(_spr_title);
	SAFE_DELETE(_spr_gameover);
	SAFE_DELETE(_spr_score);
	SAFE_DELETE(_hintText);
    SAFE_DELETE(_newRecord_spr);
}
//=============================================================================
void UI_GameMain::Dialog::calc()
{
	if (_visible) {
		int ylimit = DIALOG_Y_DOWN_LIMIT_FULL;
		if (_type == DialogTypePause) ylimit = DIALOG_Y_DOWN_LIMIT_SHORT;
		if (_y < ylimit) {
			_y += _fallSpeed;
			if (_y > 0) _y = 0;
		}
		//@TODO
		// if ([_hintText textSize].width > 170 * Screen::RATIO)
		// {
		// 	_hintText_x--;
		// 	if ([_hintText textSize].width + _hintText_x < 0) _hintText_x = 170 * Screen::RATIO;
		// }
	} else {
		if (_y >DIALOG_Y_LIMIT) {
			_y -= _fallSpeed;
			if (_y <DIALOG_Y_LIMIT) _y = DIALOG_Y_LIMIT;
		}
	}
}
//=============================================================================
void UI_GameMain::Dialog::draw(int o)
{
	const int WIDTH = 320 * Screen::RATIO;
	const int HEIGHT = 160 * Screen::RATIO;

	int x = 0;
	if (o == ORIENTATION_LANDSCAPE_LEFT || o == ORIENTATION_LANDSCAPE_RIGHT)
		x = 80 * Screen::RATIO;	
	_spr_bg->drawWithFrame(1, x, _y + _height - HEIGHT, WIDTH, HEIGHT);
	if(_height > HEIGHT)
		_spr_bg->drawWithFrame(0, x, _y, WIDTH, _height-HEIGHT);

	// Draw Buttons
	const int BUTTON_WIDTH = 40 * Screen::RATIO;
	const int BUTTON_HEIGHT = 40 * Screen::RATIO;
	if(_buttons.size()>0) {
		size_t spacing = 280 * Screen::RATIO / _buttons.size();
		for(size_t i=0;i<_buttons.size();i++) {
			_spr_button->drawWithFrame(_buttons[i]-1,
				x+BUTTON_WIDTH/2+spacing*i+(spacing-BUTTON_WIDTH)/2, 
				_y+_height-BUTTON_HEIGHT*2, 
				BUTTON_WIDTH, BUTTON_HEIGHT);
		}
	}

	// Draw Hint
	//@TODO
	/*
	Graphics::SetWriteColorMask(Graphics::WriteColorMaskNone);
	Graphics::SetStencilWriteMode(Graphics::StencilFlagUI);
	[[Draw singleton] drawBox_x:x+100 y:_y+_height-110 width:170 height:20];
	
	Graphics::SetStencilWriteMode(Graphics::StencilFlagNone);
	Graphics::SetWriteColorMask(Graphics::WriteColorMaskAll);
	Graphics::SetStencilFilter(Graphics::StencilFlagNone);
	[[Draw singleton] setColorWithRed:100 Green:180 Blue:250 Alpha:255];
	[[Draw singleton] drawBox_x:x+36 y:_y+_height-110 width:249 height:20];
	[_spr_button drawWithFrame:6 x:x+40 y:_y+_height-110+4 width:50 height:50];
	Graphics::SetStencilFilter(Graphics::StencilFlagUI);
	[_hintText setColorWithRed:255 Green:255 Blue:255 Alpha:255];
	[_hintText draw_x:x+100+_hintText_x y:_y+_height-110+4];
	Graphics::SetStencilFilter(Graphics::StencilFlagNone);
	switch (_type) {
		case DialogTypePause:
			[_spr_title drawWithFrame:2 x:x+40 y:_y+_height-150 width:128 height:32];
			break;
		case DialogTypeGameOver:
			[_spr_gameover drawWithFrame:0 
									   x:x+70
									   y:_y+20 
								   width:180
								  height:180*_spr_gameover.frameSize.height/_spr_gameover.frameSize.width];
			break;
		case DialogTypeResult:
			if( _prizeSprite != nil ){
				[_prizeSprite drawWithFrame:0 
										  x:x+70
										  y:_y+20 
									  width:180
									 height:180*_prizeSprite.frameSize.height/_prizeSprite.frameSize.width];
			}
			[_spr_title drawWithFrame:0 x:x+40 y:_y width:128 height:32];
			break;
        default:
            break;
	}
	*/

	const int DIALOG_SCORE_POS_X = 160 * Screen::RATIO;
	const int DIALOG_SCORE_POS_Y = 140 * Screen::RATIO;
	const int DIALOG_SCORE_POS_X_OFFSET = 30 * Screen::RATIO;
	const int DIALOG_RECORD_WIDTH = 77 * Screen::RATIO;
	const int DIALOG_RECORD_HEIGHT = 20 * Screen::RATIO;
	const int DIALOG_SCORE_WIDTH = 16 * Screen::RATIO;
	const int DIALOG_SCORE_HEIGHT = 21 * Screen::RATIO;
    
	// draw Score
    if (_newRecord && _newRecord_spr)
    	_newRecord_spr->drawWithFrame(1, 
    		DIALOG_SCORE_POS_X - DIALOG_SCORE_POS_X_OFFSET,
    	 	_y+_height-DIALOG_SCORE_POS_Y-DIALOG_RECORD_HEIGHT, 
    	 	DIALOG_RECORD_WIDTH, DIALOG_RECORD_HEIGHT);
    _spr_score->drawWithFrame(10,
    	 x + DIALOG_SCORE_POS_X,
    	 _y+_height-DIALOG_SCORE_POS_Y,
    	 DIALOG_SCORE_WIDTH, DIALOG_SCORE_HEIGHT);
	for (int i=0;i<8;i++)
	{
		_spr_score->drawWithFrame( (_score / ((int)pow(10.0, i))) % 10,
			 x+(180+(7-i)*11)*Screen::RATIO,
			 _y+_height-140*Screen::RATIO,
			 DIALOG_SCORE_WIDTH, DIALOG_SCORE_HEIGHT);
	}
}
//=============================================================================
UI_GameMain::Dialog::DialogButton UI_GameMain::Dialog::getTouchResult(CGPoint tp, int o)
{
	const int R = Screen::RATIO;
	int x = 0;
	if (o == ORIENTATION_LANDSCAPE_RIGHT || o == ORIENTATION_LANDSCAPE_LEFT) x = 80*R;
	size_t spacing = 280*R / _buttons.size();
	for(size_t i=0;i<_buttons.size();i++) {
		if(tp.x > x+spacing*i+20*R && tp.x < x+spacing*(i+1)+20*R &&
		   tp.y > _y + _height - 120*R && tp.y < _y + _height - 40*R) {
			return _buttons[i];
		}
	}
	return DialogButtonNone;
}
//=============================================================================
void UI_GameMain::Dialog::setHintText(const char* str)
{ 
	//@TODO
	//[_hintText initWithString:str Size:10 Alignment:UITextAlignmentLeft]; 
}
//=============================================================================
void UI_GameMain::Dialog::setPauseDialog()
{
	reset();
	_type = DialogTypePause;
	_fallSpeed = DIALOG_FALLSPEED_NORMAL;
	addButton(DialogButtonResume);
	addButton(DialogButtonRetry);
	addButton(DialogButtonExit);
}
//=============================================================================
void UI_GameMain::Dialog::setTutorialDialog()
{
	reset();
	_type = DialogTypeTutorial;
	_fallSpeed = DIALOG_FALLSPEED_NORMAL;
	addButton(DialogButtonPrevious);
	addButton(DialogButtonNext);
	addButton(DialogButtonExit);
}
//=============================================================================
void UI_GameMain::Dialog::setGameOverDialog()
{
	reset();
	_type = DialogTypeGameOver;
	_fallSpeed = DIALOG_FALLSPEED_HIGH;
	addButton(DialogButtonRetry);
	addButton(DialogButtonExit);
}
//=============================================================================
void UI_GameMain::Dialog::setResultDialog()
{
	reset();
	_type = DialogTypeResult;
	_fallSpeed = DIALOG_FALLSPEED_HIGH;
	addButton(DialogButtonRetry);
	addButton(DialogButtonExit);
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
