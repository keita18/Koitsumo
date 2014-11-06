//! @file 		Filter.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <GLES/gl.h>

class Filter
{
public:
	Filter();
	~Filter();
	void calc();
	void draw();
	void setColor(int r, int g, int b, int a);
	void fadeIn();
	void fadeOut();

	GLubyte getAlpha() { return _texCol[3]; }
	void setAlpha(GLubyte a) {
		_texCol[3] = _texCol[7] = _texCol[11] = _texCol[15] = a;
	}
private:
	GLubyte	_texCol[16];
	int 	_fadeMode;
};