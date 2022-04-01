/*#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
#define PHOTO "2.jpg"

void PlateRecognition();
Mat Image_Preprocessing(Mat temp);
Mat Morphological_Processing(Mat temp);
Mat Locate_License_Plate(Mat temp, Mat src, Mat gray_src);
Mat Affine_Transform(Mat temp);
Mat Remove_Vertial_Border(Mat temp);
Mat Remove_Horizon_Border(Mat temp);
Mat Horizon_Cut(Mat temp);
void Locate_String(int *x_begin, int *x_end, Mat temp);
void Draw_Result(int *x_begin, int *x_end, Mat temp);
void Recognize_Lisence(int *x_begin, int *x_end, Mat temp);

int main()
{
	PlateRecognition();

	waitKey();
	return 0;
}

void PlateRecognition()
{
	Mat srcImg = imread(PHOTO);
	if (!srcImg.data)
	{
		cout << "��Ƭ��ȡ����... \n";
		system("pause");
	}
//	imshow("��ԭͼ��", srcImg);
	Mat gray_src;
	cvtColor(srcImg, gray_src, COLOR_BGR2GRAY);
	Mat CannyImg;
	CannyImg = Image_Preprocessing(srcImg);
	Mat MedianImg = Morphological_Processing(CannyImg);
	Mat ContourImg = MedianImg.clone();
	Mat Roi = Locate_License_Plate(ContourImg, srcImg, gray_src);
	//��������任Ŀ��ͼ����ԭͼ��ߴ�������ͬ
	Mat warp_dstImage = Affine_Transform(Roi);
	Mat bin_warp_dstImage;
	threshold(warp_dstImage, bin_warp_dstImage, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("ͬһ�ߴ�Ķ�ֵͼ��", bin_warp_dstImage);
	//����ʶ��
	//�г����Ƶ�ˮƽ�봹ֱ�߿�
	bin_warp_dstImage = Remove_Vertial_Border(bin_warp_dstImage);
	bin_warp_dstImage = Remove_Horizon_Border(bin_warp_dstImage);
	//��ȥ���ƺ�����������ಿ��
	Mat license = Horizon_Cut(bin_warp_dstImage);
	//���ƺ���ָ��ʾ�ָ���
	int *x_begin = new int[8];
	int *x_end = new int[8];
	for (int i = 0; i < 8; i++)
	{
		x_begin[i] = 0;
		x_end[i] = 0;
	}
	Locate_String(x_begin, x_end, license);
	Draw_Result(x_begin, x_end, license);
	cout << "���ƺ�ʶ������" << endl;
	Recognize_Lisence(x_begin, x_end, license);
	delete[] x_begin;
	delete[] x_end;

}

Mat Image_Preprocessing(Mat temp)
{
	Mat kernel = getStructuringElement(MORPH_RECT, Size(25, 25), Point(-1, -1));
	Mat open_gray_blur_Image;
	morphologyEx(temp, open_gray_blur_Image, MORPH_OPEN, kernel);
	Mat rst;
	subtract(temp, open_gray_blur_Image, rst, Mat());
//	imshow("rst", rst);
	Mat Canny_Image;
	Canny(rst, Canny_Image, 400, 200, 3);
//	imshow("Canny_Image", Canny_Image);
	return Canny_Image;
}

Mat Morphological_Processing(Mat temp)//��̬ѧ����
{
	//ͼƬ���ʹ���
	Mat dilate_image, erode_image;
	//�Զ���ˣ����� x ��������͸�ʴ
	Mat elementX = getStructuringElement(MORPH_RECT, Size(25, 1));
	Mat elementY = getStructuringElement(MORPH_RECT, Size(1, 19));
	Point point(-1, -1);
	dilate(temp, dilate_image, elementX, point, 2);
	erode(dilate_image, erode_image, elementX, point, 4);
	dilate(erode_image, dilate_image, elementX, point, 2);
	//�Զ���ˣ����� Y ��������͸�ʴ
	erode(dilate_image, erode_image, elementY, point, 1);
	dilate(erode_image, dilate_image, elementY, point, 2);
	//ƽ������
	Mat median_Image;
	medianBlur(dilate_image, median_Image, 15);
	medianBlur(median_Image, median_Image, 15);
//	imshow("��ֵ�˲�", median_Image);
	return median_Image;
}

//���ƶ�λ
Mat Locate_License_Plate(Mat temp, Mat src, Mat gray_src)
{
	vector<vector<Point>> contours;
	findContours(temp, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//��������
	drawContours(temp, contours, -1, Scalar(255), 1);
	//������ʾΪһ������

//	imshow("drawContours", temp);
	Mat Roi;
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rect = minAreaRect(Mat(contours[i]));
		Point2f p[4];
		rect.points(p);
		double axisLongTemp = 0.0, axisShortTemp = 0.0;//���εĳ��ߺͶ̱�
		axisLongTemp = sqrt(pow(p[1].x - p[0].x, 2) + pow(p[1].y - p[0].y, 2));  //���㳤��
		axisShortTemp = sqrt(pow(p[2].x - p[1].x, 2) + pow(p[2].y - p[1].y, 2)); //�������
		double LengthTemp;//�м����
		if (axisShortTemp > axisLongTemp)//��������ڳ��ᣬ��������
		{
			LengthTemp = axisLongTemp;
			axisLongTemp = axisShortTemp;
			axisShortTemp = LengthTemp;
		}
		double rectArea = axisLongTemp * axisShortTemp;//����������
		double Area = contourArea(Mat(contours[i]));//�������
		double rectDegree = Area / rectArea;//������ζ�
		if (axisLongTemp / axisShortTemp >= 2.2 && axisLongTemp / axisShortTemp <= 5.1 && rectDegree > 0.63 && rectDegree < 1.37 && rectArea>2000 && rectArea < 50000)//ͨ����������ȣ����ζ��Լ���������ı仯��Χ�����������򣨸ò��ֿ���ʵ�������������
		{
			for (int i = 0; i < 4; i++)       //���߿����������
				line(src, p[i], p[((i + 1) % 4) ? (i + 1) : 0], Scalar(0, 0, 255), 2, 8, 0);

			float width_height = (float)rect.size.width / (float)rect.size.height;
			float angle = rect.angle;
			if (width_height < 1)//����ͼ������ת�Ƕȴ���90�ȵĳ���
				angle = angle + 270;
			Mat rotMat = getRotationMatrix2D(rect.center, angle, 1);//��þ��ε���ת����
			Mat warpImg;
			warpAffine(gray_src, warpImg, rotMat, src.size(), INTER_CUBIC);
//			imshow("����任", warpImg);
			//ͼ���и�
			Size minRectSize = rect.size;
			if (width_height < 1)
				swap(minRectSize.width, minRectSize.height);
			getRectSubPix(warpImg, minRectSize, rect.center, Roi);
		}
	}
	imshow("test", src);
//	imshow("������ȡ���", Roi);
	return Roi;
}

Mat Affine_Transform(Mat temp)
{
	Mat warp_dstImage = Mat::zeros(100, 500, temp.type());
	Point2f srcTri[3];
	Point2f dstTri[3];
	//�������������������任
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(temp.cols, 0);
	srcTri[2] = Point2f(0, temp.rows);

	dstTri[0] = Point2f(0, 0);
	dstTri[1] = Point2f(500, 0);
	dstTri[2] = Point2f(0, 100);
	//�������任����
	Mat warp_mat(2, 3, CV_32FC1);
	warp_mat = getAffineTransform(srcTri, dstTri);
	//�Լ���ͼ�ν��з���任����
	warpAffine(temp, warp_dstImage, warp_mat, warp_dstImage.size());
	return warp_dstImage;
}

Mat Remove_Vertial_Border(Mat temp)
{
	Mat vline = getStructuringElement(MORPH_RECT, Size(1, temp.rows), Point(-1, -1));
	Mat dst1, temp1;
	erode(temp, temp1, vline);
	dilate(temp1, dst1, vline);
//	namedWindow("��ȡ��ֱ��", WINDOW_AUTOSIZE);
//	imshow("��ȡ��ֱ��", dst1);
	subtract(temp, dst1, temp, Mat());
//	imshow("�и�ƴ�ֱ�߿���", temp);
	return temp;
}
Mat Remove_Horizon_Border(Mat temp)
{
	Mat hline = getStructuringElement(MORPH_RECT, Size(60, 1), Point(-1, -1));//������״Ϊ��1*src.cols
	Mat dst1, temp1;
	erode(temp, temp1, hline);
	dilate(temp1, dst1, hline);
//	namedWindow("��ȡˮƽ��", WINDOW_AUTOSIZE);
//	imshow("��ȡˮƽ��", dst1);
	subtract(temp, dst1, temp, Mat());
//	imshow("�и��ˮƽ�߿���", temp);
	return temp;
}

Mat Horizon_Cut(Mat temp)
{
	int *counter_y = new int[temp.rows];
	for (int i = 0; i < temp.rows; i++)
		counter_y[i] = 0;
	for (int row = 0; row < temp.rows; row++)
	{
		int count = 0;
		for (int col = 0; col < temp.cols; col++)
		{
			if (temp.at<uchar>(row, col) == 255)
			{
				count++;
			}
		}
		if (count > 50)
		{
			counter_y[row] = 1;
		}
	}
	//for (int i = 0; i < temp.rows; i++)
	//	cout << counter_y[i] << '\t';// = 0;
	//cout << endl;
	int count_temp = 0;
	int *record = new int[temp.rows];
	for (int i = 0; i < temp.rows; i++)
		record[i] = 0;
	for (int i = 0; i < temp.rows; i++)
	{
		if (counter_y[i] == 1)
		{
			count_temp++;
			record[i] = count_temp;
		}
		else
			count_temp = 0;
	}
	int max = record[0];
	int index = 0;
	for (int i = 1; i < temp.rows; i++)
	{
		if (max < record[i])
		{
			max = record[i];
			index = i;
		}
	}
	int index_row_begin = index - max + 1;
	int index_row_end = index;
	//cout << index_row_begin << endl << index_row_end << endl;
	int height = index_row_end - index_row_begin;
	Mat image_preprocess = Mat::zeros(height, temp.cols, CV_8UC1);
	for (int row = 0; row < image_preprocess.rows; row++)
	{
		for (int col = 0; col < image_preprocess.cols; col++)
		{
			image_preprocess.at<uchar>(row, col) = temp.at<uchar>(row + index_row_begin, col);
		}
	}
//	imshow("Horizon_Cut", image_preprocess);
	return image_preprocess;
}
void Locate_String(int *x_begin, int *x_end, Mat temp)
{
	int *counter_x = new int[temp.cols];//��¼ÿһ�еİ����ظ���
	for (int i = 0; i < temp.cols; i++)
		counter_x[i] = 0;
	for (int col = 0; col < temp.cols; col++)
	{
		int count = 0;
		for (int row = 0; row < temp.rows; row++)
		{
			if (temp.at<uchar>(row, col) == 255)
			{
				count++;
			}
		}
		counter_x[col] = count;
	}
	int index_col = 0;
	int number_width = 0;
	for (int i = 0; i < temp.cols - 1; i++)
	{
		if (counter_x[i] >= 4)//�˴���ֵ�����������
		{
			number_width++;
			if (number_width > 8)//�˴���ֵ�����������
			{
				x_end[index_col] = i;
				x_begin[index_col] = i - number_width + 1;
				if (counter_x[i + 1] < 4)//�˴���ֵ�����������
				{
					number_width = 0;
					index_col++;
				}
			}
		}
		else
		{
			number_width = 0;
		}
		if (index_col >= 8)
			break;
	}
}
void Draw_Result(int *x_begin, int *x_end, Mat temp)
{
	int x, y;
	int width;
	int length;
	Mat Result = temp.clone();
	for (int i = 0; i < 8; i++)
	{
		x = x_begin[i];
		y = 0;
		width = x_end[i] - x_begin[i];
		length = temp.cols;
		Rect rect(x, y, width, length);
		Scalar color(255, 255, 255);
		rectangle(Result, rect, color, 2, LINE_AA);
	}
//	imshow("���ƺ���ָ���", Result);
}
void Recognize_Lisence(int *x_begin, int *x_end, Mat temp)
{
	int cycle_index = 0;
	for (int i = 0; i < 8; i++)
	{
		if (x_end[i] > 0)
			cycle_index++;
	}
	for (int i = 0; i < cycle_index; i++)
	{
		float error[28] = { 0 };
		//	//picture1�Ƕ�ֵͼ��
		Mat picture1 = Mat::zeros(temp.rows, x_end[i] - x_begin[i], temp.type());
		for (int row = 0; row < picture1.rows; row++)
		{
			for (int col = 0; col < picture1.cols; col++)
			{
				picture1.at<uchar>(row, col) = temp.at<uchar>(row, col + x_begin[i]);
			}
		}
		Mat NUM[28];//�ַ�ƥ��ģ��
		for (int i = 0; i < 28; i++)
		{
			stringstream stream;
			stream << "pictures/num_";
			stream << i;
			stream << ".bmp";
			String name = stream.str();
			NUM[i] = imread(name);
			if (NUM[i].empty())
			{
				cout << "δ�ܶ�ȡ" << name << endl;
			}
			cvtColor(NUM[i], NUM[i], COLOR_BGR2GRAY);
			threshold(NUM[i], NUM[i], 0, 255, THRESH_BINARY);

			Point2f srcTri[3];
			Point2f dstTri[3];
			Mat warp_mat(2, 3, CV_32FC1);
			//��������任Ŀ��ͼ����ԭͼ��ߴ�������ͬ
			Mat result = Mat::zeros(picture1.rows, picture1.cols, picture1.type());
			//�������������������任
			srcTri[0] = Point2f(0, 0);
			srcTri[1] = Point2f(NUM[i].cols, 0);
			srcTri[2] = Point2f(0, NUM[i].rows);
			dstTri[0] = Point2f(0, 0);
			dstTri[1] = Point2f(picture1.cols, 0);
			dstTri[2] = Point2f(0, picture1.rows);
			//�������任����
			warp_mat = getAffineTransform(srcTri, dstTri);
			//�Լ���ͼ�ν��з���任����
			warpAffine(NUM[i], result, warp_mat, picture1.size());
			threshold(result, result, 0, 255, THRESH_BINARY_INV);
			float error_sum = 0;
			float error_temp = 0;
			for (int row = 0; row < result.rows; row++)
			{
				for (int col = 0; col < result.cols; col++)
				{
					error_temp = picture1.at<uchar>(row, col) - result.at<uchar>(row, col);
					error_sum = error_sum + pow(error_temp, 2);
				}
			}
			error[i] = error_sum / (picture1.rows*picture1.cols * 255);
		}
		float min_error = error[0];
		int Index = 0;
		for (int i = 1; i < 28; i++)
		{
			if (min_error > error[i])
			{
				min_error = error[i];
				Index = i;
			}
		}
		if (Index == 10)
			cout << "E" << '\t';
		else if (Index == 11)
			cout << "V" << '\t';
		else if (Index == 12)
			cout << "��" << '\t';
		else if (Index == 13)
			cout << "��" << '\t';
		else if (Index == 14)
			cout << "B" << '\t';
		else if (Index == 15)
			cout << "S" << '\t';
		else if (Index == 16)
			cout << "��" << '\t';
		else if (Index == 17)
			cout << "N" << '\t';
		else if (Index == 18)
			cout << "J" << '\t';
		else if (Index == 19)
			cout << "P" << '\t';
		else if (Index == 20)
			cout << "A" << '\t';
		else if (Index == 21)
			cout << "��" << '\t';
		else if (Index == 22)
			cout << "G" << '\t';
		else if (Index == 23)
			cout << "U" << '\t';
		else if (Index == 24)
			cout << "ԥ" << '\t';
		else if (Index == 25)
			cout << "K" << '\t';
		else if (Index == 26)
			cout << "��" << '\t';
		else if (Index == 27)
			cout << "��" << '\t';

		else if (Index >= 0 && Index <= 9)
			cout << Index << '\t';
	}
	cout << endl;
}
*/