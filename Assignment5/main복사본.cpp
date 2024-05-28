#include <opencv2/opencv.hpp>
#include "MatrixInverse.h"
#include "vec.h"
#include "mat.h"

IplImage* dst = nullptr;
int W = 500;										// ��� �̹��� ���� ũ��
int H = 500;										// ��� �̹��� ���� ũ��

vec3 pos[8] = {										// ����ü�� �����ϴ� 8���� ������ 3���� ��ǥ
		vec3(-0.5, -0.5,  0.5),
		vec3(-0.5,  0.5,  0.5),
		vec3(0.5,  0.5,  0.5),
		vec3(0.5, -0.5,  0.5),
		vec3(-0.5, -0.5, -0.5),
		vec3(-0.5,  0.5, -0.5),
		vec3(0.5,  0.5, -0.5),
		vec3(0.5, -0.5, -0.5) };



struct rect											// �簢�� �� ��
{
	int ind[4];										// �������� �ε���
	vec3 pos[4];									// �������� ȭ�� ���������� 3���� ��ġ
	vec3 nor;										// ����(normal) ���� ���� (= ���� ���ϴ� ����)
};

rect setRect(int a, int b, int c, int d)			// �簢�� ������ ä���ִ� �Լ�(�ٷ� �Ʒ� cube���ǿ� ���)
{
	rect r;
	r.ind[0] = a;
	r.ind[1] = b;
	r.ind[2] = c;
	r.ind[3] = d;
	return r;
}

rect cube[6] = { setRect(1, 0, 3, 2),				// �簢�� 6���� ������ ����ü�� ����
				 setRect(2, 3, 7, 6),
				 setRect(3, 0, 4, 7),
				 setRect(6, 5, 1, 2),
				 setRect(6, 7, 4, 5),
				 setRect(5, 4, 0, 1) };

vec3 epos = vec3(1.5, 1.5, 1.5);					// ī�޶�(������ 3����) ��ġ
mat4 ModelMat;										// �𵨿� ������ �ִ� ���� ���
mat4 ViewMat;										// ī�޶� ������ �����ִ� ���� ���
mat4 ProjMat;										// ȭ��� ��ġ�� �������ִ� ���� ���

void init()											// �ʱ�ȭ
{	
	ModelMat = mat4(1.0f);
	ViewMat = LookAt(epos, vec3(0, 0, 0), vec3(0, 1, 0));  
													// ī�޶� ��ġ(epos)���� (0,0,0)�� �ٶ󺸴� ī�޶� ����			
	ProjMat = Perspective(45, W / (float)H, 0.1, 100);	
													// 45���� �þ߰��� ���� ���� ��ȯ (���ðŸ� 0.1~100)
}

void rotateModel(float rx, float ry, float rz)		// ����ü �𵨿� ȸ���� �����ϴ� �Լ�
{
	ModelMat = RotateX(rx) * RotateY(ry) * RotateZ(rz) * ModelMat;
}

vec3 convert3Dto2D(vec3 in)							// 3���� ��ǥ�� ȭ�鿡 ������ 2����+���̰�(z) ��ǥ�� ��ȯ
{
	vec4 p = ProjMat * ViewMat * ModelMat * vec4(in);
	p.x /= p.w;
	p.y /= p.w;
	p.z /= p.w;
	p.x = (p.x + 1) / 2.0f * W;
	p.y = (-p.y + 1) / 2.0f * H;
	return vec3(p.x, p.y, p.z);
}

void updatePosAndNormal(rect* r, vec3 p[])			// ����ü�� ȸ���� ���� �� ���� 3���� ��ǥ �� ���� ���� ���� ������Ʈ
{
	for (int i = 0; i < 4; i++)
		r->pos[i] = convert3Dto2D(p[r->ind[i]]);
	vec3 a = normalize(r->pos[0] - r->pos[1]);
	vec3 b = normalize(r->pos[2] - r->pos[1]);
	r->nor = cross(a, b);
}

void drawImage()									// �׸��� �׸��� (�� ���� �׵θ��� �������� �׸�)
{
	cvSet(dst, cvScalar(0, 0, 0));
	for (int i = 0; i < 6; i++)
	{
		updatePosAndNormal(&cube[i], pos);
		if (cube[i].nor.z < 0) continue;			// ������ �ʴ� �簢���� ����, ���̴� �簢���� �׸���	
		for (int j = 0; j < 4; j++)
		{
			vec3 p1 = cube[i].pos[j];
			vec3 p2 = cube[i].pos[(j + 1) % 4];

			cvLine(dst, cvPoint(p1.x, p1.y), cvPoint(p2.x, p2.y), cvScalar(255,255,255), 3);
		}
	}
	cvShowImage("3D view", dst);
}

void myMouse(int event, int x, int y, int flags, void*)
{
	static CvPoint prev = cvPoint(0, 0);
	if (event == CV_EVENT_LBUTTONDOWN)
		prev = cvPoint(x, y);
	if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) == CV_EVENT_FLAG_LBUTTON)
	{
		int dx = x - prev.x;
		int dy = y - prev.y;
		rotateModel(dy, dx, -dy);					// ���콺 ���ۿ� ���� ���� ȸ����
		drawImage();
		prev = cvPoint(x, y);
	}
}

int main()
{
	dst = cvCreateImage(cvSize(W, H), 8, 3);
	init();

	while (true)
	{
		rotateModel(0, 1, 0);
		drawImage();
		cvSetMouseCallback("3D view", myMouse);
		int key = cvWaitKey(1);
		if (key == ' ') key = cvWaitKey();
	}

	return 0;
}