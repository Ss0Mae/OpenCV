#include <opencv2/opencv.hpp>

// on/off switch
// int 4byte --> 32 bit
// 00000000 00000000 00000000 0 0 0  0  0 0 0 0
//								  32 16 8 4 2 1
// event 0 : CV_EVENT_MOUSEMOVE
// event 1 : CV_EVENT_LBUTTONDOWN
// event 2 : CV_EVENT_RBUTTONDOWN
// event 3 : CV_EVENT_MBUTTONDOWN
// event 4 : CV_EVENT_LBUTTONUP
// flags 1: CV_EVENT_FLAG_LBUTTON
// flags 2: CV_EVENT_FLAG_RBUTTON
// flags 4: CV_EVENT_FLAG_MBUTTON
// flags 8: CV_EVENT_FLAG_CTRLKEY

IplImage* img;
IplImage* pal;
IplImage* buf;
CvScalar color = cvScalar(255, 0, 0);
CvPoint st = cvPoint(0, 0);
CvPoint ed = cvPoint(0, 0);

// 1. implementation
void myMouse(int event, int x, int y, int flags, void* param)
{

	if (event == CV_EVENT_LBUTTONDOWN || event == CV_EVENT_RBUTTONDOWN)
	{
		st = cvPoint(x, y);
	}
	if (event == CV_EVENT_MOUSEMOVE && flags == CV_EVENT_FLAG_LBUTTON) //선그리가ㅣ
	{
		//cvSet2D(img, y, x, color);
		ed = cvPoint(x, y);
		cvLine(img, st, ed, color, 2);
		cvCircle(img, st, 2, color, 2);
		cvShowImage("img", img);
		st = ed;
	}
	if (event == CV_EVENT_MOUSEMOVE && flags == CV_EVENT_FLAG_RBUTTON)
	{
		//cvSet(buf, cvScalar(255, 255, 255));
		cvCopy(img, buf);
		ed = cvPoint(x, y);
		float r = sqrt((st.x - ed.x) * (st.x - ed.x) + (st.y - ed.y) * (st.y - ed.y));
		cvCircle(buf, st, r, color, 2);
		cvShowImage("img", buf);
	}
	if (event == CV_EVENT_RBUTTONUP)
	{
		//cvSet2D(img, y, x, color);
		ed = cvPoint(x, y);
		//cvRectangle(img, st, ed, color, 2);

		float r = sqrt((st.x - ed.x) * (st.x - ed.x) + (st.y - ed.y) * (st.y - ed.y));
		cvCircle(img, st, r, color, 2);
		cvShowImage("img", img);
	}
}



int main()
{
	img = cvCreateImage(cvSize(500, 500), 8, 3);
	buf = cvCreateImage(cvSize(500, 500), 8, 3);
	pal = cvLoadImage("c:\\Temp\\palette.bmp");

	cvSet(img, cvScalar(255, 255, 255));
	cvSet(buf, cvScalar(255, 255, 255));

	cvRectangle(img, cvPoint(100, 100), cvPoint(300, 300), cvScalar(255, 0, 0), -1);
	cvCircle(img, cvPoint(200, 200), 100, cvScalar(0, 255, 0), -1);
	cvLine(img, cvPoint(100, 100), cvPoint(300, 300), cvScalar(0, 0, 255), 3);


	cvShowImage("img", img);
	cvShowImage("pal", pal);
	cvSetMouseCallback("img", myMouse);
	cvSetMouseCallback("pal", myMouse2);
	cvWaitKey();

	return 0;
}