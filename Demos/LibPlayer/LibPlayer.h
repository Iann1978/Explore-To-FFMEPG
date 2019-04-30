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
		   /// δ��ʼ����״̬
		   /// </summary>
		Status_Unknown = 0,

		/// <summary>
		/// ��ʼ����
		/// </summary>
		Status_Initializing,

		/// <summary>
		/// ��ʼ���Ѿ����
		/// </summary>
		Status_Initialized,

		/// <summary>
		/// ���ڴ�ӰƬ
		/// </summary>
		Status_Opening,

		/// <summary>
		/// ӰƬ�Ѿ���
		/// </summary>
		Status_Opened,

		/// <summary>
		/// ӰƬ���ڲ�����
		/// </summary>
		Status_Playing,

		/// <summary>
		/// ӰƬ��λ��
		/// </summary>
		Status_Seeking,

		/// <summary>
		/// ӰƬ��ͣ��
		/// </summary>
		Status_Paused,

		/// <summary>
		/// ӰƬ�Ѿ����ŵ���β
		/// </summary>
		Status_PlayEnd,

		/// <summary>
		/// ӰƬ�Ѿ��ر�
		/// </summary>
		Status_Closed,
	};

	/// <summary>
	  /// �������
	  /// </summary>
	enum ErrorCode
	{
		/// <summary>
		/// û�д���
		/// </summary>
		ErrorCode_NoError = 0,

		/// <summary>
		/// δ֪�Ĵ���
		/// </summary>
		ErrorCode_Unknown,

		/// <summary>
		/// ״̬����
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
	int Play();
	int Pause();
	AVFrame *DecordeOneFrame();
	int Close();
	


	void FastForward();
	void FastBackward();
};

