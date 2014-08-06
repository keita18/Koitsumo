//! @file 		Functions.cpp
//! @author 	Keita Tanji
//! @breif		
#pragma once

namespace Math{

//三角関数
float sin( float );
float cos( float );
float tan( float );
//逆三角関数
float asin( float );
float acos( float );
float atan( float );
float atan2( float y, float x );

float pow( float a, float b ); //累乗(aのb乗)
float log2( float ); //2を底とする対数
float log10( float ); //10を底とする対数
float abs( float );//絶対値
float min( float, float ); //最小
float max( float, float ); //最大
float sqrt( float ); //平方根

const float EPSILON = 0.00000011920928955078125f; //floatの限界精度(1/2^23)
const float FLOAT_MAX = 1.7014117331926442990585209174226e+38; //floatの最大値((2^24-1)/2^23 * 2^126 )

bool isSpecial( float ); //NaN,Infならtrue
	
void initRand();
int getRand( int min, int max );
	
} //namespace Math