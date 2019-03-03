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

int main(){

   	int sourcei=995,sourcej=536,desti=335,destj=1379,currenti,currentj,nexti,nextj;	
    float distance, min;
 
  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap("dynamic_obstacles.mp4"); 
  namedWindow("Frame",WINDOW_NORMAL);
    
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
     
  while(1){

  
 
    Mat frame;
    // Capture frame-by-frame
    cap >> frame;
  
    // If the frame is empty, break immediately
    if (frame.empty())
      break;

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
				if(isValid(currenti+k,currentj+l,frame.rows,frame.cols)==1)
				{
					if( (frame.at<Vec3b>(currenti+k,currentj+l)[0]>=240 && frame.at<Vec3b>(currenti+k,currentj+l)[1]>=240 && frame.at<Vec3b>(currenti+k,currentj+l)[2]>=240) || (frame.at<Vec3b>(currenti+k,currentj+l)[2]> frame.at<Vec3b>(currenti+k,currentj+l)[0] && frame.at<Vec3b>(currenti+k,currentj+l)[2]> frame.at<Vec3b>(currenti+k,currentj+l)[1]) || (frame.at<Vec3b>(currenti+k,currentj+l)[0]<=30 && frame.at<Vec3b>(currenti+k,currentj+l)[1]==255 && frame.at<Vec3b>(currenti+k,currentj+l)[2]<=30) )
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

		frame.at<Vec3b>(currenti,currentj)[0]=200;
		frame.at<Vec3b>(currenti,currentj)[1]=100;
		frame.at<Vec3b>(currenti,currentj)[2]=150;
		//imshow("Frame",frame);
		//waitKey(1);
	}
	//imshow("A*",frame);
	//waitKey(0);*/
 	
    // Display the resulting frame
    imshow( "Frame", frame );
    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
  
  // When everything done, release the video capture object
  cap.release();
 
  // Closes all the frames
  destroyAllWindows();
     
  return 0;
}
