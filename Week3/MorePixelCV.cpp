#include <opencv2/opencv.hpp>
// 우리가 이미지를 만들어보자!
int main() {

	CvSize size = cvSize(500,200);
	IplImage *img = cvCreateImage(size, 8, 3);

//	CvScalar c = cvScalar(0, 0, 255); //b g r
//	cvSet(img, c);

	// 코딩 실습 2-1
	//for (int x = 0;x < size.width;x++) {
	//	for (int y = 0;y < size.height;y++) {
	//		
	//		//int v = x;
	//		int v = float(x) / (size.width-1) * 255; // 0<=x/w*255<255
	//		CvScalar c = cvScalar(255-v, 0, v); //(255,0,0) ->(0,0,255)로 되야함
	//		cvSet2D(img, y, x, c);
	//	}
	//}

	// 코딩 실습 2-2 // 중심에 가까울 수록 빨갛고 멀수록 파랗다.
	//for (int x = 0;x < size.width;x++) {
	//	for (int y = 0;y < size.height;y++) {
	//		float d;
	//		int cx = size.width / 2;
	//		int cy = size.height / 2;
	//		d = sqrt((x - cx)*(x - cx) + (y - cy)*(y - cy));

	//		int v = d/(size.width*sqrt(2)/2)*255; //d 최대길이는 대각선길이 d루트2
	//		CvScalar c = cvScalar(v, 0, 255 - v);
	//		cvSet2D(img, y, x, c);
	//		
	//	}
	//}

	// 코딩 실습 2-3 왼쪽위에서 오른쪽 밑으로 가면서 빨->파 변해감
	for (int x = 0;x < size.width;x++) {
		for (int y = 0;y < size.height;y++) {
			
			float nx = float(x) / (size.width - 1); //[0,1]
			float ny = float(y) / (size.height - 1); //[0,1]

			int v = float(nx + ny) / (2) * 255;
			CvScalar c = cvScalar(v, 0, 255 - v);
			cvSet2D(img, y, x, c);

		}
	}
	
	// 타원 [-1,1] 좌표계 활용 직사각형 중심이 (0,0)이 되도록
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