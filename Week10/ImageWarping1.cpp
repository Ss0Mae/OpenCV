#include <opencv2/opencv.hpp>

int main()
{
	IplImage *src = cvLoadImage("C:\\Temp\\lena.png");
	IplImage *dst = cvCreateImage(cvSize(800, 800), 8, 3);

	//for(int x=0;x<src->width;x++)
	//	for (int y = 0;y < src->height;y++)
	//	{
	//		CvScalar f = cvGet2D(src, y, x);
	//		CvScalar g = f;
	//	} //img proc 기본틀
	 
	// [a  b]
	// [c  d]

	float sx = 1.0f;        //scale parameter
	float sy = 1.5f;
	//for(int y1=0;y1<src->height;y1++)
	//	for (int x1 = 0;x1 < src->width;x1++)
	//	{
	//		CvScalar c = cvGet2D(src, y1, x1);

	//		float x2 = sx * x1 + 0 * y1;
	//		float y2 = sy * y1 + 0 * y1;
	//		//if(x2>=0 &&x2<dst->width&&y2>=0&&y2<dst->height)
	//		if (x2<0 || x2>dst->width - 1) continue;
	//		if (y2<0 || y2>dst->height - 1) continue;
	//		cvSet2D(dst, y2, x2, c); // 기본틀
	//	}

	// inverse transform
	for (int y2 = 0;y2 < dst->height;y2++)
		for (int x2 = 0;x2 < dst->width;x2++) 
		{
			float x1 = 1 / sx * x2 + 0 * y2;
			float y1 = 0 * x2 + 1 / sy * y2;

			if (x1<0 || x1>src->width - 1) continue;
			if (y1<0 || y1>src->height - 1) continue;

			CvScalar c = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c);
		}
	cvShowImage("src", src);  
	cvShowImage("dst", dst);
	cvWaitKey();
}