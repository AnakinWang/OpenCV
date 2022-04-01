#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat g_srcImg, g_dstImg1, g_dstImg2, g_dstImg3;
int g_nBoxFilterValue = 3;
int g_nMeanBlurValue = 3;
int g_nGuassianBlurValue = 3;

static void on_BoxFilter(int ,void *);
static void on_MeanBlur(int, void *);
static void on_GaussianBlur(int, void *);

int main()
{
	system("color5E");

	g_srcImg = imread("100.jpg", 1);
	if (!g_srcImg.data)
	{
		cout << "读取图片错误~！ \n";
		return false;
	}

	g_dstImg1 = g_srcImg.clone();
	g_dstImg2 = g_srcImg.clone();
	g_dstImg3 = g_srcImg.clone();

	namedWindow("【<0>原图窗口】", 1);
	imshow("【<0>原图窗口】", g_srcImg);

	namedWindow("【<1>方框滤波】", 1);
	createTrackbar("内核值：", "【<1>方框滤波】", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	imshow("【<1>方框滤波】", g_dstImg1);

	namedWindow("【<2>均值滤波】", 1);
	createTrackbar("内核值：", "【<2>均值滤波】", &g_nMeanBlurValue, 40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);

	namedWindow("【<3>高斯滤波】", 1);
	createTrackbar("内核值：", "【<3>高斯滤波】", &g_nGuassianBlurValue, 40, on_GaussianBlur);
	on_GaussianBlur(g_nMeanBlurValue, 0);

	cout << endl << "\t, 请调整滚动条观察图像效果~\n\n"
		<< "\t按下'q'键退出程序 ! \n";
	while(char(waitKey(1))!= 'q')
	{ }

	return 0;
}

static void on_BoxFilter(int, void *)
{
	boxFilter(g_srcImg, g_dstImg1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
	imshow("【<1>方框滤波】", g_dstImg1);
}

static void on_MeanBlur(int, void *)
{
	blur(g_srcImg, g_dstImg2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1),Point(-1,-1));
	imshow("【<2>均值滤波】", g_dstImg2);
}

static void on_GaussianBlur(int, void *)
{
	GaussianBlur(g_srcImg, g_dstImg3, Size(g_nGuassianBlurValue*2 + 1, g_nGuassianBlurValue*2 + 1), 0, 0);
	imshow("【<3>高斯滤波】", g_dstImg3);
}