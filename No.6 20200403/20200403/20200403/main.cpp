//20200403
#include <opencv.hpp>

using namespace cv;

int canny()
{

	cv::Mat srcMat = cv::imread("C:\\Users\\lenovo\\Desktop\\lena.jpg", 0);
	cv::Mat dstMat;

	Canny(srcMat, dstMat, 20, 60,3);

	cv::imshow("canny", dstMat);
	//cv::waitKey(0);
	return 1;
}

int turn()
{
	cv::Mat dstMat;
	cv::Mat srcMat = cv::imread("C:\\Users\\lenovo\\Desktop\\lena.jpg", 1);
	if (srcMat.empty())return -1;
	
	float angle = -10.0, scale = 1;

	cv::Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);

	const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);

	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	//cv::waitKey(0);
	return 1;
}

int fangShe()
{
	cv::Mat dstMat;
	cv::Mat srcMat = cv::imread("C:\\Users\\lenovo\\Desktop\\lena.jpg", 1);
	if (srcMat.empty())return -1;

	const cv::Point2f src_pt[] =
	{
		cv::Point2f(200,200),
		cv::Point2f(250,200),
		cv::Point2f(200,100)

	};

	const cv::Point2f dst_pt[] =
	{
		cv::Point2f(300,100),
		cv::Point2f(300,50),
		cv::Point2f(200,100)
	};

	cv::Mat perspective_matrix = cv::getAffineTransform(src_pt, dst_pt);

	cv::warpAffine(srcMat, dstMat, perspective_matrix, srcMat.size());
	
	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	//cv::waitKey(0);

	return 1;
}

int touYing()
{
	cv::Mat dstMat;
	cv::Mat srcMat = cv::imread("C:\\Users\\lenovo\\Desktop\\lena.jpg", 1);
	if (srcMat.empty())return -1;

	const cv::Point2f pts1[] =
	{
		cv::Point2f(150,150),
		cv::Point2f(150,300),
		cv::Point2f(350,300),
		cv::Point2f(350,150)

	};

	const cv::Point2f pts2[] =
	{
		cv::Point2f(200,150),
		cv::Point2f(200,300),
		cv::Point2f(340,270),
		cv::Point2f(340,180)

	};

	cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);

	cv::warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	cv::waitKey(0);

	return 1;
}

int ziDong()
{
	cv::Mat srcMat = cv::imread("C:\\Users\\lenovo\\Desktop\\lena_rot.jpg", 1);
	cv::Mat dstMat;
	int a;
	int height = srcMat.rows;

	int width = srcMat.cols;

	int j = 0;
	for (int i = 0; i < width; i++)
	{
		float average = (srcMat.at<Vec3b>(j, i)[0] * 0.299 + 0.587 * srcMat.at<Vec3b>(j, i)[1] + 0.114 * srcMat.at<Vec3b>(j, i)[2])/3;
		if ((average < 250))
		{
			break;
		}
	}
	a = width;
	 width = srcMat.cols;
	 a = 80;
	const cv::Point2f pts1[] =
	{		
		cv::Point2f(a,0),
		cv::Point2f(width,a),
		cv::Point2f(0,height - a),
		cv::Point2f(width - a,height)	

	};

	const cv::Point2f pts2[] =
	{
	
		cv::Point2f(0,0),
		cv::Point2f(width,0),
		cv::Point2f(0,height),
		cv::Point2f(width,height)

	};

	cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);

	cv::warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

	cv::imshow("src", srcMat);
	cv::imshow("×Ô¶¯", dstMat);
	cv::waitKey(0);
	
	return 1;
}
int main()
{
	canny();
	turn();
	fangShe();
	touYing();
	ziDong();
}