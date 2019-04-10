// HelloFFMPEG.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#pragma warning (disable:4996)
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"
};


/**
 * AVFormat Support Information
 */
char * avformatinfo() {

	char info[40000] = { 0 };

	av_register_all();

	AVInputFormat *if_temp = av_iformat_next(NULL);
	AVOutputFormat *of_temp = av_oformat_next(NULL);
	//Input
	while (if_temp != NULL) {
		sprintf(info, "%s[In ] %10s\n", info, if_temp->name);
		if_temp = if_temp->next;
	}
	//Output
	while (of_temp != NULL) {
		sprintf(info, "%s[Out] %10s\n", info, of_temp->name);
		of_temp = of_temp->next;
	}
	return info;
}

/**
 * AVCodec Support Information
 */
char * avcodecinfo()
{
	char info[40000] = { 0 };

	av_register_all();

	AVCodec *c_temp = av_codec_next(NULL);

	while (c_temp != NULL) {
		if (c_temp->decode != NULL) {
			sprintf(info, "%s[Dec]", info);
		}
		else {
			sprintf(info, "%s[Enc]", info);
		}
		switch (c_temp->type) {
		case AVMEDIA_TYPE_VIDEO:
			sprintf(info, "%s[Video]", info);
			break;
		case AVMEDIA_TYPE_AUDIO:
			sprintf(info, "%s[Audio]", info);
			break;
		default:
			sprintf(info, "%s[Other]", info);
			break;
		}

		sprintf(info, "%s %10s\n", info, c_temp->name);

		c_temp = c_temp->next;
	}
	return info;
}

///**
// * AVFilter Support Information
// */
//char * avfilterinfo()
//{
//	char info[40000] = { 0 };
//	av_register_all();
//	AVFilter *f_temp = (AVFilter *)avfilter_next(NULL);
//	while (f_temp != NULL) {
//		sprintf(info, "%s[%10s]\n", info, f_temp->name);
//	}
//	return info;
//}

/**
 * Configuration Information
 */
char * configurationinfo()
{
	char info[10000] = { 0 };
	av_register_all();

	sprintf(info, "%s\n", avcodec_configuration());

	return info;
}

int main()
{
    std::cout << "Hello FFMPEG!\n";

	printf("\n<<Configuration>>\n%s", configurationinfo());	
	printf("\n<<AVFormat>>\n%s", avformatinfo());
	printf("\n<<AVCodec>>\n%s", avcodecinfo());
	//printf("\n<<AVFilter>>\n%s", avfilterinfo());

	getchar();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
