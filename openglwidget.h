#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QtOpenGL>

class OpenglWidget : public QGLWidget
{
public:
    OpenglWidget(QWidget *parent=0);
protected:
    void initializeGL();
    void initWidget();
    void paintGL();
    void resizeGL(int width, int height);

private:
    GLfloat mx;
    GLfloat my;
    GLfloat mz;
    GLfloat m_rotateTriangle;
    GLuint *textur;
};

#endif // OPENGLWIDGET_H
