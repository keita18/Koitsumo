//! @file 		Draw.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <GLES/gl.h>

enum DrawColorSide {
	DrawColorSideLeftTop = 0,
	DrawColorSideRightTop,
	DrawColorSideLeftBottom,
	DrawColorSideRightBottom
};

class Draw
{	
public:
	static Draw*	singleton();
public:
	void setColorWithSide(int s, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void drawBox(int x, int y, int w, int h);

private:
	Draw(){}
	~Draw(){}

private:
	static Draw*	instance_;
};