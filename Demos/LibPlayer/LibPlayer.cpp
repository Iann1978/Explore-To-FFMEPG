#include "LibPlayer.h"

int LibPlayer::Init()
{
	//avcodec_register_all();
	return 0;
}

int LibPlayer::Open()
{
	
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
AVFrame *DeepCopyFrame(AVFrame *frame)
{
	AVFrame *copyFrame = av_frame_alloc();
	copyFrame->format = frame->format;
	copyFrame->width = frame->width;
	copyFrame->height = frame->height;
	copyFrame->channels = frame->channels;
	copyFrame->channel_layout = frame->channel_layout;
	copyFrame->nb_samples = frame->nb_samples;
	av_frame_get_buffer(copyFrame, 32);
	av_frame_copy(copyFrame, frame);
	av_frame_copy_props(copyFrame, frame);
	return copyFrame;
}

AVFrame* Convert(AVFrame *avframe)
{
	return DeepCopyFrame(avframe);
}

//
//int LibPlayer::DecorderAllFrames()
//{
//	//SDL End----------------------
//	while (av_read_frame(pFormatCtx, packet) >= 0) {
//		if (packet->stream_index == videoindex) {
//			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
//			if (ret < 0) {
//				printf("Decode Error.\n");
//				return -1;
//			}
//			if (got_picture) {
//				sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
//					pFrameYUV->data, pFrameYUV->linesize);
//				pFrameYUV->width = pFrame->width;
//				pFrameYUV->height = pFrame->height;
//
//				AVFrame *frame = Convert(pFrame);
//				frame_queue.push(frame);
//			}
//		}
//		av_free_packet(packet);
//	}
//	//flush decoder
//	//FIX: Flush Frames remained in Codec
//	while (1) {
//		ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
//		if (ret < 0)
//			break;
//		if (!got_picture)
//			break;
//		sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
//			pFrameYUV->data, pFrameYUV->linesize);
//		AVFrame *frame = Convert(pFrameYUV);
//		frame_queue.push(frame);
//	}
//}

AVFrame *LibPlayer::DecordeOneFrame()
{
	AVFrame *frame = nullptr;
	while (!frame && av_read_frame(pFormatCtx, packet) >= 0) {
		if (packet->stream_index == videoindex) {
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
			if (ret < 0) {
				printf("Decode Error.\n");
				return nullptr;
			}
			if (got_picture)
				frame = Convert(pFrame);				
		}
		av_free_packet(packet);
	}
	
	while (!frame) {
		ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
		if (ret < 0)
			break;
		if (!got_picture)
			break;
		
		frame = Convert(pFrame);
	}

	if (frame)
	{
		this->pts = frame->pts;
	}
	return frame;
}

void LibPlayer::FastForward()
{
	av_seek_frame(pFormatCtx, videoindex, pts + 1000, 0);
}
void LibPlayer::FastBackward()
{
	av_seek_frame(pFormatCtx, videoindex, pts - 1000, 0);
}

//AVFrame *LibPlayer::GetOneFrame()
//{
//	if (frame_queue.size())
//	{
//		AVFrame *frame = frame_queue.front();
//		frame_queue.pop();
//		return frame;
//	}
//	return nullptr;
//
//}

void LibPlayer::FreeOneFrame(AVFrame *frame)
{
	//free((void *)frame);
}

void LibPlayer::Close()
{
	sws_freeContext(img_convert_ctx);
	av_frame_free(&pFrameYUV);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
}