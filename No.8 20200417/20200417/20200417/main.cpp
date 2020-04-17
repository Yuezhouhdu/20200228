//20200417
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <vector>



using namespace std;

using namespace cv;

int xinpian() {
    int i = 0;
    Mat src = imread("C:\\Users\\lenovo\\Desktop\\2.png", 0);
    imshow("2", src);

    

    Mat kernel = getStructuringElement(0, Size(3, 3));

    Mat out1, out2, out3, out4;
    morphologyEx(src, out3, 2, kernel);
    imshow("open", out3);
    Mat result1, result2;

    Mat labelsMat;//标签号

    Mat statsMat;//状态矩阵

    Mat centroidsMat;//连通域中心

    int count;



    threshold(out3, result1, 100, 255, THRESH_OTSU);

    count = connectedComponentsWithStats(result1, labelsMat, statsMat, centroidsMat);



    cout << count - 1 << endl;


    int max = 1;
    int maxi = 1;
    for (; i < count; i++) {

        Rect box;

        box.x = statsMat.at<int>(i, 0);

        box.y = statsMat.at<int>(i, 1);

        box.width = statsMat.at<int>(i, 2);

        box.height = statsMat.at<int>(i, 3);
        
        if (box.width * box.height > max)
        {
            max = box.width * box.height;
            maxi = i;
        }
        if (box.width * box.height > 1900)
        {
            rectangle(result1, box, CV_RGB(255, 255, 255), 1, 8, 0);
        }
    }



    imshow("result1", result1);

    waitKey(0);



    return 0;

}

int luntai()
{

    int i = 0;
    Mat src = imread("C:\\Users\\lenovo\\Desktop\\1.png", 0);
    imshow("2", src);



    Mat kernel = getStructuringElement(0, Size(3, 3));

    Mat out1, out2, out3, out4;
    morphologyEx(src, out3, 2, kernel);
    imshow("open", out3);
    Mat result1, result2;

    Mat labelsMat;//标签号

    Mat statsMat;//状态矩阵

    Mat centroidsMat;//连通域中心

    int count;



    threshold(out3, result2, 100, 255, THRESH_OTSU);
    imshow("result2", result2);
    threshold(result2, result1, 100, 255, THRESH_BINARY_INV);
    count = connectedComponentsWithStats(result1, labelsMat, statsMat, centroidsMat);



    cout << count - 1 << endl;

    for (int i = 0; i < count; i++) {

        Rect box;

        box.x = statsMat.at<int>(i, 0);

        box.y = statsMat.at<int>(i, 1);

        box.width = statsMat.at<int>(i, 2);

        box.height = statsMat.at<int>(i, 3);
        if (box.width / box.height > 0.9 && box.width / box.height < 1.1&&box.width*box.height>500)
        {
            rectangle(result1, box, CV_RGB(255, 255, 255), 1, 8, 0);
        }
    }



    imshow("result1", result1);

    waitKey(0);



    return 0;
}

int main()
{
    xinpian();
    luntai();
    return 0;
}