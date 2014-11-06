//! @file 		MainRoutine.cpp
//! @author 	Keita Tanji
//! @breif		

#include "MainRoutine.h"
#include "Title/TitleUnit.h"
#include "Puzzle/PuzzleUnit.h"
#include "UI/UI_GameMain.h"
#include "Classes/Graphics/2D/Filter.h"
#include "Classes/Routine/Base/FrameTime.h"
#include "Classes/Routine/SaveData/SaveData.h"
#include "Classes/Graphics/GraphicsBase.h"
#include <unistd.h>

/*static*/ MainRoutine* MainRoutine::pInstance = NULL;

//=============================================================================
/*static*/ void MainRoutine::onDecideScreenRatio(int ratio)
{
	UserInterface::UI_GameMain::onDecideScreenRatio(ratio);
	Puzzle::PuzzleUnit::onDecideScreenRatio(ratio);
}

//=============================================================================
/*static*/ MainRoutine* MainRoutine::singleton()
{
	if(pInstance == NULL){
		pInstance = new MainRoutine();
	}
	return pInstance;
}

//-----------------------------------------------------------------------------
MainRoutine::MainRoutine()
: _currentUnit(NULL)
, _touched(false)
, _filter(NULL)
{
	_filter = new Filter();
	//@TODO 	textLayer;

	Base::FrameTime::createSystemFrameTime();

	//@TODO
	//[SoundDrive getInstance];	//初期化
	//Graphics::EffectManager::init();

	SaveData::getInstance()->load();
}

//-----------------------------------------------------------------------------
MainRoutine::~MainRoutine()
{
	SAFE_DELETE(_currentUnit);
	SAFE_DELETE(_filter);
	Base::FrameTime::destroySystemFrameTime();
}

//=============================================================================
void MainRoutine::init()
{
	SAFE_DELETE(_currentUnit);
}

//=============================================================================
void MainRoutine::calc()
{
	_filter->calc();
	//@TODO
	//Graphics::EffectManager::getInstance()->updateEffects();

	if(_currentUnit == NULL) {
		_currentUnit = new TitleUnit();
	}

	if(_currentUnit) {
		_currentUnit->calc();
		if(_currentUnit->GetEnd()) {
			Unit* nextUnit = NULL;
			switch( _currentUnit->GetNextID() ) {
				case UNIT_TITLE:{
					nextUnit = new TitleUnit();
					break;
				}
				case UNIT_PUZZLE:{
					nextUnit = new Puzzle::PuzzleUnit(false);
					break;
				}
				case UNIT_PUZZLE_NO_TIMELIMIT:{
					nextUnit = new Puzzle::PuzzleUnit(true);
					break;
				}
				case UNIT_GAME_OVER:{
					//nextUnit
					break;
				}
			}
			setNextUnit(nextUnit);
		}
	}
}

//=============================================================================
void MainRoutine::draw()
{
	Graphics::ClearDisplayBuffer(Graphics::DisplayClearModeAll);
	if(_currentUnit) {
		_currentUnit->draw();
	}
	//@TODO
	//Gprahics::EffectManager::getInstance()->drawEffects();
}
//=============================================================================
void MainRoutine::waitForFrame()
{
#define TIME 16000
	Base::FrameTime* frameTime = Base::FrameTime::getSystemFrameTime();
	if( frameTime ){
		frameTime->calcDeltaTime();
		time_t dt = frameTime->getDeltaTime();
		if( dt < TIME ){
			time_t left = TIME - dt;
			usleep( left );
		}
	}
}
//=============================================================================
void MainRoutine::touchedBegin(CGPoint tp)
{
	_touched = true;
	if(_currentUnit) _currentUnit->touchedBegin(tp);
}
//=============================================================================
void MainRoutine::touchedMoved(CGPoint tp)
{
	if(_currentUnit) _currentUnit->touchedMoved(tp);
}
//=============================================================================
void MainRoutine::touchedEnded(CGPoint tp)
{
	if(!_touched) return;
	if(_currentUnit) _currentUnit->touchedEnded(tp);
	_touched = true;
}

//=============================================================================
Unit* MainRoutine::getCurrentUnit()
{
	return _currentUnit;
}
//=============================================================================
void MainRoutine::setNextUnit(Unit* unit)
{
	if(_currentUnit) SAFE_DELETE(_currentUnit);
	_currentUnit = unit;
	_touched = false;
}
