//! @file 		Text.h
//! @author 	Keita Tanji
//! @breif		
#pragma once
#include <GLES/gl.h>
#include "pch.h"

class Text
{
public:
	Text(const char* t, float s /*@TODO align*/);
	~Text();
	void draw(int x, int y);
	void setColorWith(int r, int g, int b, int a);

public:
	//プロパティの代わり
	const CGSize& GetTexSize() const { return _texSize; }
	//@TODO

private:
	GLuint 	_tag;
	CGSize	_texSize;
	CGSize 	_textSize;
	GLubyte	_texCol[16];
};