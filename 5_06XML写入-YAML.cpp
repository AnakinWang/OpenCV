//#define _CRT_SECURE_NO_WARNINGS
//#include "opencv2/opencv.hpp"
//#include <time.h>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	FileStorage fs("test01.xml", FileStorage::WRITE);
//
//	fs << "frameCount" << 5;
//	time_t rawtime; time(&rawtime);
//	char str[50];
//	fs << "CalibrationDate" << asctime(localtime(&rawtime));
//	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
//	Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
//	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
//	fs << "features" << "[";
//	for (int i = 0; i < 3; i++)
//	{
//		int x = rand() % 640;
//		int y = rand() % 480;
//		uchar lbp = rand() % 256;
//
//		fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
//		for (int j = 0; j < 8; j++)
//		{
//			fs << ((lbp >> j) & 1);		
//		}
//		fs << "]" << "}";
//		
//	}
//	fs << "]";
//	fs.release();
//
//	cout << "文件读写完毕，请查看生成文件...\n";
//	getchar();
//
//	return 0;
//}