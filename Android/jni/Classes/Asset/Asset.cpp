//! @file 		Asset.cpp
//! @author 	Keita Tanji
//! @breif		
#include "Asset.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

#include <pnginfo.h>


/*static*/ AAssetManager*	Asset::pAssetManager_ = NULL;
/*static*/ int 		Asset::offset_ = 0;;

//=============================================================================
/*static*/ void	Asset::setAssetManager(AAssetManager* pAssetManager)
{
	pAssetManager_ = pAssetManager;
}

//=============================================================================
/*static*/ bool Asset::loadPngImage(
	const char* filename, 
	png_uint_32* outWidth, 
	png_uint_32* outHeight, 
	GLint *type, 
	u_char **outData)
{
  png_structp png_ptr;
  png_infop info_ptr;
  int depth;
  int color_type;

  offset_ = 0;
  offset_++;

  if(pAssetManager_ == NULL) return false;

  // テクスチャ−データ(pngファイル)を読み込む
  AAsset* assetFile = AAssetManager_open(pAssetManager_, filename, AASSET_MODE_RANDOM);
  int size = AAsset_getLength(assetFile);
  u_char* buf = (u_char*)malloc(size);
  AAsset_read(assetFile, buf, size);
  AAsset_close(assetFile);

  // PNGファイルであるか？
  if (png_sig_cmp(buf,0,8) != 0)
    return false;

  // 読み込み用メモリを生成
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                   NULL, NULL, NULL);
  // メモリが生成できなければ終了
  if (png_ptr == NULL) {
    if (buf){free(buf);buf=NULL;}
    return false;
  }

  // 画像情報用メモリを生成(必須)
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    if (buf){free(buf);buf=NULL;}
    return false;
  }

  // データ読み込み時に呼ばれるコールバック関数を定義する
  png_set_read_fn(png_ptr, buf, Asset::callbackRead);
  offset_ = 8;

  // 内部でエラーが発生したら、ここに飛んでくる
  if (setjmp(png_jmpbuf(png_ptr))) {
    
    // 確保したメモリーを解放する
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    if (buf){free(buf);buf=NULL;}
    return false;
  }

  // PNGファイルの識別エリア(8バイト)をスキップ
  png_set_sig_bytes(png_ptr, 8);

  // PNGファイルを読み込む
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

  // PNG画像情報を取得
  *outWidth = info_ptr->width;
  *outHeight = info_ptr->height;
  color_type = info_ptr->color_type;
  depth = info_ptr->bit_depth;

  // 色のタイプからテクスチャの画像情報を設定
  switch (color_type) {
  case PNG_COLOR_TYPE_PALETTE:
    png_set_palette_to_rgb(png_ptr);
    *type = GL_RGB;
    break;

  case PNG_COLOR_TYPE_RGB:
    *type = GL_RGB;
    break;

  case PNG_COLOR_TYPE_RGBA:
    *type = GL_RGBA;
    break;
  default:
    // 対応していないタイプなので処理を終了
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    if (buf){free(buf);buf=NULL;}
    return false;
  }

  // 画像１ライン分のメモリ領域を確保
  unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
  *outData = (unsigned char*) malloc(row_bytes * *outHeight);

  // 画像情報を行単位で取得できるようにする
  png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

  int i;
  for (i = 0; i < *outHeight; i++) {
    // 画像が上下反転するように格納する
    // (OpenGLのテクスチャーは上下反転して表示されるため)
    memcpy(*outData+(row_bytes * (*outHeight-1-i)), row_pointers[i], row_bytes);
  }
  // メモリをすべて解放する
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  free(buf);

  return true;
}

/*static*/ void Asset::callbackRead(png_structp pPng, png_bytep buf, png_size_t size)
{
	u_char* p = (u_char*)png_get_io_ptr(pPng);
	memcpy(buf, p + offset_, size);
	offset_ += size;
}

