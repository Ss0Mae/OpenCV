#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

#define MAX_LEN 50
#define MAX_STROKES 10000
int mode = 0;
IplImage* src;
IplImage* dst;
int brush[6] = { 30,20, 15, 10, 5, 3};

struct stroke {
	int x, y;
	CvScalar color;
};



void readPicture() {
	char imagePath[MAX_LEN];
	cout << "=============================================" << endl;
	cout << "Department of Software, Sejong University" << endl;
	cout << "Multimedia Programming Homework #4" << endl;
	cout << "Painterly Rendering" << endl;
	cout << "=============================================" << endl;
	cout << "Input File Path:";
	gets_s(imagePath, MAX_LEN);
	src = cvLoadImage(imagePath);

	while (src == nullptr) {
		printf("File Not Found!\n");
		printf("Input File Name:");
		gets_s(imagePath, MAX_LEN);
		src = cvLoadImage(imagePath);
	}
	printf("Select Drawing Mode(0 = circle, 1 = stroke) : ");
	while (true) {
		if (scanf("%d", &mode) == 1 && (mode == 0 || mode == 1)) {
			break;
		}
		else {
			while (getchar() != '\n');
			printf("Wrong Drawing Mode!\n");
			printf("Select Drawing Mode(0 = circle, 1 = stroke) : ");
		}
	}
}

float calculateColorDifference(CvScalar c1, CvScalar c2) { //색상의 차이를 구하는 함수
	float diff = 0.0f;
	for (int i = 0; i < 3; i++) {
		diff += (c1.val[i] - c2.val[i]) * (c1.val[i] - c2.val[i]);
	}
	return diff;
}

void paintLayer(IplImage* dst, IplImage *src, int brushSize) {
	int grid = brushSize;
	int kernel = brushSize / 2;
	int strokeCount = 0;

	if (kernel % 2 == 0) kernel = kernel + 1;
	if (kernel == 1) kernel = 3;
	IplImage *Ref = cvCreateImage(cvGetSize(src), 8, 3);
	cvSmooth(src, Ref, CV_GAUSSIAN, 0, 0, kernel);
	stroke strokes[MAX_STROKES];
	stroke bestStroke;

	for (int y = 0; y < src-> height; y += grid) {
		for (int x = 0; x < src-> width; x +=grid) {
			float error = 0.0f;
			float maxError = 0.0f;

			for(int dy = y - grid / 2; dy <= y + grid/2; dy++){
				for (int dx = x - grid / 2; dx <= x + grid / 2; dx++) {
					if (dx >= 0 && dy >= 0 && dx < src->width && dy < src->height) {
						CvScalar c1 = cvGet2D(Ref, dy, dx);
						CvScalar c2 = cvGet2D(src, dy, dx);
						error = calculateColorDifference(c1, c2);
					}
					if (error > maxError && strokeCount < MAX_STROKES) {
						maxError = error;
						bestStroke.x = dx;
						bestStroke.y = dy;
						bestStroke.color = cvGet2D(Ref, dy, dx);
					}
				}
			}

			if (maxError > 0 && strokeCount < MAX_STROKES) {
				strokes[strokeCount++] = bestStroke;
			}

		}
	}

	// 배열을 무작위로 섞기
	srand(time(NULL));
	for (int i = 0; i < strokeCount - 1; i++) {
		int r = rand() % (strokeCount - i) + i;
		stroke temp = strokes[i];
		strokes[i] = strokes[r];
		strokes[r] = temp;
	}

	// 스트로크 그리기
	for (int i = 0; i < strokeCount; i++) {
		if (mode == 0) { // 원형 스트로크
			cvCircle(dst, cvPoint(strokes[i].x, strokes[i].y), brushSize, strokes[i].color, -1);
		}
	}

}

void paint() {
	for (int i = 0; i < 6; i++) {
		paintLayer(dst, src, brush[i]);
		cvShowImage("canvas", dst);
		cvWaitKey(1000);
	}

}

void makeSplineStroke(IplImage* dst, int brushSize) {

}
int main() {
	readPicture();
	dst = cvCreateImage(cvGetSize(src), 8, 3);
	//cvCopy(src, Ref);
	cvSet(dst, cvScalar(255, 255, 255));
	cvShowImage("src", src);
	cvShowImage("canvas", dst);
	cvWaitKey(1000);
	if(mode == 0) paint();

	cvWaitKey();

}
