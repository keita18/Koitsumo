//! @file 		model.cpp
//! @author 	Keita Tanji
//! @breif		
#include "model.h"
#include <string.h>		//memcpy
#include "pch.h"
#include "../../Asset/Asset.h"

namespace Graphics {

//=============================================================================
Model::Model()
: _vtx(0)
, _vtx_num(0)
, _textag(0)
, _position()
, _shift(0, 0, 0)
, _rotation()
, _scale(1, 1, 1)
{
}
//=============================================================================
Model::Model(const Model& m)
: _vtx(0)
, _color(0)
, _uv(0)
, _vtx_num(m._vtx_num)
, _textag(m._textag)
, _position(m._position)
, _shift(m._shift)
, _rotation(m._rotation)
, _scale(m._scale)
{
	_vtx = new float[3 * _vtx_num];
	memcpy(_vtx, m._vtx, 3 * _vtx_num * sizeof(float));
	_color = new unsigned int[3* _vtx_num];
	memcpy(_color, m._color, 3 * _vtx_num * sizeof(unsigned int));
	_uv = new float[2 * _vtx_num];
	memcpy(_uv, m._uv, 2 * _vtx_num * sizeof(float));
}
//=============================================================================
Model::~Model()
{
	delete [] _vtx;
	delete [] _color;
	delete [] _uv;
}
//=============================================================================
void Model::SetTexture(const char* imageName)
{
	//texture生成
	unsigned int width = 0;
	unsigned int height = 0;
	GLint type = 0;
	GLubyte *textureImage;

	//画像をロード
	bool loadResult = Asset::loadPngImage(imageName, &width, &height, &type, &textureImage);
	if(loadResult == false) return;

	glEnable( GL_TEXTURE_2D );
    glGenTextures(1, &_textag);
    glBindTexture(GL_TEXTURE_2D, _textag);
    glTexImage2D(GL_TEXTURE_2D, 0, type/*GL_RGBA*/, width, height, 0, type/*GL_RGBA*/, GL_UNSIGNED_BYTE, textureImage);
    glBindTexture(GL_TEXTURE_2D, 0);

    LOGI("Model::SetTexture, type=%d, w=%d, h=%d, _tag=%d", type, width, height, _textag);
}
//=============================================================================
void Model::Draw()
{
	assert(_vtx);
	if (!_vtx) return;

	Math::Vector3 pos = _position;
	Math::Vector3 scale = _scale;
	// pos *= Screen::RATIO;
	// scale *= Screen::RATIO;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// glTranslatef(_position.x + _shift.x, _position.y + _shift.y, _position.z + _shift.z);
	// glScalef(_scale.x, _scale.y, _scale.z);
	glTranslatef(pos.x + _shift.x, pos.y + _shift.y, pos.z + _shift.z);
	glScalef(scale.x, scale.y, scale.z);
	glRotatef(_rotation.z, 	  0, 	0, 	1.0f);
	glRotatef(_rotation.y,	  0, 	1.0f,	0);
	glRotatef(_rotation.x, 1.0f, 	0,	0);

	if(_textag > 0) {
		glBindTexture(GL_TEXTURE_2D, _textag);
		glEnable(GL_TEXTURE_2D);
	}
	else { 
		glDisable(GL_TEXTURE_2D);
	}

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	// Render
	glVertexPointer(3, GL_FLOAT, 0, _vtx);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, _color);
	glTexCoordPointer(2, GL_FLOAT, 0, _uv);
	
	glDrawArrays(GL_TRIANGLES, 0, _vtx_num);
}
//=============================================================================
void Model::SetVertexBuffer(void* buf, unsigned int num)
{
	VERTEX *vertex = (VERTEX *)buf;
	_vtx_num = num;
	_vtx = new GLfloat[num * 3];
	_uv = new GLfloat[num * 2];
	_color = new GLuint[num];
	for (int i = 0; i < num; ++i)
	{
		_vtx[i * 3 + 0] = vertex[i].x;
		_vtx[i * 3 + 1] = vertex[i].y;
		_vtx[i * 3 + 2] = vertex[i].z;
		_uv[i * 2 + 0] = vertex[i].u;
		_uv[i * 2 + 1] = 1.0f - vertex[i].v;	//反転forAndroid
		_color[i] = (vertex[i].a << 24) | (vertex[i].r << 16) | (vertex[i].g << 8) | vertex[i].b;
	}	
}

} // Graphics
