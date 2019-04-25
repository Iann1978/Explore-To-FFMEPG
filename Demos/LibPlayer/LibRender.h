#pragma once
#include "Windows.h"
#include <gl/gl.h>
#include "gl/glext.h"
#include "gl/wglext.h"
#include "texture.hpp"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
}
class LibRender
{
	HWND	WND;
	HDC		DC;
	HGLRC	RC;
	GLuint texture = 0;
public:
	LibRender();
	~LibRender();

public:
	int InitializeGL(HWND wnd);
	int ReleaseGL();
	int RenderOneFrame(AVFrame *frame);
};

