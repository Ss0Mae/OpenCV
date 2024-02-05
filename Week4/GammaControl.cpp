#include <opencv2/opencv.hpp>
/* 0 < gamma < 1-> ��ο�� ��� ����, ������ ��� ����, gamma >1 -> ��ο�� ��� ����, ������ ��� ����*/
// 0 ~ 1 �������� ������ ��������� �Ѵ�

void gammaCorrection(IplImage *in, IplImage *out, float gamma)
{	
	CvSize size = cvGetSize(in);

	for (int y = 0;y < size.height;y++)
		for (int x = 0;x < size.width;x++)
		{
			CvScalar f = cvGet2D(in, y, x);
			CvScalar g;

			for (int k = 0;k < 3;k++)
			{
				g.val[k] = pow(f.val[k] / 255, gamma) * 255; //g = f ^ gamma
			}
			cvSet2D(out, y, x, g);
		}
}
int main()
{
	IplImage *src = cvLoadImage("C:\\Temp\\flower1.jpg");
	CvSize size = cvGetSize(src);
	IplImage *dst = cvCreateImage(size, 8, 3);

	// sqrt : ������ ���ϴ� math �޼ҵ�, 
	// pow : ��� 

	float gamma = 1;
	int key = 0;
	while (key != 'q')
	{
		printf("gamma = %f\n", gamma);
		gammaCorrection(src, dst, gamma);
		cvShowImage("dst", dst);
		key = cvWaitKey();
		if (key == '1')gamma -= 0.1f;
		if (key == '2')gamma += 0.1f;
	}
	
	

	return 0;
}