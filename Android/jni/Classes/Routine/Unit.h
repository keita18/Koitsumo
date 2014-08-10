//! @file 		Unit.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "pch.h"

enum UnitId{
	UNIT_NONE = 0,
	UNIT_TITLE,
};

class Unit
{
public:
	Unit();
	~Unit();

	virtual void calc();
	virtual void draw();

	void touchedBegin(CGPoint tp) {}
	void touchedMoved(CGPoint tp) {}
	void touchedEnded(CGPoint tp) {}
};