#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void colorReduce(Mat& inputImage, Mat& outputImage, int div);

int main()
{
	Mat srcImg = imread("1.jpg");
	imshow("原始图像", srcImg);

	Mat dstImg;
	dstImg.create(srcImg.rows, srcImg.cols, srcImg.type());
	double time0 = static_cast<double>(getTickCount());
	colorReduce(srcImg, dstImg, 32);
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为：" << time0 << "秒" << endl;

	imshow("效果图", dstImg);
	waitKey(0);

	return 0;
}

void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols*outputImage.channels();

	for (int i = 0; i < rowNumber; i++)
	{
		uchar* data = outputImage.ptr<uchar>(i);
		for (int j = 0; j < colNumber; j++)
		{
			data[j] = data[j] / div * div + div / 2;
		}
	}
}