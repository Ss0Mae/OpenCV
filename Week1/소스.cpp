#include <opencv2/opencv.hpp>
int main() {
	IplImage *image;
	image = cvLoadImage("c:\\Temp\\sample.jpg");
	cvShowImage("Hello, OpenCV", image);

	cvWaitKey();
	return 0;
}