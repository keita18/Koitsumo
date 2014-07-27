//! @file 		Sprite.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <EGL/egl.h>
#include <GLES/gl.h>

//とりあえずでここに定義
struct CGSize
{
	float width;
	float height;

	CGSize() : width(0.0f), height(0.0f) {}
};

struct CGPoint
{
	float x;
	float y;

	CGPoint() : x(0.0f), y(0.0f) {}
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

	//アニメーション関係省略
};