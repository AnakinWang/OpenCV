/////*
////DFT()函数对图像求傅里叶变换
////得到图像中的几何结构信息
////*/
////
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat srcImg = imread("1.jpg", 0);
//	if (!srcImg.data)
//	{
//		cout << "读取图片错误... \n";
//			return false;
//	}
//	imshow("原始图像", srcImg);
//
//	int m = getOptimalDFTSize(srcImg.rows);
//	int n = getOptimalDFTSize(srcImg.cols);
//	Mat padded;
//	copyMakeBorder(srcImg, padded, 0, m - srcImg.rows, 0, n - srcImg.cols, BORDER_CONSTANT, Scalar::all(0));
//
//	Mat planes[] = { Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F) };
//	Mat complexI;
//	merge(planes, 2, complexI);
//
//	dft(complexI, complexI);
//
//	split(complexI, planes);
//	magnitude(planes[0], planes[1], planes[0]);
//	Mat magnitudeImg = planes[0];
//
//	magnitudeImg += Scalar::all(1);
//	log(magnitudeImg, magnitudeImg);
//
//	magnitudeImg = magnitudeImg(Rect(0, 0, magnitudeImg.cols &-2, magnitudeImg.rows&-2));
//	int cx = magnitudeImg.cols / 2;
//	int cy = magnitudeImg.rows / 2;
//	Mat q0(magnitudeImg, Rect(0, 0, cx, cy));
//	Mat q1(magnitudeImg, Rect(cx, 0, cx, cy));
//	Mat q2(magnitudeImg, Rect(0, cy, cx, cy));
//	Mat q3(magnitudeImg, Rect(cx, cy, cx, cy));
//
//	Mat tmp;
//	q0.copyTo(tmp);
//	q3.copyTo(q0);
//	tmp.copyTo(q3);
//
//	q1.copyTo(tmp);
//	q2.copyTo(q1);
//	tmp.copyTo(q2);
//
//	normalize(magnitudeImg, magnitudeImg, 0, 1, NORM_MINMAX);
//	imshow("频谱幅值", magnitudeImg);
//	waitKey();
//
//	return 0;
//}