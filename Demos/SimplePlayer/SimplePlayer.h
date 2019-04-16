#pragma once
#pragma warning(disable:4996)
#include <queue>

extern "C"
{
#include "SDL.h"
#include "libavcodec/avcodec.h"
};



struct MyFrame
{
	uint8_t *data[AV_NUM_DATA_POINTERS];
	int linesize[AV_NUM_DATA_POINTERS];
};
class SimplePlayer
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


	int first_time = 1;

	std::queue<MyFrame *> frame_queue;

public:
	int Open();

	void DecorderAllFrames();


	MyFrame *DecorderOneFrame();

	void Close();
};

