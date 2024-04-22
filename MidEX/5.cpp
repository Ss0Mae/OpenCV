#include <opencv2/opencv.hpp>

bool isInTarget(float dist) {
	const float ranges[][2] = { {0.1f, 0.2f}, {0.3f, 0.4f}, {0.5f, 0.6f}, {0.7f, 0.8f}, {0.9f, 1.0f}, {1.1f, 1.2f}, {1.3f, 1.4f} };
	for (auto& range : ranges) {
		if (dist >= range[0] && dist <= range[1]) return true; // 범위 내에 있으면 true 반환
	}
	return false;
}

int main() {
	IplImage *src = cvLoadImage("C:\\temp\\sejong.jpg");
	IplImage *dst = cvCreateImage(cvGetSize(src), 8, 3);
	CvSize size = cvGetSize(src);

	int w = size.width;
	int h = size.height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar c = cvGet2D(src, y, x);
			CvScalar b = cvScalar(0, 0, 0);
			float nx = 2 * (float)x / (w - 1);
			float ny = 2 * (float)y / (h - 1);
			cvSet2D(dst, y, x, c);
			if (y < h / 2 && x < w / 2) { // 
				float dist = sqrt(nx * nx + ny * ny);
				if (isInTarget(dist)) cvSet2D(dst, y, x, b);
			}
			else if (y >= h / 2 && x < w / 2) {
				float dist = sqrt(nx* nx + (2-ny) * (2-ny));
				if (isInTarget(dist)) cvSet2D(dst, y, x, b);
			}
			else if (y < h / 2 && x >= w / 2) {
				float dist = sqrt((2-nx) * (2-nx) + ny * ny);
				if (isInTarget(dist)) cvSet2D(dst, y, x, b);
			}
			else {
				float dist = sqrt((2-nx) * (2-nx) + (2-ny) * (2-ny));
				if (isInTarget(dist)) cvSet2D(dst, y, x, b);
			}
		}
	}
	cvShowImage("dst", dst);
	cvWaitKey();
}