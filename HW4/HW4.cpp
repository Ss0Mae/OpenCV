#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

#define MAX_LEN 50
#define MAX_STROKES 10000
int mode = 1;
IplImage* src;
IplImage* dst;
int brush[5] = { 30,20, 15, 10, 5};

struct stroke {
	int x, y;
	CvScalar color;
};

void readPicture() { //IO 작업을 하는 함수
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

CvPoint calculateGradient(const IplImage* img, int x, int y) {
	float gx = 0.0f, gy = 0.0f;
	if (x > 0 && x < img->width - 1 && y > 0 && y < img->height - 1) {
		CvScalar right = cvGet2D(img, y, x + 1);
		CvScalar left = cvGet2D(img, y, x - 1);
		CvScalar down = cvGet2D(img, y + 1, x);
		CvScalar up = cvGet2D(img, y - 1, x);

		gx = (right.val[0] - left.val[0]) / 2.0;
		gy = (down.val[0] - up.val[0]) / 2.0;
	}
	return cvPoint(gx, gy);
}
void makeSplineStroke(IplImage* dst, int x0, int y0, int brushSize, const IplImage* refImage) {
	CvScalar strokeColor = cvGet2D(refImage, y0, x0);
	int maxStrokeLength = 50; // 스트로크의 최대 길이
	int minStrokeLength = 10; // 최소 길이

	float dx = 0, dy = 0, lastDx = 0, lastDy = 0;
	CvPoint currentPoint = cvPoint(x0, y0);

	for (int i = 0; i < maxStrokeLength; i++) {
		if (i > minStrokeLength) {
			if (calculateColorDifference(cvGet2D(dst, currentPoint.y, currentPoint.x), strokeColor) < 10.0) {
				break; // 색상 차이가 충분히 작으면 중단
			}
		}

		CvPoint grad = calculateGradient(refImage, currentPoint.x, currentPoint.y);
		if (sqrt(grad.x * grad.x + grad.y * grad.y) == 0) break; // 그라디언트가 0이면 중단

		// 단위 벡터 계산
		float mag = sqrt(grad.x * grad.x + grad.y * grad.y);
		float unitX = grad.x / mag;
		float unitY = grad.y / mag;

		// 그라디언트의 수직 방향 계산
		dx = -unitY;
		dy = unitX;

		// 방향 전환 필요성 검사
		if (lastDx * dx + lastDy * dy < 0) {
			dx = -dx;
			dy = -dy;
		}

		// 이전 방향과 새 방향의 가중치를 혼합
		float weight = 0.1; // 방향성 스무딩에 사용될 가중치
		dx = weight * dx + (1 - weight) * lastDx;
		dy = weight * dy + (1 - weight) * lastDy;

		// 단위 길이로 정규화
		mag = sqrt(dx * dx + dy * dy);
		dx /= mag;
		dy /= mag;

		// 다음 점 계산
		int nextX = round(currentPoint.x + dx * brushSize);
		int nextY = round(currentPoint.y + dy * brushSize);

		// 경계 검사
		if (nextX < 0 || nextY < 0 || nextX >= dst->width || nextY >= dst->height) break;

		// 라인 그리기
		cvLine(dst, currentPoint, cvPoint(nextX, nextY), strokeColor, brushSize);

		// 다음 위치 업데이트
		currentPoint = cvPoint(nextX, nextY);
		lastDx = dx;
		lastDy = dy;
	}
}
void paintLayer(IplImage* dst, IplImage *src, int brushSize) {
	int grid = brushSize;
	int kernel = brushSize / 2;
	int strokeCount = 0;

	if (kernel % 2 == 0) kernel = kernel + 1;
	//if (kernel == 1) kernel = 3;
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
		else if (mode == 1) {
			makeSplineStroke(dst, strokes[i].x, strokes[i].y, brushSize, Ref);
		}
	}

}

void paint() {
	for (int i = 0; i < 5; i++) {
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
	cvSet(dst, cvScalar(255, 255, 255));

	cvShowImage("src", src);
	cvShowImage("canvas", dst);
	cvWaitKey(1000);

	paint();
	cvWaitKey();

}
