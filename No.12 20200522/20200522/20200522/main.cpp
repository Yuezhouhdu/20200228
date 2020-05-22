#include <opencv2/opencv.hpp>
#include "opencv2/features2d.hpp"
#include<opencv2/highgui.hpp>
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <time.h>
#include <math.h>  
#include<opencv2/imgproc/types_c.h> 
#define WINDOW_NAME "【程序窗口】"			
using namespace cv;
using namespace std;

int shipin()
{
	//实例化的同时初始化
	VideoCapture capture("C:\\Users\\lenovo\\Videos\\Captures\\1.mp4");		//类似于 int a=1;
	Mat frame;
	Mat bgMat, subMat, bny_subMat;	//存储每一帧的图像
	int cnt = 0;
	while (1)
	{
		capture >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		if (cnt == 0) {
			//第一帧，获得背景图像
			frame.copyTo(bgMat);
		}
		else {
			//第二帧开始背景差分
			//背 景图像和当前图像相减
			absdiff(frame, bgMat, subMat);
			//差分结果二值化
			threshold(subMat, bny_subMat, 50,255,CV_THRESH_BINARY);
			imshow(" b_subMat" , bny_subMat);
			imshow(" subMat", subMat);
			waitKey(30);
		}
		cnt++;
	}
	return 0;
}


int calcGaussianBackground(std::vector<cv::Mat> srcMats, cv::Mat& meanMat, cv::Mat& varMat)
{
	int rows = srcMats[0].rows;
	int cols = srcMats[0].cols;
	for (int h = 0; h < rows; h++)
	{
		for (int w = 0; w < cols; w++)
		{

			int sum = 0;
			float var = 0;
			//求均值
			for (int i = 0; i < srcMats.size(); i++) {
				sum += srcMats[i].at<uchar>(h, w);
			}
			meanMat.at<uchar>(h, w) = sum / srcMats.size();
			//求方差
			for (int i = 0; i < srcMats.size(); i++) {
				var += pow((srcMats[i].at<uchar>(h, w) - meanMat.at<uchar>(h, w)), 2);
			}
			varMat.at<float>(h, w) = var / srcMats.size();
		}
	}
	return 0;
}

int gaussianThreshold(cv::Mat srcMat, cv::Mat meanMat, cv::Mat varMat, float weight, cv::Mat& dstMat)
{
	int srcI;
	int meanI;
	int dstI;
	int rows = srcMat.rows;
	int cols = srcMat.cols;

	for (int h = 0; h < rows; h++)
	{
		for (int w = 0; w < cols; w++)
		{
			srcI = srcMat.at<uchar>(h, w);
			meanI = meanMat.at<uchar>(h, w);
			int dif = abs(srcI - meanI);
			int th = weight * varMat.at<float>(h, w);

			if (dif > th) {

				dstMat.at<uchar>(h, w) = 255;
			}
			else {
				dstMat.at<uchar>(h, w) = 0;
			}
		}
	}

	return 0;
}

int ziji()
{
	//实例化的同时初始化
	VideoCapture capVideo(0);

	//如果视频打开失败
	if (!capVideo.isOpened()) {
		std::cout << "Unable to open video!" << std::endl;
		return -1;
	}

	//用来计算背景模型的图像
	std::vector<cv::Mat> srcMats;


	//参数设置
	int nBg = 200;		//用来建立背景模型的数量
	float wVar = 2;		//方差的权重

	int jishu = 0;
	cv::Mat frame;
	cv::Mat meanMat;
	cv::Mat varMat;
	cv::Mat dstMat;

	while (true)
	{
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		//前面的nBg帧，计算背景
		//去掉前面不稳定的部分！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
		if (jishu > 50 && jishu < nBg) {

			srcMats.push_back(frame);

			if (jishu == 0) {
				std::cout << "reading frame " << std::endl;
			}

		}
		else if (jishu == nBg) {
			//计算模型
			meanMat.create(frame.size(), CV_8UC1);
			varMat.create(frame.size(), CV_32FC1);
			std::cout << "calculating background models" << std::endl;
			calcGaussianBackground(srcMats, meanMat, varMat);
		}
		else if(jishu > nBg){
			//背景差分
			dstMat.create(frame.size(), CV_8UC1);
			gaussianThreshold(frame, meanMat, varMat, wVar, dstMat);
			imshow("result", dstMat);
			imshow("frame", frame);
			waitKey(30);
		}

		jishu++;

	}

	return 0;
}

int main()
{
	//shipin();
	ziji();
	return 0;
}