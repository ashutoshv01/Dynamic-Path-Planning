#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include<math.h>
#include<queue>

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

float hcost(int ii, int ij, int fi, int fj)       // heuristic
{
	return sqrt( (ii-fi)*(ii-fi)+(ij-fj)*(ij-fj) );
}

float gcost(int i, int j, int fi, int fj)        // cost of travelling till that pixel
{
	if( (fi == i-1 && fj == j-1) || (fi == i+1 && fj == j+1) ||   (fi == i-1 && fj == j+1) || (fi == i+1 && fj == j-1)  )
	{
		return 0.01;
	}
	else
	{
		return 0.014;
	}
}

struct pixel         // storing info of each pixel
{
	int row;
	int col;
	float cost;
	//int parentrow;
	//int parentcol;
	//bool visited;
};

bool operator < (const pixel& p1, const pixel& p2 )
{
	return p1.cost > p2.cost;
}

int main()
{
	Mat map = imread("Test1.png",1);
	Mat map2 = map.clone();
	namedWindow("A*",WINDOW_NORMAL);
	namedWindow("test",WINDOW_NORMAL);
	int sourcei,sourcej,desti,destj;
	float h,g;
	for(int i=0;i<map.rows;i++)       
	{
		for(int j=0;j<map.cols;j++)
		{
			if( map.at<Vec3b>(i,j)[0]==0 && map.at<Vec3b>(i,j)[1]==255 && map.at<Vec3b>(i,j)[2]==0)
			{
				sourcei =i;
				sourcej =j;
				break;
			}
		}
	}

	for(int i=0;i<map.rows;i++)           
	{
		for(int j=0;j<map.cols;j++)
		{
			if(  (map.at<Vec3b>(i,j)[2]>map.at<Vec3b>(i,j)[0]) && (map.at<Vec3b>(i,j)[2]>map.at<Vec3b>(i,j)[1] ) )
			{
				desti = i;
				destj = j;
				break;
			}
		}
	}
	int parentrow[map.rows][map.cols];
	int parentcol[map.rows][map.cols];

	for(int i=0;i<map.rows;i++)
	{
		for(int j=0;j<map.cols;j++)
		{
			parentrow[i][j]=-1;
			parentcol[i][j]=-1;
		}
	}
	priority_queue<pixel> my_queue;

	pixel a;
	a.row = sourcei;
	a.col = sourcej;
	a.cost = 0;

	my_queue.push(a);         

	while( (my_queue.top().row != desti  || my_queue.top().col != destj) )   
	{
		if((my_queue.top().row == desti  && my_queue.top().col == destj))
		{
			break;
		}
		int x = my_queue.top().row;
		int y = my_queue.top().col;
		map2.at<Vec3b>(x,y)[0]=255;
		map2.at<Vec3b>(x,y)[1]=20;
		map2.at<Vec3b>(x,y)[2]=200;  
		my_queue.pop();
		for(int k=-1;k<=1;k++)
		{
			for(int l=-1;l<=1;l++)   
			{
				if( isValid( x+k, y+l, map.rows, map.cols ) ==1 )
				{
					if( (map2.at<Vec3b>(x+k,y+l)[0]==0 && map2.at<Vec3b>(x+k,y+l)[1]==0 && map2.at<Vec3b>(x+k,y+l)[2]==0) || (map2.at<Vec3b>(x+k,y+l)[1]==255 && map2.at<Vec3b>(x+k,y+l)[2]==0 && map2.at<Vec3b>(x+k,y+l)[0]==0 ) || (map.at<Vec3b>(x+k,y+l)[2]>0 && map.at<Vec3b>(x+k,y+l)[1]==0 && map.at<Vec3b>(x+k,y+l)[2]>map.at<Vec3b>(x+k,y+l)[0]) ) 
					{
						if(!(map2.at<Vec3b>(x+k,y+l)[0]==255 && map2.at<Vec3b>(x+k,y+l)[1]==20 && map2.at<Vec3b>(x+k,y+l)[2]==200) && !(map2.at<Vec3b>(x+k,y+l)[0]==20 && map2.at<Vec3b>(x+k,y+l)[1]==200 && map2.at<Vec3b>(x+k,y+l)[2]==225) )
						{	
						pixel b;
						b.row = x+k;
						b.col = y+l;
						h = hcost( x+k ,y+l, desti, destj);
						g = gcost( x,y,x+k, y+l );
						if( (h+g) <= b.cost)
						{
							b.cost = h+g;
							parentrow[x+k][y+l]=x;
							parentcol[x+k][y+l]=y;
						}

						my_queue.push(b);
						map2.at<Vec3b>(b.row,b.col)[0]=20;
						map2.at<Vec3b>(b.row,b.col)[1]=200;
						map2.at<Vec3b>(b.row,b.col)[2]=225;
						}
					}
				}
			}
		}
		imshow("test",map2);
		waitKey(30);	
	}


	for(int i=0;i<map.rows;i++)
	{
		for(int j=0;j<map.cols;j++)
		{
			if(isValid(parentrow[i][j],parentcol[i][j],map.rows,map.cols)==1)
			{
				map.at<Vec3b>(parentrow[i][j],parentcol[i][j])[0]=200;
				map.at<Vec3b>(parentrow[i][j],parentcol[i][j])[1]=100;
				map.at<Vec3b>(parentrow[i][j],parentcol[i][j])[2]=150;
			}
		}
	}
	imshow("A*",map);
	waitKey(0);
	
}

