#include <opencv2/opencv.hpp>

void drawHistogram(int in[][3],int max)
{
	CvSize size = cvSize(256, 300);
	IplImage *histo = cvCreateImage(size, 8, 3);
	cvSet(histo, cvScalar(0, 0, 0));
	int max_h = max / 255 * 3;

	for (int k = 0;k < 3;k++) {
		for (int x = 0;x < 256;x++)
		{
			int h = in[x][k];
			h = ((float)h / max_h) * size.height;
			if (h > size.height) h = size.height;

			for (int y = 0;y < h;y++)
			{
				CvScalar f = cvGet2D(histo, size.height - 1 - y, x);
				f.val[k] = 255;
				cvSet2D(histo, size.height - 1 - y, x, f);
			}
		}
	}

	cvShowImage("histo", histo);
	//cvWaitKey();
}
int main()
{
	IplImage*  src = cvLoadImage("C:\\Temp\\dddd.jpg");
	CvSize size = cvGetSize(src);
	IplImage *dst = cvCreateImage(size, 8, 3); 

	//1. histogram 계산
	int histo[256][3];
	for(int i=0;i<256;i++)
		for (int k = 0;k < 3;k++)
			histo[i][k] = 0; 

	for(int y=0;y<size.height;y++)
		for (int x = 0;x < size.width;x++) {
			CvScalar f = cvGet2D(src, y, x);
			for (int k = 0;k < 3;k++)
				histo[(int)f.val[k]][k]++;
		}
	drawHistogram(histo, size.width*size.height);

	// 2. Cumulative Histogram
	int cumul[256][3];
	for (int i = 0;i < 256;i++)
		for (int k = 0;k < 3;k++)
			cumul[i][k] = 0;

	for(int k=0;k<3;k++)
		for (int i = 0;i < 256;i++)
			for (int j = 0;j <= i;j++)
				cumul[i][k] += histo[j][k];

	/*for (int i = 0;i < 256;i++)
		printf("cumul i=%d : %d\n", i, cumul[i][0]);
*/
	// 3. 누적분포를 변환함수처럼 써서 그림 변환

	double inverSize = 1.0 / (size.width*size.height) * 255;
	for(int y=0;y<size.height;y++)
		for (int x = 0;x < size.width;x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g;
			for (int k = 0;k < 3;k++) 
			{
				g.val[k]=
				(double)cumul[(int)f.val[k]][k] * inverSize;
			}
			cvSet2D(dst, y, x, g);
		}
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	//cvSaveImage("C:\\Temp\\res.jpg", dst);
}