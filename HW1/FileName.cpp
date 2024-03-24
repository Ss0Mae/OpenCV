#include <opencv2/opencv.hpp>

void prob1(IplImage* in, int width, int height) {
	for (int y = 0; y < height / 2; y++) {
		for (int x = 0; x < width; x++) {
			CvScalar c = cvGet2D(in, y, x);
			CvScalar temp = cvGet2D(in, height - y - 1, x); // y축 대칭점
			cvSet2D(in, height - y - 1, x, c);
			cvSet2D(in, y, x, temp);
		}
	}
	cvShowImage("prob1", in);
}

void prob2(IplImage* in, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width / 2; x++) {
			CvScalar c1 = cvGet2D(in, y, x);
			CvScalar temp1 = cvGet2D(in, y, (width / 2) + x - 1); // x축 대칭점
			cvSet2D(in, y, x, temp1);
			cvSet2D(in, y, (width / 2) + x - 1, c1);
		}
	}
	cvShowImage("prob2", in);
}

void prob3(IplImage* in, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float nx = float(x) / (width - 1) * 2 - 1;
			float ny = float(y) / (height - 1) * 2 - 1;
			CvScalar c = cvGet2D(in, y, x);
			CvScalar g;
			if (nx + ny >= 1 || nx - ny <= -1 || nx + ny <= -1 || nx - ny >= 1) { // 대각선 4개의 영역
				int bri = c.val[0] + c.val[1] + c.val[2];
				g = cvScalar(bri / 3, bri / 3, bri / 3);
				cvSet2D(in, y, x, g);
			}
		}
	}
	cvShowImage("prob3", in);
}

void prob4(IplImage* in, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float d;
			float nx = float(x) / (width - 1) * 2 - 1;
			float ny = float(y) / (height - 1) * 2 - 1;
			CvScalar c = cvGet2D(in, y, x);
			CvScalar g;
			d = sqrt(nx * nx + ny * ny);
			if (d > 1) { // 타원 외부 영역
				int bri = c.val[0] + c.val[1] + c.val[2];
				g = cvScalar(bri / 3, bri / 3, bri / 3);
				cvSet2D(in, y, x, g);
			}
		}
	}
	cvShowImage("prob4", in);

}

bool isInTargetRange(float dist) {
	// 정규화된 거리(dist)가 목표 범위 내에 있는지 확인
	const float ranges[][2] = { {0.1f, 0.2f}, {0.3f, 0.4f}, {0.5f, 0.6f}, {0.7f, 0.8f}, {0.9f, 1.0f}, {1.1f, 1.2f}, {1.3f, 1.4f} };
	for (auto& range : ranges) {
		if (dist >= range[0] && dist <= range[1]) return true; // 범위 내에 있으면 true 반환
	}
	return false;
}

void prob5(IplImage* in, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float d = 0.0;
			float nx = float(x) / (width - 1) * 2 - 1;
			float ny = float(y) / (height - 1) * 2 - 1;
			d = sqrt(nx * nx + ny * ny);
			CvScalar g = cvScalar(0, 0, 0);
			if (isInTargetRange(d)) cvSet2D(in, y, x, g); 
		}
	}
	cvShowImage("prob5", in);

}

void prob6(IplImage* in, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			CvScalar b = cvScalar(0, 0, 0);
			float nx = 2 * float(x) / (width - 1) - 1; 
			float ny = 2 * float(y) / (height - 1) - 1;

			int ix = (nx + 1) / 0.2; // nx 구간 계산
			int iy = (ny + 1) / 0.2; // ny 구간 계산 

			// 구간별 처리를 위한 간소화된 로직
			if ((ix % 2 == 0 && iy % 2 == 1) || (ix % 2 == 1 && iy % 2 == 0)) { 
				cvSet2D(in, y, x, b);
			}
		}

	}
	cvShowImage("prob6", in);

}

int main() {
	IplImage* img[6];
	for (int i = 0; i < 6; i++) {
		img[i] = cvLoadImage("C:\\Temp\\sejong_small.jpg");
		if (img[i] == nullptr) {
			printf("File Not Found!");
			exit(-1);
		}
	}
	CvSize size = cvGetSize(img[0]);
	prob1(img[0], size.width, size.height);
	prob2(img[1], size.width, size.height);
	prob3(img[2], size.width, size.height);
	prob4(img[3], size.width, size.height);
	prob5(img[4], size.width, size.height);
	prob6(img[5], size.width, size.height);
	cvWaitKey();
}
/*
/*if ((nx >= 0.0 && ny >= 0.0)) {
				if (nx >= 0.0 && nx <= 0.2) {
					if (ny >= 0.0 && ny <= 0.2) cvSet2D(in, y, x, b);
					if (ny >= 0.4 && ny <= 0.6) cvSet2D(in, y, x, b);
					if (ny >= 0.8 && ny <= 1.0) cvSet2D(in, y, x, b);
				}
				else if (nx >= 0.2 && nx <= 0.4) {
					if (ny >= 0.2 && ny <= 0.4) cvSet2D(in, y, x, b);
					if (ny >= 0.6 && ny <= 0.8) cvSet2D(in, y, x, b);
				}
				else if (nx >= 0.4 && nx <= 0.6) {
					if (ny >= 0.0 && ny <= 0.2) cvSet2D(in, y, x, b);
					if (ny >= 0.4 && ny <= 0.6) cvSet2D(in, y, x, b);
					if (ny >= 0.8 && ny <= 1.0) cvSet2D(in, y, x, b);
				}
				else if (nx >= 0.6 && nx <= 0.8) {
					if (ny >= 0.2 && ny <= 0.4) cvSet2D(in, y, x, b);
					if (ny >= 0.6 && ny <= 0.8) cvSet2D(in, y, x, b);
				}
				else {
					if (ny >= 0.0 && ny <= 0.2) cvSet2D(in, y, x, b);
					if (ny >= 0.4 && ny <= 0.6) cvSet2D(in, y, x, b);
					if (ny >= 0.8 && ny <= 1.0) cvSet2D(in, y, x, b);
				}

			}

			if (nx < 0 && ny > 0) {

				if (nx <= 0.0 && nx >= -0.2) {
					if (ny >= 0.2 && ny <= 0.4) cvSet2D(in, y, x, b);
					if (ny >= 0.6 && ny <= 0.8) cvSet2D(in, y, x, b);
				}
				else if (nx <= -0.2 && nx >= -0.4) {
					if (ny >= 0.0 && ny <= 0.2) cvSet2D(in, y, x, b);
					if (ny >= 0.4 && ny <= 0.6) cvSet2D(in, y, x, b);
					if (ny >= 0.8 && ny <= 1.0) cvSet2D(in, y, x, b);
				}

				else if (nx <= -0.4 && nx >= -0.6) {
					if (ny >= 0.2 && ny <= 0.4) cvSet2D(in, y, x, b);
					if (ny >= 0.6 && ny <= 0.8) cvSet2D(in, y, x, b);
				}
				else if (nx <= -0.6 && nx >= -0.8) {
					if (ny >= 0.0 && ny <= 0.2) cvSet2D(in, y, x, b);
					if (ny >= 0.4 && ny <= 0.6) cvSet2D(in, y, x, b);
					if (ny >= 0.8 && ny <= 1.0) cvSet2D(in, y, x, b);
				}
				else {
					if (ny >= 0.2 && ny <= 0.4) cvSet2D(in, y, x, b);
					if (ny >= 0.6 && ny <= 0.8) cvSet2D(in, y, x, b);
				}

			}

			if (nx < 0 && ny < 0) {

				if (nx <= 0.0 && nx >= -0.2) {
					if (ny <= 0.0 && ny >= -0.2) cvSet2D(in, y, x, b);
					if (ny <= -0.4 && ny >= -0.6) cvSet2D(in, y, x, b);
					if (ny <= -0.8 && ny >= -1.0) cvSet2D(in, y, x, b);
				}
				else if (nx <= -0.2 && nx >= -0.4) {
					if (ny <= -0.2 && ny >= -0.4) cvSet2D(in, y, x, b);
					if (ny <= -0.6 && ny >= -0.8) cvSet2D(in, y, x, b);
				}
				else if (nx <= -0.4 && nx >= -0.6) {
					if (ny <= 0.0 && ny >= -0.2) cvSet2D(in, y, x, b);
					if (ny <= -0.4 && ny >= -0.6) cvSet2D(in, y, x, b);
					if (ny <= -0.8 && ny >= -1.0) cvSet2D(in, y, x, b);
				}
				else if (nx <= -0.6 && nx >= -0.8) {
					if (ny <= -0.2 && ny >= -0.4) cvSet2D(in, y, x, b);
					else if (ny <= -0.6 && ny >= -0.8) cvSet2D(in, y, x, b);
				}
				else {
					if (ny <= 0.0 && ny >= -0.2) cvSet2D(in, y, x, b);
					if (ny <= -0.4 && ny >= -0.6) cvSet2D(in, y, x, b);
					if (ny <= -0.8 && ny >= -1.0) cvSet2D(in, y, x, b);
				}

			}

			if (nx > 0 && ny < 0) {

				if (nx >= 0.0 && nx <= 0.2) {
					if (ny <= -0.2 && ny >= -0.4) cvSet2D(in, y, x, b);
					if (ny <= -0.6 && ny >= -0.8) cvSet2D(in, y, x, b);
				}
				else if (nx >= 0.2 && nx <= 0.4) {
					if (ny <= 0.0 && ny >= -0.2) cvSet2D(in, y, x, b);
					if (ny <= -0.4 && ny >= -0.6) cvSet2D(in, y, x, b);
					if (ny <= -0.8 && ny >= -1.0) cvSet2D(in, y, x, b);
				}

				else if (nx >= 0.4 && nx <= 0.6) {
					if (ny <= -0.2 && ny >= -0.4) cvSet2D(in, y, x, b);
					if (ny <= -0.6 && ny >= -0.8) cvSet2D(in, y, x, b);
				}
				else if (nx >= 0.6 && nx <= 0.8) {
					if (ny <= 0.0 && ny >= -0.2) cvSet2D(in, y, x, b);
					if (ny <= -0.4 && ny >= -0.6) cvSet2D(in, y, x, b);
					if (ny <= -0.8 && ny >= -1.0) cvSet2D(in, y, x, b);
				}
				else {
					if (ny <= -0.2 && ny >= -0.4) cvSet2D(in, y, x, b);
					if (ny <= -0.6 && ny >= -0.8) cvSet2D(in, y, x, b);
				}

			}*/
