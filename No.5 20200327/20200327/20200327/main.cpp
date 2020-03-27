
#include <opencv.hpp>



using namespace cv;


Point anchor = Point(-1, -1);
void openCamera()

{

	VideoCapture cap;

	cap.open(0);

	if (!cap.isOpened())

	{

		std::cout << "���ܴ�" << std::endl;

		return;

	}



	double fps = cap.get(CAP_PROP_FPS);

	std::cout << "fps" << fps << std::endl;

	while (1)

	{

		cv::Mat frame;
		cv::Mat middle;
		cv::Mat ave;
		cv::Mat gaos;//��˹
		cv::Mat suo;//����??????
		bool rSucess = cap.read(frame);

		if (!rSucess)

		{

			std::cout << "���ܴ���Ƶ�ļ��ж�ȡ֡" << std::endl;

			break;

		}

		else

		{

			cv::imshow("frame", frame);

			medianBlur(frame, middle, 7);//����7����Ч��
			cv::imshow("middle", middle);

			blur(frame, ave, Size(9, 9), anchor, BORDER_DEFAULT);//����ģ��
			cv::imshow("ave", ave);

			GaussianBlur(frame, gaos, Size(15, 15), 0, 0, BORDER_DEFAULT);//ģ��
			cv::imshow("gaos", gaos);

			Sobel(frame, suo, 0, 1, 1, 3, 1, 0, BORDER_DEFAULT);
			cv::imshow("suo", suo);
			//��ôд��Ȼ�ܿ���ÿ��ͼ�񣬻ᶪ֡���ӳ١�
		}

		waitKey(30);

	}

	return;

}

void face()

{
	cv::Mat r3;
	VideoCapture cap(0);


	
	double scale = 0.5;





	double i_minH = 0;

	double i_maxH = 20;

	double i_minS = 15;

	double i_maxS = 255;

	double i_minV = 55;

	double i_maxV = 255;





	while (1)

	{

		Mat frame;

		Mat hsvMat;

		Mat detectMat;

		Mat mopi;

		cap >> frame;

		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);

		Mat rFrame = Mat(ResImgSiz, frame.type());

		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);



		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);



		rFrame.copyTo(detectMat);



		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);



		imshow("white: in the range", detectMat);

		Mat Core = getStructuringElement(MORPH_RECT, Size(4, 4));
		//morphologyEx(detectMat, r3, MORPH_OPEN, Core);
		dilate(detectMat, r3, Core);
		imshow("r3", r3);
		

		blur(frame, mopi, Size(9, 9), anchor, BORDER_DEFAULT);

		//
		int height = detectMat.rows;

		int width = detectMat.cols;

		for (int j = 0; j < height; j++)

		{

			for (int i = 0; i < width; i++)

			{
				if ((detectMat.at<Vec3b>(j, i)[0] + detectMat.at<Vec3b>(j, i)[1] + detectMat.at<Vec3b>(j, i)[2]) < 100)//�����ֵͼ�Ǻ�ɫ
				{
					mopi.at<Vec3b>(j, i)[0] = frame.at<Vec3b>(j, i)[0];
					mopi.at<Vec3b>(j, i)[1] = frame.at<Vec3b>(j, i)[1];
					mopi.at<Vec3b>(j, i)[2] = frame.at<Vec3b>(j, i)[2];

				}
				else
				{
					mopi.at<Vec3b>(j, i)[0] = mopi.at<Vec3b>(j, i)[0] * 2; //����
				}

			}

		}
		imshow("frame", rFrame);
		imshow("mopi", mopi);


		waitKey(30);

	}



	return;

}

int main()

{
	openCamera();
	face();
	waitKey(0);

	return 0;

}