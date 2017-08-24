图像坐标系


u=x/dx+u0 v=y/dy+v0

u,v 为图像坐标 单位为像素 

dx 和dy 是感光片的长度和宽度
      
       U   | 1/dx   0    U0 |      x
       V  =|   0   1/dy  V0 |  *   y
       1   |   0    0     1 |      1

相机坐标系

x=f(Xc/Zc), y=f(Yc/Zc)
                               
              x     |  f 0 0 0  |     Xc  
       Zc *   y   = |  0 f 0 0  |  *  Yc
              1     |  0 0 1 0  |     Zc
                                1

世界坐标系



       Xc          Xw
       Yc =(R|T) * Yw 
       Zc          Zw
                   1



由以上得


            U     |1/dx      0    U0 |   | f 0 0 |          Xw
       Zc * V   = | 0      1/dy   V0 | * | 0 f 0 | *(R|T)*  Yw
            1     | 0        0     1 |   | 0 0 1 |          Zw
                                                             1
                  | fx 0  U0 |       Xw           Xw
                = | 0  fy V0 | (R|T) Yw  = M1 M2  Yw
                  | 0  0  1  |       Zw           Zw
                                     1             1


M1为相机的内参矩阵

M2为外参矩阵，包括旋转矩阵和平移矩阵


![畸变公式](http://180.76.148.87/qibiangongshi.png)

上图右侧等式中，k1,k2,k3,k4,k5,k6为径向畸变，p1,p2为切向畸变。在OpenCV中我们使用张正友相机标定法通过10幅不同角度的棋盘图像来标定相机获得相机内参和畸变系数。函数为calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs，flag)
objectPoints: 一组世界坐标系中的3D
imagePoints: 超过10张图片的角点集合
imageSize: 每张图片的大小
cameraMatrix: 内参矩阵
distCoeffs: 畸变矩阵(默认获得5个即便参数k1,k2,p1,p2,k3，可修改)
rvecs: 外参：旋转向量
tvecs: 外参：平移向量
flag: 标定时的一些选项：
CV_CALIB_USE_INTRINSIC_GUESS：使用该参数时，在cameraMatrix矩阵中应该有fx,fy,u0,v0的估计值。否则的话，将初始化(u0,v0）图像的中心点，使用最小二乘估算出fx，fy。
CV_CALIB_FIX_PRINCIPAL_POINT：在进行优化时会固定光轴点。当CV_CALIB_USE_INTRINSIC_GUESS参数被设置，光轴点将保持在中心或者某个输入的值。
CV_CALIB_FIX_ASPECT_RATIO：固定fx/fy的比值，只将fy作为可变量，进行优化计算。当CV_CALIB_USE_INTRINSIC_GUESS没有被设置，fx和fy将会被忽略。只有fx/fy的比值在计算中会被用到。
CV_CALIB_ZERO_TANGENT_DIST：设定切向畸变参数（p1,p2）为零。
CV_CALIB_FIX_K1,...,CV_CALIB_FIX_K6：对应的径向畸变在优化中保持不变。
CV_CALIB_RATIONAL_MODEL：计算k4，k5，k6三个畸变参数。如果没有设置，则只计算其它5个畸变参数。

