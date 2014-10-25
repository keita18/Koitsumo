//! @file 		MainRoutine.cpp
//! @author 	Keita Tanji
//! @breif		

#include "MainRoutine.h"
#include "Title/TitleUnit.h"
#include "Puzzle/PuzzleUnit.h"
#include "UI/UI_GameMain.h"

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
{
}

//-----------------------------------------------------------------------------
MainRoutine::~MainRoutine()
{
	SAFE_DELETE(_currentUnit);
}

//=============================================================================
void MainRoutine::init()
{
	SAFE_DELETE(_currentUnit);
}

//=============================================================================
void MainRoutine::calc()
{
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
	if(_currentUnit) {
		_currentUnit->draw();
	}
}
//=============================================================================
void MainRoutine::touchedBegin(CGPoint tp)
{
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
	if(_currentUnit) _currentUnit->touchedEnded(tp);
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
