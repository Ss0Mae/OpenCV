#include <opencv2/opencv.hpp>
int main()
{
	IplImage* src = cvLoadImage("sejong.jpg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);

	int w = src->width;
	int h = src->height;

	float k = w / 16.0;
	float l = h / 12.0;    //�ִ� �Ÿ��� ����
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (y % (h / 6) == h / 12 && x % (w / 8) == w / 12)
			{  //������ �߽�
				int y_max = y + l;
				int y_min = y - l;
				if (y_max >= h)   y_max = h - 1;
				if (y_min < 0)   y_min = 0;
				int x_max = x + k;
				int x_min = x - k;
				if (x_max >= w)   x_max = w - 1;
				if (x_min < 0)   x_min = 0;
				for (int dy = y_min; dy <= y_max; dy++)
				{   //������ ��ü ����,
					for (int dx = x_min; dx <= x_max; dx++)
					{   //������ �Ÿ� �̿��ؼ� ������ ���� ������ Į��
						double dist = sqrt((y - dy) * (y - dy) + (x - dx) * (x - dx));   //�⺻ �Ÿ�
						double distA = sqrt((dy - y_min) * (dy - y_min) + (dx - x_min) * (dx - x_min));
						double distB = sqrt((dy - y_max) * (dy - y_max) + (dx - x_min) * (dx - x_min));
						double distC = sqrt((dy - y_min) * (dy - y_min) + (dx - x_max) * (dx - x_max));
						double distD = sqrt((dy - y_max) * (dy - y_max) + (dx - x_max) * (dx - x_max));

						if (dist >= distA || dist >= distB || dist >= distC || dist >= distD)    //������ �ִ� �κп��� ������� ����ؼ� �����.
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