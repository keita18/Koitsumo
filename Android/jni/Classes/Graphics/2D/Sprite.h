//! @file 		Sprite.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <EGL/egl.h>
#include <GLES/gl.h>

//とりあえずでここに定義
struct CGSize
{
	int width;
	int height;

	CGSize() : width(0), height(0) {}
};

struct CGPoint
{
	int x;
	int y;
};

struct CGRect
{
	CGSize size;
	CGPoint origin;
};

class Sprite
{
public:
	Sprite(const char* imgName, int fw, int fh);
	~Sprite();

	void drawWithFrame(int f, int x, int y, int w, int h);

private:
	void loadImage(const char* imgName);
private:
	GLuint	_tag;
	CGSize 	_frameSize;
	CGSize	_texSize;
	int		_pitch;
	GLubyte	_sprCol[16];

	//アニメーション関係省略
};