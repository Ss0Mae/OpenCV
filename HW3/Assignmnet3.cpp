#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
using namespace std;
#define MAX_LEN 50

// �׸��� ��θ� �Է¹޴� �Լ�
IplImage* readPicture() {
	char imagePath[MAX_LEN];
	IplImage* image;
	printf("=============================================\n");
	printf("Software Department, Sejong University\n");
	printf("Multimedia Programming Class\n");
	printf("Homework: Fastest Mean Filter\n");
	printf("=============================================\n\n");
	printf("Input File Name:");
	gets_s(imagePath, MAX_LEN);
	image = cvLoadImage(imagePath);

	while (image == nullptr) {
		printf("File Not Found!\n");
		printf("Input File Name:");
		gets_s(imagePath, MAX_LEN);
		image = cvLoadImage(imagePath); //������ ���� ��� �ٽ� �Է¹���
	}
	return image;
}

void myFastestMeanFilter(IplImage* src, IplImage* dst, int K) {

	float inv = 1.0f / ((2 * K + 1) * (2 * K + 1)); // ���� ����� ���� ���� ���� ���
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;

	CvScalar** SAT = new CvScalar * [h];
	for (int i = 0; i < h; i++) SAT[i] = new CvScalar[w]; // SAT �迭 �����Ҵ�

	// Summed Area Table ����
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			SAT[y][x] = cvGet2D(src, y, x); // ��� ���� ��Ⱚ ����
		}
	}
	for (int y = 0; y < h; y++) {
		for (int x = 1; x < w; x++) {
			for(int i = 0; i<3;i++)
				SAT[y][x].val[i] += SAT[y][x - 1].val[i]; // x������ ����
		}
	}
	for (int x = 0; x < w; x++) {
		for (int y = 1; y < h; y++) {
			for(int i =0 ; i<3;i++)
				SAT[y][x].val[i] += SAT[y - 1][x].val[i]; // y������ ����
		}
	}
	/* Summed Area Table ���� �Ϸ�*/

	// Mean Filter ����
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int startY = max(y - K, 0);
			int startX = max(x - K, 0);
			int endY = min(y + K, h - 1);
			int endX = min(x + K, w - 1);

			// sum ���
			CvScalar sum;
			 
			// ������ �Ʒ� Ŀ���� ������ �Ʒ� ������ �ش��ϴ� SAT ���Դϴ�.
			CvScalar endValue = SAT[endY][endX];

			// ���� �� : Ŀ���� ���� y ��ġ �ٷ� ���� �ش��ϴ� SAT ���Դϴ�. Ŀ���� �̹��� ��� ��踦 ����� �ʴ� ��쿡�� ���ݴϴ�.
			CvScalar startValueY = startY > 0 ? SAT[startY - 1][endX] : cvScalar(0, 0, 0);

			// ������ ��  Ŀ���� ���� x ��ġ �ٷ� ���ʿ� �ش��ϴ� SAT ���Դϴ�. Ŀ���� �̹��� ���� ��踦 ����� �ʴ� ��쿡�� ���ݴϴ�.
			CvScalar startValueX = startX > 0 ? SAT[endY][startX - 1] : cvScalar(0, 0, 0);

			// ���� �� ��ġ�� �κ� ���� overlap: Ŀ���� �̹��� ��踦 ����� �ʴ� ��쿡 ���� startValueY�� startValueX�� ���� �ߺ��ؼ� �� ������ �ٽ� �����ֱ� ���� SAT ���Դϴ�.
			CvScalar overlap = (startY > 0 && startX > 0) ? SAT[startY - 1][startX - 1] : cvScalar(0, 0, 0);

			// �� ä�ο� ���� ���� ����
			for (int i = 0; i < 3; i++) {
				sum.val[i] = endValue.val[i] - startValueY.val[i] - startValueX.val[i] + overlap.val[i];
			}

			float area = (endY - startY + 1) * (endX - startX + 1);
			CvScalar mean;
			for (int i = 0; i < 3; ++i) {
				mean.val[i] = sum.val[i] / area;
			}
			cvSet2D(dst, y, x, mean);
		}
	}
	/*for (int y = K; y < h - K; y++) {
		for (int x = K; x < w - K; x++)
		{
			CvScalar g;
			for (int i = 0; i < 3; i++) {
				float sum = SAT[y + K][x + K].val[i]
					- SAT[y + K][x - K].val[i]
					- SAT[y - K][x + K].val[i]
					+ SAT[y - K][x - K].val[i];
				g.val[i] = sum * inv;
			}
			cvSet2D(dst, y, x, g);
		}
	}*/

	for(int i = 0; i<h;i++) delete[] SAT[i];
	delete[] SAT; // �����Ҵ� ����
}
int main() {
	
	IplImage* src;
	int KernelSize;
	src = readPicture();
	IplImage* dst = cvCreateImage(cvGetSize(src), 8, 3);

	printf("Input Kernel Size:");
	scanf("%d", &KernelSize);
	myFastestMeanFilter(src, dst, KernelSize);
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}

/*
/*for (int y = 0; y < K; y++) {
		for (int x = 0; x < w; x++) {
			cvSet2D(dst, y, x, cvGet2D(src, y, x));
			cvSet2D(dst, h - 1 - y, x, cvGet2D(src, h - 1 - y, x));
		}
	}
	for (int y = K; y < h - K; y++) {
		for (int x = 0; x < K; x++) {
			cvSet2D(dst, y, x, cvGet2D(src, y, x));
			cvSet2D(dst, y, w - 1 - x, cvGet2D(src, y, w - 1 - x));
		}
	}*/

	//for (int step = 0;step < 3;step++) {
	//	for (int y = 0;y < h;y++)
	//		for (int x = 0;x < w;x++)
	//			SAT[y][x] = cvScalar(0, 0, 0);
	//}
	//CvScalar std;
	//SAT[0][0] = cvGet2D(src, 0, 0);
	//std = SAT[0][0];

	//for (int step = 0;step < 3;step++) { // ��������
	//	int y = 0;
	//	CvScalar g = cvGet2D(src, 0, 1);
	//	SAT[0][1].val[step] = g.val[step] + std.val[step];
	//	std.val[step] += g.val[step];
	//	for (int x = 2;x < w;x++) {
	//		CvScalar f = cvGet2D(src, 0, x);
	//		SAT[y][x].val[step] = f.val[step] + std.val[step];
	//		std.val[step] += SAT[y][x - 1].val[step];
	//	}
	//}
	//
	//for (int step = 0;step < 3;step++){ //��������
	//	int x = 0;
	//	CvScalar g = cvGet2D(src, 1, 0);
	//	SAT[0][1].val[step] = g.val[step] + std.val[step];
	//	std.val[step] += g.val[step];
	//	for (int y = 2;y < h;y++) {
	//		CvScalar f = cvGet2D(src, y, 0);
	//		SAT[y][x].val[step] = f.val[step] + std.val[step];
	//		std.val[step] += SAT[y - 1][x].val[step];
	//	}
	//}

	//for (int step = 0;step < 3;step++){ //������
	//	for(int y=1;y<h;y++)
	//		for (int x = 1;x < w;x++)
	//		{
	//			CvScalar f = cvGet2D(src, y, x);
	//			SAT[y][x].val[step] = SAT[y][x - 1].val[step] + SAT[y - 1][x].val[step] - SAT[y - 1][x - 1].val[step] + f.val[step];
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
	//			g.val[k] *= inv;
	//		cvSet2D(dst, y, x, g);
	//	}

