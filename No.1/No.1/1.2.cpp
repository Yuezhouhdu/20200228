
#include <opencv.hpp>

using namespace cv;

void show()
{
	cv::Mat srcMat1 = imread("D:\\2.jpg",0);
	//int height = srcMat.rows;
	//int width = srcMat.cols;
	//for (int j = 0; j < height; j++)
	//{
	//	for (int i = 0; i < width; i++)
	//	{
	//		//\\/////////////////////////////////////////
	//		uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2]) / 3;
	//		srcMat.at<Vec3b>(j, i)[0] = average;
	//		srcMat.at<Vec3b>(j, i)[1] = average;
	//		srcMat.at<Vec3b>(j, i)[2] = average;
	//	}
	//}
	imshow("src1", srcMat1);
	waitKey();
	//cv::Mat srcMat = imread("D:\\2.jpg", 0);
	//return 0;
}