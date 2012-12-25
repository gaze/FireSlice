#include <QMouseEvent>

#include "view.h"
#include "ezVector3d.h"
#include "ezMatrix4.h"
#include "ezQuaternion.h"
#include "ezGL.h"

void View::initializeGL() {
    qglClearColor(QColor::fromCmykF(0.39, 0.39, 0.0, 0.0).dark());
}

void View::resizeGL( int width, int height ) {
    cam.setViewport(width,height);

	GLfloat ar = ((GLfloat)width)/((GLfloat)height);

    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum( -1.0*ar, 1.0*ar, -1.0, 1.0, 5.0, 15.0 );
    glMatrixMode( GL_MODELVIEW );
}

void drawBackground() {

	// Enable lighting
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);
    //red color
    glColor3f(0.0f,0.0f,0.30f);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0,-1.0);
    //blue color
    glColor3f(0.0f,0.0f,0.48f);
    glVertex2f(-1.0,1.0);
    glVertex2f(1.0, 1.0);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void View::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawBackground();

    CMatrix4<float> m;
    cam.getMatrix(m);
    loadMatrix4(m);
    
	glPushMatrix();

	glColor3f(1.0f,1.0f,1.0f);
	TMPmodel->paintModel();

	glPopMatrix();

    swapBuffers();
}

void View::setDragMode(Qt::MouseButtons qb){
    dragMode newDragMode;

    if(qb & Qt::RightButton){
        newDragMode = DRAG_MODE_ARCBALL;
    } else {
        newDragMode = DRAG_MODE_NONE;
    }

    if(newDragMode != currentDragMode){
        //Finalize Drag Mode
        switch(currentDragMode){
        case DRAG_MODE_ARCBALL:
            cam.finalizeArcBall();
            break;
        case DRAG_MODE_PAN:
        case DRAG_MODE_NONE:
            break;
        }
        //Initiate New Drag Mode
    }

    currentDragMode = newDragMode;
}

void View::mousePressEvent(QMouseEvent * e){
    setDragMode(e->buttons());

    xDragBegin = e->x();
    yDragBegin = e->y();
}

void View::mouseReleaseEvent(QMouseEvent * e){
    setDragMode(e->buttons());
}

void View::mouseMoveEvent(QMouseEvent * e){
    if(currentDragMode == DRAG_MODE_ARCBALL){
        cam.dragMouseArcBall(xDragBegin, yDragBegin, e->x(), e->y());
    }

    repaint();
}

View::View(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	TMPmodel = new model();

	QFile stlfile("C:\\Users\\gaze\\Desktop\\Goldberg-8-3-george-hart.stl");
//	QFile stlfile("C:\\Users\\gaze\\Downloads\\teapot.stl");

	TMPmodel->loadSTL(stlfile);
}
