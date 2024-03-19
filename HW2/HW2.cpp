#include <opencv2/opencv.hpp>
#include <stdio.h>
#define MAX_LEN 50

// �׸��� �Է� �޴� �Լ�
IplImage *readPicture(IplImage *in)
{
	char str[MAX_LEN];
	printf("Input File Name:");
	gets_s(str, MAX_LEN);
	in = cvLoadImage(str);
	if (in == nullptr) // ��θ� �� �� �Է������� �����޼��� ��� �� ���α׷� ����
	{
		printf("File Not Found!");
		exit(-1);
	}
	return in;
}

IplImage *BlueFilter(IplImage *in, IplImage *src) //Blue ���͸� �и��ؼ� ���� �����ϴ� �Լ�
{
	CvSize size = cvGetSize(src);
	CvSize CreateSize = cvSize(0, 0);
	for (int y = 0;y < (size.height) / 3;y++) CreateSize.height++;
	CreateSize.width = size.width; //�츮�� ������ ���� ũ�⸦ ������ �� �� ũ�� ��ŭ�� �� �̹����� �������ش�
	in = cvCreateImage(CreateSize, 8, 3);
	for (int y = 0;y < size.height / 3; y++)
		for (int x = 0;x < size.width;x++)
		{
			CvScalar c = cvGet2D(src, y, x);
			cvSet2D(in, y, x, c); //������ �� �̹����� �������ش�.
		}
	return in;
}

IplImage *GreenFilter(IplImage *in, IplImage *src) //Green ���͸� �и��ؼ� ���� �����ϴ� �Լ�
{
	CvSize size = cvGetSize(src);
	CvSize CreateSize = cvSize(0, 0);
	int tmp = 0;
	for (int y = (size.height)/3;y < (size.height)*2/3;y++) 
		CreateSize.height++;
	CreateSize.width = size.width;
	in = cvCreateImage(CreateSize, 8, 3);
	for (int y = size.height / 3;y < size.height * 2 / 3; y++)
	{
		for (int x = 0;x < size.width;x++)
		{
			CvScalar c = cvGet2D(src, y, x);
			cvSet2D(in, tmp, x, c);
		}
		tmp++;
	}
	return in;
}

IplImage *RedFilter(IplImage *in, IplImage *src) //Red ���͸� �и��ؼ� ���� �����ϴ� �Լ�
{
	CvSize size = cvGetSize(src);
	CvSize CreateSize = cvSize(0, 0);
	for (int y = (size.height)* 2/3;y < (size.height);y++)
		CreateSize.height++;
	CreateSize.width = size.width;
	in = cvCreateImage(CreateSize, 8, 3);
	int tmp = 0;
	for (int y = (size.height * 2) / 3;y < size.height;y++) {
		for (int x = 0;x < size.width;x++)
		{
			CvScalar c = cvGet2D(src, y, x);
			cvSet2D(in, tmp, x, c);
		}
		tmp++;
	}
	return in;
}

// �ռ��� Į�� �̹����� ����� �Լ�
IplImage *ColorPrint(IplImage * src, IplImage * in1, IplImage * in2,IplImage *in3)
{
	IplImage *sub; // �����
	CvSize size = cvGetSize(src);
	CvSize CreateSize = cvSize(0, 0);
	for (int y = 0;y < (size.height) / 3;y++) 
		CreateSize.height++;
	CreateSize.width = size.width;
	sub = cvCreateImage(CreateSize, 8, 3); //�÷� ������ �� �̹��� ����
	for (int y = 0;y < CreateSize.height;y++) {
		for (int x = 0;x < CreateSize.width;x++)
		{
			CvScalar b = cvGet2D(in1, y, x);
			CvScalar g = cvGet2D(in2, y, x);
			CvScalar r = cvGet2D(in3, y, x);
			CvScalar color;
			color.val[0] = b.val[0];
			color.val[1] = g.val[1];
			color.val[2] = r.val[2]; //������ ���͵鿡�� BGR���� �����ϰ� ���� �����Ѵ�.
			cvSet2D(sub, y, x, color);
		}
	}
	return sub;
}
//float getDiff2(CvScalar a, CvScalar b)
//{
//	return (a.val[0] - b.val[0])*(a.val[0] - b.val[0]) + (a.val[1] - b.val[1])*(a.val[1] - b.val[1]) + (a.val[2] - b.val[2])*(a.val[0] - b.val[0]);
//}
//void sort_BG(IplImage *B, IplImage *G)
//{
//	CvSize size = cvGetSize(B);
//	int w = size.width;
//	int h =size.height;
//
//	float min_diff = 1000000;
//	int min_u;
//	int min_v;
//	for (int u = -w / 4;u < w / 4;u++)           // brute-force
//		for (int v = -h / 4;v < h / 4;v++)
//		{
//			/*printf("u = %d v = %d\n", u, v);
//			cvSet(dst, cvScalar(0, 0, 0));*/
//			float diff = 0.0f;
//			int count = 0;
//			for (int y = 0;y < h;y++)
//				for (int x = 0;x < w;x++)
//				{
//					int x2 = x - u;
//					int y2 = y - v;
//					if (x2<0 || x2>w - 1) continue;
//					if (y2<0 || y2>h - 1) continue;
//
//					CvScalar f1 = cvGet2D(B, y, x);
//					CvScalar f2 = cvGet2D(G, y2, x2);
//					diff += getDiff2(f1, f2);
//					count++;
//					CvScalar g;
//					g.val[0] = (f1.val[0] + f2.val[0]) / 2;
//					g.val[1] = (f1.val[1] + f2.val[1]) / 2;
//					g.val[2] = (f1.val[2] + f2.val[2]) / 2;
//					/*cvSet2D(src, y, x, g);*/
//				}
//			diff = diff / count; //������� ���̰�;
//			if (diff < min_diff)
//			{
//				min_diff = diff;
//				min_u = u;
//				min_v = v;
//				/*printf("u=%d v=%d diff = %f min_diff= %f\n", u, v, diff, min_diff);*/
//				/*cvShowImage("dst", B);
//				cvWaitKey(1);*/
//			}
//
//
//
//		}
//	printf("u=%d v=%d  min_diff= %f\n", min_u, min_v, min_diff);
//	/*cvShowImage("src1", R);
//	cvShowImage("src2", G);*/
//
//}
//void sort_GR(IplImage *B, IplImage *G, IplImage *src)
//{
//
//}
int main()
{
	IplImage *src = nullptr;
	IplImage *B_part= nullptr, *G_part= nullptr, *R_part= nullptr;
	IplImage *dst = nullptr;
	src = readPicture(src);
	cvShowImage("src", src);
	cvWaitKey();
	CvSize size = cvGetSize(src);
	B_part = BlueFilter(B_part, src);
	G_part = GreenFilter(G_part, src);
	R_part = RedFilter(R_part, src);
	
	dst = ColorPrint(src, B_part, G_part, R_part);
	cvSaveImage("C:\\Temp\\result.jpg", dst);
	cvShowImage("dst", dst);
	cvWaitKey();
	
	 
}
