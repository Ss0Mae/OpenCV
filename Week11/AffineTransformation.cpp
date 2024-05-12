//#include <opencv2/opencv.hpp>
//
//void setIdentity(float M[][3]) {
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			if (i == j) M[i][j] = 1.0f;
//			else M[i][j] = 0.0f;
//		}
//	}
//}
//
//void setScale(float M[][3], float sx, float sy) {
//	setIdentity(M);
//	M[0][0] = sx;
//
//	M[1][1] = sy;
//
//}
//
//void setTranslation(float M[][3], float tx, float ty) {
//	setIdentity(M);
//	M[0][2] = tx;
//	M[1][2] = ty;
//}
//
////void setScale(float M[][2], float sx, float sy) {
////	M[0][0] = sx; M[0][1] = 0;
////	M[1][0] = 0; M[1][1] = sy;
////}
//
////void setRotation(float M[][2], float theta) {
////	float rad = theta / 180 * CV_PI;
////	M[0][0] = cos(rad); M[0][1] = -sin(rad);
////	M[1][0] = sin(rad); M[1][1] = cos(rad);
////}
//
//void setRotation(float M[][3], float theta) {
//	setIdentity(M);
//	float rad = theta / 180 * CV_PI;
//	M[0][0] = cos(rad); M[0][1] = -sin(rad);
//	M[1][0] = sin(rad); M[1][1] = cos(rad);
//}
////void setMultiply(float M[][2], float M1[][2], float M2[][2]) {
////	for (int i = 0; i < 2; i++) {
////		for (int j = 0; j < 2; j++) {
////			M[i][j] = 0.0f;
////			for(int k =0 ; k <2;k++)
////				M[i][j] += M1[i][k] * M2[k][j];
////		}
////	}
////}
//
//void setMultiply(float M[][3], float M1[][3], float M2[][3]) {
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			M[i][j] = 0.0f;
//			for (int k = 0; k < 3; k++)
//				M[i][j] += M1[i][k] * M2[k][j];
//		}
//	}
//}
//void setInverse(float IM[][2], float M[][2]) {
//
//	float det = M[0][0] * M[1][1] - M[0][1] * M[1][0];
//	IM[0][0] = M[1][1] / det; IM[0][1] = -M[0][1] / det;
//	IM[1][0] = -M[1][0] / det;  IM[1][1] = M[0][0] / det;
//}
//int main() {
//	IplImage *src = cvLoadImage("C:\\image\\lena.jpg");
//	IplImage* dst = cvCreateImage(cvSize(800, 800), 8, 3);
//
//	float M[3][3];
//	float sx = 1.5;
//	float sy = 0.5;
//	float theta = 30.0f;
//	float tx = 100;
//	float ty = 100;
//	float M1[3][3], M2[3][3], M3[3][3]; // M = M3 * M2 * M1 -> scale -> rotation -> translation
//	float M4[3][3]; // M4 = M2 * M1
//	/*
//	setScale(M1, sx, sy);
//	setRotation(M2, theta);
//	setTranslation(M3, tx, ty);
//	setMultiply(M4, M2, M1);
//	setMultiply(M, M3, M4);
//	*/
//
//	setScale(M1, 1 / sx, 1 / sy);
//	setRotation(M2, -theta);
//	setTranslation(M3, -tx, -ty); // IM = M1 * M2 * M3, M4 = M1 * M2
//	setMultiply(M4, M1, M2);
//	setMultiply(IM, M3, M4);
//
//	float IM[3][3];
//	setInverse(IM, M);
//	/*for (int y1 = 0; y1 < src->height; y1++) {
//		for (int x1 = 0; x1 < src->width; x1++) {
//			int w1 = 1;
//			float x2 = M[0][0] * x1 + M[0][1] * y1 + M[0][2] * w1;
//			float y2 = M[1][0] * x1 + M[1][1] * y1 + M[0][2] * w1;
//			float w2 = M[2][0] * x1 + M[2][1] * y1 + M[2][2] * w1;
//
//			x2 /= w2;
//			y2 /= w2;
//			if (x2 < 0 || x2 >dst->width - 1)continue;
//			if (y2 < 0 || y2 > dst->height - 1)continue;
//			CvScalar c = cvGet2D(src, y1, x1);
//			cvSet2D(dst, y2, x2, c);
//		}
//	}*/
//
//	for (int y2 = 0; y2 < dst->height; y2++) { //내가 그릴 y2, x2를 바탕으로 원본의 색을 찾아야함 (역변형)
//		for (int x2 = 0; x2 < dst->width; x2++) {
//			int w2 = 1;
//			float x1 = IM[0][0] * x2 + IM[0][1] * y2 + IM[0][2] * w2;/* x2 = sx * x1, x1 = x2 / sx */ // -> Inverse Matrix 
//			float y1 = IM[1][0] * x2 + IM[1][1] * y2 + IM[0][2] * w2;
//			float w1 = IM[2][0] * x2 + IM[2][1] * y2 + IM[2][2] * w2;
//
//			x1 /= w1;
//			y1 /= w1;
//			if (x1 < 0 || x1 >src->width - 1) continue;
//			if (y1 < 0 || y1 > src->height - 1) continue;
//			CvScalar c = cvGet2D(src, y1, x1);
//			cvSet2D(dst, y2, x2, c);
//		}
//	}
//	cvShowImage("src", src);
//	cvShowImage("dst", dst);
//	cvWaitKey();
//}