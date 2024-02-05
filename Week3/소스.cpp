#include <opencv2/opencv.hpp>

// image processing : source --> destination
// image filtering --> point processing //g = A * f + B;
// image warping

void adjustContrastAndBrightness(IplImage *in, IplImage *out, float A, float B) {

	CvSize size = cvGetSize(in);
	for (int y = 0;y < size.height;y++) {
		for (int x = 0;x < size.width;x++) {
			CvScalar f = cvGet2D(in, y, x);
			CvScalar g;
			g.val[0] = A * f.val[0] + B;
			g.val[1] = A * f.val[1] + B;
			g.val[2] = A * f.val[2] + B;
			cvSet2D(out, y, x, g);
		}
	}
}
int main() {
	IplImage *src = cvLoadImage("C:\\Temp\\flower1.jpg");
	CvSize size = cvGetSize(src);
	IplImage *dst = cvCreateImage(size, 8, 3);
	
	float A = 1.0f;
	float B = 0.0f;
	int key = 0;
	while (key != 'q') {

		printf("A=%f B=%f\n", A, B);
		adjustContrastAndBrightness(src, dst, A, B);
		cvShowImage("dst", dst);
		key=cvWaitKey();
		switch (key) 
		{
		case'1': B += 10; break;
		case'2': B -= 10; break;
		case'3': A += 0.1f; break;
		case'4': A -= 0.1f; break;
		default:            break;
		}
	}
}