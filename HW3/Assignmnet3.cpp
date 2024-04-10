#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
using namespace std;
#define MAX_LEN 50

// 그림의 경로를 입력받는 함수
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
		image = cvLoadImage(imagePath); //파일이 없을 경우 다시 입력받음
	}
	return image;
}

void myFastestMeanFilter(IplImage* src, IplImage* dst, int K) {

	float inv = 1.0f / ((2 * K + 1) * (2 * K + 1)); // 빠른 계산을 위한 역수 먼저 계산
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;

	CvScalar** SAT = new CvScalar * [h];
	for (int i = 0; i < h; i++) SAT[i] = new CvScalar[w]; // SAT 배열 동적할당

	// Summed Area Table 구현
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			SAT[y][x] = cvGet2D(src, y, x); // 모든 점의 밝기값 저장
		}
	}
	for (int y = 0; y < h; y++) {
		for (int x = 1; x < w; x++) {
			for(int i = 0; i<3;i++)
				SAT[y][x].val[i] += SAT[y][x - 1].val[i]; // x축으로 누적
		}
	}
	for (int x = 0; x < w; x++) {
		for (int y = 1; y < h; y++) {
			for(int i =0 ; i<3;i++)
				SAT[y][x].val[i] += SAT[y - 1][x].val[i]; // y축으로 누적
		}
	}
	/* Summed Area Table 구현 완료*/

	// Mean Filter 구현
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int startY = max(y - K, 0);
			int startX = max(x - K, 0);
			int endY = min(y + K, h - 1);
			int endX = min(x + K, w - 1);

			// sum 계산
			CvScalar sum;
			 
			// 오른쪽 아래 커널의 오른쪽 아래 구석에 해당하는 SAT 값입니다.
			CvScalar endValue = SAT[endY][endX];

			// 위를 뺌 : 커널의 시작 y 위치 바로 위에 해당하는 SAT 값입니다. 커널이 이미지 상단 경계를 벗어나지 않는 경우에만 빼줍니다.
			CvScalar startValueY = startY > 0 ? SAT[startY - 1][endX] : cvScalar(0, 0, 0);

			// 왼쪽을 뺌  커널의 시작 x 위치 바로 왼쪽에 해당하는 SAT 값입니다. 커널이 이미지 왼쪽 경계를 벗어나지 않는 경우에만 빼줍니다.
			CvScalar startValueX = startX > 0 ? SAT[endY][startX - 1] : cvScalar(0, 0, 0);

			// 왼쪽 위 겹치는 부분 더함 overlap: 커널이 이미지 경계를 벗어나지 않는 경우에 빼준 startValueY와 startValueX에 의해 중복해서 뺀 영역을 다시 더해주기 위한 SAT 값입니다.
			CvScalar overlap = (startY > 0 && startX > 0) ? SAT[startY - 1][startX - 1] : cvScalar(0, 0, 0);

			// 각 채널에 대한 연산 수행
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
	delete[] SAT; // 동적할당 해제
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

	//for (int step = 0;step < 3;step++) { // 가로한줄
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
	//for (int step = 0;step < 3;step++){ //세로한줄
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

	//for (int step = 0;step < 3;step++){ //나머지
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

