#include <opencv2/opencv.hpp>

CvScalar myGet2D(IplImage* img, float y, float x)
{
	// x = i +a;
	// y = j + b;
	int i1 = (int)x;
	float a = x - i1;
	int j1 = (int)y;
	float b = y - j1;

	int i2 = i1 + 1; if (i2 > img->width - 1) i2 = i1;
	int j2 = j1 + 1; if(j2 > img->height - 1) j2 = j1;

	CvScalar c1 = cvGet2D(img, j1, i1);
	CvScalar c2 = cvGet2D(img, j1, i2);
	CvScalar c3 = cvGet2D(img, j2, i1);
	CvScalar c4 = cvGet2D(img, j2, i2);

	float w1 = (1 - a) * (1 - b);
	float w2 = a * (1 - b);
	float w3 = (1 - a) * b;
	float w4 = a * b;

	CvScalar c;
	for (int k = 0; k < 3; k++)
		c.val[k] = w1 * c1.val[k] + w2 * c2.val[k] + w3 * c3.val[k] + w4 * c4.val[k];
	return c;
}
int main()
{
	IplImage* src = cvLoadImage("C:\\Temp\\lena.png");
	IplImage* dst = cvCreateImage(cvSize(800, 800), 8, 3);

	float cx = src->width / 2;
	float cy = src->height / 2;
	float sx = 10.0f;
	float sy = 10.0f;
	 
	for (int y2 = 0; y2 < dst->height; y2++)
		for (int x2 = 0; x2 < dst->width; x2++)
		{
			float x1 = (x2 - cx) / sx + cx;
			float y1 = (y2 - cy) / sy + cy;

			if (x1<0 || x1>src->width - 1) continue;
			if (y1<0 || y1>src->height - 1) continue;

			//CvScalar c = cvGet2D(src, y1, x1); Àü 
			CvScalar c = myGet2D(src, y1, x1); // ÈÄ
			cvSet2D(dst, y2, x2, c);

		}
	cvShowImage("src", src);
	cvShowImage("dst", dst );
	cvWaitKey();
}