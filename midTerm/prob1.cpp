#include <opencv2/opencv.hpp>
int main()
{
	IplImage *src = cvLoadImage("sejong.jpg");
	CvSize size = cvGetSize(src);
	for(int y=0;y<size.height/2;y++)
		for (int x = 0;x < size.width / 2;x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g = cvGet2D(src, y + size.height / 2, x + size.width / 2);
			cvSet2D(src, y + size.height / 2, x + size.width / 2, f);
			cvSet2D(src, y, x, g);
		}
	for (int y = 0;y < size.height / 2;y++)
		for (int x = size.width/2; x < size.width;x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g = cvGet2D(src, y + size.height / 2, x-size.width/2);
			cvSet2D(src, y + size.height / 2, x - size.width / 2, f);
			cvSet2D(src, y, x, g);
		}
	cvShowImage("src", src);
	cvWaitKey();
}