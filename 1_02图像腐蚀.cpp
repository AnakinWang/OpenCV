#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

//int main()
//{
//	Mat srcImg = imread("1.jpg");
//	imshow("��ԭͼ����ʴ����", srcImg);
//	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
//	Mat dstImg;
//	erode(srcImg, dstImg, element);
//	imshow("��Ч��ͼ����ʴ����", dstImg);
//	waitKey(0);
//
//	return 0;
//}