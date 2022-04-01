//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//using namespace std;
//using namespace cv;
//
//bool LinearBlending();
//
//int main()
//{
//	if (!LinearBlending())
//	{
//		cout << "ERROR ... \n";
//	}
//	waitKey(0);
//
//	return 0;
//}
//
//bool LinearBlending()
//{
//	double alphaValue = 0.5;
//	double betaValue;
//	Mat srcImg2, srcImg3, dstImg;
//
//	srcImg2 = imread("NY_1.jpg");
//	srcImg3 = imread("rain_1.jpg");
//
//	if (!srcImg2.data)
//	{
//		cout << "读取srcImg2错误~  \n";
//		return false;
//	}
//	if (!srcImg3.data)
//	{
//		cout << "读取srcImg3错误~  \n";
//		return false;
//	}
//	betaValue = (1.0 - alphaValue);
//	addWeighted(srcImg2, alphaValue, srcImg3, betaValue, 0.0, dstImg);
//
//	namedWindow("线性混合【原图】", 1);
//	imshow("线性混合【原图】", srcImg2);
//
//	namedWindow("线性混合【效果图】", 1);
//	imshow("线性混合【效果图】", dstImg);
//
//	return true;
//}