#include <opencv2/opencv.hpp>
#include <vector>
#include "MatrixInverse.h"
#include "vec.h"
#include "mat.h"

#define MAX_LEN 50
IplImage* dst = nullptr;
IplImage* src = nullptr;
int W = 500;
int H = 500;

vec3 pos[8] = {
    vec3(-0.5, -0.5, 0.5),
    vec3(-0.5, 0.5, 0.5),
    vec3(0.5, 0.5, 0.5),
    vec3(0.5, -0.5, 0.5),
    vec3(-0.5, -0.5, -0.5),
    vec3(-0.5, 0.5, -0.5),
    vec3(0.5, 0.5, -0.5),
    vec3(0.5, -0.5, -0.5)
};

struct rect {
    int ind[4];
    vec3 pos[4];
    vec3 nor;
};

rect setRect(int a, int b, int c, int d) {
    rect r;
    r.ind[0] = a;
    r.ind[1] = b;
    r.ind[2] = c;
    r.ind[3] = d;
    return r;
}

rect cube[6] = {
    setRect(1, 0, 3, 2),
    setRect(2, 3, 7, 6),
    setRect(3, 0, 4, 7),
    setRect(6, 5, 1, 2),
    setRect(6, 7, 4, 5),
    setRect(5, 4, 0, 1)
};

vec3 epos = vec3(1.5, 1.5, 1.5);
mat4 ModelMat;
mat4 ViewMat;
mat4 ProjMat;

void init() {
    ModelMat = mat4(1.0f);
    ViewMat = LookAt(epos, vec3(0, 0, 0), vec3(0, 1, 0));
    ProjMat = Perspective(45, W / (float)H, 0.1, 100);
}

void rotateModel(float rx, float ry, float rz) {
    ModelMat = RotateX(rx) * RotateY(ry) * RotateZ(rz) * ModelMat;
}

vec3 convert3Dto2D(vec3 in) {
    vec4 p = ProjMat * ViewMat * ModelMat * vec4(in);
    p.x /= p.w;
    p.y /= p.w;
    p.z /= p.w;
    p.x = (p.x + 1) / 2.0f * W;
    p.y = (-p.y + 1) / 2.0f * H;
    return vec3(p.x, p.y, p.z);
}

void updatePosAndNormal(rect* r, vec3 p[]) {
    for (int i = 0; i < 4; i++)
        r->pos[i] = convert3Dto2D(p[r->ind[i]]);
    vec3 a = normalize(r->pos[0] - r->pos[1]);
    vec3 b = normalize(r->pos[2] - r->pos[1]);
    r->nor = cross(a, b);
}

void computeHomography(CvPoint srcPts[4], CvPoint dstPts[4], float H[3][3]) {
    float A[8][8], b[8], invA[8][8], h[8];
    for (int i = 0; i < 4; i++) {
        int j = i * 2;
        A[j][0] = srcPts[i].x;
        A[j][1] = srcPts[i].y;
        A[j][2] = 1;
        A[j][3] = 0;
        A[j][4] = 0;
        A[j][5] = 0;
        A[j][6] = -srcPts[i].x * dstPts[i].x;
        A[j][7] = -srcPts[i].y * dstPts[i].x;
        b[j] = dstPts[i].x;

        A[j + 1][0] = 0;
        A[j + 1][1] = 0;
        A[j + 1][2] = 0;
        A[j + 1][3] = srcPts[i].x;
        A[j + 1][4] = srcPts[i].y;
        A[j + 1][5] = 1;
        A[j + 1][6] = -srcPts[i].x * dstPts[i].y;
        A[j + 1][7] = -srcPts[i].y * dstPts[i].y;
        b[j + 1] = dstPts[i].y;
    }

    if (!InverseMatrixGJ8(A, invA)) {
        printf("Matrix inversion failed!\n");
        return;
    }

    for (int i = 0; i < 8; i++) {
        h[i] = 0;
        for (int j = 0; j < 8; j++) {
            h[i] += invA[i][j] * b[j];
        }
    }

    H[0][0] = h[0]; H[0][1] = h[1]; H[0][2] = h[2];
    H[1][0] = h[3]; H[1][1] = h[4]; H[1][2] = h[5];
    H[2][0] = h[6]; H[2][1] = h[7]; H[2][2] = 1.0f;
}


void drawImage() {
    cvSet(dst, cvScalar(0, 0, 0)); // 화면을 검정색으로 초기화

    for (int i = 0; i < 6; i++) {
        updatePosAndNormal(&cube[i], pos);
        if (cube[i].nor.z < 0) continue; // 보이지 않는 면은 그리지 않음

        CvPoint srcPts[4], dstPts[4];
        for (int j = 0; j < 4; j++) {
            vec3 p = cube[i].pos[j];
            dstPts[j] = cvPoint(p.x, p.y);
        
        }

        // srcPts는 원본 이미지의 네 꼭지점을 나타냄
        srcPts[0] = cvPoint(0, 0);
        srcPts[1] = cvPoint(src->width - 1, 0);
        srcPts[2] = cvPoint(src->width - 1, src->height - 1);
        srcPts[3] = cvPoint(0, src->height - 1);

        // 호모그래피 계산
        float H[3][3];
        computeHomography(srcPts, dstPts, H);

        // 변환된 좌표로 이미지를 그리기
        for (int y = 0; y < src->height; y++) {
            for (int x = 0; x < src->width; x++) {
                float denom = H[2][0] * x + H[2][1] * y + H[2][2];
                float newX = (H[0][0] * x + H[0][1] * y + H[0][2]) / denom;
                float newY = (H[1][0] * x + H[1][1] * y + H[1][2]) / denom;

                if (newX >= 0 && newY >= 0 && newX < dst->width && newY < dst->height) {
                    CvScalar color = cvGet2D(src, y, x);
                    cvSet2D(dst,newY, newX, color);
                }
            }
        }
        for (int k = 0; k < 4; k++) {
            vec3 p1 = cube[i].pos[k];
            vec3 p2 = cube[i].pos[(k + 1) % 4];
            cvLine(dst, cvPoint(p1.x, p1.y), cvPoint(p2.x, p2.y), cvScalar(255, 255, 255), 3);
        }
    }

    cvShowImage("3D view", dst);
}


void myMouse(int event, int x, int y, int flags, void*) {
    static CvPoint prev = cvPoint(0, 0);
    if (event == CV_EVENT_LBUTTONDOWN)
        prev = cvPoint(x, y);
    if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) == CV_EVENT_FLAG_LBUTTON) {
        int dx = x - prev.x;
        int dy = y - prev.y;
        rotateModel(dy, dx, -dy);
        drawImage();
        prev = cvPoint(x, y);
    }
}

IplImage* readPicture() {
    char imagePath[MAX_LEN];
    IplImage* image;
    printf("=============================================\n");
    printf("Software Department, Sejong University\n");
    printf("Multimedia Programming Homework #5\n");
    printf("Image Warping - Homography Practice\n");
    printf("=============================================\n\n");
    printf("Input File Path:");
    gets_s(imagePath, MAX_LEN);
    image = cvLoadImage(imagePath);

    while (image == nullptr) {
        printf("File Not Found!\n");
        printf("Input File path:");
        gets_s(imagePath, MAX_LEN);
        image = cvLoadImage(imagePath);
    }
    return image;
}

int main() {
    dst = cvCreateImage(cvSize(W, H), 8, 3);
    src = readPicture();
    init();

    while (true) {
        rotateModel(0, 1, 0);
        drawImage();
        cvSetMouseCallback("3D view", myMouse);
        int key = cvWaitKey(1);
        if (key == ' ') key = cvWaitKey();
    }

    return 0;
}
