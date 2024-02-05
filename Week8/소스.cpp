#include <opencv2\opencv.hpp>
int main()
{
	IplImage *src = cvLoadImage("C:\\Temp\\Lena.jpg");
	CvSize size = cvGetSize(src);
	int cycle = size.height / 16;
}