#include <opencv2/opencv.hpp>

void MySmooth(IplImage* src, IplImage* dst, int K)  //window size: (2K+1)*(2K+1)
{
	int w = src->width;
	int h = src->height;

	float inv_sum = 1.0f / ((2 * K + 1)*(2 * K + 1));
	for(int y=K;y<h-K;y++)
		for (int x = K;x < w-K;x++)
		{
			CvScalar g = cvScalar(0, 0, 0);
			for(int v= -K;v<=K;v++)
				for (int u = -K;u <= K; u++)
				{
					CvScalar f = cvGet2D(src, y + v, x + u);
					for (int k = 0;k < 3;k++)
						g.val[k] += f.val[k];
				}
			for (int k = 0;k < 3;k++)
				g.val[k] *= inv_sum;
			cvSet2D(dst, y, x, g);
		}
}

void MyFastSmooth(IplImage* src, IplImage* dst, int K)  //¼¼·Î·Î ¹¶°×
{
	int w = src->width;
	int h = src->height;
	IplImage* tmp = cvCreateImage(cvGetSize(src), 8, 3);
	float inv_sum = 1.0f / ((2 * K + 1));
	for (int y = K;y < h - K;y++)
		for (int x = 0;x < w;x++)
		{
			CvScalar g = cvScalar(0, 0, 0);
			for (int v = -K;v <= K;v++)
				{
					CvScalar f = cvGet2D(src, y + v, x );
					for (int k = 0;k < 3;k++)
						g.val[k] += f.val[k];
				}
			for (int k = 0;k < 3;k++)
				g.val[k] *= inv_sum;
			cvSet2D(tmp, y, x, g);
		}

	for (int y = K;y <h- K;y++)
		for (int x = K;x < w - K;x++)
		{
			CvScalar g = cvScalar(0, 0, 0);
			
			for (int u = -K;u <= K; u++)
			{
				CvScalar f = cvGet2D(src, y , x + u);
				for (int k = 0;k < 3;k++)
					g.val[k] += f.val[k];
			}
			for (int k = 0;k < 3;k++)
				g.val[k] *= inv_sum;
			cvSet2D(dst, y, x, g);
		}

}
int main()
{
	IplImage* src = cvLoadImage("C:\\Temp\\flower1.jpg");
	
	IplImage *dst = cvCreateImage(cvGetSize(src), 8, 3);
	MyFastSmooth(src, dst, 10);
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
}