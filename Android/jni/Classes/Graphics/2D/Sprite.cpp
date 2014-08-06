//! @file 		Sprite.cpp
//! @author 	Keita Tanji
//! @breif		
#include "Sprite.h"
#include "pch.h"
#include "../../Asset/Asset.h"

static GLshort sprVtx[] = { 0, 0, 1, 0, 0, 1, 1, 1 };
//static GLshort sprVtx[] = { 0, 1, 1, 1, 0, 0, 1, 0 };

Sprite::Sprite(const char* imgName, int fw, int fh)
: _tag(0)
, _frameSize()
, _texSize()
, _pitch(0)
, _count(0)
{
	memset(_sprCol, 255, sizeof(GLubyte) * 16);

	_frameSize.width = fw;
	_frameSize.height = fh;

	loadImage(imgName);
}

Sprite::~Sprite()
{}

void Sprite::loadImage(const char* imgName)
{
	//texture生成
	unsigned int width = 0;
	unsigned int height = 0;
	GLint type = 0;
	GLubyte *textureImage;

	//画像をロード
	bool loadResult = Asset::loadPngImage(imgName, &width, &height, &type, &textureImage);
	if(loadResult == false) return;

	_texSize.width = width;
	_texSize.height = height;
	if(_frameSize.width < 0) _frameSize.width = _texSize.width;
	if(_frameSize.height < 0) _frameSize.height = _texSize.height;
	_pitch = width / _frameSize.width;

    // テクスチャを作成し、データを転送
	glEnable( GL_TEXTURE_2D );
    glGenTextures(1, &_tag);
    glBindTexture(GL_TEXTURE_2D, _tag);
    //※ typeであってる？
    glTexImage2D(GL_TEXTURE_2D, 0, type/*GL_RGBA*/, width, height, 0, type/*GL_RGBA*/, GL_UNSIGNED_BYTE, textureImage);
    glBindTexture(GL_TEXTURE_2D, 0);

	LOGI("#################################¥n");
    LOGI("loadImage, type=%d, w=%d, h=%d, _tag=%d", type, width, height, _tag);
}

void Sprite::drawWithFrame(int f, int x, int y, int w, int h)
{
	//倍で描画
	x *= 2;
	y *= 2;
	w *= 2;
	h *= 2;

	CGRect frameRect;
	if(_tag) {
		frameRect.origin.x = _frameSize.width * (f % _pitch) / _texSize.width;
		frameRect.origin.y = _frameSize.height * (f / _pitch) / _texSize.height;
		frameRect.size.width = _frameSize.width / _texSize.width;
		frameRect.size.height = _frameSize.height / _texSize.height;
	}
	GLfloat texCoord[8];
	//y座標反転
	texCoord[0] = texCoord[4] = frameRect.origin.x;
	texCoord[1] = texCoord[3] = 1.0f - frameRect.origin.y;
	texCoord[2] = texCoord[6] = frameRect.origin.x + frameRect.size.width;
	texCoord[5] = texCoord[7] = 1.0f - (frameRect.origin.y + frameRect.size.height);
	// texCoord[0] = texCoord[4] = frameRect.origin.x + 0.005f;
	// texCoord[1] = texCoord[3] = frameRect.origin.y + 0.005f;
	// texCoord[2] = texCoord[6] = frameRect.origin.x + frameRect.size.width + 0.005f;
	// texCoord[5] = texCoord[7] = frameRect.origin.y + frameRect.size.height + 0.005f;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	if(w<0) w = _frameSize.width;
	if(h<0) h = _frameSize.height;
	glScalef(w, h, 1);

	_count++;
	if(_count > 30)
	{
		LOGI("drawWithFrame, f=%d, x=%d, y=%d, w=%d, h=%d, tag=%d", f, x, y, w, h, _tag);
		LOGI("texcoord, %f, %f, %f, %f, %f, %f, %f, %f", texCoord[0], texCoord[1], texCoord[2], texCoord[3], texCoord[4], texCoord[5], texCoord[6], texCoord[7]);
		_count = 0;
	}

	if(_tag > 0)
		glBindTexture(GL_TEXTURE_2D, _tag);

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_SHORT, 0, sprVtx);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, _sprCol);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Sprite::drawBox()
{
	// 頂点リスト
#define LENGTH (500)
	short triangleBuffer[] = {
	/*        X                Y          Z */
	-LENGTH / 2,          -LENGTH / 2,          0, 
	 LENGTH - LENGTH / 2, -LENGTH / 2,          0, 
	-LENGTH / 2,           LENGTH - LENGTH / 2, 0,
	 LENGTH - LENGTH / 2,  LENGTH - LENGTH / 2, 0, };

	// 頂点カラーリスト
	float colorBuffer[] = {
	/*   R    G    B    A  */
	   1.0, 0.0, 0.0, 1.0, 
	   0.0, 1.0, 0.0, 1.0, 
	   0.0, 0.0, 1.0, 1.0, 
	   0.5, 0.5, 0.0, 1.0, };

	float texCoord[] = {
		0.0f, 0.0f, 
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
	};


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.0);

	//glScalef(2, 2, 1);

	//glRotatef(0, 0, 0, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	// 利用するテクスチャは非圧縮とする
	// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, _tag);

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//strideが0だと隙間なく頂点配列が埋まってるという意味
	glVertexPointer(3, GL_SHORT, 0, triangleBuffer);
	glColorPointer(4, GL_FLOAT, 0, colorBuffer);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}
