#include <opencv2/opencv.hpp>
#include "opencv2/features2d.hpp"
#include<opencv2/highgui.hpp>
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <time.h>
#include <math.h>  
#include<opencv2/imgproc/types_c.h> 
#define WINDOW_NAME "�����򴰿ڡ�"			
using namespace cv;
using namespace std;

//RNG g_rng(12345);
/****��ϰ1���������**********/
int shipin()
{
	//ʵ������ͬʱ��ʼ��
	VideoCapture capture("C:\\Users\\lenovo\\Videos\\Captures\\1.mp4");		//������ int a=1;
	Mat frame;
	Mat bgMat, subMat, bny_subMat;	//�洢ÿһ֡��ͼ��
	int cnt = 0;
	while (1)
	{
		capture >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		if (cnt == 0) {
			//��һ֡����ñ���ͼ��
			frame.copyTo(bgMat);
		}
		else {
			//�ڶ�֡��ʼ�������
			//�� ��ͼ��͵�ǰͼ�����
			absdiff(frame, bgMat, subMat);
			//��ֽ����ֵ��
			threshold(subMat, bny_subMat, 50,255,CV_THRESH_BINARY);
			imshow(" b_subMat" , bny_subMat);
			imshow(" subMat", subMat);
			waitKey(30);
		}
		cnt++;
	}
	return 0;
}


/****��ϰ2��ʵ�ָ�˹��ģ�뱳�����**********/
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
			//���ֵ
			for (int i = 0; i < srcMats.size(); i++) {
				sum += srcMats[i].at<uchar>(h, w);
			}
			meanMat.at<uchar>(h, w) = sum / srcMats.size();
			//�󷽲�
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
	//ʵ������ͬʱ��ʼ��
	//VideoCapture capture("D:\\opencv_picture_test\\videos\\video1.avi");		//������ int a=1;
	//----------------------��ȡ��Ƶ�ļ�--------------------------
	VideoCapture capVideo(0);
	//VideoCapture capVideo("../testImages\\vtest.avi");

	//�����Ƶ��ʧ��
	if (!capVideo.isOpened()) {
		std::cout << "Unable to open video!" << std::endl;
		return -1;
	}

	//�������㱳��ģ�͵�ͼ��
	std::vector<cv::Mat> srcMats;


	//��������
	int nBg = 200;		//������������ģ�͵�����
	float wVar = 1;		//����Ȩ��

	int cnt = 0;
	cv::Mat frame;
	cv::Mat meanMat;
	cv::Mat varMat;
	cv::Mat dstMat;

	while (true)
	{
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		//ǰ���nBg֡�����㱳��
		if (cnt < nBg) {

			srcMats.push_back(frame);

			if (cnt == 0) {
				std::cout << "reading frame " << std::endl;
			}

		}
		else if (cnt == nBg) {
			//����ģ��
			meanMat.create(frame.size(), CV_8UC1);
			varMat.create(frame.size(), CV_32FC1);
			std::cout << "calculating background models" << std::endl;
			calcGaussianBackground(srcMats, meanMat, varMat);
		}
		else {
			//�������
			dstMat.create(frame.size(), CV_8UC1);
			gaussianThreshold(frame, meanMat, varMat, wVar, dstMat);
			imshow("result", dstMat);
			imshow("frame", frame);
			waitKey(30);
		}

		cnt++;

	}

	return 0;
}

int main()
{
	shipin();
	//ziji();
	return 0;
}