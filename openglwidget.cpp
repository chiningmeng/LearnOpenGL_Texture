#include "openglwidget.h"
/*
 * OpenGL提供了纹理对象对象管理技术来解决上述问题。与显示列表一样，纹理对象通过一个单独的数字来标识。
 * 这允许OpenGL硬件能够在内存中保存多个纹理，而不是每次使用的时候再加载它们，从而减少了运算量，提高了速度。
  纹理映射是一个二维的数组。数组中的每一项称之为纹理点( texel )。
虽然这个数组是二维的， 但是可以映射到非二维的对象上，如球体或者其他的 3D 对象模型上。

1.创建纹理对象,并为他指定一个纹理.

2.确定纹理如何应用到每个像素上.

3.启用纹理贴图

4.绘制场景,提供纹理和几何坐标

过滤: 由于我们提供的纹理图像很少能和最终的屏幕坐标形成对应,
大小不同,所以需要设置过滤项目.允许我们进行插值或者匀和,
指定放大缩小的函数.glTexParameter*(),
使用过滤模式GL_NEAREST那么纹理单位最邻近的将被使用,
GL_LINEAR那么就用2*2的包含纹理数据的数组加权组作为纹理;

命名纹理对象: glGenTexures(GLSize n,Gluint *textureNames);
n为产生n个未使用的对象值,textureNames为纹理名字数组,
你可能有几个纹理需要使用,这个数组来区分.
*/
OpenglWidget::OpenglWidget(QWidget *parent):QGLWidget(parent)
{
    mx = 0;
    my = 0;
    mz = 0;
    initWidget();
    initializeGL();
}
void OpenglWidget::initializeGL()
{
    //加载图片
    QImage mpic;
    QImage newPic;
    mpic.load("C://Users//whc//Desktop//2k_sun.jpg");
    newPic=QGLWidget::convertToGLFormat(mpic);
    glGenTextures(1,&textur[0]);
    glBindTexture(GL_TEXTURE_2D,textur[0]);

    glTexImage2D(GL_TEXTURE_2D,0,3,newPic.width(),newPic.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,newPic.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);


    QImage mpic1;
    QImage newPic1;
    mpic1.load("C://Users//whc//Desktop//2k_sun.jpg");
    newPic1=QGLWidget::convertToGLFormat(mpic1);
    glGenTextures(1,&textur[1]);
    glBindTexture(GL_TEXTURE_2D,textur[1]);
/*
void glTexImage2D(GLenum target,    //GL_TEXTURE_2D 此纹理是一个2D纹理
　　　　　　　　　　GLint level,      　//代表图像的详细程度, 默认为0即可
　　　　　　　　　　GLint internalFormat,　//3 颜色成分R(红色分量)、G(绿色分量)、B(蓝色分量)三部分，若为4则是R(红色分量)、G(绿色分量)、B(蓝色分量)、Alpha
　　　　　　　　　　GLsizei width,    //纹理的宽度
　　　　　　　　　　GLsizei height,   //纹理的高度
　　　　　　　　　　GLint border,     //0 边框的值
　　　　　　　　　　GLenum format,    //　GL_RGB 告诉OpenGL图像数据由红、绿、蓝三色数据组成
　　　　　　　　　　GLenum type,      // GL_UNSIGNED_BYTE 组成图像的数据是无符号字节类型
　　　　　　　　　　const GLvoid * data); //告诉OpenGL纹理数据的来源,此例中指向存放在TextureImage[0]记录中的数据
*/
    //定义一个二维纹理映射
    glTexImage2D(GL_TEXTURE_2D,0,3,
                 newPic1.width(),newPic1.height(),
                 0,GL_RGBA,GL_UNSIGNED_BYTE,
                 newPic1.bits());
/*
    图象从纹理图象空间映射到帧缓冲图象空间(映射需要重新构造纹理图像,
    这样就会造成应用到多边形上的图像失真),
    这时就可用glTexParmeteri()函数来确定如何把纹理象素映射成像素.
*/
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);




    //启动纹理，负责会全为白色
    glEnable(GL_TEXTURE_2D);

    //设置着色模式，平滑的
    glShadeModel(GL_SMOOTH);
    //清除掉之前的所有颜色
    glClearColor(0.0,0.0,0.0,0.5);
    //深度缓存,设置初始值为1.0，小于1.0的部分是可见的
    glClearDepth(1.0);
    //启动OPenGL的相关功能，由参数决定，这里指
    //（启用了之后，OpenGL在绘制的时候就会检查，当前像素前面是否有别的像素，如果别的像素挡道了它，那它就不会绘制，也就是说，OpenGL就只绘制最前面的一层）
    glEnable(GL_DEPTH_TEST);
    //制定深度缓存比较值
    //这里参数指的是如果输入的深度值小于或者等于参考值则通过
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

void OpenglWidget::initWidget()
{
    //从屏幕上（400，400）为起始点，显示一个640*400的界面
    setGeometry(400,200,640,480);
    setWindowTitle("My OPenGL");
}

void OpenglWidget::paintGL()
{
    //清除颜色缓冲和深度缓冲
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //将当前点移置屏幕中心，相当于复位的操作
    glLoadIdentity();
    //平移函数,参数指的是分别从X轴，Y轴，Z轴平移
    glTranslatef(-1.5,0.0,-6.0);

    glRotatef( mx,1.0,  0.0,0.0 );
    glRotatef(my,0.0,1.0,0.0 );
    glRotatef(mz,0.0,0.0,1.0 );


    glBindTexture( GL_TEXTURE_2D, textur[0] );

    glBegin( GL_QUADS );

    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0,  1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0,  1.0 );

    glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0, -1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0, -1.0 );

    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0,  1.0,  1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0,  1.0,  1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );

    glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0, -1.0, -1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0, -1.0, -1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );

    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0, -1.0, -1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0,  1.0,  1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );

    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0, -1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0,  1.0,  1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );

    glEnd();


    glLoadIdentity();
    glTranslatef(  1.5,  0.0, -6.0 );
    glBindTexture( GL_TEXTURE_2D, textur[1] );

    glRotatef( m_rotateTriangle,  0.0,  1.0,  0.0 );
    glBegin(GL_TRIANGLES);
    glTexCoord2f( 1, 1 ); glVertex3f( 0, 1, 0 );
    glTexCoord2f( 0, 0 ); glVertex3f(  1, -1, 1 );
    glTexCoord2f( 1, 0 ); glVertex3f(  -1, -1, 1 );

    glTexCoord2f( 1, 1 ); glVertex3f( 0, 1, 0 );
    glTexCoord2f( 0, 0 ); glVertex3f( -1.0,  -1.0, 1.0 );
    glTexCoord2f( 1, 0 ); glVertex3f(  -1.0,  -1.0, -1.0 );

    glTexCoord2f( 1, 1 ); glVertex3f( 0,  1, 0 );
    glTexCoord2f( 0, 0 ); glVertex3f( -1.0,  -1.0,  -1.0 );
    glTexCoord2f( 1, 0 ); glVertex3f(  1.0,  -1.0,  -1.0 );

    glTexCoord2f( 1, 1 ); glVertex3f( 0, 1, 0 );
    glTexCoord2f( 0, 0 ); glVertex3f(  1.0, -1.0, -1.0 );
    glTexCoord2f( 1, 0 ); glVertex3f(  1.0, -1.0,  1.0 );

    glTexCoord2f( 0, 0 ); glVertex3f(  -1.0, -1.0, -1.0 );
    glTexCoord2f( 1, 0 ); glVertex3f(  1.0, -1.0,  -1.0 );
    glTexCoord2f( 1, 1 ); glVertex3f(  1.0, -1.0, 1.0 );

    glTexCoord2f( 1, 0 ); glVertex3f(  1.0, -1.0,  -1.0 );
    glTexCoord2f( 1, 1 ); glVertex3f(  1.0, -1.0, 1.0 );
    glTexCoord2f( 0, 1 ); glVertex3f(  -1.0, -1.0,  1.0 );

    glTexCoord2f( 1, 1 ); glVertex3f(  1.0, -1.0, 1.0 );
    glTexCoord2f( 0, 1 ); glVertex3f(  -1.0, -1.0,  1.0 );
    glTexCoord2f( 0, 0 ); glVertex3f(  -1.0, -1.0, -1.0 );
    glEnd();


    mx+=70;
    my+=0;
    mz+=0;
    m_rotateTriangle+=10;
}

void OpenglWidget::resizeGL(int width, int height)
{
    if(0==height)
        height=1;
    //告诉绘制到窗体的哪个位置
    glViewport(0,0,width,height);
    // 设置矩阵模式，参数是设置为投影矩阵
    glMatrixMode(GL_PROJECTION);
    //复位操作
    glLoadIdentity();

    GLdouble aspectRatio=(GLfloat)width/(GLfloat)height;
    GLdouble rFov=45.0*3.14159265/180.0;
    GLdouble zNear=0.1;
    GLdouble zFar=100.0;
    //调用glFrustum，生成矩阵与当前矩阵相乘，生成透视效果
    glFrustum(-zNear*tan(rFov/2.0)*aspectRatio,
              zNear*tan(rFov/2.0)*aspectRatio,
              -zNear*tan(rFov/2.0),
              zNear*tan(rFov/2.0),
              zNear,zFar);
    //切回模型视图矩阵
    glMatrixMode(GL_MODELVIEW);
    //复位
    glLoadIdentity();
}
