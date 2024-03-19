#include <opencv2/opencv.hpp>
int main()
{
	IplImage *src = cvLoadImage("C:\\Temp\\Lena.png");
	/*cvSmooth(src, dst, CV_BILATERAL, 0, 0, 100, 10);*/
	
	//cvWaitKey();
	CvSize size = cvGetSize(src);
	IplImage *dst = cvCreateImage(size, 8, 3);
	IplImage *blur = cvCreateImage(size, 8, 3);
	IplImage *diff = cvCreateImage(size, 8, 3);
	
	// 1. blur the src image
	cvSmooth(src, blur, CV_GAUSSIAN, 201);
	for(int y=0;y<size.height;y++)
		for (int x = 0; x < size.width; x++) {
			CvScalar S = cvGet2D(src, y, x);
			int bri = (S.val[0] + S.val[1] + S.val[2])/3;
			CvScalar B = cvScalar(bri, bri, bri);
			cvSet2D(blur, y, x, B);
		}
	// 2. compute the diff image
	for (int y = 0;y < size.height;y++) 
		for (int x = 0; x < size.width; x++)
		{
			CvScalar S = cvGet2D(src, y, x);
			CvScalar B = cvGet2D(blur, y, x);
			CvScalar D ;
			for (int k = 0; k < 3; k++)
				D.val[k] = S.val[k] - B.val[k] + 128;
			cvSet2D(diff, y, x, D);
		}
	// 3. generate dst image with blurred and diff image
	for (float alpha = 0.0f; alpha < 3.0f; alpha += 0.1f) {
		for (int y = 0; y < size.height; y++)
			for (int x = 0; x < size.width; x++)
			{
				CvScalar B = cvGet2D(blur, y, x);
				CvScalar D = cvGet2D(diff, y, x);
				CvScalar G;
				for (int k = 0; k < 3; k++)
					G.val[k] = B.val[k] + alpha * (D.val[k] - 128);
				cvSet2D(dst, y, x, G);
			}
		cvShowImage("diff", diff);
		printf("alpha = %f\n", alpha);
		cvShowImage("dst", dst);
		cvWaitKey();
	}
	
}