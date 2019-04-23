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


class LibPlayer
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

	const char *filepath = "E:/Movies/The.Meg.mkv";
	//SDL---------------------------
	int screen_w = 0, screen_h = 0;
	FILE *fp_yuv;
	int64_t pts;
	
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

	AVFrame *DecordeOneFrame();

	AVFrame *GetOneFrame();


	void FastForward();
	void FastBackward();


	void FreeOneFrame(AVFrame *frame);

	void Close();
};

