#pragma warning (disable:4996)
#include <stdio.h>
#include <thread>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
};

AVFormatContext* pFormatCtx;
int				i, videoindex;
AVCodecContext* pCodecCtx;
AVCodec* pCodec;
AVFrame* pFrame;

AVPacket* packet;
int y_size;
int ret, got_picture;
int64_t pts;



// out frame 
AVFrame* outFrame;
unsigned char* outFrameBuffer;
struct SwsContext* outFrameConvert;




AVFrame* DecordeOneFrame()
{


	AVFrame* frame = nullptr;
	while (!frame && av_read_frame(pFormatCtx, packet) >= 0) {
		if (packet->stream_index == videoindex) {
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
			if (ret < 0) {
				printf("Decode Error.\n");
				return nullptr;
			}
			if (got_picture)
				frame = pFrame;
		}
		av_free_packet(packet);
	}

	while (!frame) {
		ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
		if (ret < 0)
			break;
		if (!got_picture)
			break;

		frame = pFrame;
	}


	return frame;
}

int main(int argc, char* argv[])
{
	getchar();
	int count = 15000;
	while (count--)
	{
		printf("Leak Test Count: %d\n", count);
		const char* url = "E:/Movies/5.mp4";
		pFormatCtx = avformat_alloc_context();

		if (avformat_open_input(&pFormatCtx, url, NULL, NULL) != 0) {
			printf("Couldn't open input stream.\n");
			return -1;
		}
		if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
			printf("Couldn't find stream information.\n");
			return -1;
		}
		videoindex = -1;
		for (i = 0; i < pFormatCtx->nb_streams; i++)
			if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
				videoindex = i;
				break;
			}
		if (videoindex == -1) {
			printf("Didn't find a video stream.\n");
			return -1;
		}

		pCodecCtx = pFormatCtx->streams[videoindex]->codec;
		pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
		if (pCodec == NULL) {
			printf("Codec not found.\n");
			return -1;
		}
		if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
			printf("Could not open codec.\n");
			return -1;
		}

		//Output Info-----------------------------
		//printf("--------------- File Information ----------------\n");
		//av_dump_format(pFormatCtx, 0, url, 0);
		//printf("-------------------------------------------------\n");

		packet = nullptr;
		packet = (AVPacket*)av_malloc(sizeof(AVPacket));
		if (!packet)
		{
			printf("(AVPacket*)av_malloc(sizeof(AVPacket))");
		}

		pFrame = nullptr;
		pFrame = av_frame_alloc();
		if (!pFrame)
		{
			printf("pFrame = av_frame_alloc();");
		}

		outFrame = nullptr;
		outFrame = av_frame_alloc();
		if (!outFrame)
		{
			printf("outFrame = av_frame_alloc();");
		}

		outFrameBuffer = nullptr;
		outFrameBuffer = (unsigned char*)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1));
		if (!outFrameBuffer)
		{
			printf("outFrameBuffer");
		}
		av_image_fill_arrays(outFrame->data, outFrame->linesize, outFrameBuffer, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1);
		outFrameConvert = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
			pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);


		DecordeOneFrame();
		DecordeOneFrame();
		DecordeOneFrame();
		DecordeOneFrame();
		DecordeOneFrame();


		av_free(outFrameBuffer); outFrameBuffer = nullptr;
		av_frame_free(&outFrame); outFrame = nullptr;
		av_frame_free(&pFrame); pFrame = nullptr;

		av_free(packet);





		//av_free()
		sws_freeContext(outFrameConvert); outFrameConvert = nullptr;

		avcodec_close(pCodecCtx); pCodecCtx = nullptr;
		//avcodec_free_context(&pCodecCtx);
		avformat_close_input(&pFormatCtx);

		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		//getchar();
	}

	getchar();

	getchar();

	getchar();

	return 0;
}

