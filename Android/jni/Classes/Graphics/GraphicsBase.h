//! @file 		GraphicsBase.h
//! @author 	Keita Tanji
//! @breif		
#pragma once

#include <GLES/gl.h>

namespace Graphics {
	enum DisplayClearMode {
		DisplayClearModeColor	= 1,
		DisplayClearModeZBuffer = 1<<1,
		DisplayClearModeStencil = 1<<2,
		DisplayClearModeAll = DisplayClearModeColor | DisplayClearModeZBuffer | DisplayClearModeStencil
	};
	
	static void ClearDisplayBuffer(int m) {
		GLbitfield bit = 0;
		if (m & DisplayClearModeColor)		bit |= GL_COLOR_BUFFER_BIT;
		if (m & DisplayClearModeZBuffer)	bit |= GL_DEPTH_BUFFER_BIT;
		if (m & DisplayClearModeStencil)	bit |= GL_STENCIL_BUFFER_BIT;
		if (bit) glClear(bit);
	}

	enum WriteColorMask {
		WriteColorMaskNone = 0,
		WriteColorMaskRed = 1,
		WriteColorMaskGreen = 1<<1,
		WriteColorMaskBlue = 1<<2,
		WriteColorMaskAlpha = 1<<3,
		WriteColorMaskAll = WriteColorMaskRed | WriteColorMaskGreen | WriteColorMaskBlue | WriteColorMaskAlpha
	};
	
	static void SetWriteColorMask(unsigned char m) {
		unsigned char redMask = 0;
		unsigned char greenMask = 0;
		unsigned char blueMask = 0;
		unsigned char alphaMask = 0;
		if (m & WriteColorMaskRed) {
			redMask = 0xff;
		} else redMask = 0;
		if (m & WriteColorMaskGreen) {
			greenMask = 0xff;
		} else greenMask = 0;
		if (m & WriteColorMaskBlue) {
			blueMask = 0xff;
		} else blueMask = 0;
		if (m & WriteColorMaskAlpha) {
			alphaMask = 0xff;
		} else alphaMask = 0;
		glColorMask(redMask, greenMask, blueMask, alphaMask);
	}
								  
	enum StencilFlag {
		StencilFlagNone = 0,
		StencilFlagUI,
	};

	static void SetStencilWriteMode(StencilFlag f) {
		glEnable(GL_STENCIL_TEST);
		if (f==StencilFlagNone) {
			glStencilFunc(GL_EQUAL, 0, 0);
			glStencilOp(GL_KEEP, GL_KEEP ,GL_KEEP);
		}
		else {
			glStencilFunc(GL_ALWAYS, int(f), 0xff);
			glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);
		}
	}
	
	static void SetStencilFilter(StencilFlag f) {
		glStencilOp(GL_KEEP,GL_KEEP ,GL_KEEP);
		if (f==StencilFlagNone) {
			glDisable(GL_STENCIL_TEST);
			glStencilFunc(GL_EQUAL, 0, 0);
		}
		else {
			glEnable(GL_STENCIL_TEST);
			glStencilFunc(GL_EQUAL, int(f), 0xff);
		}
	}
}
