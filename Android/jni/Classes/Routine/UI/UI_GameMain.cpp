//! @file 		UI_GameMain.cpp
//! @author 	Keita Tanji
//! @breif		
#include "UI_GameMain.h"

using namespace UserInterface;

//=============================================================================
UI_GameMain::UI_GameMain()
{}
//=============================================================================
UI_GameMain::~UI_GameMain()
{}
//=============================================================================
/*static*/ Graphics::Model* UI_GameMain::makeCoinModel(const char* imageFileName, int divine)
{
#define COIN_MODEL_HEIGHT	0.1f
#define COIN_TEX_SIZE 		1.0f
	unsigned int size = devine * 3 * 4;
	Graphics::Model::VERTEX		vtx[size];
		for (int i=0; i < divine; i++) {
		vtx[i * 3 + 0].x = vtx[i * 3 + 2 + divine * 3].x = sinf(i * 2 * PI / divine);
		vtx[i * 3 + 0].y = vtx[i * 3 + 2 + divine * 3].y = cosf(i * 2 * PI / divine);
		vtx[i * 3 + 2].x = vtx[i * 3 + 0 + divine * 3].x = sinf((i + 1) * 2 * PI / divine);
		vtx[i * 3 + 2].y = vtx[i * 3 + 0 + divine * 3].y = cosf((i + 1) * 2 * PI / divine);
		vtx[i * 3 + 1].x = vtx[i * 3 + 1].y = vtx[i * 3 + 1 + divine * 3].x = vtx[i * 3 + 1 + divine * 3].y = 0;
		vtx[i * 3 + 0].z = vtx[i * 3 + 1].z = vtx[i * 3 + 2].z = COIN_MODEL_HEIGHT;
		vtx[i * 3 + 0 + divine * 3].z = vtx[i * 3 + 1 + divine * 3].z = vtx[i * 3 + 2 + divine * 3].z =-COIN_MODEL_HEIGHT;
        
		vtx[i * 3 + 0].u = vtx[i * 3 + 2 + divine * 3].u = vtx[i * 3 + 0].x / 2 + 0.5f;
		vtx[i * 3 + 0].v = vtx[i * 3 + 2 + divine * 3].v = vtx[i * 3 + 0].y / 2 + 0.5f;
		vtx[i * 3 + 2].u = vtx[i * 3 + 0 + divine * 3].u = vtx[i * 3 + 2].x / 2 + 0.5f;
		vtx[i * 3 + 2].v = vtx[i * 3 + 0 + divine * 3].v = vtx[i * 3 + 2].y / 2 + 0.5f;
		vtx[i * 3 + 1].u = vtx[i * 3 + 1 + divine * 3].u = 0.5f;
		vtx[i * 3 + 1].v = vtx[i * 3 + 1 + divine * 3].v = 0.5f;
		
		vtx[i * 6 + 0 + divine * 6].x = vtx[i * 6 + 2 + divine * 6].x = vtx[i * 6 + 4 + divine * 6].x = sinf(i * 2 * PI / divine);
		vtx[i * 6 + 0 + divine * 6].y = vtx[i * 6 + 2 + divine * 6].y = vtx[i * 6 + 4 + divine * 6].y = cosf(i * 2 * PI / divine);
		vtx[i * 6 + 1 + divine * 6].x = vtx[i * 6 + 3 + divine * 6].x = vtx[i * 6 + 5 + divine * 6].x = sinf((i + 1) * 2 * PI / divine);
		vtx[i * 6 + 1 + divine * 6].y = vtx[i * 6 + 3 + divine * 6].y = vtx[i * 6 + 5 + divine * 6].y = cosf((i + 1) * 2 * PI / divine);
		vtx[i * 6 + 0 + divine * 6].z = vtx[i * 6 + 4 + divine * 6].z = vtx[i * 6 + 5 + divine * 6].z =-COIN_MODEL_HEIGHT;
		vtx[i * 6 + 1 + divine * 6].z = vtx[i * 6 + 2 + divine * 6].z = vtx[i * 6 + 3 + divine * 6].z = COIN_MODEL_HEIGHT;
		vtx[i * 6 + 0 + divine * 6].u = vtx[i * 6 + 4 + divine * 6].u = 0;
		vtx[i * 6 + 0 + divine * 6].v = vtx[i * 6 + 4 + divine * 6].v = 0;
		vtx[i * 6 + 2 + divine * 6].u = 0.1f;
		vtx[i * 6 + 2 + divine * 6].v = 0;
		vtx[i * 6 + 1 + divine * 6].u = vtx[i * 6 + 3 + divine * 6].u = 0.1f;
		vtx[i * 6 + 1 + divine * 6].v = vtx[i * 6 + 3 + divine * 6].v = 0.1f;
		vtx[i * 6 + 2 + divine * 6].u = 0;
		vtx[i * 6 + 2 + divine * 6].v = 0.1f;
	}
	
	for (int i=0;i<size;i++) {
		vtx[i].r = vtx[i].g = vtx[i].b = vtx[i].a = 0xff;
	}
	
    Graphics::Model *output = new Graphics::Model();
	output->SetVertexBuffer(vtx, size);
	output->SetTexture(imageFileName);
    return output;
}
