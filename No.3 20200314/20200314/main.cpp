#include <opencv.hpp>
//20200313
using namespace cv;

void openCamera()
{
	VideoCapture cap;

	cap.open(0);
	if (!cap.isOpened())
	{
		std::cout << "不能打开" << std::endl;
		return;
	}

	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess)
		{
			std::cout << "不能从视频文件中读取帧" << std::endl;
			break;
		}
		else
		{
			cv::imshow("frame", frame);
		}
		waitKey(30);
	}
	return;
}

void draw()
{
	cv::Mat dispMat = imread("C:\\Users\\lenovo\\Desktop\\1.png");

	cv::Point pt, pt1, pt2;
	cv::Rect rect;

	rect.x = 10;
	rect.y = 10;
	rect.width = 100;
	rect.height = 100;

	pt.x = 10;
	pt.y = 10;
	pt1.x = 10;
	pt1.y = 10;
	pt2.x = 100;
	pt2.y = 100;

	rectangle(dispMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);

	circle(dispMat, pt, 100, CV_RGB(0, 255, 0), 1, 8, 0);

	line(dispMat, pt1, pt2, CV_RGB(255, 0, 0, ), 1, 8, 0);

	cv::imshow("dispMat", dispMat);

	float histgram[256];
	for (int j = 0; j < 256; j++)
	{
		histgram[j] = 0;
	}
	int height = dispMat.rows;
	int width = dispMat.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			//\\/////////////////////////////////////////李竹老师是最帅的 ///////////////////////////////助教辛苦了
			float average = (dispMat.at<Vec3b>(j, i)[0] * 0.299 + 0.587 * dispMat.at<Vec3b>(j, i)[1] + 0.114 * dispMat.at<Vec3b>(j, i)[2]) / 3;
			//dispMat.at<Vec3b>(j, i)[0] = (float)(average);
			//dispMat.at<Vec3b>(j, i)[1] = (float)(average);
			//dispMat.at<Vec3b>(j, i)[2] = (float)(average);
			histgram[(int)average]++;
		}
	}
	return;
}

int main()
{
	cv::Mat src_color = imread("C:\\Users\\lenovo\\Desktop\\1.png");
	std::vector<cv::Mat> channels;
	cv::split(src_color, channels);
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	cv::imshow("red", R);
	cv::imshow("blue", B);
	cv::imshow("green", G);
	draw();				//画画了也遍历了
	openCamera();

	waitKey(0);
	return 0;
}