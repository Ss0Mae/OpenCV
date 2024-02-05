#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
using namespace std;
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
		
		ed = cvPoint(x, y);
		cvLine(img, st, ed, color, 2);
		cvShowImage("img", img);
		
	}
}
int main()
{
	char path[50];
	int key = 0;
	
	cout << "Programming Assignment #4" << endl;
	cout << "For Multimedia Programming Class 2021" << endl;
	cout << "Department of Software, Sejong University" << endl << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "Left Mouse Button Dragging: Draw the horizon line" << endl;
	cout << "Right Mouse Button Dragging: Adjust the width of focusing region" << endl;
	cout << "Number 1 thru 5 keys: Adjust the strength of the defucusing" << endl << endl;
	cout << "ESC Key: Exit the program." << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "Input File Path:";
	
	
	cin >> path;

	img = cvLoadImage(path);
	buf = cvCreateImage(cvSize(img->width, img->height), 8, 3);

	cvShowImage("img", img);
	cvSetMouseCallback("img", myMouse);
	key = cvWaitKey();
	if (key == 'ESC')
		exit(-1);
	
}
//C:\\Temp\\sample.jpg