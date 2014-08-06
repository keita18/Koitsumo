//! @file 		model.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <GLES/gl.h>
#include "Classes/Math/Vector3.h"

namespace Graphics {
class Model
{
public:
	typedef struct {
		GLfloat 	x,y,z;
		GLfloat 	u,v;
		GLubyte		r,g,b,a;
	} VERTEX;

public:
	Model();
	Model(const Model& m);
	~Model();

	void Draw();

	void SetVertexBuffer(void* buf, unsigned int num);

	unsigned int GetVertexNumber()		{ return _vtx_num; }
	float*	GetVertex()					{ return _vtx; }
	float*	GetUV()						{ return _uv; }
	unsigned int*	GetColor()			{ return _color; }

	Math::Vector3 GetPosition() const	{ return _position; }
	Math::Vector3 GetShift() const		{ return _shift; }
	Math::Vector3 GetRotation() const 	{ return _rotation; }
	Math::Vector3 GetScale() const		{ return _scale; }
	void SetPosition(const Math::Vector3& p) 	{ _position = p; }
	void SetSfhit(const Math::Vector3& p)		{ _shift = p; }
	void SetRotation(const Math::Vector3& p)	{ _rotation = p; }
	void SetScale(const Math::Vector3& s)		{ _scale = s; }
	void SetTexture(const char* imageName);

private:
	Math::Vector3 	_position;
	Math::Vector3 	_rotation;
	Math::Vector3 	_scale;
	Math::Vector3 	_shift;

	unsigned int 	_vtx_num;
	GLfloat			*_vtx;
	GLfloat 		*_uv;
	GLuint			*_color;
	GLuint			_textag;
};
} // Graphics