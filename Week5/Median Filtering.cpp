#include <opencv2/opencv.hpp>

bool isBrighter(CvScalar a, CvScalar b)
{
	int bria = a.val[0] + a.val[1] + a.val[2];
	int brib = b.val[0] + b.val[1] + b.val[2];

	return (bria > brib) ? true : false;
}
int main()
{
	IplImage *src=cvLoadImage("C:\\Temp\\sample.jpg");
	CvSize size = cvGetSize(src);
	IplImage *dst = cvCreateImage(size, 8, 3);


	//int ksize = 1;
	//int num = (ksize * 2 + 1) * (ksize * 2 + 1);
	//CvScalar *f = new CvScalar[num];
	//for(int y=ksize;y<size.height-ksize;y++)
	//	for (int x = ksize; x < size.width-ksize; x++)
	//	{
	//		
	//		int idx = 0; 
	//		for(int v=-ksize;v<=ksize;v++)
	//			for (int u = -ksize; u <= ksize; u++)
	//			{
	//				f[idx] = cvGet2D(src, y+v, x+u);
	//				idx++;
	//			}
	//		// sorting f[0] 어두운값 ---> f[8] 제일 밝은값
	//		for(int i=0;i<num-1;i++) 
	//			for (int j = i+1; j < num; j++)
	//			{
	//				if (isBrighter(f[i], f[j]) == true)
	//				{
	//					CvScalar temp = f[i];
	//					f[i] = f[j];
	//					f[j] = temp; 
	//				}
	//			}
	//		CvScalar g=f[num/2];
	//		cvSet2D(dst, y, x, g);
	//		
	//	}
	//delete[] f;
	cvSmooth(src, dst, CV_MEDIAN, 101);
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	//cvSaveImage("C:\\Tmp\\jo.jpg", dst);
	cvWaitKey();
}