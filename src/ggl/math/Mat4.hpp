/*
 * Mat4.hpp
 * 
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_MAT4_HPP
#define GGL_MAT4_HPP
#include <cmath>
#include <iomanip>
#include "ggl/common.h"
#include "ggl/math/Vec4.hpp"
namespace Ggl {


/**
 * @brief Four-by-four matrix for 3D graphics.
 */
class Mat4 {
public:
    Mat4();
    explicit Mat4(float value);
    explicit Mat4(float arr[4][4]);
    explicit Mat4(float arr[16]);
    void toArray(float arr[4][4]);
    void toArray(float arr[16]);
// Operators
    float& operator()(int i, int j);
    float operator()(int i, int j) const;
    Mat4 operator*(const Mat4 &mat) const;
    Vec4 operator*(const Vec4 &vec) const;
// Friends
    friend Mat4 inverse(const Mat4 &mat);
    friend void print(const Mat4 &mat);
    friend Mat4 transpose(const Mat4 &mat);
private:
    float array[4][4];
    static int **chart;
// Helpers
    static int** createChart();
    static float findMinor(const Mat4& mat, int row, int col);
    static void findCofactors(const Mat4& mat, float cofactors[4][4]);
    static float findDeterminant(float [3][3]);
// Constants
    static const float EPSILON = 0.00000000000000000001;
};

/**
 * Returns a reference to an element in the matrix.
 * 
 * @param i Row of element
 * @param j Column of element
 */
inline
float& Mat4::operator()(int i, int j) {
    return array[i][j];
}

/**
 * Returns a copy of an element in the matrix.
 * 
 * @param i Row of element
 * @param j Column of element
 */
inline
float Mat4::operator()(int i, int j) const {
    return array[i][j];
}

} // namespace Ggl
#endif
