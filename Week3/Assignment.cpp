#include <opencv2/opencv.hpp>

void prob1(IplImage *in, int width, int height) {
	in = cvLoadImage("C:\\Temp\\sejong_small.jpg");
	if (in == nullptr) {
		printf("File Not Found!");
		exit(-1);
	}
	for (int x = 0;x < width;x++) {
		for (int y = 0;y < height/2 ;y++) {

			CvScalar c = cvGet2D(in, y, x);
			CvScalar temp = cvGet2D(in, height - y - 1, x);
			cvSet2D(in, height - y - 1, x, c);
			cvSet2D(in, y, x, temp);
		}
	}
	cvShowImage("prob-1", in);
}

void prob2(IplImage *in, int width, int height) {
	in = cvLoadImage("C:\\Temp\\sejong_small.jpg");
	if (in == nullptr) {
		printf("File Not Found!");
		exit(-1);
	}
	for (int x = 0;x < width /2;x++) {
		for (int y = 0;y < height;y++) {
			CvScalar c1 = cvGet2D(in, y, x);
			CvScalar temp1 = cvGet2D(in, y, (width / 2) + x - 1);
			cvSet2D(in, y, x, temp1);
			cvSet2D(in, y, (width / 2) + x - 1, c1);
		}
	}
	cvShowImage("prob-2", in);
	
}

void prob3(IplImage *in, int width, int height) {
	in = cvLoadImage("C:\\Temp\\sejong_small.jpg");
	if (in == nullptr) {
		printf("File Not Found!");
		exit(-1);
	}
	for (int x = 0;x < width;x++) {
		for (int y = 0;y < height;y++) {

			float nx = float(x) / (width - 1) * 2 - 1;
			float ny = float(y) / (height - 1) * 2 - 1;
			CvScalar c = cvGet2D(in, y, x);
			CvScalar g;
			if (nx + ny >= 1 || nx - ny <= -1 || nx + ny <= -1 || nx - ny >= 1) {
				int bri = c.val[0] + c.val[1] + c.val[2];
				g = cvScalar(bri / 3, bri / 3, bri / 3);
				cvSet2D(in, y, x, g);
			}
			else cvSet2D(in, y, x, c);
		}
	}
	cvShowImage("prob-3", in);
	
}

void prob4(IplImage *in, int width, int height) {
	in = cvLoadImage("C:\\Temp\\sejong_small.jpg");
	if (in == nullptr) {
		printf("File Not Found!");
		exit(-1);
	}
	for (int x = 0;x < width;x++) {
		for (int y = 0;y < height;y++) {
			float d;
			float nx = float(x) / (width - 1) * 2 - 1;
			float ny = float(y) / (height - 1) * 2 - 1;
			CvScalar c = cvGet2D(in, y, x);
			CvScalar g;
			d = sqrt(nx*nx + ny * ny);
			if (d > 1) {
				int bri = c.val[0] + c.val[1] + c.val[2];
				g = cvScalar(bri / 3, bri / 3, bri / 3);
				cvSet2D(in, y, x, g);
			}

			else cvSet2D(in, y, x, c);
		}
	}
	cvShowImage("prob-4", in);
	
}

void prob5(IplImage *in, int width, int height) {
	in = cvLoadImage("C:\\Temp\\sejong_small.jpg");
	if (in == nullptr) {
		printf("File Not Found!");
		exit(-1);
	}
	for (int x = 0;x < width;x++) {
		for (int y = 0;y < height;y++) {
			float d = 0.0;
			float nx = float(x) / (width - 1) * 2 - 1;
			float ny = float(y) / (height - 1) * 2 - 1;
			d = sqrt(nx*nx + ny * ny);
			CvScalar c = cvGet2D(in, y, x);
			CvScalar g = cvScalar(0, 0, 0);
			
			if (d >= 0.1&&d <= 0.2) cvSet2D(in, y, x, g);
			if (d >= 0.3&&d <= 0.4) cvSet2D(in, y, x, g);
			if (d >= 0.5&&d <= 0.6) cvSet2D(in, y, x, g);
			if (d >= 0.7&&d <= 0.8) cvSet2D(in, y, x, g);
			if (d >= 0.9&&d <= 1.0) cvSet2D(in, y, x, g);
			if (d >= 1.1&&d <= 1.2) cvSet2D(in, y, x, g);
			if (d >= 1.3&&d <= 1.4) cvSet2D(in, y, x, g);
			
		}
	}
	cvShowImage("prob-5", in);

}

void prob6(IplImage *in, int width, int height) {
	in = cvLoadImage("C:\\Temp\\sejong_small.jpg");
	if (in == nullptr) {
		printf("File Not Found!");
		exit(-1);
	}
	for (int y = 0;y < height;y++) {
		for (int x = 0;x < width;x++) {
	
			CvScalar b = cvScalar(0, 0, 0);
			float nx = 2*float(x) / (width - 1)  -1;
			float ny = 2*float(y) / (height - 1) -1;

			if ((nx >= 0.0 && ny >= 0.0)) {
				if (nx >= 0.0&&nx <= 0.2) {
					if (ny >= 0.0&&ny <= 0.2) cvSet2D(in, y, x, b);
					if (ny >= 0.4&&ny <= 0.6) cvSet2D(in, y, x, b);
					if (ny >= 0.8&&ny <= 1.0) cvSet2D(in, y, x, b);
				}
				else if (nx >= 0.2&&nx <= 0.4) {
					if (ny >= 0.2&&ny <= 0.4) cvSet2D(in, y, x, b);
					if (ny >= 0.6&&ny <= 0.8) cvSet2D(in, y, x, b);
				}
				else if (nx >= 0.4&&nx <= 0.6) {
					if (ny >= 0.0&&ny <= 0.2) cvSet2D(in, y, x, b);
					if (ny >= 0.4&&ny <= 0.6) cvSet2D(in, y, x, b);
					if (ny >= 0.8&&ny <= 1.0) cvSet2D(in, y, x, b);
				}
				else if (nx >= 0.6&&nx <= 0.8) {
					if (ny >= 0.2&&ny <= 0.4) cvSet2D(in, y, x, b);
					if (ny >= 0.6&&ny <= 0.8) cvSet2D(in, y, x, b);
				}
				else {
					if (ny >= 0.0&&ny <= 0.2) cvSet2D(in, y, x, b);
					if (ny >= 0.4&&ny <= 0.6) cvSet2D(in, y, x, b);
					if (ny >= 0.8&&ny <= 1.0) cvSet2D(in, y, x, b);
				}
				
			} 
			
			if (nx < 0 && ny > 0) {
				
				if (nx <= 0.0&&nx >= -0.2) {
					if (ny >= 0.2&&ny <= 0.4) cvSet2D(in, y, x, b);
					if (ny >= 0.6&&ny <= 0.8) cvSet2D(in, y, x, b);
				}
				else if (nx <= -0.2&&nx >= -0.4) {
					if (ny >= 0.0&&ny <= 0.2) cvSet2D(in, y, x, b);
					if (ny >= 0.4&&ny <= 0.6) cvSet2D(in, y, x, b);
					if (ny >= 0.8&&ny <= 1.0) cvSet2D(in, y, x, b);
				}
				
				else if (nx <= -0.4&&nx >= -0.6) {
					if (ny >= 0.2&&ny <= 0.4) cvSet2D(in, y, x, b);
					if (ny >= 0.6&&ny <= 0.8) cvSet2D(in, y, x, b);
				}
				else if (nx <= -0.6&&nx >= -0.8) {
					if (ny >= 0.0&&ny <= 0.2) cvSet2D(in, y, x, b);
					if (ny >= 0.4&&ny <= 0.6) cvSet2D(in, y, x, b);
					if (ny >= 0.8&&ny <= 1.0) cvSet2D(in, y, x, b);
				}
				else {
					if (ny >= 0.2&&ny <= 0.4) cvSet2D(in, y, x, b);
					if (ny >= 0.6&&ny <= 0.8) cvSet2D(in, y, x, b);
				}
				
			}
			
			if (nx < 0 && ny < 0) {
		
				if (nx <= 0.0&&nx >= -0.2) {
					if (ny <= 0.0&&ny >= -0.2) cvSet2D(in, y, x, b);
					if (ny <= -0.4&&ny >= -0.6) cvSet2D(in, y, x, b);
					if (ny <= -0.8&&ny >= -1.0) cvSet2D(in, y, x, b);
				}
				else if (nx <= -0.2&&nx >= -0.4) {
					if (ny <= -0.2&&ny >= -0.4) cvSet2D(in, y, x, b);
					if (ny <= -0.6&&ny >= -0.8) cvSet2D(in, y, x, b);
				}
				else if (nx <= -0.4&&nx >= -0.6) {
					if (ny <= 0.0&&ny >= -0.2) cvSet2D(in, y, x, b);
					if (ny <= -0.4&&ny >= -0.6) cvSet2D(in, y, x, b);
					if (ny <= -0.8&&ny >= -1.0) cvSet2D(in, y, x, b);
				}
				else if (nx <= -0.6&&nx >= -0.8) {
					if (ny <= -0.2&&ny >= -0.4) cvSet2D(in, y, x, b);
					else if (ny <= -0.6&&ny >= -0.8) cvSet2D(in, y, x, b);
				}
				else {
					if (ny <= 0.0&&ny >= -0.2) cvSet2D(in, y, x, b);
					if (ny <= -0.4&&ny >= -0.6) cvSet2D(in, y, x, b);
					if (ny <= -0.8&&ny >= -1.0) cvSet2D(in, y, x, b);
				}
				
			}
			
			if (nx > 0 && ny < 0) {
				
				if (nx >= 0.0&&nx <= 0.2) {
					if (ny <= -0.2&&ny >= -0.4) cvSet2D(in, y, x, b);
					if (ny <= -0.6&&ny >= -0.8) cvSet2D(in, y, x, b);
				}
				else if (nx >= 0.2&&nx <= 0.4) {
					if (ny <= 0.0&&ny >= -0.2) cvSet2D(in, y, x, b);
					if (ny <= -0.4&&ny >= -0.6) cvSet2D(in, y, x, b);
					if (ny <= -0.8&&ny >= -1.0) cvSet2D(in, y, x, b);
				}

				else if (nx >= 0.4&&nx <= 0.6) {
					if (ny <= -0.2&&ny >= -0.4) cvSet2D(in, y, x, b);
					if (ny <= -0.6&&ny >= -0.8) cvSet2D(in, y, x, b);
				}
				else if (nx >= 0.6&&nx <= 0.8) {
					if (ny <= 0.0&&ny >= -0.2) cvSet2D(in, y, x, b);
					if (ny <= -0.4&&ny >= -0.6) cvSet2D(in, y, x, b);
					if (ny <= -0.8&&ny >= -1.0) cvSet2D(in, y, x, b);
				}
				else {
					if (ny <= -0.2&&ny >= -0.4) cvSet2D(in, y, x, b);
					if (ny <= -0.6&&ny >= -0.8) cvSet2D(in, y, x, b);
				}
				
			}
		}
		
	}
	cvShowImage("prob-6", in);
	

}

int main() { 
	IplImage *img;
	img = cvLoadImage("C:\\Temp\\sejong_small.jpg");
	if (img == nullptr) {
		printf("File Not Found!");
		exit(-1);
	}
	CvSize size = cvGetSize(img);
	prob1(img, size.width, size.height);
	prob2(img, size.width, size.height);
	prob3(img, size.width, size.height);
	prob4(img, size.width, size.height);
	prob5(img, size.width, size.height);
	prob6(img, size.width, size.height);
	cvWaitKey();
}

