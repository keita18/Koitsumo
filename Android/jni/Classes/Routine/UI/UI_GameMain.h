//! @file 		UI_GameMain.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <vector>
#include <map>

#include "Classes/Graphics/3D/model.h"
#include "Classes/Graphics/2D/Sprite.h"
#include "Classes/Math/Vector2.h"
#include "Classes/Math/Vector3.h"

namespace UserInterface {
class UI_GameMain
{
public:
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

		void setOrientaion(int o)	{ _orientation = 0; }
	private:
		Sprite*		_sprite0;
		Sprite*		_sprite1;
		Math::Vector2 	_pos;
		int 		_orientation;
		float 		_scl;
		float 		_sclframe;
	};

public:
	UI_GameMain();
	~UI_GameMain();

	static Graphics::Model* makeCoinModel(const char* imageFileName, int divine = 16);
};
} // UserInterface