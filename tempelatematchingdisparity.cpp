#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include<math.h>

using namespace cv;
using namespace std;

int main()
{
	int disparity;
	Mat li = imread("left_image.jpg",0);
	Mat ri = imread("right_image.jpg",0);
	Mat output(li.rows,li.cols,CV_8UC1,Scalar(0));
	Mat result(li.rows,li.cols,CV_8UC1,Scalar(0));
	namedWindow("disparitymap",WINDOW_NORMAL);

	Mat temp(3,3,CV_8UC1,Scalar(0));

	for(int i=1;i<10;i++)
	{
		for(int j=1;j<10;j++)
		{
			for(int l=-1;l<=1;l++)
			{
				for(int k=-1;k<=1;k++)
				{
					temp.at<uchar>(i+l,j+k)=li.at<uchar>(i+l,j+k);
				}
			}

			matchTemplate( ri , temp, result, TM_SQDIFF);

			double minVal; double maxVal; Point minLoc; Point maxLoc;
  			Point matchLoc;
  			minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  			matchLoc=minLoc;
  			disparity = abs(matchLoc.x-li.cols);
  			output.at<uchar>(i,j)=(disparity/li.cols)*255;
		}
	}

	imshow("disparitymap",output);
	waitKey(0);
}	