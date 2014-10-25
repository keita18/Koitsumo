//! @file 		UI_GameMain.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <vector>
#include <map>

#include "pch.h"
#include "Classes/Graphics/3D/model.h"
#include "Classes/Graphics/2D/Sprite.h"
#include "Classes/Graphics/2D/Text.h"
#include "Classes/Math/Vector2.h"
#include "Classes/Math/Vector3.h"

static const float BlockProgressUnit = 0.085f;

namespace UserInterface {
class UI_GameMain
{
public:
	enum 
	{
		NONE = 0,
	};
	
	enum ORIENTATION
	{
		ORIENTATION_PORTRAIT_UP = 0,
		ORIENTATION_PORTRAIT_DOWN,
		ORIENTATION_LANDSCAPE_LEFT,
		ORIENTATION_LANDSCAPE_RIGHT
	};

	static int STAGE_WIDTH;
	static int STAGE_VERTICAL_OFFSET_X;
	static int STAGE_VERTICAL_OFFSET_Y;
	static int STAGE_HORIZON_OFFSET_X;
	static int STAGE_HORIZON_OFFSET_Y;
	static void onDecideScreenRatio(int ratio);
public:
	class MiniNumber
	{
	public:
	    enum ITEM_TYPE
	    {
	        ITEM_TYPE_TIME = 0,
	        ITEM_TYPE_POINT,
	        ITEM_TYPE_MAX
	    };
	    
	    typedef struct
	    {
	        Math::Vector2       pos;
	        unsigned int        type;
	        int                 number;
	        int                 time;
	    } ITEM;

	    const static unsigned int ITEM_MAX = 16;
	    const static unsigned int DEFAULT_TIME = 150;
	    
	    Sprite                  *_sprite_time;
	    Sprite                  *_sprite_money;
	    Sprite                  *_spr_items_t[ITEM_MAX];
	    Sprite                  *_spr_items_m[ITEM_MAX];
	    unsigned int             _itemCount;
	    ITEM                     _items[ITEM_MAX];
	public:
	    MiniNumber();
	    ~MiniNumber();

	    void addNumber(unsigned int n, unsigned int type, const Math::Vector2 &pos, unsigned int t = DEFAULT_TIME);
	    
	    void calc();
	    void draw();
	};
	
	class MiniPaper
	{
	    typedef struct
	    {
	        bool                enabled;
	        Math::Vector2       pos;
	        Math::Vector2       throwPower;
	        float               sinval;
	    } ITEM;
	    
	    const static unsigned int ITEM_MAX = 16;
	    
	    ITEM                     _items[ITEM_MAX];
	    Sprite                  *_sprite;
	public:
	    MiniPaper();
	    ~MiniPaper();
	    
	    void addPaper(const Math::Vector2 &pos);
	    
	    void calc();
	    void draw();
	};

	class Coin
	{
	public:
		static void onDecideScreenRatio(int ratio);
	private:
		Graphics::Model	*_model;
		Math::Vector2	*_pos;
		Math::Vector2	_posorg;
		Math::Vector2	_dir;
		Math::Vector3	_rot;
		float			_popScale;
		bool			_shake;
		int				_shakeFlag;
		int				_state;
		float			_progress;
		int				_shineEffect;
		int				_rolldir;
		int				_waitFrame;
		
	public:
		enum 
		{
			//Width = 35,
			GForce = 1,
			UnionSpeed = 10,
		};
		static int Width;

		enum TYPE
		{
			Type_1yen = 1,
			Type_5yen = 5,
			Type_10yen = 10,
			Type_50yen = 50,
			Type_100yen = 100,
			Type_500yen = 500,
			Type_Max,
		};

		enum STATE
		{
			STATE_READY = 0,
			STATE_FALL,
			STATE_UNION,
			STATE_CLEAR,
			STATE_OVER_FALL,
			STATE_END,
		};
		
		Coin(Graphics::Model *m);
		~Coin()			{}
		
		void calc();
		
		void popEffectOn()					{ _popScale = 5.0f * Screen::RATIO; }
		bool isPopEffectOn()				{ return _popScale > 0; }
		
		void shineEffectOn();
		
		void drawWithOffset(const Math::Vector2 &offset, int orientation);
		void drawWithPosition(const Math::Vector2 &position, int orientation);
		
		void setWaitFrame(int f)			{ _waitFrame = f; }
		void setShake(bool s)				{ _shake = s; _shakeFlag = 4; }
		void setPosition(Math::Vector2 *p)	{ _pos = p; }
		int getState()						{ return _state; }
		void setState(int s);
		float getProgress()					{ return _progress; }
		void setProgress(float p)			{ if(p<0.0f) _progress = 0.0f; else _progress = p; }
	};

	class BackGround
	{
	public:
		enum ORIENTATION
		{
			ORIENTATION_PORTRAIT_UP = 0,
			ORIENTATION_PORTRAIT_DOWN,
			ORIENTATION_LANDSCAPE_LEFT,
			ORIENTATION_LANDSCAPE_RIGHT
		};
	public:
		BackGround();
		virtual ~BackGround();

		void calc();
		void draw();

		void setOrientation(int o)	{ _orientation = 0; }
	private:
		Sprite*		_sprite0;
		Sprite*		_sprite1;
		Math::Vector2 	_pos;
		int 		_orientation;
		float 		_scl;
		float 		_sclframe;
	};

	class Dialog
	{
	public:
		static int DIALOG_Y_LIMIT;
		static int DIALOG_Y_DOWN_LIMIT_FULL;
		static int DIALOG_Y_DOWN_LIMIT_SHORT;
		static int DIALOG_FALLSPEED_NORMAL;
		static int DIALOG_FALLSPEED_HIGH;
		static void onDecideScreenRatio(int ratio);

	public:			// Predefinition
		enum ORIENTATION
		{
			ORIENTATION_PORTRAIT_UP = 0,
			ORIENTATION_PORTRAIT_DOWN,
			ORIENTATION_LANDSCAPE_LEFT,
			ORIENTATION_LANDSCAPE_RIGHT
		};

		enum DialogButton {
			DialogButtonNone = 0,
			DialogButtonExit,
			DialogButtonRetry,
			DialogButtonResume,
			DialogButtonPrevious,
			DialogButtonNext
		};
		
		enum DialogType {
			DialogTypeNone = 0,
			DialogTypePause,
			DialogTypeResult,
			DialogTypeGameOver,
			DialogTypeTutorial
		};
		
	public:
		Dialog();
		virtual ~Dialog();
		
		void reset()							{ _buttons.clear(); }
		void addButton(DialogButton b)			{ _buttons.push_back(b); }
		
		void calc();
		void draw(int o);
		
		void show()								{ _visible = true; _hintText_x = 0; }
		void hide()								{ _visible = false; }
		
		bool isVisible()						{ return _visible; }
		
		DialogButton getTouchResult(CGPoint tp, int o);
		
		void setPrize(Sprite *prizeSprite)		{ _prizeSprite = prizeSprite; }
		void setFallSpeed(int f)				{ _fallSpeed = f; }
		void setScore(int s)					{ _score = s; }
        void setNewRecord(bool b)               { _newRecord = b; }
		void setHintText(const char* str);
		void setPauseDialog();
		void setTutorialDialog();
		void setGameOverDialog();
		void setResultDialog();
		
	private:			// Private Properties
		Sprite			*_spr_bg;
		Sprite			*_spr_button;
		Sprite			*_spr_title;
		Sprite			*_spr_gameover;
		Sprite			*_spr_score;
        Sprite          *_newRecord_spr;
		
		Text			*_hintText;
		int				 _hintText_x;
		
		bool			 _visible;
        bool             _newRecord;
		int				 _y;
		int				 _height;
		int				 _fallSpeed;
		int				 _score;
		
		DialogType		 _type;
		
		std::vector<DialogButton>		_buttons;
		
		Sprite			*_prizeSprite;
	};

	class LinearPath
	{
		std::vector<Math::Vector2>		_points;
		float							_length;
		
	public:
		LinearPath() : _length(0) {}
		~LinearPath() { _points.clear(); }
		
		void addPoint(const Math::Vector2 &p)
		{ 
			if (_points.size() > 0) {
				_length += (p - _points[_points.size()-1]).length();
			}
			_points.push_back(p); 
		}
		
		LinearPath& operator << (const Math::Vector2 &p) { addPoint(p); return *this; }
		void operator += (const Math::Vector2 &p) { addPoint(p); }
		
		float getLength()		{ return _length; }
		Math::Vector2 getPosition(float progress)
		{
			if (_points.size() < 2) return Math::Vector2();
			assert(progress>=0);
            
			float dist = _length * progress;
			Math::Vector2 prev = _points[0];
			Math::Vector2 result;
			for (int i=1;i<_points.size();i++) {
				float point_len = (_points[i] - prev).length();
				if (dist - point_len < 9) {
					float per = dist / point_len;
					result = prev + (_points[i] - prev) * per;
					break;
				}
				dist -= point_len;
				prev = _points[i];
			}
			
			return result;
		}
	};

public:
	UI_GameMain();
	~UI_GameMain();

	static Graphics::Model* makeCoinModel(const char* imageFileName, int divine = 16);

	void init();
	void calc();
	void draw(bool noTime = false);
	void term();

	Coin* addCoin(Coin::TYPE t);
	void removeCoin(Coin *c);
	void moveCoinFront(Coin *c);
    
    void addScorePlus(unsigned int num, const Math::Vector2 &pos);
    void addTimePlus(unsigned int num);
    
	void showPauseDialog()							{ _dialog.setPauseDialog(); _dialog.show(); }
	void showTutorialDialog()						{ _dialog.setTutorialDialog(); _dialog.show(); }
	void showGameOverDialog()						{ _dialog.setGameOverDialog(); _dialog.show(); }
	void showResultDialog()							{ _dialog.setResultDialog(); _dialog.show(); }
	void hideDialog()								{ _dialog.hide(); }
	void setPrize( Sprite *prizeSprite )			{ _dialog.setPrize(prizeSprite); }
	void setHintText(const char* str)				{ _dialog.setHintText(str); }
	void setNewRecord(bool b)                       { if (b) _newRecord_prog = 0; else _newRecord_prog = -1.0f; }
    bool isNewRecord()                              { return _newRecord_prog >=0.0f; }
    
	bool isPauseTouched(CGPoint tp);
	bool isEndPauseTouched(CGPoint tp);
	bool isRetryTouched(CGPoint tp);
	bool isReturnToTitleTouched(CGPoint tp);
	
	void setTime(int t)								{ _time = t; }
	void setLimitTime(int l)						{ _limitTime = l; }
	void setScore(int s)							{ _score = s; _dialog.setScore(s); }
    void setBestScore(int s)                        { _bestScore = s; }
	void setOrientation(ORIENTATION o)				{ _orientation = o; _bg.setOrientation(o); }
	void setHighScoreInDialog(bool b)               { _dialog.setNewRecord(true); }
    
private:	// Private Members
    MiniNumber                           _miniNumber;
    MiniPaper                            _miniPaper;
    
	Sprite								*_pipe_portrait;
	Sprite								*_pipe_portrait_back;
	Sprite								*_pipe_landscape;
	Sprite								*_pipe_landscape_back;
	Sprite								*_score_spr;
    Sprite                              *_best_spr;
    Sprite                              *_newRecord_spr;
	Sprite								*_spr_timebar;
	BackGround							 _bg;
	Dialog								 _dialog;
	LinearPath							 _path_horizon;
	LinearPath							 _path_vertical;
	int									 _orientation;
	int									 _score;
    int                                  _bestScore;
    float                                _newRecord_prog;
	unsigned int						 _time;
	unsigned int						 _limitTime;
	std::map<int, Graphics::Model *>	 _coinModels;
	std::vector<Coin *>					 _coins;	
};

} // UserInterface