#include "cv.h"
#include "highgui.h"
#include <math.h>

using namespace cv;

CvSeq* cutFPRegion(Mat M)
{
	//先进行轮廓提取,只提取出最外层轮廓
	IplImage src(M);
	IplImage *dsw = cvCreateImage(cvSize(M.cols,M.rows), 8, 1); 
	IplImage *dst = cvCreateImage(cvSize(M.cols,M.rows), 8, 3); 
	
	CvMemStorage *storage = cvCreateMemStorage(0);  
	CvSeq *first_contour = NULL;   

	cvThreshold(&src, dsw, 100, 255, CV_THRESH_BINARY);
	//查找轮廓的函数结果存储在storage当中
	cvFindContours(dsw, storage, &first_contour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);    
   
	//外轮廓也可能有多个，所以我们需要选取出最主要的，也就是最大的外轮廓
	//这一步就是cut false positive,虽然没有在图上体现出来，但是我们只要获得了最大轮廓就相当于做了这一步
	//因为后面的步骤只用到了轮廓这个特征点集
	CvSeq *max_contour;//该变量保存了最大的那个轮廓 
	double max_area = 0;
	double area = 0;
    int cnt = 0;    

    for(; first_contour != 0; first_contour = first_contour->h_next)    
    {    
		area = cvContourArea(first_contour);
		if(area > max_area)
		{
			max_area = area;
			max_contour = first_contour;
		} 
		cnt++;
    }    
  
    //printf("the num of contours : %d\n", cnt);      
    
	cvZero(dst);  
	CvScalar color = CV_RGB(255, 255, 255);
	max_contour->h_next = 0;//为了防止把后面的轮廓也画上去
	//画出来看看效果
    //cvDrawContours(dst, max_contour, color, color, 0, 2, CV_FILLED, cvPoint(0, 0)); 
	cvDrawContours(dst, max_contour, CV_RGB(255, 255, 255), CV_RGB(255, 255, 255), 2, CV_FILLED, 8, cvPoint(0, 0));
    //CvRect rect = cvBoundingRect(first_contour,0);  
    //cvRectangle(dst, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height),CV_RGB(255, 0, 0), 1, 8, 0); 

    //cvNamedWindow( "2.3 RemoveFalsePositive", 1 );    
    //cvShowImage( "2.3 RemoveFalsePositive", dst );    
	cvReleaseImage(&dsw);  
	cvReleaseImage(&dst);  
	cvReleaseMemStorage(&storage);  
	return max_contour;
}