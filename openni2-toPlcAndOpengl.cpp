
//深度图像转成三维坐标


pdepth = (DepthPixel*)frameDepth.getData();  
for (int i = 0; i < frameDepth.getHeight(); i++)  
{  
    for (int j = 0; j < frameDepth.getWidth(); j++)  
    {  
        depthv = pdepth[i*frameDepth.getWidth() + j];  
        CoordinateConverter::convertDepthToWorld(streamDepth, i, j, depthv, &x, &y, &z);  
        xyzdata[i][j][0] = x ;  
        xyzdata[i][j][1] = y ;  
        xyzdata[i][j][2] = z ;  
    }  
}

//获取纹理
for (int i = 0; i < cImageBGR.rows; i++)  
{  
    Vec3b *p = cImageBGR.ptr<Vec3b>(i);  
    for (int j = 0; j < cImageBGR.cols; j++)  
    {  
        texture[i][j][0] = p[j][2];  //red  
        texture[i][j][1] = p[j][1];  //green  
        texture[i][j][2] = p[j][0];  //blue  
    }  
} 
//opengl画出来
void display(void)  
{  
    // clear screen and depth buffer    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    // Reset the coordinate system before modifying     
    glLoadIdentity();  
    // set the camera position    
    gluLookAt(0.0, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  
    glRotatef(-90.0, 0.0, 0.0, 1.0); //绕Z轴逆时针旋转90°  
  
    float x,y,z;  
    // 绘制图像点云  
    glBegin(GL_POINTS);  
    for (int i=0;i<480;i++){  
        for (int j=0;j<640;j++){  
            // color interpolation  
            glColor3f(texture[i][j][0]/255, texture[i][j][1]/255, texture[i][j][2]/255);  
            x= xyzdata[i][j][0];  
            y= xyzdata[i][j][1];  
            z= xyzdata[i][j][2];  
            glVertex3f(x,y,z);  
        }  
    }  
    glEnd();  
    glutSwapBuffers();  
}  

//鼠标旋转缩放
void mouse(int button, int state, int x, int y)  
{  
    if (state == GLUT_DOWN)  
    {  
        mousedown = GL_TRUE;  
    }  
    mousex = x, mousey = y;  
}  
  
void motion(int x, int y)  
{  
    if (mousedown == GL_TRUE)  
    {       /// 所除以的数字是调整旋转速度的，随便设置，达到自己想要速度即可  
        xrotate -= (x - mousex) / 10.0f;  
        yrotate -= (y - mousey) / 10.0f;  
    }  
    mousex = x, mousey = y;  
    glutPostRedisplay();  
}  


void keyboard(unsigned char c, int x, int y)  
{  
    switch (c)  
    {  
    case 'w':  
        eye[2] += 20.0f;  
        break;  
    case 's':  
        eye[2] -= 20.0f;  
        break;  
    case 'a':  
        eye[0] += 20.0f;  
        break;  
    case 'd':  
        eye[0] -= 20.0f;  
        break;  
    case 'r':  
        eye[0] = 0.0f;  
        eye[2] = 0.0f;  
        xrotate = 0;  
        yrotate = 0;  
        break;  
    case 27:  
        exit(0);  
    default:  
        break;  
    }  
    glutPostRedisplay();  
} 

//改进opengl显示

void display(void)  
{  
    // clear screen and depth buffer    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    // Reset the coordinate system before modifying     
    glLoadIdentity();  
    // set the camera position    
//  gluLookAt(0.0, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  
    gluLookAt(eye[0], eye[1], eye[2],  
        center[0], center[1], center[2],  
        0, 1, 0);  
    glPushMatrix();  
    glRotatef(-90.0, 0.0, 0.0, 1.0);  
    glTranslatef(-350.0, -300.0, 5000.0);  
    glRotatef(xrotate, 1.0, 0.0, 0.0);  
    glRotatef(yrotate, 0.0, 1.0, 0.0);  
    glTranslatef(350.0, 300.0, -5000.0);  
  
    float x,y,z;  
    // 绘制图像点云  
    glBegin(GL_POINTS);  
    for (int i=0;i<480;i++){  
        for (int j=0;j<640;j++){  
            // color interpolation  
            glColor3f(texture[i][j][0]/255, texture[i][j][1]/255, texture[i][j][2]/255);  
            x= xyzdata[i][j][0];  
            y= xyzdata[i][j][1];  
            z= xyzdata[i][j][2];  
            glVertex3f(x,y,z);  
        }  
    }  
    glEnd();  
  
    glPopMatrix();  
    glutSwapBuffers();  
}  