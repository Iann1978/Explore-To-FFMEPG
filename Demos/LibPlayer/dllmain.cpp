#include "Windows.h"
#include <stdio.h>
#include <gl/gl.h>
#include "gl/glext.h"
#include "gl/wglext.h"
#include "texture.hpp"
#include "LibPlayer.h"




extern "C" int __declspec(dllexport)  GetDllVersion()
{
	return 0;
};
static HWND	WND;
static HDC DC;
static HGLRC RC;
extern "C" int __declspec(dllexport) InitializeGL(HWND wnd)
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

	return 0;
}

extern "C" int __declspec(dllexport) ReleaseGL()
{
	wglMakeCurrent(NULL, NULL);
	if (RC) {
		wglDeleteContext(RC);
	}
	if (DC) {
		ReleaseDC(WND, DC);
	}
	return 0;
}

LibPlayer *player = nullptr;
GLuint texture = 0;
extern "C" int __declspec(dllexport) CreatePlayer()
{
	player = new LibPlayer();
	player->Init();
	player->Open();
	return 0;
}

extern "C" int __declspec(dllexport) RenderOneFrame()
{
	AVFrame *frame = player->DecordeOneFrame();

	int width = player->GetWidth();
	int height = player->GetHeight();

	SwsContext *img_convert_ctx = sws_getContext(width, height, AV_PIX_FMT_YUV420P,
		width, height, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL,
		NULL, NULL);

	AVFrame *pFrameRGB = av_frame_alloc();
	unsigned char *out_buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGB24, width, height, 1));
	av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, out_buffer,
		AV_PIX_FMT_RGB24, width, height, 1);



	int lines = sws_scale(img_convert_ctx, frame->data, frame->linesize, 0, height, pFrameRGB->data, pFrameRGB->linesize);


	if (0 == texture)
	{
		glGenTextures(1, &texture);
	}
	

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texture);



	// Give the image to OpenGL
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 512, 256, GL_RGB, GL_UNSIGNED_BYTE, frame->data[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pFrameRGB->data[0]);


	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

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

extern "C" int __declspec(dllexport) DestroyPlayer()
{
	delete player;
	return 0;
}







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

	//GLuint texture = loadBMP_custom("d:/a.bmp");
	//glEnable(GL_TEXTURE);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture);

	//glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glBindTexture(GL_TEXTURE_2D, texture);

	//glClearColor(1.0f, 0.586f, 0.949f, 1.0f);	// rgb(33,150,243)
	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0, 0, 0);
	


	//glBegin(GL_TRIANGLES);

	//glTexCoord2f(0, 0);
	//glVertex3d(0, 0, 0);

	//glTexCoord2f(1, 0);
	//glVertex3d(1, 0, 0);

	//glTexCoord2f(0, 1);
	//glVertex3d(0, 1, 0);

	//glEnd();

	LibPlayer player;
	player.Init();
	player.Open();
	AVFrame *frame = player.DecordeOneFrame();

	int count = 5;
	while (count--)
	{
		frame = player.DecordeOneFrame();

	}
	int width = player.GetWidth();
	int height = player.GetHeight();

	SwsContext *img_convert_ctx = sws_getContext(width,		height, AV_PIX_FMT_YUV420P,
		width, height, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL,
		NULL, NULL);

	AVFrame *pFrameRGB = av_frame_alloc();
	unsigned char *out_buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGB24, width, height, 1));
	av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, out_buffer,
		AV_PIX_FMT_RGB24, width,height, 1);


	
	int lines = sws_scale(img_convert_ctx, frame->data, frame->linesize, 0, height, pFrameRGB->data, pFrameRGB->linesize);


	GLuint texture;
	glGenTextures(1, &texture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texture);

	

	// Give the image to OpenGL
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 512, 256, GL_RGB, GL_UNSIGNED_BYTE, frame->data[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pFrameRGB->data[0]);


	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

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