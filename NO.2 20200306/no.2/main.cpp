
#include <opencv.hpp>

using namespace cv;
//������
void show();
void show2();
int main()
{
	cv::Mat srcMat = imread("D:\\2.jpg");
	int height = srcMat.rows;
	int width = srcMat.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			//\\/////////////////////////////////////////
			uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2]) / 3;
			srcMat.at<Vec3b>(j, i)[0] = average;
			srcMat.at<Vec3b>(j, i)[1] = average;
			srcMat.at<Vec3b>(j, i)[2] = average;
		}
	}
	imshow("src", srcMat);
	show();
	show2();
	waitKey();
	return 0;
}
//������ʦ����˧��123556 ����������0.0��̫����