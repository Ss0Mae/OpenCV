#include <opencv2/opencv.hpp>

int main() {
	IplImage *src = cvLoadImage("C:\\temp\\sejong.jpg");
	IplImage *dst = cvCreateImage(cvGetSize(src), 8, 3);
	CvSize size = cvGetSize(src);

    int w = size.width;
    int h = size.height;
    int patternWidth = w / 8; // 패턴의 가로 크기
    int patternHeight = h / 6; // 패턴의 세로 크기

    // 패턴 반복 간격 설정
    int stepX = w / 8;
    int stepY = h / 6;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            // 패턴의 중심 좌표 계산
            int patternX = x % stepX;
            int patternY = y % stepY;

            // 마름모 모양 내부 조건
            if ((abs(patternX - patternWidth / 2) + abs(patternY - patternHeight / 2)) <= (patternWidth / 2) &&
                (abs(patternX - patternWidth / 2) + abs(patternY - patternHeight / 2)) <= (patternHeight / 2)) {
                // 패턴 내부인 경우 원본 이미지의 색상 사용
                CvScalar color = cvGet2D(src, y, x);
                cvSet2D(dst, y, x, color);
            }

            else {
                float nx = 2 * (float)x / (w - 1) - 1;
                float ny = 2 * (float)y / (h - 1) - 1;
                float dist = sqrt(nx * nx + ny * ny);
                // 거리에 따라 그레이스케일 값 조절
                int grayValue = (1.0 - dist) * 255; // 거리가 0에 가까울수록 밝아짐
                grayValue = 255 - grayValue;
                CvScalar color = cvScalar(grayValue, grayValue, grayValue);
                cvSet2D(dst, y, x, color);
            }
        }
    }
   

	cvShowImage("dst", dst);
	cvWaitKey();
}
