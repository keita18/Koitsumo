//! @file 		Draw.cpp
//! @author 	Keita Tanji
//! @breif		
#include "Draw.h"

/*static*/ Draw*	Draw::instance_ = NULL;

static GLshort drawVtx[] = { 0, 0, 1, 0, 0, 1, 1, 1 };
static GLubyte drawCol[] = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };

//=============================================================================
/*static*/ Draw*	Draw::singleton()
{
	if(instance_ == NULL) instance_ = new Draw();
	return instance_;
}

//=============================================================================
void Draw::setColorWithSide(int s, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	drawCol[s*4+0] = r;
	drawCol[s*4+1] = g;
	drawCol[s*4+2] = b;
	drawCol[s*4+3] = a;
}
//=============================================================================
void Draw::setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	drawCol[0] = drawCol[4] = drawCol[8] =  drawCol[12] = r;
	drawCol[1] = drawCol[5] = drawCol[9] =  drawCol[13] = g;
	drawCol[2] = drawCol[6] = drawCol[10] = drawCol[14] = b;
	drawCol[3] = drawCol[7] = drawCol[11] = drawCol[15] = a;
}
//=============================================================================
void Draw::drawBox(int x, int y, int w, int h)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	glScalef(w, h, 1);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//Render
	glVertexPointer(2, GL_SHORT, 0, drawVtx);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, drawCol);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
