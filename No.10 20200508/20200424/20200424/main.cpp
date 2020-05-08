//20200424
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace cv;

using namespace std;


int main()
{
	Mat refMat = imread("C:\\Users\\lenovo\\Desktop\\00.jpg", 0);
	int cellSize = 16;
	int nX = refMat.cols / cellSize;
	int nY = refMat.rows / cellSize;
	//cout << nX << endl;

	Mat gx, gy;
	Mat mag, angle;
	Sobel(refMat, gx, CV_32F, 1, 0, 1);
	Sobel(refMat, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);
	cout << "hello" << endl;
	int i;
	int j;
	int k;//直方图个数
	for (i = 0; i < refMat.cols; i++)
	{
		for (j = 0; j < refMat.rows; j++)
		{
			angle.at<float>(j, i) = (int)angle.at<float>(j, i) / 45; //角度变成0 - 7
			//cout << mag.at<float>(j, i) << endl;
		}
	}
	//构建直方图
	k = nX * nY;
	int rows = k;
	int columns = 8;
	vector<vector<int> > a0(rows, vector<int>(columns));    //a3是直方图  为了减小算量用int
	vector<vector<int> > a1(rows, vector<int>(columns));    //a3是直方图  为了减小算量用int
	vector<vector<int> > a2(rows, vector<int>(columns));    //a3是直方图  为了减小算量用int 结果应该会偏小
	for (i = 0; i < rows; i++)
	{//初始化        
		for (j = 0; j < columns; j++) {
			a0[i][j] = 0;
		}
	}
	int hang = 0;
	int lie = 0;
	k = 0;
	cout << nX << endl;
	cout << nY << endl;
	for (hang = 0; hang < nX; hang++)
	{
		for (lie = 0; lie < nY; lie++)
		{

			for (j = 0; j < 16; j++)
			{
				for (i = 0; i < 16; i++)
				{
					//cout << lie * 16 + j, hang * 16 + i << endl;
					a0[k][(int)angle.at<float>(lie * 16 + j, hang * 16 + i)] += mag.at<float>(lie * 16 + j, hang * 16 + i);
				}
			}
			k++;
		}
	}
	//123
	


	Mat firstMat = imread("C:\\Users\\lenovo\\Desktop\\01.jpg", 0);
	Sobel(firstMat, gx, CV_32F, 1, 0, 1);
	Sobel(firstMat, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);
	cout << "hello" << endl;
	for (i = 0; i < firstMat.cols; i++)
	{
		for (j = 0; j < firstMat.rows; j++)
		{
			angle.at<float>(j, i) = (int)angle.at<float>(j, i) / 45; //角度变成0 - 7
			//cout << mag.at<float>(j, i) << endl;
		}
	}

	for (i = 0; i < rows; i++)
	{//初始化        
		for (j = 0; j < columns; j++) {
			a1[i][j] = 0;
		}
	}
	k = 0;
	for (hang = 0; hang < nX; hang++)
	{
		for (lie = 0; lie < nY; lie++)
		{

			for (j = 0; j < 16; j++)
			{
				for (i = 0; i < 16; i++)
				{
					//cout << lie * 16 + j, hang * 16 + i << endl;
					a1[k][(int)angle.at<float>(lie * 16 + j, hang * 16 + i)] += mag.at<float>(lie * 16 + j, hang * 16 + i);
				}
			}
			k++;
		}
	}





	double sum = 0;
	for (i = 0; i < nX * nY; i++)
	{
		for (j = 0; j < 8; j++)
		{
			sum += (a1[i][j] - a0[i][j])* (a1[i][j] - a0[i][j]);
		}
	}	
	cout << "sum" << endl;
	cout << sqrt(sum) << endl;


	Mat secondMat = imread("C:\\Users\\lenovo\\Desktop\\02.jpg", 0);
	Sobel(secondMat, gx, CV_32F, 1, 0, 1);
	Sobel(secondMat, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);
	cout << "hello" << endl;
	for (i = 0; i < firstMat.cols; i++)
	{
		for (j = 0; j < firstMat.rows; j++)
		{
			angle.at<float>(j, i) = (int)angle.at<float>(j, i) / 45; //角度变成0 - 7
			//cout << mag.at<float>(j, i) << endl;
		}
	}

	for (i = 0; i < rows; i++)
	{//初始化        
		for (j = 0; j < columns; j++) {
			a2[i][j] = 0;
		}
	}
	k = 0;
	for (hang = 0; hang < nX; hang++)
	{
		for (lie = 0; lie < nY; lie++)
		{

			for (j = 0; j < 16; j++)
			{
				for (i = 0; i < 16; i++)
				{
					//cout << lie * 16 + j, hang * 16 + i << endl;
					a2[k][(int)angle.at<float>(lie * 16 + j, hang * 16 + i)] += mag.at<float>(lie * 16 + j, hang * 16 + i);
				}
			}
			k++;
		}
	}


	double sum1 = 0;
	for (i = 0; i < nX * nY; i++)
	{
		for (j = 0; j < 8; j++)
		{
			sum1 += (a2[i][j] - a0[i][j]) * (a2[i][j] - a0[i][j]);
		}
	}
	cout << "sum1" << endl;
	cout << sqrt(sum1) << endl;
	//float ceshi = 180.000;
	//cout << (int)ceshi % 45 << endl;


	imshow("refmat", refMat);

	waitKey(0);
	return 0;
}