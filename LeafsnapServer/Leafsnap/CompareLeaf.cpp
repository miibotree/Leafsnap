#include"cv.h"  
#include"cxcore.h"  
#include"highgui.h" 
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace cv;

vector<Mat> getData(){
    double line;
    ifstream f(".\\HoCS_Features.txt");
    int len = 21*25;
    Mat res(len,1,CV_32FC1);
    int i = 0;
    int loc = 0;
    vector<Mat> result;
    while(f>>line){

        res.at<float>(i,0) = line;
        i++;
        if(i == len){
            result.push_back(res);
            i=0;
            //id[loc] = loc;
            loc ++;
            res = Mat(len,1,CV_32FC1);
        }
    }
    return result;
}

void bubble_sort(double unsorted[],int id[],int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = i; j < len; j++)
        {
            if (unsorted[i] < unsorted[j])
            {
                double temp = unsorted[i];
                unsorted[i] = unsorted[j];
                unsorted[j] = temp;
                int t = id[i];
                id[i] = id[j];
                id[j] = t;
            }
        }
    }
}

vector<int> CompareLeaf(Mat test)
{
	vector<Mat> data = getData();
    double *res = new double[data.size()];
    for(int i = 0 ; i < data.size() ; i ++){
        res[i] = compareHist(test,data[i],CV_COMP_CORREL);
		if(res[i] == 1)
			res[i] = 0;
        cout<<"res "<<i<<" :"<<res[i]<<endl;
    }
    int *id = new int[data.size()];
    for(int j = 0 ; j < data.size() ; j ++){
        id[j] = j;
    }
    bubble_sort(res,id,data.size());
    vector<int> result ;

    for(int p = 0 ; p < 5 ; p++){
        result.push_back(id[p]);
    }
	delete[] res;
	delete[] id;
    return result;
}