//! @file 		GRDefinition.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
#define PI 3.14159265f

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
	CGPoint(float x_, float y_) : x(x_), y(y_) {}
};

struct CGRect
{
	CGSize size;
	CGPoint origin;
};
