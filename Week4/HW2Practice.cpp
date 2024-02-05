#include <opencv2/opencv.hpp>

float getDiff2(CvScalar a, CvScalar b)
{
	return (a.val[0] - b.val[0])*(a.val[0] - b.val[0]) + (a.val[1] - b.val[1])*(a.val[1] - b.val[1]) + (a.val[2] - b.val[2])*(a.val[0] - b.val[0]);
}
int main() 
{

	IplImage *src1 = cvLoadImage("C:\\Temp\\hw2_1.jpg");
	IplImage *src2 = cvLoadImage("C:\\Temp\\hw2_2.jpg");
	CvSize size = cvGetSize(src1);
	IplImage *dst = cvCreateImage(size, 8, 3);

	int w = size.width;
	int h = size.height;

	float min_diff = 1000000;
	int min_u;
	int min_v;
	for (int u = -w/4;u < w/4;u++)           // brute-force
		for (int v = -h/4;v < h/4;v++)
		{
			//printf("u = %d v = %d\n", u, v);
			cvSet(dst, cvScalar(0, 0, 0));
			float diff = 0.0f;
			int count = 0;
			for (int y = 0;y < h;y++)
				for (int x = 0;x < w;x++)
				{	
					int x2 = x - u;
					int y2 = y - v;
					if (x2<0 || x2>w - 1) continue;
					if (y2<0 || y2>h - 1) continue;

					CvScalar f1 = cvGet2D(src1, y, x);
					CvScalar f2 = cvGet2D(src2, y2, x2);
					diff += getDiff2(f1,f2);
					count++;
					CvScalar g;
					g.val[0] = (f1.val[0] + f2.val[0]) / 2;
					g.val[1] = (f1.val[1] + f2.val[1]) / 2;
					g.val[2] = (f1.val[2] + f2.val[2]) / 2;
					cvSet2D(dst, y, x, g);
				}
			diff = diff / count; //평균적인 차이값;
			if (diff < min_diff)
			{
				min_diff = diff;
				min_u = u;
				min_v = v;
				printf("u=%d v=%d diff = %f min_diff= %f\n", u, v, diff, min_diff);
				cvShowImage("dst", dst);
				cvWaitKey(1);
			}
			
			
			
		}
	cvShowImage("src1", src1);
	cvShowImage("src2", src2);
	
}