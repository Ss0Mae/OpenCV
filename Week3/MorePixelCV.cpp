#include <opencv2/opencv.hpp>
// �츮�� �̹����� ������!
int main() {

	CvSize size = cvSize(500,200);
	IplImage *img = cvCreateImage(size, 8, 3);

//	CvScalar c = cvScalar(0, 0, 255); //b g r
//	cvSet(img, c);

	// �ڵ� �ǽ� 2-1
	//for (int x = 0;x < size.width;x++) {
	//	for (int y = 0;y < size.height;y++) {
	//		
	//		//int v = x;
	//		int v = float(x) / (size.width-1) * 255; // 0<=x/w*255<255
	//		CvScalar c = cvScalar(255-v, 0, v); //(255,0,0) ->(0,0,255)�� �Ǿ���
	//		cvSet2D(img, y, x, c);
	//	}
	//}

	// �ڵ� �ǽ� 2-2 // �߽ɿ� ����� ���� ������ �ּ��� �Ķ���.
	//for (int x = 0;x < size.width;x++) {
	//	for (int y = 0;y < size.height;y++) {
	//		float d;
	//		int cx = size.width / 2;
	//		int cy = size.height / 2;
	//		d = sqrt((x - cx)*(x - cx) + (y - cy)*(y - cy));

	//		int v = d/(size.width*sqrt(2)/2)*255; //d �ִ���̴� �밢������ d��Ʈ2
	//		CvScalar c = cvScalar(v, 0, 255 - v);
	//		cvSet2D(img, y, x, c);
	//		
	//	}
	//}

	// �ڵ� �ǽ� 2-3 ���������� ������ ������ ���鼭 ��->�� ���ذ�
	for (int x = 0;x < size.width;x++) {
		for (int y = 0;y < size.height;y++) {
			
			float nx = float(x) / (size.width - 1); //[0,1]
			float ny = float(y) / (size.height - 1); //[0,1]

			int v = float(nx + ny) / (2) * 255;
			CvScalar c = cvScalar(v, 0, 255 - v);
			cvSet2D(img, y, x, c);

		}
	}
	
	// Ÿ�� [-1,1] ��ǥ�� Ȱ�� ���簢�� �߽��� (0,0)�� �ǵ���
	for (int x = 0;x < size.width;x++) {
		for (int y = 0;y < size.height;y++) {
			
			float d;
			float nx = float(x) / (size.width -1)* 2 - 1;
			float ny = float(y) / (size.height -1)* 2 - 1;


			d = sqrt(nx*nx + ny * ny);
			int v = d / (sqrt(2)) * 255;

			CvScalar c = cvScalar(v, 0, 255 - v);
			cvSet2D(img, y, x, c);
		}
	}

	cvShowImage("More Pixel", img);
	cvWaitKey();


}