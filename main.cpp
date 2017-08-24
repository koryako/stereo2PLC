#include<stdio.h>
#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{

    //首先我们打开摄像头并按下'g'键开始标定：
      VideoCapture cap(1);  
      cap.set(CV_CAP_PROP_FRAME_WIDTH,640);  
      cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);  
      if(!cap.isOpened()){  
         std::cout<<"打开摄像头失败，退出";  
         exit(-1);  
      }  
      namedWindow("Calibration");  
      std::cout<<"Press 'g' to start capturing images!"<<endl; 
//按下空格键(SPACE)后使用findChessboardCorners函数在当前帧寻找是否存在可用于标定的角点，如果存在将其提取出来后亚像素化并压入角点集合，保存当前图像
       if( cap.isOpened() && key == 'g' )  
      {  
<span style="white-space:pre">    </span>mode = CAPTURING;  
    } 

if( (key & 255) == 32 )  
{  
    image_size = frame.size();  
    /* 提取角点 */     
    Mat imageGray;  
    cvtColor(frame, imageGray , CV_RGB2GRAY);  
    bool patternfound = findChessboardCorners(frame, board_size, corners,CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK );  
    if (patternfound)     
    {      
        n++;  
        tempname<<n;  
        tempname>>filename;  
        filename+=".jpg";  
        /* 亚像素精确化 */  
        cornerSubPix(imageGray, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));  
        count += corners.size();  
        corners_Seq.push_back(corners);  
        imwrite(filename,frame);  
        tempname.clear();  
        filename.clear();  
    }  
    else  
    {  
        std::cout<<"Detect Failed.\n";  
    }  
}

//角点提取完成后开始标定，首先初始化定标板上角点的三维坐标：
for (int t=0;t<image_count;t++)   
{     
<span style="white-space:pre">    </span>vector<Point3f> tempPointSet;  
        for (int i=0;i<board_size.height;i++)   
    {     
        <span style="white-space:pre">    </span>for (int j=0;j<board_size.width;j++)   
        {     
                /* 假设定标板放在世界坐标系中z=0的平面上 */     
            Point3f tempPoint;  
            tempPoint.x = i*square_size.width;  
            tempPoint.y = j*square_size.height;  
            tempPoint.z = 0;  
            tempPointSet.push_back(tempPoint);  
           <span style="white-space:pre"> </span>}     
        }  
    object_Points.push_back(tempPointSet);  
}  
//使用calibrateCamera函数开始标定：

calibrateCamera(object_Points, corners_Seq, image_size,  intrinsic_matrix  ,distortion_coeffs, rotation_vectors, translation_vectors);
//完成定标后对标定进行评价，计算标定误差并写入文件：
std::cout<<"每幅图像的定标误差："<<endl;     
fout<<"每幅图像的定标误差："<<endl<<endl;     
for (int i=0;  i<image_count;  i++)   
{  
    vector<Point3f> tempPointSet = object_Points[i];  
        /****    通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点     ****/  
    projectPoints(tempPointSet, rotation_vectors[i], translation_vectors[i], intrinsic_matrix, distortion_coeffs, image_points2);  
        /* 计算新的投影点和旧的投影点之间的误差*/    
    vector<Point2f> tempImagePoint = corners_Seq[i];  
    Mat tempImagePointMat = Mat(1,tempImagePoint.size(),CV_32FC2);  
    Mat image_points2Mat = Mat(1,image_points2.size(), CV_32FC2);  
    for (int j = 0 ; j < tempImagePoint.size(); j++)  
    {  
        image_points2Mat.at<Vec2f>(0,j) = Vec2f(image_points2[j].x, image_points2[j].y);  
        tempImagePointMat.at<Vec2f>(0,j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);  
    }  
    err = norm(image_points2Mat, tempImagePointMat, NORM_L2);  
        total_err += err/=  point_counts[i];     
        std::cout<<"第"<<i+1<<"幅图像的平均误差："<<err<<"像素"<<endl;     
        fout<<"第"<<i+1<<"幅图像的平均误差："<<err<<"像素"<<endl;     
}     
std::cout<<"总体平均误差："<<total_err/image_count<<"像素"<<endl;     
fout<<"总体平均误差："<<total_err/image_count<<"像素"<<endl<<endl;     
std::cout<<"评价完成！"<<endl;  


//显示标定结果并写入文件：
std::cout<<"开始保存定标结果………………"<<endl;         
Mat rotation_matrix = Mat(3,3,CV_32FC1, Scalar::all(0)); /* 保存每幅图像的旋转矩阵 */     
         
fout<<"相机内参数矩阵："<<endl;     
fout<<intrinsic_matrix<<endl<<endl;     
fout<<"畸变系数：\n";     
fout<<distortion_coeffs<<endl<<endl<<endl;     
for (int i=0; i<image_count; i++)   
{   
        fout<<"第"<<i+1<<"幅图像的旋转向量："<<endl;     
        fout<<rotation_vectors[i]<<endl;     
    
        /* 将旋转向量转换为相对应的旋转矩阵 */     
        Rodrigues(rotation_vectors[i],rotation_matrix);     
        fout<<"第"<<i+1<<"幅图像的旋转矩阵："<<endl;     
        fout<<rotation_matrix<<endl;     
        fout<<"第"<<i+1<<"幅图像的平移向量："<<endl;     
        fout<<translation_vectors[i]<<endl<<endl;     
}     
std::cout<<"完成保存"<<endl;   
fout<<endl;
}





