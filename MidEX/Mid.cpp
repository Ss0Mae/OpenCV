#include <opencv2/opencv.hpp>

void prob1(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h / 2; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			CvScalar temp = cvGet2D(src, h - y - 1, x); // y축 대칭점
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
			CvScalar temp1 = cvGet2D(src, y, w - 1 - x); // x축 대칭점
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
			// Calculate the saturation factor based on the x-coordinate
			float saturationFactor = (float)x / (w - 1);

			// Get the original color at the current pixel
			CvScalar color = cvGet2D(src, y, x);

			// Convert the color to grayscale
			float grayscale = (color.val[0] + color.val[1] + color.val[2]) / 3.0;

			// Adjust the saturation of the color
			for (int i = 0; i < 3; i++) {
				// Linearly interpolate between original color and grayscale
				color.val[i] = (1 - saturationFactor) * color.val[i] + saturationFactor * grayscale;
			}

			// Set the adjusted color in the destination image
			cvSet2D(dst, y, x, color);
		}
	}
	cvShowImage("prob9", dst);
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
	int flag = 1;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			CvScalar b = cvScalar(0, 0, 0);
			float nx = 2 * float(x) / (w - 1) - 1;  // [-1, 1]로 정규화
			float ny = 2 * float(y) / (h - 1) - 1;

			int ix = (nx + 1) / 0.25; // nx 구간 계산 [0, 8] 변환
			int iy = (ny + 1) / 0.25; // ny 구간 계산 [0, 8] 변환

			// 구간별 처리를 위한 간소화된 로직
			if ((ix % 2 == 0 && iy % 2 == 1) || (ix % 2 == 1 && iy % 2 == 0)) {
				for (int i = 0; i < 3; i++) {
					b.val[i] = 0.5 * b.val[i];
				}
				cvSet2D(dst, y, x, b);
			}
			else {
				cvSet2D(dst, y, x, c);
			}
		}
	}
	cvShowImage("prob17", dst);
}

bool isInTargetRange(float dist) {
	// 정규화된 거리(dist)가 목표 범위 내에 있는지 확인
	const float ranges[][2] = { {0.1f, 0.2f}, {0.3f, 0.4f}, {0.5f, 0.6f}, {0.7f, 0.8f}, {0.9f, 1.0f}, {1.1f, 1.2f}, {1.3f, 1.4f} };
	for (auto& range : ranges) {
		if (dist >= range[0] && dist <= range[1]) return true; // 범위 내에 있으면 true 반환
	}
	return false;
}

void prob20(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			float nx = 2 * float(x) / (w - 1) - 1; // [-1, 1]로 정규화
			float ny = 2 * float(y) / (h - 1) - 1;
			float dist = sqrt(nx * nx + ny * ny);
			CvScalar g = cvScalar(0, 0, 0);
			if (isInTargetRange(dist)) cvSet2D(dst, y, x, g);
			else cvSet2D(dst, y, x, c);
		}
	}
	cvShowImage("prob20", dst);
}

void prob21(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			float nx = 2 * float(x) / w - 1; // [-1, 1]로 정규화
			float ny = 2 * float(y) / h - 1;
			float d = fabs(nx) + fabs(ny);  // 절대값의 합을 계산하여 패턴 생성
			float pattern = fmod(d, 0.2);   // 0.2 간격으로 패턴을 반복
			if (d <= 0.1) pattern = 0.2;    // 0.1~0.2 사이의 값으로 정규화
			CvScalar g = cvScalar(0, 0, 0); // 검정색 값
			if (pattern > 0.1 && pattern < 0.2) {
				cvSet2D(dst, y, x, g); // 패턴에 해당되면 원본 색상 적용
			}
			else {
				cvSet2D(dst, y, x, c); // 패턴에 해당되지 않으면 검정색 적용
			}
		}
	}
	cvShowImage("prob21", dst);
}

void prob22(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	cvSet(dst, cvScalar(0, 0, 0));
	float nx;
	float ny;
	float newX;
	float peak = w / 4;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			ny = (float)y / (h - 1) * CV_PI * 2;
			newX = x + peak * sin(ny);
			if (newX < 0) newX = 0;
			if (newX > w) newX = w - 1;
			cvSet2D(dst, y, newX, c);
		}
	}
	cvShowImage("prob22", dst);
}

void prob23(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	cvSet(dst, cvScalar(0, 0, 0));
	float nx;
	float ny;
	float newY;
	float peak = h / 4;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			nx = (float)x / (w - 1) * CV_PI * 2;
			newY = y + peak * sin(nx);
			if (newY < 0) newY = 0;
			if (newY >= h) newY = h - 1;
			cvSet2D(dst, newY, x, c);
		}
	}
	cvShowImage("prob23", dst);
}

void prob24(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;

	float amplitude = h / 10.0; // Amplitude is 1/10th of the image height
	float frequency = 2 * CV_PI / h; // Full wave across the image height

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			// Normalize the coordinates to the range [-1, 1]
			float ny = (2.0 * y / h) - 1;
			// Calculate the sine wave pattern
			float sineValue = amplitude * sin(frequency * y);

			// Decide on the pixel color based on the sine value
			CvScalar color;
			if (x < sineValue) {
				// Below the sine wave, we keep the original color
				color = cvGet2D(src, y, x);
			}
			else {
				// Above the sine wave, we set the color to black
				color = CV_RGB(0, 0, 0);
			}

			// Set the color in the destination image
			cvSet2D(dst, y, x, color);
		}
	}

	cvShowImage("prob24", dst);
}

void prob25(IplImage* src, IplImage* dst) {
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
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
	prob9(src[8], dst[8]);
	prob10(src[9], dst[9]);
	prob11(src[10], dst[10]);
	prob12(src[11], dst[11]);
	prob13(src[12], dst[12]);
	prob14(src[13], dst[13]);
	prob15(src[14], dst[14]);
	prob16(src[15], dst[15]);
	prob17(src[16], dst[16]);
	prob20(src[17], dst[17]);
	prob21(src[18], dst[18]);
	prob22(src[19], dst[19]);
	prob23(src[20], dst[20]);
	prob24(src[21], dst[21]);
	prob25(src[22], dst[22]);
	cvWaitKey();
}
