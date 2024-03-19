#include <opencv2/opencv.hpp>

void setRotation(float angle, float M[][2])
{
	float rad = angle / 180.0f*3.141592;

	M[0][0] = cos(rad);           M[0][1] = -sin(rad);
	M[1][0] = sin(rad);           M[1][1] = cos(rad);
}

void setScale(float sx, float sy, float M[][2])
{
	M[0][0] = sx;   M[0][1] = 0;
	M[1][0] = 0;    M[1][1] = sy;
}

void setMultiply(float M[][2], float A[][2], float B[][2]) //M = A * B;
{
	M[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
	M[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
	M[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
	M[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
}

void setInverse(float M[][2], float IM[][2])
{
	// IM = [d    -b]  /(ad-bc)
	//      [-c    a]
	float det = 1 / (M[0][0] * M[1][1] - M[0][1] * M[1][0]);
	
	IM[0][0] = M[1][1] * det;			IM[0][1] = -M[0][1] * det;
	IM[1][0] = -M[1][0] * det;			IM[1][1] = M[0][0] * det;
}
int main()
{
	IplImage *src = cvLoadImage("C:\\Temp\\lena.png");
	IplImage *dst = cvCreateImage(cvSize(800, 800), 8, 3);

	float theta = 30;// angle : degree
	float M[2][2];
	float M1[2][2];
	float M2[2][2];
	
	setScale(2, 0.5, M1);
	setRotation(theta, M2);
	
	setMultiply(M, M2, M1); //크기를 변경하고 회전

	// Transform
	
	//for(float y1=0;y1<src->height;y1++)
	//	for (float x1 = 0;x1 < src->width;x1++) {

	//		float x2 = M[0][0]*x1 - M[0][1]*y1;
	//		float y2 = M[1][0]*x1 + M[1][1]*y1;

	//		if (x2<0 || x2>dst->width - 1) continue;
	//		if (y2<0 || y2>dst->height - 1) continue;
	//		CvScalar c = cvGet2D(src, y1, x1);
	//		cvSet2D(dst, y2, x2, c);
	//	}

	// InverseTransform

	float IM[2][2];
	setInverse(M, IM);
	for(float y2=0;y2<dst->height;y2++)
		for (float x2 = 0;x2 < dst->width;x2++)
		{
			float x1 = IM[0][0]*x2 + IM[0][1] *y2;
			float y1 = IM[1][0] *x2 + IM[1][1] *y2;

			if (x1<0 || x1>src->width - 1) continue;
			if (y1<0 || y1>src->height - 1)continue;
			CvScalar c = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c);
		}


	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
}