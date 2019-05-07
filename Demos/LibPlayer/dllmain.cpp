#include "Windows.h"
#include <stdio.h>
#include <gl/gl.h>
#include "gl/glext.h"
#include "gl/wglext.h"
#include "texture.hpp"
#include "LibPlayer.h"
#include "LibRender.h"

//LibPlayer *player = nullptr;
//LibRender *render = nullptr;

extern "C" __declspec(dllexport) int GetDllVersion()
{
	return 0;
};

extern "C" __declspec(dllexport) LibRender *CreateRender(HWND wnd)
{
	LibRender *render = new LibRender();
	render->InitializeGL(wnd);
	return render;
}

extern "C" __declspec(dllexport) int DestroyRender(LibRender *render)
{
	if (render)
	{
		render->ReleaseGL();
		delete render;
		render = nullptr;
	}
	return 0;
}


//extern "C" __declspec(dllexport) int InitializeGL(HWND wnd)
//{
//	CreateRender(wnd);
//	return 0;
//}
//
//extern "C" __declspec(dllexport) int ReleaseGL()
//{
//	ReleaseRender();
//	return 0;
//}

extern "C" __declspec(dllexport) LibPlayer *CreatePlayer()
{
	LibPlayer *player = new LibPlayer();
	player->Init();
	//player->Open();
	return player;
}

extern "C" __declspec(dllexport) int DestroyPlayer(LibPlayer *player)
{
	if (player)
	{
		delete player;
		player = nullptr;
	}
	return 0;
}

extern "C" __declspec(dllexport) int Player_Open(LibPlayer *player, const char *url)
{
	return player->Open(url);
}

extern "C" __declspec(dllexport) int Player_Play(LibPlayer *player)
{
	return player->Play();
}

extern "C" __declspec(dllexport) int Player_Pause(LibPlayer *player)
{
	if (player)
	{
		return player->Pause();
	}
	return -1;
}

extern "C" __declspec(dllexport) int Player_Close(LibPlayer *player)
{
	if (player)
	{
		return player->Close();
	}
	return -1;
}

extern "C" __declspec(dllexport) int Player_GetDuation(LibPlayer *player)
{
	if (player)
	{
		return player->GetDuation();
	}
	return -1;
}

extern "C" __declspec(dllexport) int Player_GetCurrentPosition(LibPlayer *player)
{
	if (player)
	{
		return player->GetCurrentPosition();
	}
	return -1;
}





extern "C" __declspec(dllexport) int RenderOneFrame(LibRender *render, LibPlayer *player)
{
	AVFrame *frame = player->DecordeOneFrame();
	render->RenderOneFrame(frame);
	return 0;
}




