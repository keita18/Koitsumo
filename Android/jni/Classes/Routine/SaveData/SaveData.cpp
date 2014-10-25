//! @file 		SaveData.cpp
//! @author 	Keita Tanji
//! @breif		

#include "SaveData.h"
#include "pch.h"
#include <fstream>

/*static*/ SaveData* SaveData::instance_ = NULL;

//@TODO

// NSString* keys[] = {
// 	@"isFirstTime",
// 	@"highScore",
//     @"highScoreWithoutTimeLimit",
// };

SaveData* SaveData::getInstance()
{
	if( instance_ == NULL ){
		instance_ = new SaveData();
		instance_->setup();
	}
	return instance_;
}

void SaveData::setup()
{
	//デフォルト値
	// NSUserDefaults* ud = [NSUserDefaults standardUserDefaults];
	// NSMutableDictionary* defaults = [NSMutableDictionary dictionary];
	// [defaults setObject:@"1" forKey:keys[KEY_ISFIRSTTIME]];
	// [defaults setObject:@"0" forKey:keys[KEY_HIGHSCORE]];
 //    [defaults setObject:@"0" forKey:keys[KEY_HIGHSCORE_WITHOUT_TIMELIMIT]];
	
	// [ud registerDefaults:defaults];
}

void SaveData::load()
{
	// NSUserDefaults* ud = [NSUserDefaults standardUserDefaults];
	// isFirstTime_ = [ud boolForKey:keys[KEY_ISFIRSTTIME]];
	// highScore_ = [ud integerForKey:keys[KEY_HIGHSCORE]];
 //    highScoreWithoutTimeLimit_ = [ud integerForKey:keys[KEY_HIGHSCORE_WITHOUT_TIMELIMIT]];
}

void SaveData::save()
{
	// NSUserDefaults* ud = [NSUserDefaults standardUserDefaults];
	// [ud setBool:isFirstTime_ forKey:keys[KEY_ISFIRSTTIME]];
	// [ud setInteger:highScore_ forKey:keys[KEY_HIGHSCORE]];
 //    [ud setInteger:highScoreWithoutTimeLimit_ forKey:keys[KEY_HIGHSCORE_WITHOUT_TIMELIMIT]];
}

