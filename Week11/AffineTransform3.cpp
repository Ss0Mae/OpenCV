#include <opencv2/opencv.hpp>


void setIdentity(float M[][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			M[i][j] = (i == j) ? 1.0f : 0.0f;
	/*
		M[0][0] = 1.0f;		M[0][1] = 0.0f;		M[0][2] = 0.0f;
		M[1][0] = 0.0f;		M[1][1] = 1.0f;		M[1][2] = 0.0f;
		M[2][0] = 0.0f;		M[2][1] = 0.0f;		M[2][2] = 1.0f;
	*/
}

void setTranslation(float M[][3], float tx, float ty)
{
	setIdentity(M);
	M[0][2] = tx;
	M[1][2] = ty;
}
void setScale(float M[][3], float sx, float sy)
{
	setIdentity(M);
	M[0][0] = sx;
	M[1][1] = sy;
}
void setRotation(float M[][3], float theta)
{
	float rad = theta / 180.0f * 3.141592;
	setIdentity(M);
	M[0][0] = cos(rad);			M[0][1] = -sin(rad);
	M[1][0] = sin(rad);			M[1][1] = cos(rad);
}
void setMultiply(float M[][3], float A[][3], float B[][3])	// M = A B
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			M[i][j] = 0.0f;
			for (int k = 0; k < 3; k++)
				M[i][j] += A[i][k] * B[k][j];
		}
}

IplImage* src;
IplImage* dst;
CvPoint pt1, pt2;

float M[3][3];
float total_angle = 0;
float total_scale = 1.0f;


void getTransform(float M[][3], CvPoint pt1, CvPoint pt2)
{
	float phi1, phi2;

	float R[3][3], S[3][3];
	// tan (phi1) = pt1.y / pt1.x;
	phi1 = atan2(pt1.y, pt1.x);				// -pi < phi1 < pi in radian
	phi2 = atan2(pt2.y, pt2.x);
	float theta = phi2 - phi1;				// radian
	float angle = theta / 3.141592 * 180.0f;	// degree
	total_angle += angle;
	printf("angle = %f total_angle = %f \n", angle, total_angle);

	setRotation(R, total_angle);

	float r1, r2;
	r1 = sqrt(pt1.x * pt1.x + pt1.y * pt1.y);
	r2 = sqrt(pt2.x * pt2.x + pt2.y * pt2.y);
	float s = r2 / r1;
	total_scale *= s;

	setScale(S, total_scale, total_scale);
	setMultiply(M, R, S);
}


void applyTransform(IplImage* src, IplImage* dst, float M[][3])
{
	cvSet(dst, cvScalar(0, 0, 0));

	for (float y1 = 0; y1 < src->height; y1++)
		for (float x1 = 0; x1 < src->width; x1++)
		{
			float w1 = 1.0f;
			float x2 = M[0][0] * x1 + M[0][1] * y1 + M[0][2] * w1;
			float y2 = M[1][0] * x1 + M[1][1] * y1 + M[1][2] * w1;
			float w2 = M[2][0] * x1 + M[2][1] * y1 + M[2][2] * w1;
			x2 /= w2;
			y2 /= w2;

			if (x2<0 || x2>dst->width - 1) continue;
			if (y2<0 || y2>dst->height - 1) continue;
			CvScalar c = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c);
		}
}

void applyInverseTransform(IplImage* src, IplImage* dst, float IM[][3])
{
	cvSet(dst, cvScalar(0, 0, 0));

	for (float y2 = 0; y2 < dst->height; y2++)
		for (float x2 = 0; x2 < dst->width; x2++)
		{
			float w2 = 1.0f;
			float x1 = IM[0][0] * x2 + IM[0][1] * y2 + IM[0][2] * w2;
			float y1 = IM[1][0] * x2 + IM[1][1] * y2 + IM[1][2] * w2;
			float w1 = IM[2][0] * x2 + IM[2][1] * y2 + IM[2][2] * w2;
			x1 /= w1;
			y1 /= w1;

			if (x1<0 || x1>src->width - 1) continue;
			if (y1<0 || y1>src->height - 1) continue;
			CvScalar c = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c);
		}
}

void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		pt1 = cvPoint(x, y);
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		pt2 = cvPoint(x, y);
		//getTransform(M, pt1, pt2);
		//applyTransform(src, dst, M);
		getTransform(M, pt2, pt1);
		applyInverseTransform(src, dst, M);
		cvShowImage("dst", dst);
	}
	
}

int main()
{
	src = cvLoadImage("c:\\Temp\\lena.png");
	dst = cvCreateImage(cvSize(800, 800), 8, 3);

	setIdentity(M);
	applyTransform(src, dst, M);

	cvShowImage("dst", dst);
	
	cvWaitKey();

	return 0;
}