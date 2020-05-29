//20200529
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

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
		if (num == 3) //���Բ�Ῠ֡
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

	return 0;
}

int main()
{

	kuang();
}