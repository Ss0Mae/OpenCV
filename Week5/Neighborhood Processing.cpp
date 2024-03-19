#include <opencv2/opencv.hpp>
int main()
{
	IplImage* src = cvLoadImage("C:\\Temp\\flower1.jpg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);

	/*float H[3][3] = { {1 / 16.0f,2 / 16.0f,1 / 16.0f},
					  {2 / 16.0f,4 / 16.0f,2 / 16.0f},
					  {1 / 16.0f,2 / 16.0f,1 / 16.0f} };*/ // 다 더해서 1이되야함 안그러면 어두어짐

	float H[3][3] = { {-1,-1,-1},
					  {0,0,0,},
					  {1,1,1} };
	for (int step = 0;step < 20;step++) {
		int Ksize = 1;
		float inv_area = 1.0f / ((2 * Ksize + 1)*(2 * Ksize + 1));
		for (int y = Ksize;y < size.height - Ksize;y++) {
			for (int x = Ksize;x < size.width - Ksize;x++)
			{
				CvScalar g = cvScalar(0, 0, 0);
				for (int u = -Ksize;u <= Ksize;u++)
					for (int v = -Ksize;v <= Ksize;v++)
					{
						CvScalar f = cvGet2D(src, y + v, x + u);
						for (int k = 0;k < 3;k++)
							g.val[k] += H[u + Ksize][v + Ksize] * f.val[k];
						//밑 코드를 위로 합칠수 있음 나누는 것보다 역수를 곱하는게 연산 속도가 빠름
					}
				/*for (int k = 0;k < 3;k++) g.val[k] /=area;*/
				cvSet2D(dst, y, x, g);
			}
			
		}
		printf("Filtering %d times\n", step);
		cvShowImage("dst", dst);
		cvWaitKey();
		IplImage *temp = src;
		src = dst;
		dst = temp;
	}
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	
}
