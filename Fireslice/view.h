#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>

#include "camera.h"
#include "model.h"

class View : public QGLWidget
{
  Q_OBJECT

public:
  explicit View(QWidget *parent = 0);

protected:
  void initializeGL();
  void resizeGL( int width, int height );
  void paintGL();

  Camera cam;

//  virtual void keyPressEvent( QKeyEvent *e );

//  virtual void timeOut();

protected slots:
//  virtual void timeOutSlot();

private:
  QTimer *m_timer;

    typedef enum {
        DRAG_MODE_NONE,
        DRAG_MODE_PAN,
        DRAG_MODE_ARCBALL
    } dragMode;

  dragMode currentDragMode;

  int xDragBegin;
  int yDragBegin;

  void mousePressEvent(QMouseEvent * e);
  void mouseReleaseEvent(QMouseEvent * e);
  void mouseMoveEvent(QMouseEvent * e);

  void setDragMode(Qt::MouseButtons qb);

  model *TMPmodel;

};

#endif // VIEW_H
