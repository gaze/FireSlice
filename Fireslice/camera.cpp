#include "camera.h"
#include "ezVector3d.h"

#include <iostream>

Camera::Camera()
{
    currentRotation.set(0.279845, -0.364706, -0.115916, 0.880477);
    center.set(0,0,-12);
}

void Camera::mapToSphere(int x, int y, vector3df &vec) const
{
    f32 length2;

    f32 sceneX, sceneY;

    //Adjust point coords and scale down to range of [-1 ... 1]
    sceneX  =        2.0f*(((float)x) / ((float)width))  - 1.0f;
    sceneY  = 1.0f - 2.0f*(((float)y) / ((float)height));

    //Compute the square of the length of the vector to the point from the center
    length2      = (sceneX * sceneX) + (sceneY * sceneY);

    //If the point is mapped outside of the sphere... (length > radius squared)
    if (length2 > 1.0f)
    {
        GLfloat norm;

        //Compute a normalizing factor (radius / sqrt(length))
        norm    = 1.0f / squareroot(length2);

        //Return the "normalized" vector, a point on the sphere
        vec.set(sceneX * norm, sceneY * norm, 0.0f);
    }
    else    //Else it's on the inside
    {
        //Return a vector to a point mapped inside the sphere sqrt(radius squared - length)
        vec.set(sceneX,sceneY,squareroot(1.0f - length2));
    }
}

void Camera::finalizeArcBall(){
    currentRotation = currentRotation * delta;
    delta.makeIdentity();
}

void Camera::dragMouseArcBall(int x1, int y1, int x2, int y2) {
    vector3df start;
    vector3df end;

    mapToSphere(x1, y1, start);
    mapToSphere(x2, y2, end);

    delta.rotationFromTo(start,end);
}
