#include <opencv2/opencv.hpp>

int main() {
	IplImage* src = cvLoadImage("C:\\temp\\sejong.jpg");
	IplImage* dst = cvCreateImage(cvGetSize(src), 8, 3);
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;

	for (int y = 0; y < h / 2; y++) {
		for (int x = 0; x < w / 2; x++) {
			CvScalar c1 = cvGet2D(src, y, x);
			CvScalar temp1 = cvGet2D(src, (h / 2) + y - 1, (w / 2) + x - 1);
			cvSet2D(dst, y, x, temp1);
			cvSet2D(dst, h / 2 + y - 1, (w / 2) + x - 1, c1);
		}
	}

	for (int y = h / 2; y < h; y++) {
		for (int x = 0; x < w / 2; x++) {
			CvScalar c1 = cvGet2D(src, y, x);
			CvScalar temp1 = cvGet2D(src, y - h / 2, (w / 2) + x - 1);
			cvSet2D(dst, y, x, temp1);
			cvSet2D(dst, y - h / 2, (w / 2) + x - 1, c1);
		}
	}
	/*for (int y = 0; y < h / 2; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			CvScalar temp = cvGet2D(src, h - 1 - y, x);
			cvSet2D(dst, h - 1 - y, x, c);
			cvSet2D(dst, y, x, temp);
		}
	}*/

	cvShowImage("src", src);
	cvShowImage("dst", dst);	
	cvWaitKey();
}