//! @file 		ViewController.cpp
//! @author 	Keita Tanji
//! @breif		

#include "ViewController.h"
#include "Classes/Routine/MainRoutine.h"
#include "glu.h"

ViewController::ViewController(engine* engine)
: engine_(*engine)
, count_(0)
{}

void ViewController::setFrameBuffer()
{
	//@TDOO 他の処理も？

	glViewport(0, 0, engine_.width, engine_.height);

	//デバッグ
	count_++;
	if(count_ > 30)
	{
		count_ = 0;
		LOGI("setFrameBuffer, width=%d, height=%d", engine_.width, engine_.height);
	}
}

void ViewController::drawFrame()
{
    //Proc
    MainRoutine::singleton()->calc();

    setFrameBuffer();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glPushMatrix();
	//--
	// glScalef(1, -1, 1);
	// glOrthof(0.0f, engine_.width, 0.0f, engine_.height, 1000.0f, -1000.0f);
	//--
	glOrthof(0.0f, engine_.width, engine_.height, 0.0f, 1000.0f, -1000.0f);
	//--

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//回転処理周りは省略

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	MainRoutine::singleton()->draw();

	//presentFramebuffer?

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//@TODO sleep処理(waitForFrame)
}
