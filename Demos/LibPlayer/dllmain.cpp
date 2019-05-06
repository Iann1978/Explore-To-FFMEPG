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

extern "C" __declspec(dllexport) int GetDllVersion()
{
	return 0;
};

extern "C" __declspec(dllexport) int CreateRender(HWND wnd)
{
	render = new LibRender();
	return render->InitializeGL(wnd);
}

extern "C" __declspec(dllexport) int ReleaseRender()
{
	if (render)
	{
		render->ReleaseGL();
		delete render;
		render = nullptr;
	}
	return 0;
}


extern "C" __declspec(dllexport) int InitializeGL(HWND wnd)
{
	CreateRender(wnd);
	return 0;
}

extern "C" __declspec(dllexport) int ReleaseGL()
{
	ReleaseRender();
	return 0;
}

extern "C" __declspec(dllexport) int CreatePlayer()
{
	player = new LibPlayer();
	player->Init();
	//player->Open();
	return 0;
}

extern "C" __declspec(dllexport) int Player_Open(const char *url)
{
	return player->Open(url);
}

extern "C" __declspec(dllexport) int Player_Play()
{
	return player->Play();
}

extern "C" __declspec(dllexport) int Player_Pause()
{
	if (player)
	{
		return player->Pause();
	}
	return -1;
}

extern "C" __declspec(dllexport) int Player_Close()
{
	if (player)
	{
		return player->Close();
	}
	return -1;
}

extern "C" __declspec(dllexport) int DestroyPlayer()
{
	if (player)
	{
		delete player;
		player = nullptr;
	}
	return 0;
}


extern "C" __declspec(dllexport) int RenderOneFrame()
{
	AVFrame *frame = player->DecordeOneFrame();
	render->RenderOneFrame(frame);
	return 0;
}




