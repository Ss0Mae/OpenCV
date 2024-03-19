#include <opencv2/opencv.hpp>
float getDist(CvScalar a, CvScalar b)
{
	return sqrt((a.val[0] - b.val[0])*(a.val[0] - b.val[0])
		+ (a.val[1] - b.val[1])*(a.val[1] - b.val[1])
		+ (a.val[2] - b.val[2])*(a.val[2] - b.val[2]));
}
void applyThresholding(IplImage* src, IplImage* dst)
{
	CvSize size = cvGetSize(src);
	CvScalar colors[] = { cvScalar(0,0,0),
						cvScalar(255,255,255),
						 cvScalar(255,255,128),
						 cvScalar(128,255,255),
						 cvScalar(255,128,255),
						 cvScalar(255,128,128),
						 cvScalar(128,255,128),
						 cvScalar(128,128,255) };
	int num = 8;
	for (int y = 0; y < size.height; y++)
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			int min_index = 1;
			float min_dist = FLT_MAX;
			for (int i = 0; i < num; i++)
			{
				float dist = getDist(f, colors[i]);
				if (dist < min_dist)
				{
					min_index = i;
					min_dist = dist;
				}
			}
			CvScalar g = colors[min_index]; //같은 경계값법 인데 색추가에 용이함
			cvSet2D(dst, y, x, g);
			/*int bri = (f.val[0] + f.val[1] + f.val[2]) / 3;

			CvScalar g;
			if (bri < 64) g = cvScalar(0, 0, 0);
			else if (bri < 192) g = cvScalar(128, 128, 128);
			else g = cvScalar(255, 255, 255);
			cvSet2D(dst, y, x, g);*/ 
			//경계값법
		}
}

void applyPatterning(IplImage *src, IplImage *dst)
{
	CvSize size = cvGetSize(src);
	IplImage *blur = cvCreateImage(size, 8, 3);
	cvSmooth(src, blur, 5);

	//int pattern[] = { 2,1,3,0 };
	int pattern[] = { 1,8,0,6,2,5,7,3,4 };
	int div = 3;
	float interval = 255.0f / (div*div + 1);

	cvSet(dst, cvScalar(0, 0, 0));

	for (int y = 0; y < size.height - div; y += div)
		for (int x = 0; x < size.width - div; x += div)
		{
			CvScalar f = cvGet2D(blur, y, x);
			for (int k = 0; k < 3; k++)
			{
				int bri = f.val[k];
				int num = bri / interval;
				if (num > div*div) num = div * div;
				for (int i = 0; i < num; i++)
				{
					int pos = pattern[i];
					int u = pos % div;
					int v = pos / div;
					CvScalar g = cvGet2D(dst, y + v, x + u);
					g.val[k] = 255;
					cvSet2D(dst, y + v, x + u, g);
				}
			}
		}
}
int main()
{
	IplImage *src = cvLoadImage("C:\\Temp\\sample.jpg");
	IplImage *dst = cvCreateImage(cvGetSize(src), 8, 3);
	CvSize size = cvGetSize(src);

	//applyThresholding(src, dst);
	applyPatterning(src, dst);
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}