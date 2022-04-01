//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//using namespace std;
//using namespace cv;
//
//bool ROI_AddImg();
//
//int main()
//{
//	if (!ROI_AddImg())
//	{
//		cout << "ERROR ... \n";
//	}
//	waitKey(0);
//
//	return 0;
//}
//
//bool ROI_AddImg()
//{
//	Mat srcImg1 = imread("1.jpg");
//	Mat logoImg = imread("logo.jpg");
//	if (!srcImg1.data)
//	{
//		cout << "读取srcImg错误~！ \n";
//		return false;
//	}
//	if (!logoImg.data)
//	{
//		cout << "读取logoImg错误~！ \n";
//		return false;
//	}
//	Mat imgROI = srcImg1(Rect(5, 5, logoImg.cols, logoImg.rows));
//	Mat mask = imread("logo.jpg", 0);
//	logoImg.copyTo(imgROI, mask);
//	namedWindow("利用ROI实现图像叠加示例窗口");
//	imshow("利用ROI实现图像叠加示例窗口",srcImg1);
//
//	return true;
//}