#include "SimplePlayer.h"

int SimplePlayer::Init()
{
	avcodec_register_all();
	return 0;
}

int SimplePlayer::Open()
{
	
	const char *filepath_in = "bigbuckbunny_480x272.h264";

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


	pFrame = av_frame_alloc();
	av_init_packet(&packet);
	return 0;
};
void DecorderOneFrame()
{

}
void SimplePlayer::DecorderAllFrames()
{
	while (1) {

		cur_size = fread(in_buffer, 1, in_buffer_size, fp_in);
		if (cur_size == 0)
			break;
		cur_ptr = in_buffer;

		while (cur_size > 0) {

			int len = av_parser_parse2(pCodecParserCtx, 
				pCodecCtx,
				&packet.data, &packet.size,
				cur_ptr, cur_size,
				AV_NOPTS_VALUE, AV_NOPTS_VALUE,
				AV_NOPTS_VALUE);

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




			}
		}

	}

	//Flush Decoder
	packet.data = NULL;
	packet.size = 0;
	while (1) {		
		ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
		if (ret < 0) {
			printf("Decode Error.\n");
			return;
		}
		if (!got_picture) {
			break;
		}
		else {
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
	fclose(fp_in);
	fclose(fp_out);


	av_parser_close(pCodecParserCtx);

	//av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	av_free(pCodecCtx);
}