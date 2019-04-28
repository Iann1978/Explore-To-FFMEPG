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

	enum Status {
		/// <summary>
		   /// 未初始化的状态
		   /// </summary>
		Status_Unknown = 0,

		/// <summary>
		/// 初始化中
		/// </summary>
		Status_Initializing,

		/// <summary>
		/// 初始化已经完成
		/// </summary>
		Status_Initialized,

		/// <summary>
		/// 正在打开影片
		/// </summary>
		Status_Opening,

		/// <summary>
		/// 影片已经打开
		/// </summary>
		Status_Opened,

		/// <summary>
		/// 影片正在播放中
		/// </summary>
		Status_Playing,

		/// <summary>
		/// 影片定位中
		/// </summary>
		Status_Seeking,

		/// <summary>
		/// 影片暂停中
		/// </summary>
		Status_Paused,

		/// <summary>
		/// 影片已经播放到结尾
		/// </summary>
		Status_PlayEnd,

		/// <summary>
		/// 影片已经关闭
		/// </summary>
		Status_Closed,
	};

	/// <summary>
	  /// 错误代码
	  /// </summary>
	enum ErrorCode
	{
		/// <summary>
		/// 没有错误
		/// </summary>
		ErrorCode_NoError = 0,

		/// <summary>
		/// 未知的错误
		/// </summary>
		ErrorCode_Unknown,

		/// <summary>
		/// 状态错误
		/// </summary>
		ErrorCode_StateError,
	};

	Status status = Status_Unknown;

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
	int Open(const char *url);
	AVFrame *DecordeOneFrame();
	void Close();
	


	void FastForward();
	void FastBackward();
};

