#include "Windows.h"
#include <stdio.h>
#include <gl/gl.h>
#include "gl/glext.h"
#include "gl/wglext.h"
#include "texture.hpp"
#include "LibPlayer.h"
#include "LibRender.h"

LibPlayer *player = nullptr;
LibRender *render = nullptr;

extern "C" int __declspec(dllexport)  GetDllVersion()
{
	return 0;
};

extern "C" int __declspec(dllexport) CreateRender(HWND wnd)
{
	render = new LibRender();
	return render->InitializeGL(wnd);
}

extern "C" int __declspec(dllexport) ReleaseRender()
{
	render->ReleaseGL();
	delete render;
	return 0;
}


extern "C" int __declspec(dllexport) InitializeGL(HWND wnd)
{
	CreateRender(wnd);
	return 0;
}

extern "C" int __declspec(dllexport) ReleaseGL()
{
	ReleaseRender();
	return 0;
}

extern "C" int __declspec(dllexport) CreatePlayer()
{
	player = new LibPlayer();
	player->Init();
	//player->Open();
	return 0;
}

extern "C" int __declspec(dllexport) Player_Open(const char *url)
{
	return player->Open(url);
}

extern "C" int __declspec(dllexport) Player_Play()
{
	return player->Play();
}

extern "C" int __declspec(dllexport) Player_Pause()
{
	if (player)
	{
		return player->Pause();
	}
	return -1;
}

extern "C" int __declspec(dllexport) Player_Close()
{
	if (player)
	{
		return player->Close();
	}
	return -1;
}

extern "C" int __declspec(dllexport) DestroyPlayer()
{
	if (player)
	{
		delete player;
		player = nullptr;
	}
	return 0;
}


extern "C" int __declspec(dllexport) RenderOneFrame()
{
	AVFrame *frame = player->DecordeOneFrame();
	render->RenderOneFrame(frame);
	return 0;
}




