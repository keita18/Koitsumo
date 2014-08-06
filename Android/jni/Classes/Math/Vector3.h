//! @file 		Vector3.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

namespace Math {
class Vector3
{public:
	// Constructure & Destructure
	Vector3() : x(0), y(0), z(0) {}
	Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3(float f) : x(f), y(f), z(f) {}

	// Operator
	Vector3& operator = (const Vector3& v)		{ x = v.x; y = v.y; z = v.z; return *this; }
	Vector3& operator = (float f)				{ x = y = z = f; return *this; }
	Vector3 operator + (const Vector3& v) const	{ return Math::Vector3(x + v.x, y + v.y, z + v.z); }
	Vector3 operator - (const Vector3& v) const { return Math::Vector3(x - v.x, y - v.y, z - v.z); }
	void operator += (const Vector3& v)			{ x += v.x; y += v.y; z += v.z; }
	
	// Public Functions
	void init()		{ x = y = z = 0; }
	
	// Properties
	float x, y, z, pad;					// [16]
}; // (16)
} // namespace Math
