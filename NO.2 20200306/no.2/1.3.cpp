
#include <opencv.hpp>

using namespace cv;

void show2()
{
	cv::Mat srcMat2 = imread("D:\\2.jpg");
	int height = srcMat2.rows;
	int width = srcMat2.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			//\\/////////////////////////////////////////
			uchar average = (srcMat2.at<Vec3b>(j, i)[0] + srcMat2.at<Vec3b>(j, i)[1] + srcMat2.at<Vec3b>(j, i)[2]) / 3;
			if (average > 100)
			{
				srcMat2.at<Vec3b>(j, i)[0] = 255;
				srcMat2.at<Vec3b>(j, i)[1] = 255;
				srcMat2.at<Vec3b>(j, i)[2] = 255;
			}
			else
			{
				srcMat2.at<Vec3b>(j, i)[0] = 0;
				srcMat2.at<Vec3b>(j, i)[1] = 0;
				srcMat2.at<Vec3b>(j, i)[2] = 0;
			}
		}
	}
	imshow("src2", srcMat2);
	waitKey();
	//cv::Mat srcMat = imread("D:\\2.jpg", 0);
	//return 0;
}