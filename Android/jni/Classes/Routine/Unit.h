//! @file 		Unit.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "pch.h"

enum UnitId{
	UNIT_NONE = 0,
	UNIT_TITLE,
	UNIT_PUZZLE,
	UNIT_PUZZLE_NO_TIMELIMIT,
	UNIT_GAME_OVER,
};

class Unit
{
public:
	Unit();
	~Unit();

	virtual void calc();
	virtual void draw();

	virtual void touchedBegin(CGPoint tp) {}
	virtual void touchedMoved(CGPoint tp) {}
	virtual void touchedEnded(CGPoint tp) {}

	void SetEnd(bool val) { _end = val; }
	bool GetEnd() const { return _end; }
	void SetNextID(int nextID) { _nextID = nextID; }
	int GetNextID() const { return _nextID; }
private:
	bool 	_end;
	int 	_nextID;
};