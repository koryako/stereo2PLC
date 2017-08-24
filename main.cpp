#include<stdio.h>
#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
      VideoCapture cap(1);  
      cap.set(CV_CAP_PROP_FRAME_WIDTH,640);  
      cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);  
      if(!cap.isOpened()){  
         std::cout<<"打开摄像头失败，退出";  
         exit(-1);  
      }  
      namedWindow("Calibration");  
      std::cout<<"Press 'g' to start capturing images!"<<endl;  
}





