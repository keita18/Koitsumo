//! @file 		Unit.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

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
};