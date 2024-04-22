#include <opencv2/opencv.hpp>
#include <algorithm> // std::min, std::max�� ����ϱ� ���� �����մϴ�.

int main() {
    // �̹��� �ε�
    IplImage* src = cvLoadImage("C:\\temp\\sejong.jpg");
    CvSize size = cvGetSize(src);

    // ������� ����� ������ �̹���
    IplImage* dstH = cvCreateImage(size, IPL_DEPTH_8U, 3);
    IplImage* dstH2 = cvCreateImage(size, IPL_DEPTH_8U, 3);
    IplImage* dstV = cvCreateImage(size, IPL_DEPTH_8U, 3);
    IplImage* dstV2 = cvCreateImage(size, IPL_DEPTH_8U, 3);
    IplImage* dstFinal = cvCreateImage(size, IPL_DEPTH_8U, 3);

    // Ŀ�� ����
    float H1[3][3] = { {-1, -2, -1}, 
                        {0, 0, 0}, 
                        {1, 2, 1} };
    float H2[3][3] = { {1, 2, 1},
                        {0, 0, 0},
                        {-1, -2, -1} };
    float H3[3][3] = { {-1, 0, 1}, 
                        {-2, 0, 2}, 
                        {-1, 0, 1} };
    float H4[3][3] = { {1, 0, -1},
                       {2, 0, -2},
                       {1, 0, -1} };

    int w = size.width;
    int h = size.height;
    int K = 1; // Ŀ�� ������

    // ���� ���� �������
    for (int y = K; y < h - K; y++) {
        for (int x = K; x < w - K; x++) {
            CvScalar g = cvScalar(0, 0, 0);
            for (int v = -K; v <= K; v++) {
                for (int u = -K; u <= K; u++) {
                    CvScalar f = cvGet2D(src, y + v, x + u);
                    for (int k = 0; k < 3; k++) {
                        g.val[k] += H1[v + K][u + K] * f.val[k];
                    }
                }
            }
            //for (int c = 0; c < 3; c++) {
            //    g.val[c] = std::max(0.0, std::min(255.0, g.val[c] + 128)); // ����ȭ
            //}
            cvSet2D(dstH, y, x, g);
        }
    }

    // ���� ���� �������
    for (int y = K; y < h - K; y++) {
        for (int x = K; x < w - K; x++) {
            CvScalar g = cvScalar(0, 0, 0);
            for (int v = -K; v <= K; v++) {
                for (int u = -K; u <= K; u++) {
                    CvScalar f = cvGet2D(src, y + v, x + u);
                    for (int k = 0; k < 3; k++) {
                        g.val[k] += H2[v + K][u + K] * f.val[k];
                    }
                }
            }
            //for (int c = 0; c < 3; c++) {
            //    g.val[c] = std::max(0.0, std::min(255.0, g.val[c] + 128)); // ����ȭ
            //}
            cvSet2D(dstH2, y, x, g);
        }
    }

    for (int y = K; y < h - K; y++) {
        for (int x = K; x < w - K; x++) {
            CvScalar g = cvScalar(0, 0, 0);
            for (int v = -K; v <= K; v++) {
                for (int u = -K; u <= K; u++) {
                    CvScalar f = cvGet2D(src, y + v, x + u);
                    for (int k = 0; k < 3; k++) {
                        g.val[k] += H3[v + K][u + K] * f.val[k];
                    }
                }
            }
          
            cvSet2D(dstV, y, x, g);
        }
    }

    for (int y = K; y < h - K; y++) {
        for (int x = K; x < w - K; x++) {
            CvScalar g = cvScalar(0, 0, 0);
            for (int v = -K; v <= K; v++) {
                for (int u = -K; u <= K; u++) {
                    CvScalar f = cvGet2D(src, y + v, x + u);
                    for (int k = 0; k < 3; k++) {
                        g.val[k] += H4[v + K][u + K] * f.val[k];
                    }
                }
            }
            //for (int c = 0; c < 3; c++) {
            //    g.val[c] = std::max(0.0, std::min(255.0, g.val[c] + 128)); // ����ȭ
            //}
            cvSet2D(dstV2, y, x, g);
        }
    }

    // �� ������� ��� ��ġ��
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            CvScalar hPixel = cvGet2D(dstH, y, x);
            CvScalar h2Pixel = cvGet2D(dstH2, y, x);
            CvScalar vPixel = cvGet2D(dstV, y, x);
            CvScalar v2Pixel = cvGet2D(dstV2, y, x);
            CvScalar finalPixel;
            for (int i = 0; i < 3; i++) {
                // ����� ���밪�� ���� �������� ����
                finalPixel.val[i] = std::min(255.0, std::sqrt(hPixel.val[i] * hPixel.val[i] + h2Pixel.val[i] * h2Pixel.val[i] + vPixel.val[i] * vPixel.val[i] + v2Pixel.val[i] * v2Pixel.val[i]));
            }
            cvSet2D(dstFinal, y, x, finalPixel);
        }
    }

    // ��� ǥ��
    cvShowImage("Horizontal", dstH);
    cvShowImage("Vertical", dstV);
    cvShowImage("Final", dstFinal);
    cvWaitKey(0);

    // �޸� ����
    cvReleaseImage(&src);
    cvReleaseImage(&dstH);
    cvReleaseImage(&dstV);
    cvReleaseImage(&dstFinal);
    return 0;
}
