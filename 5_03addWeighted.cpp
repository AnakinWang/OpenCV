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
//		cout << "��ȡsrcImg2����~  \n";
//		return false;
//	}
//	if (!srcImg3.data)
//	{
//		cout << "��ȡsrcImg3����~  \n";
//		return false;
//	}
//	betaValue = (1.0 - alphaValue);
//	addWeighted(srcImg2, alphaValue, srcImg3, betaValue, 0.0, dstImg);
//
//	namedWindow("���Ի�ϡ�ԭͼ��", 1);
//	imshow("���Ի�ϡ�ԭͼ��", srcImg2);
//
//	namedWindow("���Ի�ϡ�Ч��ͼ��", 1);
//	imshow("���Ի�ϡ�Ч��ͼ��", dstImg);
//
//	return true;
//}