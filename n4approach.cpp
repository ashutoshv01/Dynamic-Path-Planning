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

	Mat output(100,100,CV_8UC1,Scalar(0));
	namedWindow("disparitymap",WINDOW_NORMAL);

	Mat sli(100,100,CV_8UC1,Scalar(0));
	Mat sri(100,100,CV_8UC1,Scalar(0));

	//namedWindow("t1",WINDOW_NORMAL);
	//namedWindow("T2",WINDOW_NORMAL);

	//imshow("t1",li);
	//imshow("T2",ri);
	//waitKey(0);

	for(int i=200;i<299;i++)
	{
		for(int j=240;j<339;j++)
		{
			sli.at<uchar>(i-200,j-240)=li.at<uchar>(i,j);
			sri.at<uchar>(i-200,j-240)=ri.at<uchar>(i,j);
			//cout <<"a"<<endl;
		}
	}

	//imshow("t1",sli);
	//imshow("T2",sri);
	//waitKey(0);

	Mat temp(11,11,CV_8UC1,Scalar(0));
	int flag,mx,my,disparity;

	for(int i=5;i<95;i++)
	{
		for(int j=5;j<95;j++)
		{
			for(int l=-5;l<=5;l++)
			{
				for(int k=-5;k<=5;k++)
				{
					temp.at<uchar>(5+l,5+k)=sli.at<uchar>(i+l,j+k);
					//cout<<'b'<<endl;
					//imshow("test",temp);
					//waitKey(0);
				}
			}

			for(int x=5;x<95;x++)
			{
				for(int y=5;y<95;y++)
				{
					flag = 0;
					for(int p=-5;p<=5;p++)
					{
						for(int q=-5;q<=5;q++)
						{
							//cout<<'c'<<endl;
							if(temp.at<uchar>(5+p,5+q)==sri.at<uchar>(x+p,y+q))
							{
								flag =1;
							}
							else
							{
								flag =0;
							}
						}
					}
					//cout<<flag<<endl;
					if(flag ==1)
					{
						//cout<<'d'<<endl;
						mx = x;
						my = y;
						//cout<<j<<' '<<mx<<endl;
						disparity = abs(mx-j);
						output.at<uchar>(i,j)=(disparity/100)*255;
					}

				}
			}
			

		}
	}
	//cout <<'e'<<endl;
	imshow("disparitymap",output);
	waitKey(0);

}





	/*int suml,sumr,mind,mins,diff,shift;
	int mapl[li.rows][li.cols],mapr[ri.rows][ri.cols],disparity[li.rows][li.cols];

	for(int i=1;i<li.rows;i++)
	{
		for(int j=1;j<li.cols;j++)
		{
			suml=0;
			for(int l=-1;l<=1;l++)
			{
				for(int k=-1;k<=1;k++)
				{
					suml=suml+li.at<uchar>(i+l,j+k);
				}
			}
		}
	}

	for(int i=1;i<ri.rows;i++)
	{
		for(int j=1;j<ri.cols;j++)
		{
			sumr=0;
			for(int l=-1;l<=1;l++)
			{
				for(int k=-1;k<=1;k++)
				{
					sumr=sumr+ri.at<uchar>(i+l,j+k);
				}
			}

			mapr[i][j]=sumr;
		}
	}

	for(int i=1;i<li.rows;i++)
	{
		for(int j=1;j<li.cols;j++)
		{
			mind = 10000,mins = 10000;
			for(int x=1;x<ri.rows;x++)
			{
				for(int y=1;y<ri.cols;y++)
				{
					if(li.at<uchar>(i,j)==ri.at<uchar>(x,y))
					{
						//cout<<'1'<<endl;
						diff = abs(mapl[i][j]-mapr[x][y]);
						if(diff<=mind)
						{
							mind = diff;
							shift= abs(j-y);
							if(shift<=mins)
							{
								mins=shift;
								//cout<<mins<<endl;
							}
						}
					}
				}
			}
			//cout<<mins<<endl;
			disparity[i][j]=mins;
		}
	}

	for(int i=1;i<li.rows;i++)
	{
		for(int j=1;j<li.cols;j++)
		{
			output.at<uchar>(i,j)=(disparity[i][j]/li.cols)*255;
		}
	}

	imshow("disparitymap",output);
	waitKey(0);
}*/