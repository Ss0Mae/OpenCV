#include <opencv2/opencv.hpp>

void prob1(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h / 2; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			CvScalar temp = cvGet2D(src, h - y - 1, x); // yÃà ´ëÄªÁ¡
			cvSet2D(dst, h - y - 1, x, c);
			cvSet2D(dst, y, x, temp);
		}
	}
	cvShowImage("prob1", dst);

}

void prob2(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w / 2; x++) {
			CvScalar c1 = cvGet2D(src, y, x);
			CvScalar temp1 = cvGet2D(src, y, w - 1 - x); // xÃà ´ëÄªÁ¡
			cvSet2D(dst, y, x, temp1);
			cvSet2D(dst, y, w - 1 - x, c1);
		}
	}
	cvShowImage("prob2", dst);
	//cvWaitKey();
}

void prob3(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h / 2; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			CvScalar temp = cvGet2D(src, y + h / 2, x);
			cvSet2D(dst, y, x, temp);
			cvSet2D(dst, y + h / 2, x, c);
		}
	}
	cvShowImage("prob3", dst);
	//cvWaitKey();
}

void prob4(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);

	int w = size.width;
	int h = size.height;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w / 2; x++) {
			CvScalar c = cvGet2D(src, y, x);
			CvScalar temp = cvGet2D(src, y, x + w / 2);
			cvSet2D(dst, y, x, temp);
			cvSet2D(dst, y, x + w / 2, c);
		}
	}
	cvShowImage("prob4", dst);
	//cvWaitKey();
}

void prob5(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	int i = 0;
	int j = 0;
	// Process each quadrant
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			int newX, newY;

			// Top-left quadrant (rotate 180 degrees)
			if (x < w / 2 && y < h / 2) {
				newX = (w / 2 - 1) - x;
				newY = (h / 2 - 1) - y;
			}
			// Top-right quadrant (rotate 180 degrees)
			else if (x >= w / 2 && y < h / 2) {
				newX = w - 1 - (x - w / 2);
				newY = (h / 2 - 1) - y;
			}
			// Bottom-left quadrant (rotate 180 degrees)
			else if (x < w / 2 && y >= h / 2) {
				newX = (w / 2 - 1) - x;
				newY = h - 1 - (y - h / 2);
			}
			// Bottom-right quadrant (rotate 180 degrees)
			else {
				newX = w - 1 - (x - w / 2);
				newY = h - 1 - (y - h / 2);
			}
			cvSet2D(dst, newY, newX, c);
		}
	}
	cvShowImage("prob5", dst);
	//cvWaitKey();
}

void prob6(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			float nx = 2 * (float)x / (w - 1) - 1;
			float ny = 2 * (float)y / (h - 1) - 1;
			CvScalar c = cvGet2D(src, y, x);
			if (nx + ny >= 1 || nx + ny <= -1 || nx - ny >= 1 || nx - ny <= -1) {
				int bri = c.val[0] + c.val[1] + c.val[2];
				CvScalar g = cvScalar(bri / 3, bri / 3, bri / 3);
				cvSet2D(dst, y, x, g);
			}
			else cvSet2D(dst, y, x, c);
		}
	}
	cvShowImage("prob6", dst);
	//cvWaitKey();
}

void prob7(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	float dist = 0.0f;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			float nx = 2*float(x) / (w - 1);
			float ny = 2*float(y) / (h - 1);
			if (x < w / 2 && y < h / 2) {
				dist = sqrt(nx * nx + ny * ny);
			}
			else if (x >= w / 2 && y < h / 2) {
				dist = sqrt(pow(nx - 2, 2) + ny * ny);
			}
			else if (x < w / 2 && y >= h / 2) {
				dist = sqrt(nx * nx + pow(ny - 2, 2));
			}
			else {
				dist = sqrt(pow(nx - 2, 2) + pow(ny - 2, 2));
			}
			CvScalar c = cvGet2D(src, y, x);
			if (dist > 0.99) {
				int bri = c.val[0] + c.val[1] + c.val[2];
				CvScalar g = cvScalar(bri / 3, bri / 3, bri / 3);
				cvSet2D(dst, y, x, g);
			}
			else cvSet2D(dst, y, x, c);
		}
	}
	cvShowImage("prob7", dst);
	//cvWaitKey();
}


void prob8(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			float nx = 2*float(x) / (w - 1) -1;
			float ny = 2*float(y) / (h - 1) -1 ;
			float dist = sqrt(nx * nx + ny * ny);
			CvScalar c = cvGet2D(src, y, x);
			if (dist >= 1) {
				int bri = c.val[0] + c.val[1] + c.val[2];
				CvScalar g = cvScalar(bri / 3, bri / 3, bri / 3);
				cvSet2D(dst, y, x, g);
			}
			else cvSet2D(dst, y, x, c);
		}
	}
	cvShowImage("prob8", dst);
	//cvWaitKey();
}

void prob9(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {

		}
	}
}

void prob10(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int i = 1; i <= 3; i++) {
		for (int y = (float)(h / 3) * (i - 1); y < (float)(h / 3) * i; y++) {
			for (int x = 0; x < w; x++) {
				CvScalar c = cvGet2D(src, y, x);
				CvScalar g = cvScalar(0, 0, 0);
				if (i == 1) {
					g.val[0] = 0;
					g.val[1] = 0;
					g.val[2] = c.val[2];
				}
				else if (i == 2) {
					g.val[0] = c.val[0];
					g.val[1] = 0;
					g.val[2] = 0;
				}
				else if (i == 3) {
					g.val[0] = 0;
					g.val[1] = c.val[1];
					g.val[2] = 0;
				}
				cvSet2D(dst, y, x, g);
			}
		}
	}
	cvShowImage("prob10", dst);
	//cvWaitKey();
}

void prob11(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			CvScalar g = cvScalar(0, 0, 0);
			if (x < w / 2 && y < h / 2) {
				g.val[0] = 0;
				g.val[1] = 0;
				g.val[2] = c.val[2];
			}
			else if (x >= w / 2 && y < h / 2) {
				g.val[0] = 0;
				g.val[1] = c.val[1];
				g.val[2] = 0;
			}
			else if (x < w / 2 && y >= h / 2) {
				g.val[0] = c.val[0];
				g.val[1] = 0;
				g.val[2] = 0;
			}
			else {
				int bri = c.val[0] + c.val[1] + c.val[2];
				g = cvScalar(bri/3, bri/3, bri/3);
			}
			cvSet2D(dst, y, x, g);
		}
	}
	cvShowImage("prob11", dst);
}

void prob12(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	float contrast_factor_left = 2.0f; // Increase contrast for the left half
	float contrast_factor_right = -1.1f; // Inverse contrast for the right half
	int brightness_offset_left = 0; // Adjust brightness offset for left
	int brightness_offset_right = 128; // Adjust brightness offset for right

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			// Get the source pixel
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g;

			for (int i = 0; i < 3; i++) {
				if (f.val[i] < 128) {
					g.val[i] = f.val[i] * 2;
				}
				else {
					g.val[i] = -1* f.val[i] + 255;
				}
			}
			//// Determine the contrast factor and brightness offset based on x position
			//float contrast_factor = (x > w / 2) ? contrast_factor_right : contrast_factor_left;
			//int brightness_offset = (x > w / 2) ? brightness_offset_right : brightness_offset_left;

			//// Apply contrast and brightness adjustments
			//for (int i = 0; i < 3; i++) {
			//	float value = contrast_factor * (f.val[i] - 128) + 128 + brightness_offset;
			//	g.val[i] = (uchar)(value < 0 ? 0 : (value > 255 ? 255 : value));
			//}

			//// Set the destination pixel
			cvSet2D(dst, y, x, g);
		}
	}
	cvShowImage("prob12", dst);
}

void prob13(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			CvScalar g;
			float dB = (float) 255 / w * x;
			for (int i = 0; i < 3; i++) {
				g.val[i] = c.val[i] + dB;
			}
			cvSet2D(dst, y, x, g);
		}
	}
	cvShowImage("prob13", dst);
}

void prob14(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	
	int brightness_offset_right = 128; // Adjust brightness offset for right

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			// Get the source pixel
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g;

			for (int i = 0; i < 3; i++) {
				if (f.val[i] < 128) {
					g.val[i] = -2 * f.val[i] + 255 ;
				}
				else {
					g.val[i] = f.val[i] * 1;
				}
			}
			

			//// Set the destination pixel
			cvSet2D(dst, y, x, g);
		}
	}
	cvShowImage("prob14", dst);
}

void prob15(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	int yStep = h / 16;
	int xStep = w / 16;
	for (int y = 0; y < h; y+= yStep) {
		for (int x = 0; x < w; x+=xStep) {
			CvScalar c = cvGet2D(src, y, x);
			for (int i = 0; i < yStep; i++) {
				for (int j = 0; j < xStep; j++) {
					cvSet2D(dst, y + i, x + j, c);
				}
			}
		}
	}
	cvShowImage("prob15", dst);
}

void prob16(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	int yStep = h / 8;
	int ct = 0;
	for (int y = 0; y < h; y++) {
		if (y!=0 &&y % yStep == 0)ct++;
		for (int x = 0; x < w; x ++) {
			CvScalar c = cvGet2D(src, y, x);
			CvScalar g;
			//printf("%d\n", y % yStep);
			for (int i = 0; i < 3; i++) {
				g.val[i] = c.val[i] + (255 / 8) * (ct);
			}
			cvSet2D(dst, y, x, g);
		}
	}
	
	cvShowImage("prob16", dst);
}

void prob17(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	int stepX = w / 8;
	int stepY = h / 8;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			
		}
	}
}
int main() {
	IplImage* src[30];
	IplImage* dst[30];
	for (int i = 0; i < 30; i++) {
		src[i] = cvLoadImage("C:\\temp\\lena.jpg");
		dst[i] = cvCreateImage(cvGetSize(src[i]), 8, 3);
	}
	prob1(src[0], dst[0]);
	prob2(src[1], dst[1]);
	prob3(src[2], dst[2]);
	prob4(src[3], dst[3]);
	prob5(src[4], dst[4]);
	prob6(src[5], dst[5]);
	prob7(src[6], dst[6]);
	prob8(src[7], dst[7]);
	//prob8(src[7], dst[7]);
	prob10(src[9], dst[9]);
	prob11(src[10], dst[10]);
	prob12(src[11], dst[11]);
	prob13(src[12], dst[12]);
	prob14(src[13], dst[13]);
	prob15(src[14], dst[14]);
	prob16(src[15], dst[15]);
	cvWaitKey();
}