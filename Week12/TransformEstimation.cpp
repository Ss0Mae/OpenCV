#include <opencv2/opencv.hpp>
#include "MatrixInverse.h"
IplImage* src;
IplImage* dst;

CvPoint In[3] = { cvPoint(250,100),cvPoint(100,350),cvPoint(400,350) };
//CvPoint Out[3] = { cvPoint(150,100),cvPoint(140,450),cvPoint(400,300) };
CvPoint Out[3] = { cvPoint(250,100),cvPoint(100,350),cvPoint(400,350) };
int selectedIdx = -1;

void drawPoints(IplImage* img,CvPoint pts[],int num,CvScalar c)
{
	for (int i = 0; i < 3; i++)
		cvCircle(img, pts[i], 5, c,-1);

	if(selectedIdx>=0)
		cvCircle(img, pts[selectedIdx], 8, c, -1);
}

void computeMatrixMultiply(float M[][3], float A[][3], float B[][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			M[i][j] = 0.0f;
			for (int k = 0; k < 3; k++)
				M[i][j] += A[i][k] * B[k][j];
		}
}

void ComputeMatrix(float M[][3], CvPoint In[], CvPoint Out[])
{
	// B = M A
	// B InvA = M
	float A[3][3], B[3][3];

	for (int i = 0; i < 3; i++)
	{
		A[0][i] = In[i].x;
		A[1][i] = In[i].y;
		A[2][i] = 1;

		B[0][i] = Out[i].x;
		B[1][i] = Out[i].y;
		B[2][i] = 1;
	}

	float InvA[3][3];
	InverseMatrixGJ(A, InvA, 3);
	computeMatrixMultiply(M, B, InvA);


}

void TransformImage(float M[][3], IplImage* s, IplImage* d)
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

void InverseTransformImage(float M[][3], IplImage* s, IplImage* d)
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

int findSelected(CvPoint pts[], int num, CvPoint in)
{
	for (int i = 0; i < 3; i++)
	{
		float dist = sqrt((pts[i].x - in.x) * (pts[i].x - in.x) + (pts[i].y - in.y) * (pts[i].y - in.y));
		if (dist < 5)
			return i;
	}
	return -1;
}

void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		selectedIdx = findSelected(Out, 3, cvPoint(x, y));
		if (selectedIdx >= 0)
		{
			drawPoints(dst, Out, 3, cvScalar(255, 0, 0));
			cvShowImage("dst", dst);
		}
	}
	if (event == CV_EVENT_LBUTTONUP || (event == CV_EVENT_MOUSEMOVE && flags == CV_EVENT_FLAG_LBUTTON))
	{
		if (selectedIdx < 0) return;
		Out[selectedIdx] = cvPoint(x, y);
		float M[3][3];
		ComputeMatrix(M, Out, In);
		InverseTransformImage(M, src, dst);

		if(event == CV_EVENT_LBUTTONUP) selectedIdx = -1;
		drawPoints(dst, Out, 3, cvScalar(255, 0, 0));
		cvShowImage("dst", dst);
	}
}

int main()
{
	src = cvLoadImage("C:\\Temp\\lena_triangle.png");
	dst = cvCreateImage(cvGetSize(src), 8, 3);

	//cvCopy(src,dst);

	//float M[3][3];
	//ComputeMatrix(M, Out, In);
	//InverseTransformImage(M, src, dst);

	//drawPoints(src, In, 3, cvScalar(0, 0, 255));
	//drawPoints(dst, Out, 3, cvScalar(255, 0, 0));

	cvCopy(src, dst);
	drawPoints(dst, Out, 3, cvScalar(255, 0, 0));

	//cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvSetMouseCallback("dst", myMouse);
	cvWaitKey();
	return 0;
}