#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//int main()
//{
//	Mat srcImg = imread("1.jpg");
//	imshow("¡¾Ô­Ê¼Í¼¡¿Canny±ßÔµ¼ì²â", srcImg);
//	Mat dstImg, edge, grayImg;
//
//	dstImg.create(srcImg.size(), srcImg.type());
//	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
//
//	blur(grayImg, edge, Size(3, 3));
//
//	Canny(edge, edge, 3, 9, 3);
//	imshow("¡¾Ð§¹ûÍ¼¡¿Canny±ßÔµ¼ì²â", edge);
//
//	waitKey(0);
//
//	return 0;
//}