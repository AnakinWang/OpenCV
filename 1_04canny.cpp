#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//int main()
//{
//	Mat srcImg = imread("1.jpg");
//	imshow("��ԭʼͼ��Canny��Ե���", srcImg);
//	Mat dstImg, edge, grayImg;
//
//	dstImg.create(srcImg.size(), srcImg.type());
//	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
//
//	blur(grayImg, edge, Size(3, 3));
//
//	Canny(edge, edge, 3, 9, 3);
//	imshow("��Ч��ͼ��Canny��Ե���", edge);
//
//	waitKey(0);
//
//	return 0;
//}