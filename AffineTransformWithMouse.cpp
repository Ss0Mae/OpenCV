// 원점 기준으로 회전 실시간
#include <opencv2/opencv.hpp>
#include <math.h>
void setIdentity(float M[][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			M[i][j] = 0;
	M[0][0] = 1;
	M[1][1] = 1;
	M[2][2] = 1;
}
void setTranslation(float M[][3], float tx, float ty) {
	setIdentity(M);
	M[0][2] = tx;
	M[1][2] = ty;
}
void setScale(float M[][3], float sx, float sy) {
	setIdentity(M);
	M[0][0] = sx;			M[0][1] = 0;
	M[1][0] = 0;			M[1][1] = sy;
}
void setRotation(float M[][3], float theta) {
	setIdentity(M);
	float rad = theta / 180.0f * CV_PI;
	M[0][0] = cos(rad);		M[0][1] = -sin(rad);
	M[1][0] = sin(rad);		M[1][1] = cos(rad);
}
void setMultiply(float M[][3], float A[][3], float B[][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			M[i][j] = 0;
			for (int k = 0; k < 3; k++)
				M[i][j] += A[i][k] * B[k][j];
		}
}
void setInverse(float IM[][2], float M[][2]) {
	float det = M[0][0] * M[1][1] - M[0][1] * M[1][0];
	IM[0][0] = M[1][1] / det;		IM[0][1] = -M[0][1] / det;
	IM[1][0] = -M[1][0] / det;		IM[1][1] = M[0][0] / det;
}

void applyTransform(IplImage* src, IplImage* dst,
	float sx, float sy, float theta, float cx, float cy)
{
	cvSet(dst, cvScalar(0, 0, 0));

	float IM[3][3];	// M = T(cx, cy) R(theta) S(sx,sy) T(-cx,-cy)
	//IM = T(cx,cy) S(1/sx,1/sy) R(-theta) T(-cx, -cy)
	// M =     M4        M3       M2        M1
	// M =          M6                 M5

	float M1[3][3], M2[3][3], M3[3][3], M4[3][3], M5[3][3], M6[3][3];
	setTranslation(M1, -cx, -cy);
	setRotation(M2, -theta);
	setScale(M3, 1 / sx, 1 / sy);
	setTranslation(M4, cx, cy);

	setMultiply(M5, M2, M1);
	setMultiply(M6, M4, M3);
	setMultiply(IM, M6, M5);

	for (int y2 = 0; y2 < dst->height; y2++)
		for (int x2 = 0; x2 < dst->width; x2++)
		{
			int w2 = 1;

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

IplImage* src;
IplImage* dst;
CvPoint p1;
CvPoint p2;
float theta = 0.0f;
float scale = 1;
bool Lbut = false;
float getAngle(CvPoint p, CvPoint q) {
	float rad1 = atan2(p.y, p.x);
	float rad2 = atan2(q.y, q.x);

	float rad = rad2 - rad1;
	float theta = rad / CV_PI * 180.0f;
	return theta;
}

void setScaleAndRotation(CvPoint p1, CvPoint p2) {
	float len1 = sqrt(p1.x * p1.x + p1.y * p1.y);
	float len2 = sqrt(p2.x * p2.x + p2.y * p2.y);
	scale *= len2 / len1;
	theta += getAngle(p1, p2);
	
}

void myMouse(int event, int x, int y, int flags, void*) {
	if (event == CV_EVENT_LBUTTONDOWN) {
		p1 = cvPoint(x, y);
		Lbut = true;
	}
	if (event == CV_EVENT_MOUSEMOVE && Lbut == true) {
		p2 = cvPoint(x, y);
		setScaleAndRotation(p1, p2);
		applyTransform(src, dst, scale, scale, theta, 0, 0);
		cvShowImage("image", dst);
		p1 = p2;
	}
	if (event == CV_EVENT_LBUTTONUP) {
		Lbut = false;
		p2 = cvPoint(x, y);
		setScaleAndRotation(p1, p2);
		applyTransform(src, dst, scale, scale, theta, 0, 0);
		cvShowImage("image", dst);
	}

}

int main()
{
	src = cvLoadImage("c:\\image\\lena.jpg");
	dst = cvCreateImage(cvGetSize(src), 8, 3);
	cvShowImage("image", src);
	cvSetMouseCallback("image", myMouse);
	cvWaitKey();

	return 0;
}
