#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#define MAX_LEN 50
using namespace std;

// �׸��� �Է� �޴� �Լ�
IplImage *readPicture(IplImage *in)
{
	char str[MAX_LEN];
	printf("Input File Path:");
	gets_s(str, MAX_LEN);
	in = cvLoadImage(str);
	if (in == nullptr) // ��θ� �� �� �Է������� �����޼��� ��� �� ���α׷� ����
	{
		printf("File Not Found!");
		exit(-1);
	}
	return in;
}
void MyFastestMeanFilter(IplImage* src, IplImage *dst, int K)  //���η� ����
{	
	float inv_sum = 1.0f / ((2 * K + 1)*(2 * K + 1));
	
	IplImage* tmp = cvCreateImage(cvGetSize(src), 8, 3);

	int w = src->width;
	int h = src->height;

	CvScalar **Sum = new CvScalar*[h];
	for (int i = 0;i < h;i++)
		Sum[i] = new CvScalar[w]; //CvScalar 2�����迭 �����Ҵ�


	for (int y = 0; y < h; y++){     //��� ���� ��� �� ����
		for (int x = 0; x < w; x++) 
			Sum[y][x] = cvGet2D(src, y, x);
	}

	for (int y = 0; y < h; y++) {      //����� ��� �� ������ �����ֱ�--> summed area table
		for (int x = 1; x < w; x++) {
			for (int i = 0; i < 3; i++){
				Sum[y][x].val[i] = Sum[y][x].val[i] + Sum[y][x - 1].val[i];    //�������� ���� �� + ���� ��� �� (������Ŵ)         
			}
		}
	}//���η� ���� 

	for (int x = 0; x < w; x++){
		for (int y = 1; y < h; y++) {
			for (int i = 0; i < 3; i++){
				Sum[y][x].val[i] = Sum[y][x].val[i] + Sum[y - 1][x].val[i];   //���� ���������� �ٽ� ����
			}
		}
	}
	for (int y = K;y < h - K;y++)
		for (int x = K;x < w - K;x++)
		{
			CvScalar g;
			for (int i = 0;i < 3;i++) {
				g.val[i] = Sum[K + 1][K + 1].val[i];
			}
			for (int k = 0;k < 3;k++) g.val[k] *= inv_sum;
			cvSet2D(dst, y, x, g);
		}

	//for (int step = 0;step < 3;step++) {
	//	for (int y = 0;y < h;y++)
	//		for (int x = 0;x < w;x++)
	//			Sum[y][x] = cvScalar(0, 0, 0);
	//}
	//CvScalar std;
	//Sum[0][0] = cvGet2D(src, 0, 0);
	//std = Sum[0][0];

	//for (int step = 0;step < 3;step++) { // ��������
	//	int y = 0;
	//	CvScalar g = cvGet2D(src, 0, 1);
	//	Sum[0][1].val[step] = g.val[step] + std.val[step];
	//	std.val[step] += g.val[step];
	//	for (int x = 2;x < w;x++) {
	//		CvScalar f = cvGet2D(src, 0, x);
	//		Sum[y][x].val[step] = f.val[step] + std.val[step];
	//		std.val[step] += Sum[y][x - 1].val[step];
	//	}
	//}
	//
	//for (int step = 0;step < 3;step++){ //��������
	//	int x = 0;
	//	CvScalar g = cvGet2D(src, 1, 0);
	//	Sum[0][1].val[step] = g.val[step] + std.val[step];
	//	std.val[step] += g.val[step];
	//	for (int y = 2;y < h;y++) {
	//		CvScalar f = cvGet2D(src, y, 0);
	//		Sum[y][x].val[step] = f.val[step] + std.val[step];
	//		std.val[step] += Sum[y - 1][x].val[step];
	//	}
	//}

	//for (int step = 0;step < 3;step++){ //������
	//	for(int y=1;y<h;y++)
	//		for (int x = 1;x < w;x++)
	//		{
	//			CvScalar f = cvGet2D(src, y, x);
	//			Sum[y][x].val[step] = Sum[y][x - 1].val[step] + Sum[y - 1][x].val[step] - Sum[y - 1][x - 1].val[step] + f.val[step];
	//		}
	//}
	
		

	

	//for (int y = K;y < h - K;y++)
	//	for (int x = K;x < w - K;x++)
	//	{
	//		CvScalar g = cvScalar(0, 0, 0);
	//		for (int u = -K;u <= K; u++)
	//		{
	//			CvScalar f = cvGet2D(src, y, x + u);
	//			for (int k = 0;k < 3;k++)
	//				g.val[k] += f.val[k];
	//		}
	//		for (int k = 0;k < 3;k++)
	//			g.val[k] *= inv_sum;
	//		cvSet2D(dst, y, x, g);
	//	}
} 

int main()
{
	IplImage* src = nullptr;
	int KernelSize;
	cout << "=============================================" << endl;
	cout << "Software Department, Sejong University" << endl;
	cout << "Multimedia Programming Class" << endl;
	cout << "Homework: Fastest Mean Filte" << endl;
	cout << "=============================================" << endl;
	src = readPicture(src);
	IplImage *dst = cvCreateImage(cvGetSize(src), 8, 3);
	cout << "Input Kernel Size:";
	cin >> KernelSize;
	cvShowImage("src", src);
	MyFastestMeanFilter(src, dst, KernelSize);
	cvWaitKey();
	cvShowImage("dst", dst);
	cvWaitKey();
}