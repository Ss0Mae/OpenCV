#include <opencv2/opencv.hpp>
int main()
{
	IplImage* src[2];
	src[0] = cvLoadImage("C:\\Temp\\cross1.jpg");
	src[1] = cvLoadImage("C:\\Temp\\cross2.jpg");

	CvSize size = cvGetSize(src[0]);
	IplImage* dst = cvCreateImage(size, 8, 3);

	float alpha = 0.5f;
	for (alpha = 0.0f; alpha <= 1.0f; alpha += 0.1)
	{
		for (int y = 0; y < size.height; y++)
			for (int x = 0; x < size.width; x++)
			{
				CvScalar f1 = cvGet2D(src[0], y, x);
				CvScalar f2 = cvGet2D(src[1], y, x);
				CvScalar g;
				for (int k = 0; k < 3; k++)
					g.val[k] = (1 - alpha) * f1.val[k] + alpha * f2.val[k];
				cvSet2D(dst, y, x, g);
			}
		//	cvShowImage("src1", src[0]);
		//	cvShowImage("src2", src[1]);
		cvShowImage("dst", dst);
		cvWaitKey();
	}



}