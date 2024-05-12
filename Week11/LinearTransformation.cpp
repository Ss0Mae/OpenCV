#include <opencv2/opencv.hpp>

float sx = 1.5f;
float sy = 0.5f;
float theta = 30.0f; // degree 0 ~360
float M[2][2]; // [ M[0][0] M[0][1] ]   [x1]
			   // [ M[1][0] M[1][1] ]   [y1]

float M1[2][2]; // for scale
float M2[2][2]; // for rotation

void setScale(float M[][2], float sx, float sy) {
	M[0][0] = sx;	M[0][1] = 0;
	M[1][0] = 0;	M[1][1] = sy;
}

void setRotation(float M[][2], float theta) {
	float rad = theta / 180 * CV_PI;
	M[0][0] = cos(rad);	M[0][1] = -sin(rad);
	M[1][0] = sin(rad);	M[1][1] = cos(rad);
}

void setMultiply(float M[][2], float M1[][2], float M2[][2]) {

	M[0][0] = M1[0][0] * M2[0][0] + M1[0][1] * M2[1][0];
	M[0][1] = M1[0][0] * M2[0][1] + M1[0][1] * M2[1][1];
	M[1][0] = M1[1][0] * M2[0][0] + M1[1][1] * M2[1][0];
	M[1][1] = M1[1][0] * M2[0][1] + M1[1][1] * M2[1][1];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			M[i][j] = 0.0f;
			for(int k = 0 ; k<2;k++)
				M[i][j] += M1[i][k] * M2[k][j];
		}
	}


}
// 축소의 경우에는 괜찮은데, 확대의 경우에는 문제가 생김. 확대시킨 좌표의 색이 비어있게됨. 
int main() {
	IplImage *src = cvLoadImage("C:\\image\\lena.jpg");
	IplImage* dst = cvCreateImage(cvSize(800, 800), 8, 3);

	//for (int y1 = 0; y1 < src->height; y1++) {
	//	for (int x1 = 0; x1 < src->width; x1++) {
	//		int x2 = sx * x1;
	//		int y2 = sy * y1;
	//		if (x2 < 0 || x2 >dst->width - 1)continue;
	//		if (y2 < 0 || y2 > dst->height - 1)continue;
	//		// x2 와 y2에 대한 식을 바꿔가면서 다양한 변환을 이룸.
	//		CvScalar f = cvGet2D(src, y1, x1);
	//		cvSet2D(dst, y2, x2, f);
	//	}
	//}

	//for (int y2 = 0; y2 < dst->height; y2++) { //내가 그릴 y2, x2를 바탕으로 원본의 색을 찾아야함 (역변형)
	//	for (int x2 = 0; x2 < dst->width; x2++) {
	//		int x1 = x2 / sx;     // x2 = sx * x1
	//		int y1 = y2 / sy;
	//		if (x1 <0 || x1> src->width - 1) continue;
	//		if (y1 < 0 || y1 > src->height - 1) continue;
	//		CvScalar f = cvGet2D(src, y1, x1);
	//		cvSet2D(dst, y2, x2, f);
	//	}
	//}

	//for (int y1 = 0; y1 < src->height; y1++) { // 2D rotation (정변형)
	//	for (int x1 = 0; x1 < src->width; x1++) {
	//		int x2 = cos(rad) * x1 - sin(rad) * y1;
	//		int y2 = sin(rad) * x1 + cos(rad) * y1;
	//		if (x2 < 0 || x2 >dst->width - 1)continue;
	//		if (y2 < 0 || y2 > dst->height - 1)continue;
	//		// x2 와 y2에 대한 식을 바꿔가면서 다양한 변환을 이룸.
	//		CvScalar f = cvGet2D(src, y1, x1);
	//		cvSet2D(dst, y2, x2, f);
	//	}
	//}


	//for (int y2 = 0; y2 < dst->height; y2++) { // 2D rotation (역변형)
	//	for (int x2 = 0; x2 < dst->width; x2++) {
	//		int x1 = cos(-rad) * x2 - sin(-rad) * y2;    // x2 = sx * x1
	//		int y1 = sin(-rad) * x2 + cos(-rad) * y2;
	//		if (x1 <0 || x1> src->width - 1) continue;
	//		if (y1 < 0 || y1 > src->height - 1) continue;
	//		CvScalar f = cvGet2D(src, y1, x1);
	//		cvSet2D(dst, y2, x2, f);
	//	}
	//}

	setScale(M1, sx, sy);
	setRotation(M2, theta);
	// M = M2 * M1  first scale and then rotate
	setMultiply(M, M2, M1);
	for (int y1 = 0; y1 < src->height; y1++) { // 2D rotation (정변형) with Matrix
		for (int x1 = 0; x1 < src->width; x1++) {
			int x2 = M[0][0] * x1 + M[0][1] * y1;
			int y2 = M[1][0] * x1 + M[1][1] * y1;

			if (x2 < 0 || x2 >dst->width - 1)continue;
			if (y2 < 0 || y2 > dst->height - 1)continue;
			// x2 와 y2에 대한 식을 바꿔가면서 다양한 변환을 이룸.
			CvScalar f = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, f);
		}
	}
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();

}