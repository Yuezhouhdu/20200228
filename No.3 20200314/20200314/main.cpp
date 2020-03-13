#include <opencv.hpp>
#include <iostream>

//20200313
using namespace std;

using namespace cv;

void face()
{
	VideoCapture cap(0);

	double scale = 0.5;


	double i_minH = 0;
	double i_maxH = 20;
	double i_minS = 15;
	double i_maxS = 255;
	double i_minV = 55;
	double i_maxV = 255;


	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;

		cap >> frame;
		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		imshow("white: in the range", detectMat);
		imshow("frame", rFrame);

		waitKey(30);
	}

	return;
}

void oneZero()
{
	Mat srcImage = imread("C:\\Users\\lenovo\\Desktop\\1.jpg", 0);	
	namedWindow("原图", WINDOW_NORMAL);
	imshow("原图", srcImage);

	Mat dstImage1, dstImage2;
	dstImage1.create(srcImage.rows, srcImage.cols, CV_8UC1);
	dstImage2.create(srcImage.rows, srcImage.cols, CV_8UC1);
	double time0 = static_cast<double>(getTickCount());	

	threshold(srcImage, dstImage1, 83, 255, THRESH_BINARY);
	adaptiveThreshold(srcImage, dstImage2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 9, 10);

	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为：" << time0 << "秒" << endl;	
	namedWindow("图1", WINDOW_NORMAL);
	imshow("图1", dstImage1);
	namedWindow("图2", WINDOW_NORMAL);
	imshow("图2", dstImage2);
	//waitKey(0);
	return;
}
string window_name = "binaryMat";

void threshod_Mat(int th, void* data)
{
	
	Mat src = *(Mat*)(data);

	Mat dst;

	threshold(src, dst, th, 255, 0);

	imshow(window_name, dst);
}

void rushB()//按钮
{
	Mat srcMat;
	Mat gryMat;
	int lowTh = 30;
	int maxTh = 255;

	srcMat = imread("C:\\Users\\lenovo\\Desktop\\2.jpg");
	if (!srcMat.data)
	{
		cout << "失败" << endl;
		return;
	}
	cvtColor(srcMat, gryMat, CV_BGR2GRAY);
	imshow(window_name, gryMat);
	createTrackbar("threshold",
		window_name,
		&lowTh,
		maxTh,
		threshod_Mat,
		&gryMat);
	//waitKey(0);
	return;
}
int main()
{
	oneZero();
	rushB();
	face();
	
}
