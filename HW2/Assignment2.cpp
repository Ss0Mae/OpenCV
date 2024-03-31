#include <opencv2/opencv.hpp>
#include <stdio.h>
#define MAX_LEN 50

// 그림의 경로를 입력받는 함수

IplImage* readPicture() {
	char str[MAX_LEN];
	IplImage* src;

	printf("Input File Name:");
	gets_s(str, MAX_LEN);
	src = cvLoadImage(str);

	while (src == nullptr) {
		printf("File Not Found!\n");
		printf("Input File Name:");
		gets_s(str, MAX_LEN);
		src = cvLoadImage(str);
	}
	return src;
}

void dividePicture(IplImage* src, IplImage* dst[], int w, int h) {
	for (int i = 0; i < 3; i++) { //입력받는 그림을 3등분 하여 각각의 배열에 저장
		dst[i] = cvCreateImage(cvSize(w, h), 8, 3);
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				CvScalar c = cvGet2D(src, y + i * h, x);
				cvSet2D(dst[i], y, x, c);
			}
		}
	}
}

IplImage* colorPrint(IplImage* src, IplImage* dst[],int w, int h) {
	IplImage* out = cvCreateImage(cvSize(w, h), 8, 3);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c1 = cvGet2D(dst[0], y, x);
			CvScalar c2 = cvGet2D(dst[1], y, x);
			CvScalar c3 = cvGet2D(dst[2], y, x);
			CvScalar c = cvScalar(c1.val[0], c2.val[1], c3.val[2]);
			cvSet2D(out, y, x, c);
		}
	}
	return out;
}

float getDiff2(CvScalar a, CvScalar b) {
	return (a.val[0] - b.val[0]) * (a.val[0] - b.val[0]) + (a.val[1] - b.val[1]) * (a.val[1] - b.val[1]) + (a.val[2] - b.val[2]) * (a.val[2] - b.val[2]);
}

void templateMatching(IplImage* src, IplImage* dst, int w, int h) {
	int min = 1000000000;
	int min_x = 0;
	int min_y = 0;
	for (int y = 0; y < src->height - h; y++) {
		for (int x = 0; x < src->width - w; x++) {
			int sum = 0;
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					CvScalar c1 = cvGet2D(src, y + i, x + j);
					CvScalar c2 = cvGet2D(dst, i, j);
					sum += getDiff2(c1, c2);
				}
			}
			if (sum < min) {
				min = sum;
				min_x = x;
				min_y = y;
			}
		}
	}
	printf("x:%d y:%d\n", min_x, min_y);
}
int main() {
	IplImage* src;
	IplImage* dst[3];
	IplImage * out;

	src = readPicture();
	int w = src->width;
	int h = src->height / 3;

	dividePicture(src, dst, w, h);
	out = colorPrint(src, dst, w, h);
	cvShowImage("src", src);
	cvShowImage("dst1", dst[0]);
	cvShowImage("dst2", dst[1]);
	cvShowImage("dst3", dst[2]);
	cvShowImage("out", out);
	templateMatching(src, dst[0], w, h);
	templateMatching(src, dst[1], w, h);
	templateMatching(src, dst[2], w, h);
	cvWaitKey();
}