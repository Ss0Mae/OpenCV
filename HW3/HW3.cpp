#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#define MAX_LEN 50
using namespace std;

void MyFastestMeanFilter(IplImage* src, IplImage *dst, int K)  
{	
	float inv_sum = 1.0f / ((2 * K + 1)*(2 * K + 1));
	

	int w = src->width;
	int h = src->height;

	CvScalar **Sum = new CvScalar*[h];
	for (int i = 0;i < h;i++)
		Sum[i] = new CvScalar[w]; //CvScalar 2차원배열 동적할당


	for (int y = 0; y < h; y++){     
		for (int x = 0; x < w; x++) 
			Sum[y][x] = cvGet2D(src, y, x);
	}

	for (int y = 0; y < h; y++) {      // 가로줄의 BGR값을 더해준다.
		for (int x = 1; x < w; x++) {
			for (int step = 0; step < 3; step++) {
				Sum[y][x].val[step] = Sum[y][x].val[step] + Sum[y][x - 1].val[step];    //현재 BGR값 + 이전까지의 누적 BGR값    
			}
		}
	}

	for (int x = 0; x < w; x++){ //세로줄의 BGR값을 더해준다.
		for (int y = 1; y < h; y++) {
			for (int step = 0; step < 3; step++){
				Sum[y][x].val[step] = Sum[y][x].val[step] + Sum[y - 1][x].val[step];   // 현재 BGR값 + 이전까지의 누적 BGR값( 가로줄의 BGR값이 포함됨)
			}
		}
	} 

	CvScalar g;
	for (int y = K; y < h - K; y++) {
		for (int x = K; x < w - K; x++)
		{
			for (int i = 0; i < 3; i++) {
				g.val[i] =(Sum[y + K][x + K].val[i] - Sum[y + K][x - K].val[i] - Sum[y - K][x + K].val[i] + Sum[y - K][x - K].val[i]) * inv_sum;
			}
			cvSet2D(dst, y, x, g);
		}
	}
	for (int i = 0; i < h; i++) delete[] Sum[i];
	delete[] Sum;
	
} 

int main()
{
	cout << "=============================================" << endl;
	cout << "Software Department, Sejong University" << endl;
	cout << "Multimedia Programming Class" << endl;
	cout << "Homework: Fastest Mean Filte" << endl;
	cout << "=============================================" << endl<<endl;

	IplImage* src = nullptr;
	int KernelSize;
	char str[MAX_LEN];

	printf("Input File Path:");
	gets_s(str, MAX_LEN);
	src = cvLoadImage(str);
	if (str == nullptr) {
		printf("File Not Found!");
		exit(-1);
	}
	IplImage *dst = cvCreateImage(cvGetSize(src), 8, 3);
	cout << "Input Kernel Size:";
	cin >> KernelSize;
	MyFastestMeanFilter(src, dst, KernelSize);
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
}
