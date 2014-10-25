//! @file 		FrameTime.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <ctime>

namespace Base {

class FrameTime
{
public:
	FrameTime();
	void calcDeltaTime();
	time_t getDeltaTime() const;
	void reset();
public:
	static void createSystemFrameTime();
	static FrameTime* getSystemFrameTime();
	static void destroySystemFrameTime();
private:
	time_t gettimeofday_usec_();
	
private:
	time_t time_[2];
	bool isInit_;
	
	static FrameTime* systemFrameTime_;
};

}/*namespace Base*/
