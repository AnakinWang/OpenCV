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
//		cout << "��ȡsrcImg����~�� \n";
//		return false;
//	}
//	if (!logoImg.data)
//	{
//		cout << "��ȡlogoImg����~�� \n";
//		return false;
//	}
//	Mat imgROI = srcImg1(Rect(5, 5, logoImg.cols, logoImg.rows));
//	Mat mask = imread("logo.jpg", 0);
//	logoImg.copyTo(imgROI, mask);
//	namedWindow("����ROIʵ��ͼ�����ʾ������");
//	imshow("����ROIʵ��ͼ�����ʾ������",srcImg1);
//
//	return true;
//}