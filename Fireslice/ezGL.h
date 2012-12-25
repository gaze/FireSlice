#ifndef EZGL_H
#define EZGL_H

#define QT

#include "ezMatrix4.h"

#ifdef QT
#include <QGLWidget>
#endif

inline void loadMatrix4(matrix4 mtx){
    f32 *M = mtx.pointer();
    glLoadMatrixf(M);
}

#endif // EZGL_H
