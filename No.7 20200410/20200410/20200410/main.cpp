//20200410
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;
int turn()
{
	float angle = 15.0, scale = 1;
	cv::Mat src = imread("C:\\Users\\lenovo\\Desktop\\1.png");

	Mat dst;
	cv::Point2f center(src.cols / 2.0, src.rows / 2.0);
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);

	cv::Rect bbox = cv::RotatedRect(center, src.size(), angle).boundingRect();

	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

	cv::warpAffine(src, dst, rot, bbox.size());
	imshow("dst", dst);

	return 0;
}

int canny()
{
	cv::Mat srcMat = cv::imread("C:\\Users\\lenovo\\Desktop\\1.jpg", 0);

	cv::Mat dstMat;



	Canny(srcMat, dstMat, 20, 60, 3);



	cv::imshow("canny", dstMat);


	return 1;
}
int hofu()
{
	//canny
	cv::Mat srcMat = cv::imread("C:\\Users\\lenovo\\Desktop\\1.png", 0);
	cv::Mat dstMat;
	cv::Mat outMat = cv::imread("C:\\Users\\lenovo\\Desktop\\1.png");
	
	Canny(srcMat, dstMat, 120, 130, 3);

	std::vector<cv::Vec2f> lines;
	cv::HoughLines(dstMat, lines, 1, CV_PI / 180, 83);
	
	
	cv::imshow("1", dstMat);
	float r = lines[0][0];
	float t = lines[0][1];

	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it)
	{
		float rho = (*it)[0], theta = (*it)[1];
		cv::Point pt1,pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(outMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
	}
	cv::imshow("outMat", outMat);

	return 1;
}

int hofu1()
{
	//canny
	cv::Mat srcMat = cv::imread("C:\\Users\\lenovo\\Desktop\\1.png", 0);
	cv::Mat dstMat;
	cv::Mat outMat = cv::imread("C:\\Users\\lenovo\\Desktop\\1.png");

	Canny(srcMat, dstMat, 120, 130, 3);

	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(dstMat, lines, 1, CV_PI / 180, 23,10,5);


	cv::imshow("1", dstMat);


	std::vector<cv::Vec4i>::iterator it = lines.begin();
	for (; it != lines.end(); ++it)
	{
		cv::Point pt1, pt2;
		pt1.x = (*it)[0];
		pt1.y = (*it)[1];
		pt2.x = (*it)[2];
		pt2.y = (*it)[3];
		cv::line(outMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
	}
	cv::imshow("outMat1", outMat);
	waitKey();
	return 1;
}
int main()
{
	turn();
	hofu();
	hofu1();
	return 1;
}


