/*
 * Matrix.hpp
 * 
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_MATRIX_HPP
#define GGL_MATRIX_HPP
#include <cmath>
#include <iomanip>
#include "ggl/common.h"
#include "ggl/math/Vec4.hpp"
namespace Ggl {


/**
 * @brief Four-by-four matrix for 3D graphics.
 */
class Matrix {
public:
    Matrix();
    Matrix(float array[4][4]);
    void set(float array[16]);
    void toArray(float array[16]);
// Operators
    float& operator()(int i, int j);
    float operator()(int i, int j) const;
    Matrix operator*(const Matrix &mat) const;
    Vec4 operator*(const Vec4 &vec) const;
// Friends
    friend Matrix inverse(const Matrix &matrix);
    friend void print(const Matrix &mat);
    friend Matrix transpose(const Matrix &matrix);
private:
    float arr[4][4];
    static int **chart;
// Helpers
    static int** createChart();
    static float findMinor(const Matrix& matrix, int row, int column);
    static void findCofactors(const Matrix& matrix, float cofactors[4][4]);
    static float findDeterminant(float [3][3]);
};

} // namespace Ggl
#endif
