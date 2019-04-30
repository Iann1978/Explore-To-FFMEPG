#include "LibPlayer.h"

int LibPlayer::Init()
{
	//avcodec_register_all();
	return 0;
}

int LibPlayer::Open(const char *url)
{
	//const char *filepath = "E:/githome/Explore-To-FFMEPG/Demos/SimplePlayer/bigbuckbunny_480x272.h264";
	//const char *filepath = "E:/Movies/10.mp4";
	
	//avformat_network_init();
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

	pFrame = av_frame_alloc();
	

	packet = (AVPacket *)av_malloc(sizeof(AVPacket));
	//Output Info-----------------------------
	printf("--------------- File Information ----------------\n");
	av_dump_format(pFormatCtx, 0, url, 0);
	printf("-------------------------------------------------\n");


	outFrame = av_frame_alloc();
	outFrameBuffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1));
	av_image_fill_arrays(outFrame->data, outFrame->linesize, outFrameBuffer, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1);
	outFrameConvert = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);

	status = Status_Opened;
	return 0;
};


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

AVFrame* LibPlayer::Convert(AVFrame *frame)
{
	int lines = sws_scale(outFrameConvert, frame->data, frame->linesize, 0, frame->height, outFrame->data, outFrame->linesize);
	outFrame->width = frame->width;
	outFrame->height = frame->height;
	return outFrame;

	//return DeepCopyFrame(avframe);
}


AVFrame *LibPlayer::DecordeOneFrame()
{
	if (status != Status_Playing)
	{
		printf("Error(Status Error): LibPlayer::DecordeOneFrame() status:%d", status);
		return nullptr;
	}

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

int LibPlayer::Close()
{
	sws_freeContext(outFrameConvert);
	av_frame_free(&outFrame);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
	return 0;
}

int LibPlayer::Play()
{
	status = Status_Playing;
	return 0;
}

int LibPlayer::Pause()
{
	status = Status_Paused;
	return 0;
}