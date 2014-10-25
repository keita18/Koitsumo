//! @file 		Sprite.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <EGL/egl.h>
#include <GLES/gl.h>
#include "../GRDefinition.h"

class Sprite
{
public:
	Sprite(const char* imgName, int fw, int fh);
	Sprite(Sprite* spr);
	~Sprite();

	void drawImage(int x, int y, int w, int h, CGPoint leftTop, CGPoint rightDown);
	
	void drawWithFrame(int f, int x, int y, int w, int h);

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	//test
	void drawBox();

private:
	void loadImage(const char* imgName);
private:
	GLuint	_tag;
	CGSize 	_frameSize;
	CGSize	_texSize;
	int		_pitch;
	GLubyte	_sprCol[16];

	bool	_shared;

	//開発ログ用
	int 	_count;
};