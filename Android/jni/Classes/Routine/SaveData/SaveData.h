//! @file 		SaveData.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

class SaveData
{
	enum {
		KEY_ISFIRSTTIME,
		KEY_HIGHSCORE,
        KEY_HIGHSCORE_WITHOUT_TIMELIMIT,
		NB_KEY,
	};
public:
	static SaveData* getInstance();
	void load();
	void save();
	
	bool isFirstTime() { return isFirstTime_; }
	void setIsFirstTime( bool val ) { isFirstTime_ = val; } 
	int  getHighScore() { return highScore_; }
	void setHighScore( int score ) { highScore_ = score; }
	int  getHighScoreWithoutTimeLimit() { return highScoreWithoutTimeLimit_; }
    void setHighScoreWithoutTimeLimit( int score ) { highScoreWithoutTimeLimit_ = score; }
private:
	SaveData() 
	: isFirstTime_(true) 
	, highScore_(0)
    , highScoreWithoutTimeLimit_(0)
	{}
	SaveData( const SaveData& );
	~SaveData();
	void setup();
	
private:
	bool isFirstTime_;
	int  highScore_;
    int  highScoreWithoutTimeLimit_;
	
	static SaveData* instance_;
};
