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