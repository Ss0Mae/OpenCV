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

int main()
{
	IplImage* src = cvLoadImage("c:\\temp\\lena.png");
	IplImage* dst = cvCreateImage(cvSize(800, 800), 8, 3);


	float M[3][3];
	float theta = 0.0f;
	float cx = src->width / 2;
	float cy = src->height / 2;
	/*
		for (theta = 0.0f; theta <= 360; theta += 10)
		{
			cvSet(dst, cvScalar(0, 0, 0));
			float A[3][3], B[3][3], C[3][3], D[3][3];
			setTranslation(A, -cx, -cy);
			setRotation(B, theta);
			setTranslation(C, cx, cy);

			// M = C B A
			// D =   B A
			// M = C Dtx
			setMultiply(D, B, A);
			setMultiply(M, C, D);

			// transformation
			for (float y1 = 0; y1 < src->height; y1++)
				for (float x1 = 0; x1 < src->width; x1++)
				{
					float w1 = 1.0f;

					float x2 = M[0][0] * x1 + M[0][1] * y1 + M[0][2] * w1;
					float y2 = M[1][0] * x1 + M[1][1] * y1 + M[1][2] * w1;
					float w2 = M[2][0] * x1 + M[2][1] * y1 + M[2][2] * w1;
					x2 = x2 / w2;
					y2 = y2 / w2;

					if (x2<0 || x2>dst->width - 1) continue;
					if (y2<0 || y2>dst->height - 1) continue;
					CvScalar c = cvGet2D(src, y1, x1);
					cvSet2D(dst, y2, x2, c);
				}
			cvShowImage("dst", dst);
			cvWaitKey(30);
		}
	*/
	while (true)
	{

		cvSet(dst, cvScalar(0, 0, 0));

		float s = sin(theta / 180.0f * 3.141592) + 1;

		float IA[3][3], IB1[3][3], IB2[3][3], IC[3][3], ID[3][3], IE[3][3];
		setTranslation(IA, cx, cy);
		setScale(IB1, 1 / s, 1 / s);
		setRotation(IB2, -theta);
		setTranslation(IC, -cx, -cy);
		float IM[3][3];

		// IM = IA IB1 IB2 IC
		// ID = IA IB1
		// IE =        IB2 IC
		// IM =    ID IE
		setMultiply(ID, IA, IB1);
		setMultiply(IE, IB2, IC);
		setMultiply(IM, ID, IE);

		// inverse transformation

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

		//cvShowImage("src", src);
		cvShowImage("dst", dst);
		cvWaitKey(30);
		theta += 10.0f;
	}

	return 0;
}