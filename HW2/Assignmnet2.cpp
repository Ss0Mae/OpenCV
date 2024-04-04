#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#define MAX_LEN 50

struct FilterSort 
{
	int dx;
	int dy;
	float error;
}; //정렬을 위한 구조체

float getDiff(CvScalar c1, CvScalar c2) { //색상의 차이를 구하는 함수
	float diff = 0.0f;
	for (int i = 0; i < 3; i++) {
		diff += (c1.val[i] - c2.val[i]) * (c1.val[i] - c2.val[i]);
	}
	return diff;
}

// 그림의 경로를 입력받는 함수
IplImage* readPicture() {
	char str[MAX_LEN];
	IplImage* src;

	printf("Input File Name:");
	gets_s(str, MAX_LEN);
	src = cvLoadImage(str);

	while (src == nullptr) {
		printf("File Not Found!\n");
		printf("Input File Name:");
		gets_s(str, MAX_LEN);
		src = cvLoadImage(str); //파일이 없을 경우 다시 입력받음
	}
	return src;
}


void dividePicture(IplImage* src, IplImage* dst[], int w, int h) {
	for (int i = 0; i < 3; i++) { //입력받는 그림을 3등분 하여 각각의 배열에 저장
		dst[i] = cvCreateImage(cvSize(w, h), 8, 3);
		for (int y = 0; y < h; y++) { 
			for (int x = 0; x < w; x++) {
				CvScalar c = cvGet2D(src, y + i * h, x); //3등분하여 저장
				cvSet2D(dst[i], y, x, c);
			}
		}
	}
}

void templateMatching(IplImage* src1, IplImage* src2, FilterSort* info, int du, int dv, int offset)
{
	int w = src1->width;
	int h = src1->height;

	int u_st = info->dx - du;
	int u_ed = info->dx + du;

	int v_st = info->dy - dv;
	int v_ed = info->dy + dv;

	int xstep = w / 100;
	int ystep = h / 100;

	printf("###Debuging Start###\n");
	for (int u = u_st; u < u_ed; u += offset)
		for (int v = v_st; v < v_ed; v += offset)
		{
			//printf("%d %d\n", u, v);
			float err = 0.0f; //에러 초기화
			int ct = 0; //카운트 초기화
			for (int y = h /15; y < h - h/15 ; y += ystep)
				for (int x = w/15; x < w - w/15 ; x += xstep) //가운데 부분만 보겠다
				{
					int nx = x + u;
					int ny = y + v; //이동시킬 좌표
					if (nx < 0 || nx > w - 1) continue;
					if (ny < 0 || ny > h - 1) continue;
					CvScalar c1 = cvGet2D(src1, y, x);
					CvScalar c2 = cvGet2D(src2, ny, nx);
					err += getDiff(c1, c2);
					ct++;
				}
			err /= ct; // 차이의 평균값을 구함
			if (err < info->error) 
			{
				info->error = err;	//에러가 가장 작은 값을 저장
				info->dx = u; //에러가 가장 작은 좌표를 저장
				info->dy = v; //에러가 가장 작은 좌표를 저장
				printf("Error Renewal Alert= %f \n", err);
			}
		}
	printf("###Debuging End###\n");
}


void restoreColor(IplImage* dst[], IplImage* out, FilterSort* info, int w, int h) {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++)
		{
			CvScalar g = cvScalar(0, 0, 0);
			for (int i = 0; i < 3; i++) {
				int nx = x + info[i].dx; // 정렬시킨 결과를 토대로 정확한 좌표로 보정
				int ny = y + info[i].dy;
				if (nx<0 || nx>w - 1) continue; //범위를 벗어나면 continue
				if (ny<0 || ny>h - 1) continue;
				CvScalar f = cvGet2D(dst[i], ny, nx);
				g.val[i] = f.val[i];
			}
			cvSet2D(out, y, x, g);
		}
	}
}

int main() {
	IplImage* src;
	IplImage* dst[3];
	IplImage* out;
	FilterSort info[3]; 

	clock_t start, end; //시간 측정을 위한 변수
	double duration; //시간 측정을 위한 변수
	for (int i = 0; i < 3; i++)
	{
		info[i].dx = 0;
		info[i].dy = 0;
		info[i].error = FLT_MAX; //구조체 초기화
	}

	src = readPicture(); // 파일 입력을 받는 함수
	int w = src->width;
	int h = src->height / 3;

	dividePicture(src, dst, w, h); //사진을 3등분 하여 dst배열에 저장하는 함수
	out = cvCreateImage(cvSize(w, h), 8, 3); //결과를 저장할 out이미지 생성
	start = clock(); //시간 측정 시작

	templateMatching(dst[0], dst[1], &info[1], w / 20, h / 20, 16); // dst[0]을 고정하여 dst[1]을 이동시키는 함수
	templateMatching(dst[0], dst[1], &info[1], w / 50, h / 50, 4); // dst[0]을 고정하여 dst[1]을 이동시키는 함수
	templateMatching(dst[0], dst[1], &info[1], 4, 4, 1); // dst[0]을 고정하여 dst[1]을 이동시키는 함수

	templateMatching(dst[0], dst[2], &info[2], w / 20, h / 20, 16); // dst[0]을 고정하여 dst[2]을 이동시키는 함수
	templateMatching(dst[0], dst[2], &info[2], w / 50, h / 50, 4); // dst[0]을 고정하여 dst[2]을 이동시키는 함수
	templateMatching(dst[0], dst[2], &info[2], 4, 4, 1); // dst[0]을 고정하여 dst[2]을 이동시키는 함수

	restoreColor(dst, out, info, w, h); //정렬된 결과를 토대로 원래 색상으로 복원하는 함수
	end = clock(); //시간 측정 종료
	cvShowImage("src", out);
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("duration = %f\n", duration); //시간 출력
	cvWaitKey();



}