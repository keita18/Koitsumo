//! @file 		MainRoutine.h
//! @author 	Keita Tanji
//! @breif		

#pragma once

#include "pch.h"

class Unit;

class MainRoutine
{
public:
	static MainRoutine* singleton();

	void calc();
	void draw();

	Unit* getCurrentUnit();

private:
	MainRoutine();
	~MainRoutine();

private:
	static MainRoutine* pInstance;

private:
	Unit* _currentUnit;
	
};