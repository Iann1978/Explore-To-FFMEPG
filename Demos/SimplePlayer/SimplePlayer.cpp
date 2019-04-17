#include "SimplePlayer.h"

int SimplePlayer::Init()
{
	//avcodec_register_all();
	return 0;
}

int SimplePlayer::Open()
{
	av_register_all();
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();

	if (avformat_open_input(&pFormatCtx, filepath, NULL, NULL) != 0) {
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

	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();
	out_buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1));
	av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, out_buffer,
		AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);

	packet = (AVPacket *)av_malloc(sizeof(AVPacket));
	//Output Info-----------------------------
	printf("--------------- File Information ----------------\n");
	av_dump_format(pFormatCtx, 0, filepath, 0);
	printf("-------------------------------------------------\n");
	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
	return 0;
};

void DecorderOneFrame()
{

}


MyFrame* Convert(AVFrame *avframe)
{
	MyFrame *frame = new MyFrame();
	int size0 = avframe->height*avframe->linesize[0];
	frame->data[0] = (uint8_t *)malloc(size0);
	frame->linesize[0] = avframe->linesize[0];
	memcpy(frame->data[0], avframe->data[0], size0);

	int size1 = avframe->height*avframe->linesize[1]/2;
	frame->data[1] = (uint8_t *)malloc(size1);
	frame->linesize[1] = avframe->linesize[1];
	memcpy(frame->data[1], avframe->data[1], size1);

	int size2 = avframe->height*avframe->linesize[2]/2;
	frame->data[2] = (uint8_t *)malloc(size2);
	frame->linesize[2] = avframe->linesize[2];
	memcpy(frame->data[2], avframe->data[2], size2);
	
	return frame;
}


int SimplePlayer::DecorderAllFrames()
{
	//SDL End----------------------
	while (av_read_frame(pFormatCtx, packet) >= 0) {
		if (packet->stream_index == videoindex) {
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
			if (ret < 0) {
				printf("Decode Error.\n");
				return -1;
			}
			if (got_picture) {
				sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
					pFrameYUV->data, pFrameYUV->linesize);
				pFrameYUV->width = pFrame->width;
				pFrameYUV->height = pFrame->height;

				MyFrame *frame = Convert(pFrame);
				frame_queue.push(frame);
			}
		}
		av_free_packet(packet);
	}
	//flush decoder
	//FIX: Flush Frames remained in Codec
	while (1) {
		ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
		if (ret < 0)
			break;
		if (!got_picture)
			break;
		sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
			pFrameYUV->data, pFrameYUV->linesize);
		MyFrame *frame = Convert(pFrameYUV);
		frame_queue.push(frame);
	}
}


MyFrame *SimplePlayer::GetOneFrame()
{
	if (frame_queue.size())
	{
		MyFrame *frame = frame_queue.front();
		frame_queue.pop();
		return frame;
	}
	return nullptr;

}

void SimplePlayer::FreeOneFrame(MyFrame *frame)
{
	free((void *)frame);
}

void SimplePlayer::Close()
{
	sws_freeContext(img_convert_ctx);





	av_frame_free(&pFrameYUV);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
}