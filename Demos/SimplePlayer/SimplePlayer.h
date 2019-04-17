#pragma once
#pragma warning(disable:4996)
#include <queue>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
};


class SimplePlayer
{
	AVFormatContext	*pFormatCtx;
	int				i, videoindex;
	AVCodecContext	*pCodecCtx;
	AVCodec			*pCodec;
	AVFrame	*pFrame, *pFrameYUV;
	unsigned char *out_buffer;
	AVPacket *packet;
	int y_size;
	int ret, got_picture;
	struct SwsContext *img_convert_ctx;

	const char *filepath = "Titanic.mkv";
	//SDL---------------------------
	int screen_w = 0, screen_h = 0;
	FILE *fp_yuv;
	
	std::queue<AVFrame *> frame_queue;

public:

	int GetWidth()
	{
		return pCodecCtx->width;
	}

	int GetHeight()
	{
		return pCodecCtx->height;
	}

	int Init();

	int Open();

	int DecorderAllFrames();

	

	AVFrame *GetOneFrame();

	void FreeOneFrame(AVFrame *frame);

	void Close();
};

