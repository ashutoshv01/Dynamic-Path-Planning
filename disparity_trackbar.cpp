#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include<math.h>

using namespace cv;
using namespace std;

int main()
{
	Mat li = imread("left_image.jpg",0);
	Mat ri = imread("right_image.jpg",0);

	Mat output(li.rows,li.cols,CV_8UC1,Scalar(0));
	namedWindow("disparitymap",WINDOW_NORMAL);

	
	int sum,diff,match,disparity,min,intensity;

	int th=1;

	//createTrackbar("size","disparitymap",&th,5);
	//while(1)
	//{
	Mat temp((2*th)+1,(2*th)+1,CV_8UC1,Scalar(0));
	for(int i=th;i<(li.rows)-(th);i++)
	{
		for(int j=th;j<(li.cols)-(th);j++)
		{
			for(int l=-th;l<=th;l++)
			{
				for(int k=-th;k<=th;k++)
				{
					temp.at<uchar>(th+l,th+k)=li.at<uchar>(i+l,j+k);
				}
			}
			min=10000,match=10000,diff=10000;
			for(int h=1;h<ri.cols;h++)
			{
				sum=0;
				for(int p=-th;p<=th;p++)
				{
					for(int q=-th;q<=th;q++)
					{
						diff=abs(temp.at<uchar>(th+p,th+q)-ri.at<uchar>(i+p,h+q));
						sum = sum+diff;
						if(sum<min)
						{
							match=h;
							min =sum;
						}
					}
				}
			}
			disparity=abs(match-j);
			intensity= ((float)disparity/li.cols)*255;
			output.at<uchar>(i,j)= intensity;
		}
	}
	imshow("disparitymap",output);
	waitKey(0);
	//}

}