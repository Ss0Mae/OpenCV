#include <opencv2/opencv.hpp>

IplImage* src;
IplImage* dst;

CvPoint pt1, pt2;
void ApplyWarping(IplImage* src, IplImage* dst, CvPoint p1, CvPoint p2)
{
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	cvSet(dst, cvScalar(0, 0, 0));
	int w = src->width;
	int h = src->height;

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			float vx, d1x, d2x, alphax;
			if (x < p1.x)
			{
				d1x = 0;
				d2x = dx;
				alphax = x / float(p1.x);
			}
			else
			{
				d1x = dx;
				d2x = 0;
				alphax = (x - p1.x) / float(w - p1.x);
			}
			vx = d1x * (1 - alphax) + d2x * alphax;

			float vy, d1y, d2y, alphay;
			if (y < p1.y)
			{
				d1y = 0;
				d2y = dy;
				alphay = y / float(p1.y);
			}
			else
			{
				d1y = dy;
				d2y = 0;
				alphay = (y - p1.y) / float(h - p1.y);
			}
			vy = d1y * (1 - alphay) + d2y * alphay;

			int x2 = x + vx;
			int y2 = y + vy;
			if (x2<0 || x2>w - 1) continue;
			if (y2<0 || y2>h - 1) continue;
			CvScalar c = cvGet2D(src, y, x);
			cvSet2D(dst, y2, x2, c);
		}
}

void ApplyWarping2(IplImage* src, IplImage* dst, CvPoint p1, CvPoint p2)
{
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	cvSet(dst, cvScalar(0, 0, 0));
	int w = src->width;
	int h = src->height;

	for (float y1 = 0; y1 < h; y1+=0.5f)
		for (float x1 = 0; x1 < w; x1 += 0.5f)
		{
			float vx, Dx[4], alpha=0;
			float vy, Dy[4], beta=0;
			
			for (int i = 0; i < 4; i++)
			{
				Dx[i] = 0.0f; Dy[i] = 0.0f;
			}

			if (x1 < p1.x && y1 < p1.y)
			{
				Dx[3] = dx;
				Dy[3] = dy;
				alpha = x1 / float(p1.x);
				beta = y1 / float(p1.y);
			}
			else if (x1 >= p1.x && y1 < p1.y)
			{

				Dx[2] = dx;
				Dy[2] = dy;
				alpha = (x1-p1.x) / float(w-p1.x);
				beta = y1 / float(p1.y);
			}

			else if (x1 < p1.x && y1 >= p1.y)
			{

				Dx[1] = dx;
				Dy[1] = dy;
				alpha = x1 / float(p1.x);
				beta = (y1-p1.y) / float(h-p1.y);
			}

			else if (x1 >= p1.x && y1 >= p1.y)
			{

				Dx[0] = dx;
				Dy[0] = dy;
				alpha = (x1 - p1.x) / float(w - p1.x);
				beta = (y1 - p1.y) / float(h - p1.y);
			}

			vx = (1 - alpha) * (1 - beta) * Dx[0] 
				 + (alpha) * (1 - beta)*Dx[1] 
				 + (1 - alpha) * (beta) * Dx[2] 
				 + (alpha) * (beta) * Dx[3];

			vy = (1 - alpha) * (1 - beta) * Dy[0]
				+ (alpha) * (1 - beta) * Dy[1]
				+ (1 - alpha) * (beta) * Dy[2]
				+ (alpha) * (beta) * Dy[3];
			int x2 = x1 + vx;
			int y2 = y1 + vy;
			if (x2<0 || x2>w - 1) continue;
			if (y2<0 || y2>h - 1) continue;
			CvScalar c = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c);
		}
}

void ApplyInverseWarping(IplImage* src, IplImage* dst, CvPoint p1, CvPoint p2)
{
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;
	cvSet(dst, cvScalar(0, 0, 0));
	int w = src->width;
	int h = src->height;

	for (int y2 = 0; y2 < h; y2++)
		for (int x2 = 0; x2 < w; x2++)
		{
			float vx, d1x, d2x, alphax;
			if (x2 < p2.x)
			{
				d1x = 0;
				d2x = dx;
				alphax = x2 / float(p2.x);
			}
			else
			{
				d1x = dx;
				d2x = 0;
				alphax = (x2 - p2.x) / float(w - p2.x);
			}
			vx = d1x* (1 - alphax) + d2x * alphax;

			float vy, d1y, d2y, alphay;
			if (y2 < p2.y)
			{
				d1y = 0;
				d2y = dy;
				alphay = y2 / float(p2.y);
			}
			else
			{
				d1y = dy;
				d2y = 0;
				alphay = (y2 - p2.y) / float(h - p2.y);
			}
			vy = d1y * (1 - alphay) + d2y * alphay;
			int x1 = x2 + vx;
			int y1 = y2 + vy;
			if (x1<0 || x1>w - 1) continue;
			if (y1<0 || y1>h - 1) continue;
			CvScalar c = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c);
		}
}
void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		pt1 = cvPoint(x, y);
	}

	if (event == CV_EVENT_LBUTTONUP)
	{
		pt2 = cvPoint(x , y);
		cvCopy(dst, src);
		ApplyWarping2(src, dst, pt1, pt2);
		//ApplyInverseWarping(src, dst, pt1, pt2);
		cvShowImage("image", dst);
	}
}
int main()
{
	src = cvLoadImage("C:\\Temp\\lena.png");
	dst = cvCreateImage(cvGetSize(src), 8, 3);

	cvCopy(src, dst);
	cvShowImage("image", dst);
	cvSetMouseCallback("image", myMouse);
	cvWaitKey();

}