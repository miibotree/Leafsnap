#include "cv.h"
#include "highgui.h"
#include <math.h>

using namespace cv;

#define morph_size  10

Mat TopHat(CvSeq* contour, int height, int width)
{
	IplImage *img_origin = cvCreateImage(cvSize(width, height), 8, 1); 
	Mat img_tophat(height, width, CV_8UC1);

	CvScalar color = CV_RGB(255, 255, 255);   
	//cvDrawContours(img_origin, contour, color, color, 0, 2, CV_FILLED, cvPoint(0, 0)); 
	cvDrawContours(img_origin, contour, CV_RGB(255, 255, 255), CV_RGB(255, 255, 255), 2, CV_FILLED, 8, cvPoint(0, 0));
	Mat origin(img_origin);
	//设定内核
	Mat element = getStructuringElement( 
		MORPH_CROSS, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
	/// 运行指定形态学操作
	morphologyEx(origin, img_tophat, MORPH_TOPHAT, element);

	//显示tophat操作之后的图像
	//IplImage ipl_img(img_tophat);
    //cvShowImage("2.4 TopHat", &ipl_img); 
	
	cvReleaseImage(&img_origin);  
	return img_tophat;
}