#include"cv.h"  
#include"cxcore.h"  
#include"highgui.h" 

using namespace std;

int GRB2SV(char *filename)  
{  
    IplImage *image,*change,*H,*S,*V,*two,*Zero;  
    //创建图像显示窗口  
    cvNamedWindow("image",CV_WINDOW_AUTOSIZE);   
    cvNamedWindow("VS",CV_WINDOW_AUTOSIZE);  
    cvNamedWindow("Zero",CV_WINDOW_AUTOSIZE);  
  
    image=cvLoadImage(filename);//载入图像  
  
    //分配图像空间  
    change=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,3);    
    H=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);  
    S=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);  
    V=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);  
    two=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,3);  
    Zero=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);  
  
    cvZero(Zero);//在将两个通道合并是，不能没有第三个通道，而是将该通道设为空白，即全0  
  
    cout<<"IPL_DEPTH_8U = "<<IPL_DEPTH_8U<<endl;  
    cout<<"CV_RGB2HSV = "<<CV_RGB2HSV<<endl;  
    cout<<"CV_HSV2RGB = "<<CV_HSV2RGB<<endl;  
  
    cvCvtColor(image,change,CV_RGB2HSV);  //将RGB色系转换为HSV色系  
          
    cvSplit(change,H,S,V,0);//分离多通道  
  
    //显示RGB图单通道图  
    cvShowImage("image",image);  
  
    cvMerge(Zero,S,V,0,two);  
    cvCvtColor(two,change,CV_HSV2RGB);//cvShowImage是按照RGB色彩方式显示图像的，故要通过RGB色系展示对HSV色系的更改效果  
    cvShowImage("VS",change);   
  
    cvWaitKey(0);  
  
    cvDestroyAllWindows();  
    cvReleaseImage(&image);  
    cvReleaseImage(&change);  
 
    system("pause");  
    return 1;  
}  