#pragma warning (disable:4996)
#include <stdio.h>
#include "SimplePlayer.h"
extern "C"
{
#include "SDL.h"
};


int thread_exit = 0;
#define REFRESH_EVENT  (SDL_USEREVENT + 1)

#define BREAK_EVENT  (SDL_USEREVENT + 2)
int refresh_video(void *opaque) {
	thread_exit = 0;
	while (!thread_exit) {
		SDL_Event event;
		event.type = REFRESH_EVENT;
		SDL_PushEvent(&event);
		SDL_Delay(40);
	}
	thread_exit = 0;
	//Break
	SDL_Event event;
	event.type = BREAK_EVENT;
	SDL_PushEvent(&event);

	return 0;
}


int main(int argc, char* argv[])
{

	SimplePlayer player;
	player.Init();
	player.Open();
	player.DecorderAllFrames();


	//SDL---------------------------
	int screen_w = 0, screen_h = 0;
	SDL_Window *screen;
	SDL_Renderer* sdlRenderer;
	SDL_Texture* sdlTexture;
	SDL_Rect sdlRect;

	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return -1;
	}

	screen_w = player.GetWidth();
	screen_h = player.GetHeight();
	//SDL 2.0 Support for multiple windows
	screen = SDL_CreateWindow("Simplest ffmpeg player's Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screen_w, screen_h,
		SDL_WINDOW_OPENGL);

	if (!screen) {
		printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		return -1;
	}

	sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
	//IYUV: Y + U + V  (3 planes)
	//YV12: Y + V + U  (3 planes)
	sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, 
		player.GetWidth(), player.GetHeight());

	sdlRect.x = 0;
	sdlRect.y = 0;
	sdlRect.w = screen_w;
	sdlRect.h = screen_h;

	

	SDL_Thread *refresh_thread = SDL_CreateThread(refresh_video, NULL, NULL);
	SDL_Event event;


	while (1) {
		//Wait
		SDL_WaitEvent(&event);
		if (event.type == REFRESH_EVENT) {
			AVFrame *frame = player.GetOneFrame();
			SDL_UpdateYUVTexture(sdlTexture, &sdlRect,
				frame->data[0], frame->linesize[0],
				frame->data[1], frame->linesize[1],
				frame->data[2], frame->linesize[2]);

			player.FreeOneFrame(frame);


			SDL_RenderClear(sdlRenderer);
			SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &sdlRect);
			SDL_RenderPresent(sdlRenderer);

		}
		else if (event.type == SDL_WINDOWEVENT) {
			//If Resize
			SDL_GetWindowSize(screen, &screen_w, &screen_h);
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_LEFT) {
				int a = 0;
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				int b = 0;
			}
		}
		else if (event.type == SDL_QUIT) {
			thread_exit = 1;
		}
		else if (event.type == BREAK_EVENT) {
			break;
		}
	}

	SDL_Quit();
	return 0;
}

