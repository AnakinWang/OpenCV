//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//using namespace std;
//using namespace cv;
//
//void colorReduce(Mat& inputImage, Mat& outputImage, int div);
//
//int main()
//{
//	Mat srcImg = imread("1.jpg");
//	imshow("ԭʼͼ��", srcImg);
//
//	Mat dstImg;
//	dstImg.create(srcImg.rows, srcImg.cols, srcImg.type());
//	double time0 = static_cast<double>(getTickCount());
//	colorReduce(srcImg, dstImg, 32);
//	time0 = ((double)getTickCount() - time0) / getTickFrequency();
//	cout << "�˷�������ʱ��Ϊ��" << time0 << "��" << endl;
//
//	imshow("Ч��ͼ", dstImg);
//	waitKey(0);
//
//	return 0;
//}
//
////  ��ָ��������أ���ʱ0.004015s
//void colorReduce(Mat& inputImage, Mat& outputImage, int div)
//{
//	outputImage = inputImage.clone();
//	int rowNumber = outputImage.rows;
//	int colNumber = outputImage.cols*outputImage.channels();
//
//	for (int i = 0; i < rowNumber; i++)
//	{
//		uchar* data = outputImage.ptr<uchar>(i); //  ��ȡ��i�е��׵�ַ
//		for (int j = 0; j < colNumber; j++)
//		{
//			data[j] = data[j] / div * div + div / 2;
//		}
//	}
//}
//
//////  �õ�������������,ʱ����0.112947s
////void colorReduce(Mat& inputImage, Mat& outputImage, int div)
////{
////	outputImage = inputImage.clone();
////	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();
////	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();
////
////	for (; it != itend; ++it)
////	{
////		(*it)[0] = (*it)[0] / div * div + div / 2;
////		(*it)[1] = (*it)[1] / div * div + div / 2;
////		(*it)[2] = (*it)[2] / div * div + div / 2;
////
////	}
////}
//
//////  ��̬��ַ����,ʱ����0.184045s
////void colorReduce(Mat& inputImage, Mat& outputImage, int div)
////{
////	outputImage = inputImage.clone();
////	int rowNumber = inputImage.rows;
////	int colNumber = inputImage.cols;
////
////	for (int i = 0; i < rowNumber; i++)
////	{
////		for (int j = 0; j < colNumber; j++)
////		{
////			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;
////			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;
////			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;
////		}
////	}
////}
//
//
//
//
//
//
