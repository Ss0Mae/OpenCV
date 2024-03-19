#include <opencv2/opencv.hpp>
int main()
{
	IplImage* src = cvLoadImage("sejong.jpg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);

	int w = src->width;
	int h = src->height;

	float k = w / 16.0;
	float l = h / 12.0;    //최대 거리를 위해
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (y % (h / 6) == h / 12 && x % (w / 8) == w / 12)
			{  //마름모 중심
				int y_max = y + l;
				int y_min = y - l;
				if (y_max >= h)   y_max = h - 1;
				if (y_min < 0)   y_min = 0;
				int x_max = x + k;
				int x_min = x - k;
				if (x_max >= w)   x_max = w - 1;
				if (x_min < 0)   x_min = 0;
				for (int dy = y_min; dy <= y_max; dy++)
				{   //마름모 전체 범위,
					for (int dx = x_min; dx <= x_max; dx++)
					{   //마름모 거리 이용해서 마름모 내에 있으면 칼라값
						double dist = sqrt((y - dy) * (y - dy) + (x - dx) * (x - dx));   //기본 거리
						double distA = sqrt((dy - y_min) * (dy - y_min) + (dx - x_min) * (dx - x_min));
						double distB = sqrt((dy - y_max) * (dy - y_max) + (dx - x_min) * (dx - x_min));
						double distC = sqrt((dy - y_min) * (dy - y_min) + (dx - x_max) * (dx - x_max));
						double distD = sqrt((dy - y_max) * (dy - y_max) + (dx - x_max) * (dx - x_max));

						if (dist >= distA || dist >= distB || dist >= distC || dist >= distD)    //검은색 주는 부분에서 흰색까지 겸비해서 줘야함.
						{

							double r = sqrt((dy - h / 2) * (dy - h / 2) + (dx - w / 2) * (dx - w / 2));

							double white = r;
							CvScalar f = cvScalar(r, r, r);
							cvSet2D(dst, dy, dx, f);
						}
						else
						{
							CvScalar g = cvGet2D(src, dy, dx);
							cvSet2D(dst, dy, dx, g);
						}
					}
				}
			}
		}
	}

	cvShowImage("src", src);
	cvShowImage("dst", dst);

	cvWaitKey();

	return 0;
}