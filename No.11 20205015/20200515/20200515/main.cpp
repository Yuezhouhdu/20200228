//20200515




#include <opencv.hpp>

using namespace cv;

#include <opencv2/opencv.hpp>

#include <iostream>



using namespace cv;

using namespace std;
void gamma()
{
	Mat srcMat = imread("E:/上位机图像文件夹/2020.5.16 10.35.30/原图/9.bmp",0);
	int height = srcMat.rows;
	int width = srcMat.cols;
	int rate = 4;
	Mat dstMat=Mat::zeros(height,width,CV_8UC1);
	Mat dstMat1 = Mat::zeros(height* rate, width* rate, CV_8UC1);
	Mat dstMat2 = Mat::zeros(height* rate, width* rate, CV_8UC1);
	float Lut[256] = { 0 };
	for (int i = 0; i < 256; i++) 
	{
		Lut[i] = pow((float)i  / 255, 2.5)* 255;
	}
	for (int i = 0; i < srcMat.rows; i++)
	{
		for (int j = 0; j < srcMat.cols; j++)
		{
			dstMat.at<uchar>(i, j) = Lut[srcMat.at<uchar>(i, j)] ;
		}
	}
	resize(srcMat, dstMat1, dstMat1.size());
	resize(dstMat, dstMat2, dstMat2.size());
	imshow("原图", dstMat1);
	imshow("gamma", dstMat2);
	waitKey(0);
}
void junheng()
{
	Mat srcMat = imread("E://zy//大二下//数字图像处理//etest.jpg",1);

	int height = srcMat.rows;

	int width = srcMat.cols;

	Mat dstMatB;
	Mat dstMatG;
	Mat dstMatR;
	Mat result;
	//vector<Mat> channels;
	//split(srcMat, channels);
	//Mat B = channels.at(0);
	//Mat G = channels.at(1);
	//Mat R = channels.at(2);
	//equalizeHist(B, dstMatB);
	//equalizeHist(G, dstMatG);
	//equalizeHist(R, dstMatR);
	//imshow("B", dstMatB);
	//imshow("G", dstMatG);
	//imshow("R", dstMatR);
	/*merge(B, 3, result);*/
	//for (int i = 0; i < height; i++) 
	//{
	//	for (int j = 0; j < width; j++) 
	//	{
	//		result.at<Vec3b>(i, j)[0] = B.at<uchar>(i, j);
	//		result.at<Vec3b>(i, j)[1] = G.at<uchar>(i, j);
	//		result.at<Vec3b>(i, j)[2] = R.at<uchar>(i, j);
	//	}
	//}
	//imshow("result", result);


	Mat channels[3];
	Mat fenchannels[3];
	split(srcMat, channels);           
	//imshow("B", channels[0]);
	//imshow("G", channels[1]);
	//imshow("R", channels[2]);
	for (int i = 0;i < 3;i++)
	{
		equalizeHist(channels[i], fenchannels[i]);
	}
	 merge(fenchannels,3, srcMat);
	imshow("结果", srcMat);
	waitKey(0);
}	
void lizhu()
{
	Mat srcMat = imread("E://zy//大二下//数字图像处理//gtest.jpg",0);
	float Lut[256] = { 0 };
	for (int i = 0; i < 256; i++)
	{
		Lut[i] = pow((float)i / 255, 0.5) * 255;
	}

	for (int i = 0; i < srcMat.rows; i++)
	{
		for (int j = 0; j < srcMat.cols; j++)
		{
			srcMat.at<uchar>(i, j) = Lut[srcMat.at<uchar>(i, j)] ;
		}
	}
	imshow("srcMat", srcMat);
	waitKey(0);
}
int main()
{
	gamma();
	//junheng();
	//lizhu();
}