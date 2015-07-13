#include "cv.h"
#include "highgui.h"
#include"cxcore.h"  
#include <vector>

using namespace cv;
using namespace std;

#define MAX_SCALE 26//最大的scale
#define PI 3.1415

//不同scale圆的面积
double CircleArea[MAX_SCALE];

void CalArea()
{
	for(int i = 0; i < MAX_SCALE - 1; i++)
		CircleArea[i] = PI * (i + 2)* (i + 2);
}

void NMattoOne(Mat &res , Mat hist , int n)
{
    int loc = 0;
    for(int i = hist.rows*n ; i < hist.rows*n + hist.rows ; i ++)
	{
        res.at<float>(i,0) = hist.at<float>(loc,0);
        loc++;
    }
}

/*
IplImage *DrawHistogram(Mat hist, float scaleX = 1, float scaleY = 1){  // 画直方图  
    float histMax = 0;  

    cvGetMinMaxHistValue(hist, 0 , &histMax, 0, 0);  // 取得直方图中的最值  
    IplImage *imgHist = cvCreateImage(cvSize(256 * scaleX, 64*scaleY), 8, 1);  
    cvZero(imgHist); //// 清空随机值  
    for(int i = 0; i < 255; i++)  
    {  
        float histValue = cvQueryHistValue_1D(hist, i); // 取得直方图中的i值  
        float nextValue = cvQueryHistValue_1D(hist, i+1);  
        int numPt = 5;  
        CvPoint pt[5];  
        pt[0] = cvPoint(i*scaleX, 64*scaleY);  
        pt[1] = cvPoint((i+1)*scaleX, 64*scaleY);  
        pt[2] = cvPoint((i+1)*scaleX, (1 -(nextValue/histMax))* 64 * scaleY);  
        pt[3] = cvPoint((i+1)*scaleX, (1 -(histValue/histMax))* 64 * scaleY);  
        pt[4] = cvPoint(i*scaleX, 64*scaleY);  
        cvFillConvexPoly(imgHist, pt, numPt, cvScalarAll(255));  
    }  
    return imgHist;  
}  
*/

//使用面积法来获得HoCS
Mat CalCurvatures(CvSeq* contour, int height, int width)
{
	Mat *allcontours = new Mat[MAX_SCALE];
	float curvature;//存放曲率结果
	CvPoint p;
	uchar *p1;
    uchar *p2;
	Mat res((MAX_SCALE-1)*21,1,CV_32FC1);
	int channels[] = {0};
    int histSize[] = {21};
    float hranges[] = { 0, 1 };
    Mat hist;
    const float* ranges[] = {hranges};
	
	CalArea();

	//根据轮廓画出图
	IplImage *img_origin = cvCreateImage(cvSize(width, height), 8, 1); 
	CvScalar color = CV_RGB(255, 255, 255);   
	cvDrawContours(img_origin, contour, CV_RGB(255, 255, 255), CV_RGB(255, 255, 255), 2, CV_FILLED, 8, cvPoint(0, 0));
	Mat img(img_origin);

	//既然CvSeq*不能转化为<vetor<Point>>,就遍历转化
	vector<CvPoint> LeafPoints;
	for(int i = 0; i < contour->total; i++)
	{
		CvPoint* tmp = (CvPoint*)cvGetSeqElem(contour, i);
		LeafPoints.push_back(*tmp);
	}

	for(int r = 2 ;r <= MAX_SCALE ; r++)//计算不同scale下面的曲率
	{
        Mat curvatureforscale(height, width, CV_32FC1, Scalar::all(-1));
        for(int i = 394 ; i < LeafPoints.size() ; i++)
		{
            int count = 0;
            Mat img2 = Mat::zeros(height, width, CV_8UC1);
            p.x = LeafPoints[i].x;
            p.y = LeafPoints[i].y;
            circle(img2, p, r, color, CV_FILLED, 8, 0);//画了个圆
			//test
			//IplImage img_test = img2;
			//cvShowImage("test circle", &img_test); 

            for(int row = (int)(p.y-r); row <= p.y + r && row < height && row >= 0; row++)
			{
                for(int col = (int)(p.x-r); col <= p.x + r && col < width && col >= 0; col++)
				{
                    if(img.at<uchar>(row, col) == 255 && img2.at<uchar>(row, col) == 255){
                        count++;//计算重叠部分的公共面积
                    }
                }
            }
            curvature = count / CircleArea[r-2];//使用面积法计算曲率
            curvatureforscale.at<float>((int)p.y,(int)p.x) = curvature;

            img2.release();
        }
        allcontours[r-2] = curvatureforscale;
    }

    for(int j = 0 ; j < MAX_SCALE-1 ; j ++){
        channels[0] = j;
		//第一个参数是二级指针，选择channel 就相当于选择scale
        calcHist(allcontours,MAX_SCALE-1,channels,Mat(),hist,1,histSize,ranges,true,false);
        normalize(hist,hist);
        //cout<<hist.rows<<" "<<hist.cols<<endl<<" "<<hist<<endl;
		NMattoOne(res,hist,j);
    }
	cvReleaseImage(&img_origin); 
    return  res;
}
