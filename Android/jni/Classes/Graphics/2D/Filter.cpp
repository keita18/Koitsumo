//! @file 		Filter.cpp
//! @author 	Keita Tanji
//! @breif		
#include "Filter.h"
#include "pch.h"

namespace {	//anonymous
	enum FADE_TYPE {
		FADE_NONE = 0, FADE_IN = 1, FADE_OUT = 2,
	};
	static GLshort txtVtx[] = { 0, 0, 1, 0, 0, 1, 1, 1 };
}	//anonymous

//=============================================================================
Filter::Filter()
: _fadeMode(FADE_NONE)
{}
//=============================================================================
Filter::~Filter()
{}
//=============================================================================
void Filter::calc()
{
	for (int i=0;i<3;i++)
	switch (_fadeMode) {
		case FADE_IN:
			if (_texCol[3] > 0) _texCol[3] = _texCol[7] = _texCol[11] = _texCol[15] = (_texCol[3]-1);
			else _fadeMode = FADE_NONE;
			break;
		case FADE_OUT:
			if (_texCol[3] < 255) _texCol[3] = _texCol[7] = _texCol[11] = _texCol[15] = (_texCol[3]+1);
			else _fadeMode = FADE_NONE;
			break;
	}
}
//=============================================================================
void Filter::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glScalef(Screen::HEIGHT, Screen::WIDTH, 1);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);	
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_SHORT, 0, txtVtx);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, _texCol);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}
//=============================================================================
void Filter::setColor(int r, int g, int b, int a)
{
	_texCol[0] = _texCol[4] = _texCol[8] =  _texCol[12] = r;
	_texCol[1] = _texCol[5] = _texCol[9] =  _texCol[13] = g;
	_texCol[2] = _texCol[6] = _texCol[10] = _texCol[14] = b;
	_texCol[3] = _texCol[7] = _texCol[11] = _texCol[15] = a;
}
//=============================================================================
void Filter::fadeIn()
{
	_texCol[3] = _texCol[7] = _texCol[11] = _texCol[15] = 255;
	_fadeMode = FADE_IN;
}
//=============================================================================
void Filter::fadeOut()
{
	_texCol[3] = _texCol[7] = _texCol[11] = _texCol[15] = 0;
	_fadeMode = FADE_OUT;
}
