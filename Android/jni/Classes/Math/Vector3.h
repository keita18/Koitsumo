//! @file 		Vector3.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <cmath>

namespace Math {

/*
* @ brief 3次元ベクタクラス
*/
class Vector3
{
public:
    //! @brief パラメータ。呼ぶ回数が多いのでpublic
    float x, y, z;

public:
    //! @brief コンストラクタ 
    Vector3(){
    }

    //! @brief 引数つきコンストラクタ 
    Vector3( float ax, float ay, float az ) : x(ax), y(ay), z(az){
    }

    //! @brief vector3オブジェクトからのコンストラクタ（コピーコンストラクタ）
    Vector3( const Vector3& a ) : x( a.x ), y( a.y ), z( a.z ){
    }

    //! @brief パラメータセット
    void set( float aX, float aY, float aZ ){
	    x = aX; y = aY; z = aZ;
    }

    //! @brief 零ベクトルをセット
    void setZero(){
        x = 0.0; y = 0.0; z = 0.0;
    }

    //! @brief ゼロベクトル？
    bool isZero() const{
        return x == 0.0f && y ==0.0f && z == 0.0f;
    }

    //! ベクタの長さを返す
    float length() const{
        return sqrt( x*x + y*y + z*z );
    }

    //! ベクタの長さの２乗を返す
    float squareLength() const{
        return  ( x*x + y*y + z*z );
    }

	//! @brief 加算
    void operator+=( const Vector3& in ){
        x += in.x;
        y += in.y;
        z += in.z;
    }	

    //! @brief 減算
    void operator-=( const Vector3& in ){
        x -= in.x;
        y -= in.y;
        z -= in.z;
    }

    //! @brief スカラ積
    void operator*=( const float r ){
        x *= r;
        y *= r;
        z *= r;
    }

    //! @brief 代入
    void operator=( const Vector3& in ){
        x = in.x;
        y = in.y;
        z = in.z;
    }

    //! @brief 同値比較
    bool operator==(const Vector3& a){
        if( (x == a.x) & (y == a.y) & (z == a.z) )
            return true;
        else 
            return false;
    }

    //! @brief 同値比較
    bool operator!=(const Vector3& a){
        if( (x == a.x) & (y == a.y) & (z == a.z) )
            return false;
        else 
            return true;
    }
    
    //! 正規化
    void normalize();

    //! もう1つのベクトルとの加算
    //! インスタンスのコピーが生じることに注意
    Vector3 operator+( const Vector3& a ) const;

    //! もう1つのベクトルとの減算
    //! インスタンスのコピーが生じることに注意
    Vector3 operator-( const Vector3& a ) const;

    //! 2つのベクトルの減算結果をセット
    void setSub( const Vector3&, const Vector3& );

    //! 内積を返す
    float dot( const Vector3& ) const;   
    
    //! 外積をセット
    void setCross( const Vector3&, const Vector3& );
};

// class Vector3
// {public:
// 	// Constructure & Destructure
// 	Vector3() : x(0), y(0), z(0) {}
// 	Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
// 	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
// 	Vector3(float f) : x(f), y(f), z(f) {}

// 	// Operator
// 	Vector3& operator = (const Vector3& v)		{ x = v.x; y = v.y; z = v.z; return *this; }
// 	Vector3& operator = (float f)				{ x = y = z = f; return *this; }
// 	Vector3 operator + (const Vector3& v) const	{ return Math::Vector3(x + v.x, y + v.y, z + v.z); }
// 	Vector3 operator - (const Vector3& v) const { return Math::Vector3(x - v.x, y - v.y, z - v.z); }
// 	void operator += (const Vector3& v)			{ x += v.x; y += v.y; z += v.z; }
	
// 	// Public Functions
// 	void init()		{ x = y = z = 0; }
	
// 	// Properties
// 	float x, y, z, pad;					// [16]
// }; // (16)

} // namespace Math
