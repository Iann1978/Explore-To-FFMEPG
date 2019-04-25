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
	AVFrame	*pFrame;
	
	AVPacket *packet;
	int y_size;
	int ret, got_picture;
	int64_t pts;



	// out frame 
	AVFrame				*outFrame;
	unsigned char		*outFrameBuffer;
	struct SwsContext	*outFrameConvert;

private:
	AVFrame* Convert(AVFrame *frame);

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
	AVFrame *DecordeOneFrame();
	void Close();
	


	void FastForward();
	void FastBackward();
};

