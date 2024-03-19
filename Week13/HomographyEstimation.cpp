#include <opencv2/opencv.hpp>
#include "MatrixInverse.h"

IplImage* src;
IplImage* dst;

CvPoint In[4] = { cvPoint(175,277), cvPoint(479,499), cvPoint(700,370),  cvPoint(395,172) };
//CvPoint Out[4] = { cvPoint(175,277), cvPoint(479,499), cvPoint(700,370),  cvPoint(395,172) };
CvPoint Out[4] = { cvPoint(100,100), cvPoint(100,400), cvPoint(400,400), cvPoint(400,100) };

void drawPoints(IplImage* img, CvPoint pts[], int num, CvScalar c)
{
	for (int i = 0; i < num; i++)
		cvCircle(img, pts[i], 5, c, -1);
}

void transformImage(float M[][3], IplImage* s, IplImage* d)
{
	for (float y1 = 0; y1 < s->height; y1++)
		for (float x1 = 0; x1 < s->width; x1++)
		{
			float w1 = 1;
			float x2 = M[0][0] * x1 + M[0][1] * y1 + M[0][2] * w1;
			float y2 = M[1][0] * x1 + M[1][1] * y1 + M[1][2] * w1;
			float w2 = M[2][0] * x1 + M[2][1] * y1 + M[2][2] * w1;
			x2 /= w2;
			y2 /= w2;

			if (x2<0 || x2>d->width - 1) continue;
			if (y2<0 || y2>d->height - 1) continue;

			CvScalar c = cvGet2D(s, y1, x1);
			cvSet2D(d, y2, x2, c);
		}
}

void inverseTransformImage(float M[][3], IplImage* s, IplImage* d)
{
	cvSet(d, cvScalar(0, 0, 0));

	for (float y2 = 0; y2 < d->height; y2++)
		for (float x2 = 0; x2 < d->width; x2++)
		{
			float w2 = 1;
			float x1 = M[0][0] * x2 + M[0][1] * y2 + M[0][2] * w2;
			float y1 = M[1][0] * x2 + M[1][1] * y2 + M[1][2] * w2;
			float w1 = M[2][0] * x2 + M[2][1] * y2 + M[2][2] * w2;
			x1 /= w1;
			y1 /= w1;

			if (x1<0 || x1>s->width - 1) continue;
			if (y1<0 || y1>s->height - 1) continue;

			CvScalar c = cvGet2D(s, y1, x1);
			cvSet2D(d, y2, x2, c);
		}
}


void computeMatrix(float M[][3], CvPoint In[], CvPoint Out[])
{
	float A[8][8], h[8], B[8];
	for (int i = 0; i < 4; i++)
	{
		float x1 = In[i].x;
		float y1 = In[i].y;
		float x2 = Out[i].x;
		float y2 = Out[i].y;
		A[2 * i][0] = -x1;
		A[2 * i][1] = -y1;
		A[2 * i][2] = -1;
		A[2 * i][3] = 0;
		A[2 * i][4] = 0;
		A[2 * i][5] = 0;
		A[2 * i][6] = x2 * x1;
		A[2 * i][7] = x2 * y1;

		A[2 * i + 1][0] = 0;
		A[2 * i + 1][1] = 0;
		A[2 * i + 1][2] = 0;
		A[2 * i + 1][3] = -x1;
		A[2 * i + 1][4] = -y1;
		A[2 * i + 1][5] = -1;
		A[2 * i + 1][6] = y2 * x1;
		A[2 * i + 1][7] = y2 * y1;

		B[2 * i] = -x2;
		B[2 * i + 1] = -y2;
	}

	// h = InvA B
	float InvA[8][8];
	InverseMatrixGJ(A, InvA, 8);

	for (int i = 0; i < 8; i++)
	{
		h[i] = 0.0f;
		for (int j = 0; j < 8; j++)
			h[i] += InvA[i][j] * B[j];
	}

	M[0][0] = h[0]; M[0][1] = h[1]; M[0][2] = h[2];
	M[1][0] = h[3]; M[1][1] = h[4]; M[1][2] = h[5];
	M[2][0] = h[6]; M[2][1] = h[7]; M[2][2] = 1;
}

int main()
{
	src = cvLoadImage("c:\\Temp\\book.jpg");
	dst = cvCreateImage(cvSize(500, 500), 8, 3);

	float M[3][3];
	/*computeMatrix(M, In, Out);
	transformImage(M, src, dst);*/

	computeMatrix(M, Out, In);
	inverseTransformImage(M, src, dst);

	drawPoints(src, In, 4, cvScalar(255, 0, 0));
	drawPoints(dst, Out, 4, cvScalar(0, 0, 255));

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();


	return 0;
}
