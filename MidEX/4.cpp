#include <opencv2/opencv.hpp>
#include <math.h>
int main() {
	IplImage *src = cvLoadImage("C:\\temp\\sejong.jpg");
	IplImage *dst = cvCreateImage(cvGetSize(src), 8, 3);
	cvSet(dst, cvScalar(255, 255, 255));
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	
	int offset = 16;
    int x_step = w / 16;

    // ������ ������ ���ļ� ����
    float amplitude = h / 4; // ������ ����
    float nx = 0;
    float ny = 0;
    float newY = 0;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (x != 0 && x % x_step == 0) {
                nx = (float)x / (w - 1) * CV_PI * 2;
            }
            ny = (float)y / (h - 1) ;
            newY = y + amplitude * sin(nx);

            if (newY > h) newY = h - 1;
            if (newY < 0) newY = 0;

            // ���ο� ��ġ�� �ȼ� ������ ������
            CvScalar color = cvGet2D(src, y, x);

            // ���� ��ġ�� ���� ����
            cvSet2D(dst, newY, x, color);
        }
    }

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
}