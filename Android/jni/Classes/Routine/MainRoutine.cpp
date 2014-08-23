//! @file 		MainRoutine.cpp
//! @author 	Keita Tanji
//! @breif		

#include "MainRoutine.h"
#include "Title/TitleUnit.h"

/*static*/ MainRoutine* MainRoutine::pInstance = NULL;

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
