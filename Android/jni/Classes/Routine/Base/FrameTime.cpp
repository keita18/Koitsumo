#include "FrameTime.h"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

namespace Base{

	/*static*/ FrameTime* FrameTime::systemFrameTime_ = NULL;
	
	/*static*/void FrameTime::createSystemFrameTime()
	{
		if( systemFrameTime_ == NULL ){
			systemFrameTime_ = new FrameTime;
		}
	}
	
	/*static*/FrameTime* FrameTime::getSystemFrameTime()
	{
		return systemFrameTime_;
	}
	
	/*static*/void FrameTime::destroySystemFrameTime()
	{
		if( systemFrameTime_ != NULL ){
			delete systemFrameTime_;
			systemFrameTime_ = NULL;
		}
	}
	
	FrameTime::FrameTime()
		: isInit_( false )
	{
		time_[0] = time_[1] = 0;
	}
		
	void FrameTime::calcDeltaTime()
	{		
		if( !isInit_ ){
			time_[0] = gettimeofday_usec_();
			isInit_ = true;
		}
		else{
			time_[0] = time_[1];
		}
		
		time_[1] = gettimeofday_usec_();
		
		if( time_[1] < time_[0] ){
			time_[1] += (1000 * 1e+6);/// time_[1]のみ1000sec越えした補正
		}
	}
	
	time_t FrameTime::getDeltaTime() const
	{
        return time_[1] - time_[0];
//		double dt = (double)difftime( time_[1], time_[0] );
//		dt /= (double)1e+6;
//		return (float)dt;
	}
	
	time_t FrameTime::gettimeofday_usec_()
	{
		struct timeval tv;
		gettimeofday( &tv, NULL );
		time_t sec = tv.tv_sec % 1000;
		return sec*1e+6 + (time_t)tv.tv_usec;
	}
	
	void FrameTime::reset()
	{
		isInit_ = false;
		time_[0] = time_[1] = 0;
	}
	

}/*namespace Base*/