#include <opencv2/opencv.hpp>
int main()
{
	IplImage *src = cvLoadImage("sejong.jpg");
	CvSize size = cvGetSize(src);
	for(int y=0;y<size.height/2;y++)
		for (int x = 0;x < size.width / 2;x++)
		{
			float nx = (float(x) / (size.width));
			float ny = (float(y) / (size.height));
			float d = sqrt(nx*nx + ny * ny);
			CvScalar f = cvScalar(0,0,0);
			if (d >= 0.05&&d <= 0.1) cvSet2D(src, y, x, f);
			if (d >= 0.15&&d <= 0.2) cvSet2D(src, y, x, f);
			if (d >= 0.25&&d <= 0.3) cvSet2D(src, y, x, f);
			if (d >= 0.35&&d <= 0.4) cvSet2D(src, y, x, f);
			if (d >= 0.45&&d <= 0.5) cvSet2D(src, y, x, f);
			if (d >= 0.55&&d <= 0.6) cvSet2D(src, y, x, f);
			if (d >= 0.65&&d <= 0.7) cvSet2D(src, y, x, f);
		
		}

	for (int y = size.height-1;y >= size.height/2;y--)
		for (int x = 0;x < size.width / 2;x++)
		{
			float nx = (float(x) / (size.width));
			float ny = -1*((float(y)) / (size.height))+1.0f;
			float d = sqrt(nx*nx + ny * ny);
			CvScalar f = cvScalar(0, 0, 0);
			if (d >= 0.05&&d <= 0.1) cvSet2D(src, y, x, f);
			if (d >= 0.15&&d <= 0.2) cvSet2D(src, y, x, f);
			if (d >= 0.25&&d <= 0.3) cvSet2D(src, y, x, f);
			if (d >= 0.35&&d <= 0.4) cvSet2D(src, y, x, f);
			if (d >= 0.45&&d <= 0.5) cvSet2D(src, y, x, f);
			if (d >= 0.55&&d <= 0.6) cvSet2D(src, y, x, f);
			if (d >= 0.65&&d <= 0.7) cvSet2D(src, y, x, f);

			
		}

	for (int y = 0;y < size.height / 2;y++)
		for (int x = size.width-1;x >= size.width/2;x--)
		{
			float nx = -1*(float(x) / (size.width))+1.0f;
			float ny = (float(y) / (size.height));
			float d = sqrt(nx*nx + ny * ny);
			CvScalar f = cvScalar(0, 0, 0);
			if (d >= 0.05&&d <= 0.1) cvSet2D(src, y, x, f);
			if (d >= 0.15&&d <= 0.2) cvSet2D(src, y, x, f);
			if (d >= 0.25&&d <= 0.3) cvSet2D(src, y, x, f);
			if (d >= 0.35&&d <= 0.4) cvSet2D(src, y, x, f);
			if (d >= 0.45&&d <= 0.5) cvSet2D(src, y, x, f);
			if (d >= 0.55&&d <= 0.6) cvSet2D(src, y, x, f);
			if (d >= 0.65&&d <= 0.7) cvSet2D(src, y, x, f);
		}

	for (int y = size.height - 1;y >= size.height / 2;y--)
		for (int x = size.width - 1;x >= size.width / 2;x--)
		{
			float nx = -1 * (float(x) / (size.width)) + 1.0f;
			float ny = -1 * ((float(y)) / (size.height)) + 1.0f;
			float d = sqrt(nx*nx + ny * ny);
			CvScalar f = cvScalar(0, 0, 0);
			if (d >= 0.05&&d <= 0.1) cvSet2D(src, y, x, f);
			if (d >= 0.15&&d <= 0.2) cvSet2D(src, y, x, f);
			if (d >= 0.25&&d <= 0.3) cvSet2D(src, y, x, f);
			if (d >= 0.35&&d <= 0.4) cvSet2D(src, y, x, f);
			if (d >= 0.45&&d <= 0.5) cvSet2D(src, y, x, f);
			if (d >= 0.55&&d <= 0.6) cvSet2D(src, y, x, f);
			if (d >= 0.65&&d <= 0.7) cvSet2D(src, y, x, f);
		}

	cvShowImage("src", src);
	cvWaitKey();
}