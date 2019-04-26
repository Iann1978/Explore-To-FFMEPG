#include "LibRender.h"
#include <stdio.h>
#include <gl/gl.h>
#include "gl/glext.h"
#include "gl/wglext.h"
#include "texture.hpp"

LibRender::LibRender()
{
	
}


LibRender::~LibRender()
{
}


int LibRender::InitializeGL(HWND wnd)
{
	WND = wnd;
	DC = GetDC(wnd);

	PIXELFORMATDESCRIPTOR fakePFD;
	ZeroMemory(&fakePFD, sizeof(fakePFD));
	fakePFD.nSize = sizeof(fakePFD);
	fakePFD.nVersion = 1;
	fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	fakePFD.iPixelType = PFD_TYPE_RGBA;
	fakePFD.cColorBits = 32;
	fakePFD.cAlphaBits = 8;
	fakePFD.cDepthBits = 24;

	const int fakePFDID = ChoosePixelFormat(DC, &fakePFD);
	if (fakePFDID == 0) {
		printf("ChoosePixelFormat() failed.");
		return 1;
	}

	if (SetPixelFormat(DC, fakePFDID, &fakePFD) == false) {
		printf("SetPixelFormat() failed.");
		return 2;
	}

	RC = wglCreateContext(DC);	// Rendering Contex

	if (RC == 0) {
		printf("wglCreateContext() failed.");
		return 3;
	}

	if (wglMakeCurrent(DC, RC) == false) {
		printf("wglMakeCurrent() failed.");
		return 4;
	}

	if (0 == texture)
	{
		glGenTextures(1, &texture);
	}



	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return 0;
}


int LibRender::ReleaseGL()
{
	if (texture)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}
	

	wglMakeCurrent(NULL, NULL);
	if (RC) {
		wglDeleteContext(RC);
	}
	if (DC) {
		ReleaseDC(WND, DC);
	}
	return 0;
}

int LibRender::RenderOneFrame(AVFrame *frame)
{
	if (frame == nullptr)
		return 1;

	int width = frame->width;
	int height = frame->height;

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, frame->data[0]);
	

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE);
	glEnable(GL_TEXTURE_2D);	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3d(-1, -1, 0);
	glTexCoord2f(0, 1);
	glVertex3d(1, -1, 0);
	glTexCoord2f(0, 0);
	glVertex3d(1, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3d(-1, 1, 0);
	glEnd();

	SwapBuffers(DC);
	return 0;
}