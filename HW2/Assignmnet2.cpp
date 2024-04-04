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
}; //������ ���� ����ü

float getDiff(CvScalar c1, CvScalar c2) { //������ ���̸� ���ϴ� �Լ�
	float diff = 0.0f;
	for (int i = 0; i < 3; i++) {
		diff += (c1.val[i] - c2.val[i]) * (c1.val[i] - c2.val[i]);
	}
	return diff;
}

// �׸��� ��θ� �Է¹޴� �Լ�
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
		src = cvLoadImage(str); //������ ���� ��� �ٽ� �Է¹���
	}
	return src;
}


void dividePicture(IplImage* src, IplImage* dst[], int w, int h) {
	for (int i = 0; i < 3; i++) { //�Է¹޴� �׸��� 3��� �Ͽ� ������ �迭�� ����
		dst[i] = cvCreateImage(cvSize(w, h), 8, 3);
		for (int y = 0; y < h; y++) { 
			for (int x = 0; x < w; x++) {
				CvScalar c = cvGet2D(src, y + i * h, x); //3����Ͽ� ����
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
			float err = 0.0f; //���� �ʱ�ȭ
			int ct = 0; //ī��Ʈ �ʱ�ȭ
			for (int y = h /15; y < h - h/15 ; y += ystep)
				for (int x = w/15; x < w - w/15 ; x += xstep) //��� �κи� ���ڴ�
				{
					int nx = x + u;
					int ny = y + v; //�̵���ų ��ǥ
					if (nx < 0 || nx > w - 1) continue;
					if (ny < 0 || ny > h - 1) continue;
					CvScalar c1 = cvGet2D(src1, y, x);
					CvScalar c2 = cvGet2D(src2, ny, nx);
					err += getDiff(c1, c2);
					ct++;
				}
			err /= ct; // ������ ��հ��� ����
			if (err < info->error) 
			{
				info->error = err;	//������ ���� ���� ���� ����
				info->dx = u; //������ ���� ���� ��ǥ�� ����
				info->dy = v; //������ ���� ���� ��ǥ�� ����
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
				int nx = x + info[i].dx; // ���Ľ�Ų ����� ���� ��Ȯ�� ��ǥ�� ����
				int ny = y + info[i].dy;
				if (nx<0 || nx>w - 1) continue; //������ ����� continue
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

	clock_t start, end; //�ð� ������ ���� ����
	double duration; //�ð� ������ ���� ����
	for (int i = 0; i < 3; i++)
	{
		info[i].dx = 0;
		info[i].dy = 0;
		info[i].error = FLT_MAX; //����ü �ʱ�ȭ
	}

	src = readPicture(); // ���� �Է��� �޴� �Լ�
	int w = src->width;
	int h = src->height / 3;

	dividePicture(src, dst, w, h); //������ 3��� �Ͽ� dst�迭�� �����ϴ� �Լ�
	out = cvCreateImage(cvSize(w, h), 8, 3); //����� ������ out�̹��� ����
	start = clock(); //�ð� ���� ����

	templateMatching(dst[0], dst[1], &info[1], w / 20, h / 20, 16); // dst[0]�� �����Ͽ� dst[1]�� �̵���Ű�� �Լ�
	templateMatching(dst[0], dst[1], &info[1], w / 50, h / 50, 4); // dst[0]�� �����Ͽ� dst[1]�� �̵���Ű�� �Լ�
	templateMatching(dst[0], dst[1], &info[1], 4, 4, 1); // dst[0]�� �����Ͽ� dst[1]�� �̵���Ű�� �Լ�

	templateMatching(dst[0], dst[2], &info[2], w / 20, h / 20, 16); // dst[0]�� �����Ͽ� dst[2]�� �̵���Ű�� �Լ�
	templateMatching(dst[0], dst[2], &info[2], w / 50, h / 50, 4); // dst[0]�� �����Ͽ� dst[2]�� �̵���Ű�� �Լ�
	templateMatching(dst[0], dst[2], &info[2], 4, 4, 1); // dst[0]�� �����Ͽ� dst[2]�� �̵���Ű�� �Լ�

	restoreColor(dst, out, info, w, h); //���ĵ� ����� ���� ���� �������� �����ϴ� �Լ�
	end = clock(); //�ð� ���� ����
	cvShowImage("src", out);
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("duration = %f\n", duration); //�ð� ���
	cvWaitKey();



}