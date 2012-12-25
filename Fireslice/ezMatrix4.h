#ifndef EZMATRIX4_H
#define EZMATRIX4_H

#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

#include "ezMath.h"

template <class T>
class CMatrix4
{
        public:
        CMatrix4();

        // FIXME: Const?
        T* pointer() { return M; }

        //! Simple operator for directly accessing every element of the matrix.
        T& operator()(const s32 row, const s32 col)
        {
                return M[ row * 4 + col ];
        }

        void print_matrix(){

#ifdef DEBUG
            std::cout << "----" << std::endl;
            std::cout << M[0]  << " " << M[1]  << " " << M[2]  << " " << M[3]  << std::endl;
            std::cout << M[4]  << " " << M[5]  << " " << M[6]  << " " << M[7]  << std::endl;
            std::cout << M[8]  << " " << M[9]  << " " << M[10] << " " << M[11] << std::endl;
            std::cout << M[12] << " " << M[13] << " " << M[14] << " " << M[15] << std::endl;
            std::cout << "----" << std::endl;
#endif
        }

private:
        //! Matrix data, stored in row-major order
        T M[16];

};

// Default constructor
template <class T>
inline CMatrix4<T>::CMatrix4()
{}

//! Typedef for f32 matrix
typedef CMatrix4<f32> matrix4;

#endif // MATRIX4_H
