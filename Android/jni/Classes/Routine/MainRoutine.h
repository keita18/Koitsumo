//! @file 		MainRoutine.h
//! @author 	Keita Tanji
//! @breif		

#pragma once

#include "pch.h"

class Unit;
class Filter;

class MainRoutine
{
public:
	static void onDecideScreenRatio(int ratio);
public:
	static MainRoutine* singleton();
	void init();

	void calc();
	void draw();
	void waitForFrame();
	void touchedBegin(CGPoint tp);
	void touchedMoved(CGPoint tp);
	void touchedEnded(CGPoint tp);

	Unit* getCurrentUnit();

	void setNextUnit(Unit* unit);

	//@TODO
	void notifyRotateDevice() {}
	void reactivate() {}
private:
	MainRoutine();
	~MainRoutine();

private:
	static MainRoutine* pInstance;

private:
	//@TODO
	//UIView  _textLayer
	Unit* _currentUnit;
	Filter*	_filter;
	int 	_status;
	
	int 	*_aplPtr;
	bool	_touched;
};