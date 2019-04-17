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



struct MyFrame
{
	uint8_t *data[AV_NUM_DATA_POINTERS];
	int linesize[AV_NUM_DATA_POINTERS];
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
	
	std::queue<MyFrame *> frame_queue;

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

	

	MyFrame *GetOneFrame();

	void FreeOneFrame(MyFrame *frame);

	void Close();
};

