//! @file 		Vector3.cpp
//! @author 	Keita Tanji
//! @breif		
#include "Vector3.h"

namespace Math {

void Vector3::normalize(){
    float length = this->length();
    //長さがほぼ0なら何もしない
    if(length < 0.0001f) {
    	return;
    }
    *this *= 1/length;
}

Vector3 Vector3::operator +(const Vector3& a) const{
    Vector3 ret;
    ret.x = x + a.x;
    ret.y = y + a.y;
    ret.z = z + a.z;
    return ret;
}

Vector3 Vector3::operator -(const Vector3& a) const{
    Vector3 ret;
    ret.x = x - a.x;
    ret.y = y - a.y;
    ret.z = z - a.z;
    return ret;
}

void Vector3::setSub( const Vector3& a, const Vector3& b ){
	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
}

float Vector3::dot( const Vector3& a ) const{
    float ret = a.x*x + a.y*y + a.z*z;
    return ret;
}

void Vector3::setCross( const Vector3& a, const Vector3& b){
    x = a.y*b.z - a.z*b.y;
    y = a.z*b.x - a.x*b.z;
    z = a.x*b.y - a.y*b.x;
}

} //namespace