#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include<math.h>

using namespace cv;
using namespace std;

int isValid(int x,int y,int rows,int cols)
{
	if(x<0|| y<0|| x>rows|| y>cols)
	{
		return 0;
	}
	return 1;
}

float dist(int ii, int ij, int fi, int fj)
{
	return sqrt( (ii-fi)*(ii-fi)+(ij-fj)*(ij-fj) );
}

int main()
{
	Mat map = imread("Test1.png",1);
	namedWindow("A*",WINDOW_NORMAL);
	int sourcei,sourcej,desti,destj,currenti,currentj,nexti,nextj;
	float distance, min;

	for(int i=0;i<map.rows;i++)
	{
		for(int j=0;j<map.cols;j++)
		{
			if(map.at<Vec3b>(i,j)[0]==0 && map.at<Vec3b>(i,j)[1]==255 && map.at<Vec3b>(i,j)[2]==0)
			{
				sourcei = i;
				sourcej = j;
				break;
			}
		}
	}

	for(int i=0;i<map.rows;i++)
	{
		for(int j=0;j<map.cols;j++)
		{
			if(map.at<Vec3b>(i,j)[0]==0 && map.at<Vec3b>(i,j)[1]==0 && map.at<Vec3b>(i,j)[2]>0)
			{
				desti = i;
				destj = j;
				break;
			}
		}
	}
	currenti = sourcei;
	currentj = sourcej;
	nexti = currenti;
	nextj = currentj;
	while(nexti!=desti || nextj!=destj)
	{
		min = 100000.0;
		for(int k = -1;k<=1;k++)
		{
			for(int l = -1;l<=1;l++)
			{
				if(isValid(currenti+k,currentj+l,map.rows,map.cols)==1)
				{
					if( (map.at<Vec3b>(currenti+k,currentj+l)[0]==0 && map.at<Vec3b>(currenti+k,currentj+l)[1]==0 && map.at<Vec3b>(currenti+k,currentj+l)[2]==0) || (map.at<Vec3b>(currenti+k,currentj+l)[0]==0 && map.at<Vec3b>(currenti+k,currentj+l)[1]==255 && map.at<Vec3b>(currenti+k,currentj+l)[2]==0) || (map.at<Vec3b>(currenti+k,currentj+l)[2]>map.at<Vec3b>(currenti+k,currentj+l)[1]&& map.at<Vec3b>(currenti+k,currentj+l)[2]>map.at<Vec3b>(currenti+k,currentj+l)[0])  )
					{
						distance = dist(currenti+k,currentj+l,desti,destj);
						if(distance<min)
						{
							min = distance;
							nexti = currenti+k;
							nextj = currentj+l;
						}
					}
				}
			}
		}
		
		currenti = nexti;
		currentj = nextj;

		map.at<Vec3b>(currenti,currentj)[0]=200;
		map.at<Vec3b>(currenti,currentj)[1]=100;
		map.at<Vec3b>(currenti,currentj)[2]=150;
		imshow("A*",map);
		waitKey(50);
	}
	//imshow("A*",map);
	//waitKey(0);
}