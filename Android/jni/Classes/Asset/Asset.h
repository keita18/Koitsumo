//! @file 		Asset.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <jni.h>
#include <errno.h>
#include <android/asset_manager.h>
#include <android/log.h>
#include <GLES/gl.h>
#include <png.h>

class Asset
{
public:
	static void	setAssetManager(AAssetManager* pAssetManager);
	static bool loadPngImage(
		const char* filename, 
		png_uint_32* outWidth, 
		png_uint_32* outHeight, 
		GLint *type, 
		u_char **outData);
	static void callbackRead(png_structp pPng, png_bytep buf, png_size_t size);

private:
	static AAssetManager*	pAssetManager_;
	static int 		offset_;
};