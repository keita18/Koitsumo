//! @file 		ViewController.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "Engine.h"

//! iPhoneのViewContollerに相当する機能をもつクラス
class ViewController
{
public:
	ViewController(engine* engine);
	void setFrameBuffer();
	void drawFrame();

private:
	engine& engine_;

	//log用
	int count_;
};