//! @file 		MainRoutine.h
//! @author 	Keita Tanji
//! @breif		

#pragma once

#include "pch.h"

class Unit;

class MainRoutine
{
public:
	static void onDecideScreenRatio(int ratio);
public:
	static MainRoutine* singleton();
	void init();

	void calc();
	void draw();

	void touchedBegin(CGPoint tp);
	void touchedMoved(CGPoint tp);
	void touchedEnded(CGPoint tp);

	Unit* getCurrentUnit();

	void setNextUnit(Unit* unit);
private:
	MainRoutine();
	~MainRoutine();

private:
	static MainRoutine* pInstance;

private:
	Unit* _currentUnit;
	
	bool	_touched;
};