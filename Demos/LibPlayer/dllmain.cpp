#include "Windows.h"
#include <stdio.h>
#include <gl/gl.h>
#include "gl/glext.h"
#include "gl/wglext.h"
#include "texture.hpp"




extern "C" int __declspec(dllexport)  GetDllVersion()
{
	return 0;
};

extern "C" int __declspec(dllexport) DrawTriange();

extern "C" int __declspec(dllexport) CreateGL(HWND wnd)
{
	HDC DC = GetDC(wnd);

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

	HGLRC RC = wglCreateContext(DC);	// Rendering Contex

	if (RC == 0) {
		printf("wglCreateContext() failed.");
		return 3;
	}

	if (wglMakeCurrent(DC, RC) == false) {
		printf("wglMakeCurrent() failed.");
		return 4;
	}

	GLuint texture = loadBMP_custom("d:/a.bmp");
	glEnable(GL_TEXTURE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture);

	glClearColor(1.0f, 0.586f, 0.949f, 1.0f);	// rgb(33,150,243)
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	


	glBegin(GL_TRIANGLES);

	glTexCoord2f(0, 0);
	glVertex3d(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3d(1, 0, 0);

	glTexCoord2f(0, 1);
	glVertex3d(0, 1, 0);

	glEnd();



	//DrawTriange();
	SwapBuffers(DC);
	return 0;

}


extern "C" int __declspec(dllexport) DrawTriange()
{
	glClearColor(1.0f, 0.586f, 0.949f, 1.0f);	// rgb(33,150,243)
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(1, 0);
	glVertex2d(0, 1);
	glEnd();
	return 0;
}