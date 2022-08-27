#include "header/glview.h"
#include "header/mainviewer.h"

glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{
    timer = new QTimer();
    xRot = 0;
    yRot = 0;
    zRot = 0;
    xPos = 0;
    yPos = 0;
    zPos = 0;
    xR = 0;
    yR = 0;
    zR = 0;
    x = 0;
    y = 0;
    z = 0;
    nSca = 3;
    project = false;
    timer->start(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(Updater()));


}
void glView::Updater()
{
    update();
}

void glView::slot_Data(obj_t obj) {
    project = true;
    objx = obj;
}
void glView::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_ALPHA_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

}
void glView::resizeGL(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-1, 1, -1, 1, 1, qPow(3000, 2));
    ratio=(GLfloat)w/(GLfloat)h;
    if (w>=h)
        //glFrustum(-1, 1, -1, 1, 1, qPow(3000, 2));
        glOrtho(-2.0/ratio, 2.0/ratio, -2.0, 2.0, -10.0, 10.0);
    else
       //glOrtho(-2.0, 2.0, -2.0*ratio, 2.0*ratio, -10.0, 10.0);
       glOrtho(-2.0*ratio, 2.0*ratio, -2.0, 2.0, -10.0, 10.0);

    glViewport(0, 0, (GLint)w, (GLint)h);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
}
void glView::DrawPoint(double x, double y, double z) {
            glColor4f(y*0.1, x*0.1, z*0.1,1);
            glEnable(GL_BLEND);
            glEnable(GL_POINT_SMOOTH);

            glPointSize(5.0f);
            glBegin(GL_POINTS);
                glVertex3f(x, y, z);
            glEnd();
}
void glView::DrawObject(obj_t objx) {
    if (project) {

        //draw point
        for(int i = 0; i < objx.vertex_cnt; i++)
        {

                DrawPoint(objx.vertices[i][0],objx.vertices[i][1],objx.vertices[i][2]);
        }

        //draw vertex
        //draw polygons

        for (int i = 0; i < objx.edge_cnt; i++) {

            glBegin(GL_LINE_LOOP);
                int res_line = objx.edges[i][0]-1;
                int res_line1 = objx.edges[i][1]-1;
                int res_line2 = objx.edges[i][2]-1;
                glColor4f(objx.vertices[res_line][1]/10.0, objx.vertices[res_line][0]/10.0, objx.vertices[res_line][2]/10.0,1);
                glVertex3f(objx.vertices[res_line][0], objx.vertices[res_line][1], objx.vertices[res_line][2]);
                glVertex3f(objx.vertices[res_line1][0], objx.vertices[res_line1][1], objx.vertices[res_line1][2]);
                glVertex3f(objx.vertices[res_line2][0], objx.vertices[res_line2][1], objx.vertices[res_line2][2]);
            glEnd();

            glBegin(GL_TRIANGLE_STRIP);
                int res = objx.edges[i][0]-1;
                int res1 = objx.edges[i][1]-1;
                int res2 = objx.edges[i][2]-1;
                glColor4f(objx.vertices[res][1]/10.0, objx.vertices[res][0]/10.0, objx.vertices[res][2]/10.0,1);
                glVertex3f(objx.vertices[res][0], objx.vertices[res][1], objx.vertices[res][2]);
                glVertex3f(objx.vertices[res1][0], objx.vertices[res1][1], objx.vertices[res1][2]);
                glVertex3f(objx.vertices[res2][0], objx.vertices[res2][1], objx.vertices[res2][2]);
            glEnd();
        }
        glDisableClientState(GL_COLOR_ARRAY);
    }
}


void glView::DrawGrid(float cx, float cy, float step) {
    float _cx = cx / 2;
    float _cy = cy / 2;
        glLineStipple(1, 0xAAAA);
        glStencilFunc(GL_NOTEQUAL, 1, 255);
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_TRIANGLE_FAN);
        glColor4d(1, 1, 1, 0.3);
        for (int x = -_cx; x <= _cx; x += step) {
            glBegin(GL_LINE_STRIP);

            glVertex3f(x, 0, _cy);

            glVertex3f(x, 0, -_cy);
            glEnd();
        }
        for(int y = -_cy; y <= _cy; y += step) {
            glBegin(GL_LINE_STRIP);

            glVertex3f(_cx, 0, y);

            glVertex3f(-_cx, 0, y);
            glEnd();
        }
        glDisable(GL_BLEND);
        glDisable(GL_ALPHA_TEST);
        glDisable(GL_STENCIL_TEST);
}

void glView::paintGL() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
                glScalef(nSca, nSca, nSca);
                glTranslatef(xPos, 0, 0);
                glTranslatef(0, yPos, 0);
                glTranslatef(0, 0, zPos);
                glRotatef(xRot, 1.0f, 0.0f, 0.0f);
                glRotatef(yRot, 0.0f, 1.0f, 0.0f);
                glRotatef(zRot, 0.0f, 0.0f, 1.0f);
                DrawObject(objx);
                drawAxis();
                DrawGrid(100.0, 100.0, 1.0);
            glPopMatrix();

}

void glView::mousePressEvent(QMouseEvent* mo) {
    mPos = mo->pos();
}

void glView::mouseMoveEvent(QMouseEvent* mo) {

    double translateSensative = 100;
    static int currentX = 0;
    static int currentY = 0;
    if (!currentX && !currentY) {
      currentX = mo->pos().x();
      currentY = mo->pos().y();
    }
    if (abs(mo->pos().x() - currentX) < translateSensative &&
         abs(mo->pos().y() - currentY) < translateSensative) {
       if (mo->buttons() & Qt::LeftButton) {
           xPos += 0.01 / nSca*(mo->pos().x() - mPos.x());
           yPos += -0.01 / nSca*(mo->pos().y() - mPos.y());
           x = (xPos) / -M_PI;
           y = (yPos) / -M_PI;
       } else {
           xRot += 1 / M_PI*(mo->pos().y() - mPos.y());
           yRot += 1 / M_PI*(mo->pos().x() - mPos.x());
           zRot += 0.01 / M_PI*(sin(xRot));
           xR = xRot / -M_PI;
           yR = yRot / -M_PI;
           zR = zRot;
       }
    }
    emit mouseRotTrigger(x, y, nSca, xR, yR, zR);
    mPos = mo->pos();
    currentX = mo->pos().x();
    currentY = mo->pos().y();
    //update();
}
void glView::wheelEvent(QWheelEvent* pe) {

    int res = pe->angleDelta().y();
    if (res > 0) nSca+=0.1;
    else if (res < 0 && nSca > 0.2) nSca-=0.1;;
    emit mouseRotTrigger(x, y, nSca, xR, yR, zR);
    //update();
}

void glView::drawAxis() {

   glLineWidth(3.0f);
   glColor4f(1.0f, 0.0f, 0.0f, 0.3);
   glBegin(GL_LINES);
      glVertex3f( 1.0f,  0.0f,  0.0f);
      glVertex3f(-1.0f,  0.0f,  0.0f);
   glEnd();
   glColor4f(0.0f, 1.0f, 0.0f, 0.3);
   glBegin(GL_LINES);
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);
   glColor4f(0.0f, 0.0f, 1.0f, 0.3);
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
   glEnd();
}

void glView::get_rot_x(int value) {
    rotate_x(&objx, (float)value/-100.);
}
void glView::get_rot_y(int value) {
    rotate_y(&objx, (float)value/-100.);
}
void glView::get_rot_z(int value) {
    rotate_z(&objx, (float)value/-100.);
}
void glView::get_scale(int value) {
    if (value > 0)
    {
        scale(&objx, 1.1);
    }
    if (value < 0)
    {
        scale(&objx, 0.9);
    }
}
void glView::get_move_x(int value) {
    move_x(&objx, (float)value/-100.);
}
void glView::get_move_y(int value) {
    move_y(&objx, (float)value/-100.);
}
void glView::get_move_z(int value) {
    move_z(&objx, (float)value/-100.0);
}
