//! @file 		ViewController.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include "Engine.h"
#include "pch.h"

//! iPhoneのViewContollerに相当する機能をもつクラス
class ViewController
{
public:
	ViewController(engine* engine);
	void init();
	
	void setFrameBuffer();
	void drawFrame();

	void touchesBegan(CGPoint tp);
	void touchesMoved(CGPoint tp);
	void touchesEnded(CGPoint tp);
private:
	engine& engine_;

	//log用
	int count_;
};