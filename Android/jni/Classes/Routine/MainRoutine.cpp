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
{}


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
Unit* MainRoutine::getCurrentUnit()
{
	return _currentUnit;
}
