#include <opencv2/opencv.hpp>

int main() {

	IplImage *img = cvLoadImage("C:\\Temp\\flower1.jpg");
	if (img == nullptr) {
		printf("File Not Found!\n");
		exit(-1);
	}
	CvSize size = cvGetSize(img);
	IplImage *cpy = cvCreateImage(size, 8, 3);

	for (int x = 0;x < size.width;x++) {
		for (int y = 0;y < size.height;y++) {

			CvScalar c = cvGet2D(img, y, x);
			int bri = c.val[0] + c.val[1] + c.val[2];
			CvScalar g;
			if (x < size.width / 2) g = c;
			else g = cvScalar(bri / 3, bri / 3, bri / 3);
			cvSet2D(cpy, y, x, g);
		}
		
	}

	cvShowImage("image", cpy);
	cvWaitKey();
	return 0;
}