#ifndef CAMERA_H
#define CAMERA_H

#include "ezVector3d.h"
#include "ezGL.h"
#include "ezMatrix4.h"
#include "ezQuaternion.h"
#include "ezMath.h"

#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

class Camera
{
public:

    void getMatrix(CMatrix4<float> &m) {
        (currentRotation*delta).getMatrix(m,center);
    }

    void setViewport(int w, int h){ width = w; this->height = h; }
    void mapToSphere(int x, int y, vector3df &vec) const;
    void finalizeArcBall();
    void dragMouseArcBall(int x1, int y1, int x2, int y2);

    Camera();

private:
    quaternion currentRotation;
    quaternion delta;
    vector3df center;

    int width, height;
};

#endif // CAMERA_H
