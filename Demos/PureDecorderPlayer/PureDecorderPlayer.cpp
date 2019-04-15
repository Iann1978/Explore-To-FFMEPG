
#pragma warning(disable:4996)
#include <stdio.h>

extern "C"
{
	#include "SDL.h"
	#include "libavcodec/avcodec.h"
};

#include <queue>

const int bpp = 12;

int screen_w = 480, screen_h = 272;
const int pixel_w = 480, pixel_h = 272;

unsigned char buffer[pixel_w*pixel_h*bpp / 8];


//Refresh Event
#define REFRESH_EVENT  (SDL_USEREVENT + 1)

#define BREAK_EVENT  (SDL_USEREVENT + 2)

int thread_exit = 0;

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

struct MyFrame
{
	uint8_t *data[AV_NUM_DATA_POINTERS];
	int linesize[AV_NUM_DATA_POINTERS];
};
class FrameDecorder
{
	AVCodec *pCodec;
	AVCodecContext *pCodecCtx = NULL;
	AVCodecParserContext *pCodecParserCtx = NULL;

	FILE *fp_in;
	FILE *fp_out;
	

	#define in_buffer_size 4096
	uint8_t in_buffer[in_buffer_size + AV_INPUT_BUFFER_PADDING_SIZE] = { 0 };
	uint8_t *cur_ptr;
	int cur_size;
	AVPacket packet;
	int ret, got_picture;
	int y_size;


	AVCodecID codec_id = AV_CODEC_ID_H264;
	#define filepath_in  "bigbuckbunny_480x272.h264"

	#define filepath_out  "bigbuckbunny_480x272.yuv"
	int first_time = 1;

	std::queue<MyFrame *> frame_queue;

public:
	int Open()
	{
		avcodec_register_all();

		pCodec = avcodec_find_decoder(codec_id);
		if (!pCodec) {
			printf("Codec not found\n");
			return -1;
		}
		pCodecCtx = avcodec_alloc_context3(pCodec);
		if (!pCodecCtx) {
			printf("Could not allocate video codec context\n");
			return -1;
		}

		pCodecParserCtx = av_parser_init(codec_id);
		if (!pCodecParserCtx) {
			printf("Could not allocate video parser context\n");
			return -1;
		}

		//if(pCodec->capabilities&CODEC_CAP_TRUNCATED)
		//    pCodecCtx->flags|= CODEC_FLAG_TRUNCATED; 

		if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
			printf("Could not open codec\n");
			return -1;
		}
		//Input File
		fp_in = fopen(filepath_in, "rb");
		if (!fp_in) {
			printf("Could not open input stream\n");
			return -1;
		}
		//Output File
		fp_out = fopen(filepath_out, "wb");
		if (!fp_out) {
			printf("Could not open output YUV file\n");
			return -1;
		}

		//pFrame = av_frame_alloc();
		av_init_packet(&packet);
		return 0;
	};


	void DecorderAllFrames()
	{
		while (1) {

			cur_size = fread(in_buffer, 1, in_buffer_size, fp_in);
			if (cur_size == 0)
				break;
			cur_ptr = in_buffer;

			while (cur_size > 0) {

				int len = av_parser_parse2(
					pCodecParserCtx, pCodecCtx,
					&packet.data, &packet.size,
					cur_ptr, cur_size,
					AV_NOPTS_VALUE, AV_NOPTS_VALUE, AV_NOPTS_VALUE);

				cur_ptr += len;
				cur_size -= len;

				if (packet.size == 0)
					continue;

				//Some Info from AVCodecParserContext
				printf("[Packet]Size:%6d\t", packet.size);
				switch (pCodecParserCtx->pict_type) {
				case AV_PICTURE_TYPE_I: printf("Type:I\t"); break;
				case AV_PICTURE_TYPE_P: printf("Type:P\t"); break;
				case AV_PICTURE_TYPE_B: printf("Type:B\t"); break;
				default: printf("Type:Other\t"); break;
				}
				printf("Number:%4d\n", pCodecParserCtx->output_picture_number);
				AVFrame	*pFrame = av_frame_alloc();
				ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
				if (ret < 0) {
					printf("Decode Error.\n");
					return;
				}
				if (got_picture) {
					if (first_time) {
						printf("\nCodec Full Name:%s\n", pCodecCtx->codec->long_name);
						printf("width:%d\nheight:%d\n\n", pCodecCtx->width, pCodecCtx->height);
						first_time = 0;
					}

					printf("Succeed to decode 1 frame!\n");
					MyFrame *frame = new MyFrame();
					int size0 = pFrame->height*pFrame->linesize[0];
					frame->data[0] = (uint8_t *)malloc(size0);
					frame->linesize[0] = pFrame->linesize[0];
					memcpy(frame->data[0], pFrame->data[0], size0);

					int size1 = pFrame->height*pFrame->linesize[1];
					frame->data[1] = (uint8_t *)malloc(size1);
					frame->linesize[1] = pFrame->linesize[1];
					memcpy(frame->data[1], pFrame->data[1], size1);

					int size2 = pFrame->height*pFrame->linesize[2];
					frame->data[2] = (uint8_t *)malloc(size2);
					frame->linesize[2] = pFrame->linesize[2];
					memcpy(frame->data[2], pFrame->data[2], size2);

					frame_queue.push(frame);
					
					//return pFrame;
					////Y, U, V
					//for (int i = 0; i < pFrame->height; i++) {
					//	fwrite(pFrame->data[0] + pFrame->linesize[0] * i, 1, pFrame->width, fp_out);
					//}
					//for (int i = 0; i < pFrame->height / 2; i++) {
					//	fwrite(pFrame->data[1] + pFrame->linesize[1] * i, 1, pFrame->width / 2, fp_out);
					//}
					//for (int i = 0; i < pFrame->height / 2; i++) {
					//	fwrite(pFrame->data[2] + pFrame->linesize[2] * i, 1, pFrame->width / 2, fp_out);
					//}


				}
			}

		}

		//Flush Decoder
		packet.data = NULL;
		packet.size = 0;
		while (1) {
			AVFrame	*pFrame = av_frame_alloc();
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
			if (ret < 0) {
				printf("Decode Error.\n");
				return ;
			}
			if (!got_picture) {
				break;
			}
			else {
				//Y, U, V
				//for (int i = 0; i < pFrame->height; i++) {
				//	fwrite(pFrame->data[0] + pFrame->linesize[0] * i, 1, pFrame->width, fp_out);
				//}
				//for (int i = 0; i < pFrame->height / 2; i++) {
				//	fwrite(pFrame->data[1] + pFrame->linesize[1] * i, 1, pFrame->width / 2, fp_out);
				//}
				//for (int i = 0; i < pFrame->height / 2; i++) {
				//	fwrite(pFrame->data[2] + pFrame->linesize[2] * i, 1, pFrame->width / 2, fp_out);
				//}

				printf("Flush Decoder: Succeed to decode 1 frame!\n");
				MyFrame *frame = new MyFrame();
				int size0 = pFrame->height*pFrame->linesize[0];
				frame->data[0] = (uint8_t *)malloc(size0);
				frame->linesize[0] = pFrame->linesize[0];
				memcpy(frame->data[0], pFrame->data[0], size0);

				int size1 = pFrame->height*pFrame->linesize[1];
				frame->data[1] = (uint8_t *)malloc(size1);
				frame->linesize[1] = pFrame->linesize[1];
				memcpy(frame->data[1], pFrame->data[1], size1);

				int size2 = pFrame->height*pFrame->linesize[2];
				frame->data[2] = (uint8_t *)malloc(size2);
				frame->linesize[2] = pFrame->linesize[2];
				memcpy(frame->data[2], pFrame->data[2], size2);

				frame_queue.push(frame);
				return;
			}
		}
	}

	MyFrame *DecorderOneFrame()
	{
		if (frame_queue.size())
		{
			MyFrame *frame = frame_queue.front();
			frame_queue.pop();
			return frame;
		}
		return nullptr;

	}

	void Close()
	{
		fclose(fp_in);
		fclose(fp_out);


		av_parser_close(pCodecParserCtx);

		//av_frame_free(&pFrame);
		avcodec_close(pCodecCtx);
		av_free(pCodecCtx);
	}
	
};



int main(int argc, char* argv[])
{

	FrameDecorder decorder;
	if (decorder.Open() != 0)
	{
		printf("Could open frame decorder.");
		return -1;
	}

	decorder.DecorderAllFrames();
	//decorder(argc, argv);

	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return -1;
	}

	SDL_Window *screen;
	//SDL 2.0 Support for multiple windows
	screen = SDL_CreateWindow("Simplest Video Play SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screen_w, screen_h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!screen) {
		printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		return -1;
	}
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(screen, -1, 0);

	Uint32 pixformat = 0;

	//IYUV: Y + U + V  (3 planes)
	//YV12: Y + V + U  (3 planes)
	pixformat = SDL_PIXELFORMAT_IYUV;

	SDL_Texture* sdlTexture = SDL_CreateTexture(sdlRenderer, pixformat, SDL_TEXTUREACCESS_STREAMING, pixel_w, pixel_h);

	FILE *fp = NULL;
	errno_t err = fopen_s(&fp, "akiyo_qcif.yuv", "rb+");

	if (fp == NULL) {
		printf("cannot open this file\n");
		return -1;
	}

	SDL_Rect sdlRect;

	SDL_Thread *refresh_thread = SDL_CreateThread(refresh_video, NULL, NULL);
	SDL_Event event;
	while (1) {
		//Wait
		SDL_WaitEvent(&event);
		if (event.type == REFRESH_EVENT) {

			MyFrame *frame = decorder.DecorderOneFrame();
			if (!frame)
			{
				printf("Error when decorder one frame.\n");
				return -1;
			}

			printf("Succeed decord one frame.\n");

			int err = SDL_UpdateYUVTexture(sdlTexture, NULL,
				frame->data[0], frame->linesize[0],
				frame->data[1], frame->linesize[1],
				frame->data[2], frame->linesize[2]);

			//if (fread(buffer, 1, pixel_w*pixel_h*bpp / 8, fp) != pixel_w * pixel_h*bpp / 8) {
			//	// Loop
			//	fseek(fp, 0, SEEK_SET);
			//	fread(buffer, 1, pixel_w*pixel_h*bpp / 8, fp);
			//}

			//SDL_UpdateTexture(sdlTexture, NULL, buffer, pixel_w);

			////FIX: If window is resize
			//sdlRect.x = 0;
			//sdlRect.y = 0;
			//sdlRect.w = screen_w;
			//sdlRect.h = screen_h;

			SDL_RenderClear(sdlRenderer);
			SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
			SDL_RenderPresent(sdlRenderer);

		}
		else if (event.type == SDL_WINDOWEVENT) {
			//If Resize
			SDL_GetWindowSize(screen, &screen_w, &screen_h);
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
