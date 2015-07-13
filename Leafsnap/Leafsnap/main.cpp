#include"cv.h"  
#include"cxcore.h"  
#include"highgui.h" 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

IplImage* GRB2SV(char *filename);
Mat trainEM(Mat img_sv, int height, int width);
CvSeq* cutFPRegion(Mat M);
Mat TopHat(CvSeq* contour, int height, int width);
Mat CalCurvatures(CvSeq* contour, int height, int width);
vector<int> CompareLeaf(Mat test);

char LeafChinese[][100] = {"合欢花", "加拿大一枝黄花", "黑桦", "金樱子山楂", "银杏", "广玉兰", "杨树", "柳树", "枳树", "红松"};

int main(int argc, char **argv)  
{  
	//从10类每类10张图片中提取HoCS特征，存入当前目录下的HoCS_Features.txt文件中
	/*
	char img_path[20] = ".\\Database\\";
	ofstream f1("HoCS_Features.txt", ios::app);
	for(int i = 9; i <= 10; i++)
	{
		for(int j = 1; j <= 10; j++)
		{
			char name[256];
			memset(name, 0, 256);
			sprintf(name, "%s%d\\%d (%d).jpg", img_path, i, i, j);
			
			IplImage* img_sv = GRB2SV(name);

			Mat mtx(img_sv);
	
			//EM algorithm
			Mat img_binary = trainEM(img_sv, img_sv->height, img_sv->width);
	
			//cut false positive region
			CvSeq* contour = cutFPRegion(img_binary);
	
			//TopHat algorithm to remove the stem
			//Mat img_segmented = TopHat(contour, img_sv->height, img_sv->width);
	
			//extract the HoCS features
			Mat HoCS_Features = CalCurvatures(contour, img_sv->height, img_sv->width);
			//save each leaf's HoCS feature

			for(int i = 0; i < HoCS_Features.rows; i++)//row is always 1
				f1<<HoCS_Features.at<float>(i, 0)<<' ';
			f1<<endl;
			printf("the HoCS features of the picture %s has finished!\n", name);
			//compareLeaves

			//cvWaitKey(0);  
			//cvDestroyAllWindows(); 
			cvReleaseImage(&img_sv);
		}
	}
	*/
	//读取一张图片进行测试
	char name[256] = "加拿大一枝黄花.jpg";
	IplImage* img_sv = GRB2SV(name);
	Mat mtx(img_sv);
	//EM algorithm
	Mat img_binary = trainEM(img_sv, img_sv->height, img_sv->width);
	//cut false positive region
	CvSeq* contour = cutFPRegion(img_binary);
	//TopHat algorithm to remove the stem
	//Mat img_segmented = TopHat(contour, img_sv->height, img_sv->width);
	//extract the HoCS features
	Mat HoCS_Features_Test = CalCurvatures(contour, img_sv->height, img_sv->width);
	
	vector <int> res_list = CompareLeaf(HoCS_Features_Test);
	for(int i = 0; i < res_list.size(); i++)
	{
		int species = (res_list[i]) / 10;
		printf("第%d可能的物种是：%s\n", i, LeafChinese[species]);
	}
	printf("\n");
	return 0;
}  