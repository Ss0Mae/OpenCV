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
						cvScalar(128,128,128),
						cvScalar(255,255,128),
						cvScalar(128,255,255),
						cvScalar(255,128,255) };
	int num = 6;
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
			cvSet2D(dst, y, x, g);*/ //경계값법
		}
}

void applyPatterning(IplImage *src, IplImage *dst)
{
	CvSize size = cvGetSize(src);
	IplImage *blur = cvCreateImage(size, 8, 3);
	cvSmooth(src, blur, 5);

	//int pattern[] = { 2,1,3,0 };
	int pattern[] = { 1,8,0,6,2,5,7,3,4 };
	int div = 10;
	float interval = 255.0f / div;
	cvSet(dst, cvScalar(0, 0, 0));
	for (int y = 0;y < size.height - 2;y += 3)
		for (int x = 0; x < size.width - 2; x += 3)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g;
			int bri = (f.val[0] + f.val[1] + f.val[2]) / 3;
			int num = bri / interval;
			if (num > div - 1) num = div - 1;
			for (int i = 0; i < num; i++)
			{
				int pos = pattern[i];
				int u = pos % 3;
				int v = pos / 3;
				cvSet2D(dst, y + v, x + u, cvScalar(255, 255, 255));
			}

		}
}
void applyDithering(IplImage *src, IplImage* dst)
{
	CvSize size = cvGetSize(src);
	CvScalar colors[] = { cvScalar(0,0,0),
						  cvScalar(255,255,255),
						  cvScalar(255,0,0),
						  cvScalar(0,255,0),
						  cvScalar(0,0,255), 
						  cvScalar(128,128,128),
						  cvScalar(255,255,128),
						  cvScalar(128,255,255),
						  cvScalar(255,128,255) };
	int num = 9;

	for(int y=0;y<size.height-1;y++)
		for (int x = 1;x < size.width-1;x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			int min_index = -1;
			float min_dist = FLT_MAX;
			for (int i = 0;i < num;i++)
			{
				float dist = getDist(f, colors[i]);
				if (dist < min_dist)
				{
					min_index = i;
					min_dist = dist;
				}
			}
			CvScalar g = colors[min_index];
			cvSet2D(dst, y, x, g);

			CvScalar d;
			for (int k = 0;k < 3;k++)
				d.val[k] = f.val[k] - g.val[k];

			CvScalar f1 = cvGet2D(src, y, x + 1);
			for (int k = 0;k < 3;k++)
				f1.val[k] += d.val[k] * 7.0 / 16.0;
			cvSet2D(src, y, x + 1,f1);

			CvScalar f2 = cvGet2D(src, y+1, x - 1);
			for (int k = 0;k < 3;k++)
				f2.val[k] += d.val[k] * 3.0 / 16.0;
			cvSet2D(src, y+1, x - 1, f2);

			CvScalar f3 = cvGet2D(src, y + 1, x);
			for (int k = 0;k < 3;k++)
				f3.val[k] += d.val[k] * 3.0 / 16.0;
			cvSet2D(src, y+1, x, f3);

			CvScalar f4 = cvGet2D(src, y + 1, x+1);
			for (int k = 0;k < 3;k++)
				f4.val[k] += d.val[k] * 1.0 / 16.0;
			cvSet2D(src, y + 1, x, f4);
		}
}
int main()
{
	IplImage *src = cvLoadImage("C:\\Temp\\sample.jpg");
	IplImage *dst = cvCreateImage(cvGetSize(src), 8, 3);
	CvSize size = cvGetSize(src);

	//applyThresholding(src, dst);
	//applyPatterning(src, dst);
	applyDithering(src, dst);
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}