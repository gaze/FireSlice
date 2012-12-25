#ifndef EZQUATERNION_H
#define EZQUATERNION_H

#include "ezVector3d.h"
#include "ezMatrix4.h"

class quaternion
{
    public:
    //! Default Constructor
    quaternion() : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}

    //! Creates a matrix from this quaternion
    void getMatrix( matrix4 &dest, const vector3df &translation );

    quaternion& set(f32 x, f32 y, f32 z, f32 w);
    quaternion& normalize();
    quaternion& makeIdentity();
    quaternion& rotationFromTo(const vector3df& from, const vector3df& to);

    quaternion& operator*=(f32);

    //! Multiplication operator
    quaternion& operator*=(const quaternion& other);

    quaternion operator*(const quaternion& other) const;

    //! Quaternion elements.
    f32 X; // vectorial (imaginary) part
    f32 Y;
    f32 Z;
    f32 W; // real part
};

// multiplication operator
inline quaternion& quaternion::operator*=(f32 s)
{
        X*=s;
        Y*=s;
        Z*=s;
        W*=s;
        return *this;
}

inline void quaternion::getMatrix( matrix4 &dest, const vector3df &center )
{
        f32 * m = dest.pointer();

        m[0] = 1.0f - 2.0f*Y*Y - 2.0f*Z*Z;
        m[1] = 2.0f*X*Y + 2.0f*Z*W;
        m[2] = 2.0f*X*Z - 2.0f*Y*W;
        m[3] = 0.0f;

        m[4] = 2.0f*X*Y - 2.0f*Z*W;
        m[5] = 1.0f - 2.0f*X*X - 2.0f*Z*Z;
        m[6] = 2.0f*Z*Y + 2.0f*X*W;
        m[7] = 0.0f;

        m[8] = 2.0f*X*Z + 2.0f*Y*W;
        m[9] = 2.0f*Z*Y - 2.0f*X*W;
        m[10] = 1.0f - 2.0f*X*X - 2.0f*Y*Y;
        m[11] = 0.0f;

        m[12] = center.X;
        m[13] = center.Y;
        m[14] = center.Z;
        m[15] = 1.f;
}

// sets new quaternion
inline quaternion& quaternion::set(f32 x, f32 y, f32 z, f32 w)
{
        X = x;
        Y = y;
        Z = z;
        W = w;
        return *this;
}

// multiplication operator
inline quaternion quaternion::operator*(const quaternion& other) const
{
        quaternion tmp;

        tmp.W = (other.W * W) - (other.X * X) - (other.Y * Y) - (other.Z * Z);
        tmp.X = (other.W * X) + (other.X * W) + (other.Y * Z) - (other.Z * Y);
        tmp.Y = (other.W * Y) + (other.Y * W) + (other.Z * X) - (other.X * Z);
        tmp.Z = (other.W * Z) + (other.Z * W) + (other.X * Y) - (other.Y * X);

        return tmp;
}

// multiplication operator
inline quaternion& quaternion::operator*=(const quaternion& other)
{
        return (*this = other * (*this));
}

// normalizes the quaternion
inline quaternion& quaternion::normalize()
{
        const f32 n = X*X + Y*Y + Z*Z + W*W;

        if (n == 1)
                return *this;

        //n = 1.0f / sqrtf(n);
        return (*this *= reciprocal_squareroot ( n ));
}

// set quaternion to identity
inline quaternion& quaternion::makeIdentity()
{
        W = 1.f;
        X = 0.f;
        Y = 0.f;
        Z = 0.f;
        return *this;
}

inline quaternion& quaternion::rotationFromTo(const vector3df& from, const vector3df& to)
{
        // Based on Stan Melax's article in Game Programming Gems
        // Copy, since cannot modify local
        vector3df v0 = from;
        vector3df v1 = to;
        v0.normalize();
        v1.normalize();

        const f32 d = v0.dotProduct(v1);
        if (d >= 1.0f) // If dot == 1, vectors are the same
        {
                return makeIdentity();
        }
        else if (d <= -1.0f) // exactly opposite
        {
                vector3df axis(1.0f, 0.f, 0.f);
                axis = axis.crossProduct(v0);
                if (axis.getLength()==0)
                {
                        axis.set(0.f,1.f,0.f);
                        axis.crossProduct(v0);
                }
                // same as fromAngleAxis(core::PI, axis).normalize();
                return set(axis.X, axis.Y, axis.Z, 0).normalize();
        }

        const f32 s = sqrtf( (1+d)*2 ); // optimize inv_sqrt
        const f32 invs = 1.f / s;
        const vector3df c = v0.crossProduct(v1)*invs;
        return set(c.X, c.Y, c.Z, s * 0.5f).normalize();
}


#endif // QUATERNION_H
