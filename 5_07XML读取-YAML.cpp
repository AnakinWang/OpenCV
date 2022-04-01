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
//	system("color 6F");
//
//	FileStorage fs2("test01.xml", FileStorage::READ);
//
//	int frameCount = (int)fs2["frameCount"];
//	std::string date;
//	fs2["calibrationDate"] >> date;
//
//	Mat cameraMatrix2, distCoeffs2;
//	fs2["cameraMatrix"] >> cameraMatrix2;
//	fs2["distCoeffs"] >> distCoeffs2;
//
//	cout << "frameCount: " << frameCount << endl
//		<< "calibration date: " << date << endl
//		<< "camera matrix: " << cameraMatrix2 << endl
//		<< "distortion coeffs:" << distCoeffs2 << endl;
//
//	FileNode features = fs2["features"];
//	FileNodeIterator it = features.begin(), it_end = features.end();
//	int idx = 0;
//	std::vector<uchar> lbpval;
//
//	for (; it != it_end; ++it, idx++)
//	{
//		cout << "feature #" << idx << ": ";
//		cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp:(";
//		(*it)["lbp"] >> lbpval;
//		for (int i = 0; i < (int)lbpval.size(); i++)
//		{
//			cout << " " << (int)lbpval[i];
//		}
//		cout << ")" << endl;
//
//	}
//	fs2.release();
//
//	printf("\n文件读取完毕，按任意键退出~");
//	getchar();
//
//	return 0;
//}