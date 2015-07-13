#include"cv.h"  
#include"cxcore.h"  
#include"highgui.h" 
#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/legacy.hpp>

using namespace std;
using namespace cv;

Mat trainEM(Mat img_sv, int height, int width)
{
	Mat samples;
	Mat img_binary(height, width, CV_8UC1);
	Mat labels;
	Mat probs;
	CvEM em;
	CvEMParams em_params;

	//给EM算法赋值，均值，方差和权值采用kmeans初步聚类得到
    em_params.means = NULL;
    em_params.covs = NULL;
    em_params.weights = NULL;
    em_params.nclusters = 2;
    em_params.start_step = CvEM::START_AUTO_STEP;
    em_params.cov_mat_type = CvEM::COV_MAT_SPHERICAL;
    //达到最大迭代次数或者迭代误差小到一定值，应该有系统默认的值
    em_params.term_crit.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;

	samples = Mat(height * width, 2, CV_64FC1); 
	int num = 0;
	
	//提取img_sv中第二通道的S分量和第三通道的V分量，分别作为两个行向量，存储在samples当中
	for(int i = 0; i < img_sv.rows; i++)
	{
		for(int j = 0 ; j < img_sv.cols; j++)
		{
			samples.at<double>(num, 0) = img_sv.at<Vec3b>(i, j)[1];//S分量
			samples.at<double>(num, 1) = img_sv.at<Vec3b>(i, j)[2];//V分量
			num++;
		}
	}
	//EM算法训练过程
    em.train( samples, Mat(), em_params, &labels);
	
	//我们再依据label得出相应的二值化图像
	num = 0;
	for(int i = 0; i < img_sv.rows; i++)
	{
		for(int j = 0 ; j < img_sv.cols; j++)
		{
			img_binary.at<uchar>(i, j) = labels.at<int>(num, 0);
			num++;
		}
	}

	
	//这里为了显示效果，我们把1变成255
	for(int i = 0; i < img_binary.rows; i++)
	{
		for(int j = 0 ; j < img_binary.cols; j++)
		{
			if(img_binary.at<uchar>(i, j) == 1)
				img_binary.at<uchar>(i, j) = 255;
		}
	}

	//IplImage ipl_img(img_binary);
    //cvShowImage("2.2 Segmentation_EM", &ipl_img); 
	//imshow("after segmentation", img_binary);
	return img_binary; 
}