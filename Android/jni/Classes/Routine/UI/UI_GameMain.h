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
	UI_GameMain();
	~UI_GameMain();

	static Graphics::Model* makeCoinModel(const char* imageFileName, int divine = 16);
};
} // UserInterface