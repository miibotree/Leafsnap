#include"cv.h"  
#include"cxcore.h"  
#include"highgui.h" 

using namespace std;
using namespace cv;

IplImage* GRB2SV(char *filename)  //opencv下使用mat来处理图像比较好，但是老版本使用了IplImage，需要手动分配和释放空间
{  
    IplImage *src, *image, *change, *H, *S, *V, *two, *Zero;  
    //创建图像显示窗口  

    src = cvLoadImage(filename);//载入图像  
	CvSize sz;  
    double scale = 0.2;  
	sz.width = src->width*scale;  
    sz.height = src->height*scale;  
    image = cvCreateImage(sz,src->depth,src->nChannels);  
    cvResize(src, image, CV_INTER_CUBIC);  

    //分配图像空间  
    change=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,3);    
    H=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);  
    S=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);  
    V=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);  
    two=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,3);  
    Zero=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);  
  
    cvZero(Zero);//在将两个通道合并是，不能没有第三个通道，而是将该通道设为空白，即全0   
  
    cvCvtColor(image,change,CV_RGB2HSV);  //将RGB色系转换为HSV色系  
    
    cvSplit(change,H,S,V,0);//分离多通道  
  
    cvMerge(Zero,S,V,0,two);  
    cvCvtColor(two,change,CV_HSV2RGB);//cvShowImage是按照RGB色彩方式显示图像的，故要通过RGB色系展示对HSV色系的更改效果  
    //显示vs空间下的图
	//cvNamedWindow("2.1 RGB->SV",CV_WINDOW_AUTOSIZE); 
	//cvShowImage("2.1 RGB->SV",change);   
  
    //cvDestroyAllWindows();  
    cvReleaseImage(&image);  
	cvReleaseImage(&H);  
	cvReleaseImage(&S);  
	cvReleaseImage(&V);  
	cvReleaseImage(&two);  
	cvReleaseImage(&Zero);  
    //cvReleaseImage(&change);  

    return change;  
}  