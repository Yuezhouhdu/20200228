//20200529
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

vector<float> getHog(const Mat& img) {
	int blocksize = 16;
	int nX = img.cols / blocksize;
	int nY = img.rows / blocksize;
	Mat gx, gy;
	Mat mag, angle;
	Sobel(img, gx, CV_32F, 1, 0, 1);
	Sobel(img, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);
	int i, j, x, y;
	vector<float> hist(1.0 * nX * nY * 8, 0);
	for (j = 0; j < nY; j++) 
	{
		for (i = 0; i < nX; i++) 
		{
			for (y = 0; y < blocksize; y++) 
			{
				for (x = 0; x < blocksize; x++)
				{
					int count = (int)(angle.at<float>(16 * j + y, 16 * i + x) / 45);
					hist[1.0 * 8 * nX * j + 8 * i + count] += mag.at<float>(16 * j + y, 16 * i + x);
				}
			}
		}
	}
	return hist;
}

int kuang()
{
	VideoCapture capture(0);
	int num = 0;
	Mat frame;	
	Mat tempMat;
	Mat refMat;
	Mat resultMat;
	Mat dispMat;
	while (1)
	{
		capture >> frame;	
		if (num == 3) //电脑差会卡帧
		{                     
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
		}
		if (num > 3)
		{
			int match_method = 0;
			matchTemplate(frame, refMat, resultMat, match_method);
			normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());
			double minVal; double maxVal; Point minLoc; Point maxLoc; Point matchLoc;
			minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
			if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
				matchLoc = minLoc;
			else
				matchLoc = maxLoc;
			frame.copyTo(dispMat);
			rectangle(dispMat, matchLoc, Point(matchLoc.x + refMat.cols, matchLoc.y + refMat.rows), Scalar::all(0), 2, 8, 0);
			num++;
			imshow("template", refMat);
			imshow("dispMat", dispMat);
			waitKey(30);
		}
		num++;
	}
	return 0;
}

int huakuang()
{
	Mat refMat = imread("E:\\zy\\大二下\\数字图像处理\\template.png" ,0);
	Mat src = imread("E:\\zy\\大二下\\数字图像处理\\img.png", 0);
	int smallrow = refMat.rows;
	int smallcol = refMat.cols;
	int row = src.rows;
	int col = src.cols;
	float distance = 0; //减少计算量
	float min = 0;
	vector<float> hist0;
	vector<float> hist1;
	hist0 = getHog(refMat);
	Rect rect;
	for (int i = 0; i < row - smallrow; i++)
	{
		for (int j = 0; j < col - smallcol; j++)
		{
			Mat slide = src(Rect(j, i, smallcol, smallrow));
			hist1 = getHog(slide);
			for (int k = 0; k < hist0.size(); k++) 
			{
				distance += (hist0[k] - hist1[k]) * (hist0[k] - hist1[k]);
				if (distance > 1000)//减少计算量
				{
					break;
				}
			}
			distance = sqrt(distance);
			if (i == 0 && j == 0) 
			{
				min = distance;
			}
			if (distance < min) 
			{
				min = distance;
				rect = Rect(j, i, smallcol, smallrow);
			}
		}
	}





	rectangle(src, rect, CV_RGB(255, 255, 255), 1, 8, 0);



	// imshow("test",dist);

	imshow("test", src);

	waitKey(0);



	return 0;
}

int main()
{
	huakuang();
	//kuang();
}