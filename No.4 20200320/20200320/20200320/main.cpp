#include <opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
//20200320

void process()
{
	Mat r1, r2, r3, r4;
	Mat srcMat = imread("C:\\Users\\lenovo\\Desktop\\1.png", 0);
	Mat dstMat;
	Mat Core = getStructuringElement(MORPH_RECT, Size(4, 4));

	threshold(srcMat, dstMat, 100, 255, THRESH_BINARY);
	erode(dstMat, r1, Core);
	dilate(dstMat, r2, Core);
	morphologyEx(dstMat, r3, MORPH_OPEN, Core);
	morphologyEx(dstMat, r4, MORPH_CLOSE, Core);

	imshow("src", srcMat);
	imshow("r1", r1);
	imshow("r2", r2);
	imshow("r3", r3);
	imshow("r4", r4);
	return;
}

void count()
{
	Mat lableMat;
	Mat statsMat;
	Mat centerMat;
	Mat dstMat;

	Mat srcMat = imread("C:\\Users\\lenovo\\Desktop\\1.png", 0);
	threshold(srcMat, dstMat, 100, 255, THRESH_BINARY);

	int nComp = cv::connectedComponentsWithStats(dstMat,
		lableMat,
		statsMat,
		centerMat,
		8,
		CV_32S);

	for (int i = 1; i < nComp; i++)
	{
		cout << "connected Components " << i << endl;
		cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
		cout << "width = " << statsMat.at<int>(i, 2) << endl;
		cout << "height = " << statsMat.at<int>(i, 3) << endl;
		cout << endl;
	}

	for (int i = 1; i < nComp; i++)
	{
		Rect bndbox;
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);
		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);
		rectangle(dstMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}

	imshow("src", srcMat);
	imshow("dst", dstMat);
	return;
}

void porcessCount()
{
	Mat lableMat;
	Mat statsMat;
	Mat centerMat;


	Mat output;
	Mat dstMat;
	Mat srcMat = imread("C:\\Users\\lenovo\\Desktop\\1.jpg", 0);	
	threshold(srcMat, dstMat, 100, 255, THRESH_BINARY_INV);

	Mat Core = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));


	erode(dstMat, output, Core);
	imshow("output", output);

	int nComp = cv::connectedComponentsWithStats(output,
		lableMat,
		statsMat,
		centerMat,
		8,
		CV_32S);

	Mat antiOutput;

	cout << nComp - 1  << endl;

	waitKey();
}

int main()
{
//	process();
//	count();
	porcessCount();
	return 0;
}

