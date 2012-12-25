#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "ezMath.h"

// This file is based on the Irrlicht engine by Nikolaus Gebhardt

template <class T>
class vector3d
{
public:
        //! Default constructor (null vector).
        vector3d() : X(0), Y(0), Z(0) {}
        //! Constructor with three different values
        vector3d(T nx, T ny, T nz) : X(nx), Y(ny), Z(nz) {}

        vector3d<T> crossProduct(const vector3d<T>& p) const
        {
                return vector3d<T>(Y * p.Z - Z * p.Y, Z * p.X - X * p.Z, X * p.Y - Y * p.X);
        }

        //! Get the dot product with another vector.
        T dotProduct(const vector3d<T>& other) const
        {
                return X*other.X + Y*other.Y + Z*other.Z;
        }

		vector3d<T> operator+(const vector3d<T>& other) const { return vector3d<T>(X + other.X, Y + other.Y, Z + other.Z); }
		vector3d<T> operator-(const vector3d<T>& other) const { return vector3d<T>(X - other.X, Y - other.Y, Z - other.Z); }

        vector3d<T> operator*(const vector3d<T>& other) const { return vector3d<T>(X * other.X, Y * other.Y, Z * other.Z); }
        vector3d<T>& operator*=(const vector3d<T>& other) { X*=other.X; Y*=other.Y; Z*=other.Z; return *this; }
        vector3d<T> operator*(const T v) const { return vector3d<T>(X * v, Y * v, Z * v); }
        vector3d<T>& operator*=(const T v) { X*=v; Y*=v; Z*=v; return *this; }

        vector3d<T>& set(const T nx, const T ny, const T nz) {X=nx; Y=ny; Z=nz; return *this;}

        vector3d<T>& normalize()
        {
                f64 length = X*X + Y*Y + Z*Z;
                if (length == 0 ) // this check isn't an optimization but prevents getting NAN in the sqrt.
                        return *this;
                length = reciprocal_squareroot(length);

                X = (T)(X * length);
                Y = (T)(Y * length);
                Z = (T)(Z * length);
                return *this;
        }

        T getLength() const { return squareroot( X*X + Y*Y + Z*Z ); }

        T X;
        T Y;
        T Z;
};


//! Typedef for a f32 3d vector.
typedef vector3d<f32> vector3df;

//! Typedef for an integer 3d vector.
typedef vector3d<s32> vector3di;

//! Function multiplying a scalar and a vector component-wise.
template<class S, class T>
vector3d<T> operator*(const S scalar, const vector3d<T>& vector) { return vector*scalar; }

#endif // VECTOR3D_H
