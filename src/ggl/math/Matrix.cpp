/*
 * Matrix.hpp
 * 
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#include "Matrix.hpp"
using namespace std;
using namespace Ggl;
namespace Ggl {

/**
 * Creates the identity matrix.
 */
Matrix::Matrix() {
    
    // Initialize
    for (int i=0; i<4; ++i)
        for (int j=0; j<4; ++j)
            arr[i][j] = 0.0;
    
    // Set ones on diagonal
    for (int i=0; i<4; ++i)
        arr[i][i] = 1.0;
}

/**
 * Creates a matrix from an array.
 * 
 * @param array Array with values for matrix
 */
Matrix::Matrix(float array[4][4]) {
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            this->arr[i][j] = array[i][j];
        }
    }
}

/**
 * Sets the matrix from values in a column-major array.
 */
void Matrix::set(float array[16]) {
    for (int j=0; j<4; j++)
        for (int i=0; i<4; i++)
            arr[i][j] = array[j*4+i];
}

/**
 * Puts the matrix into a single-subscript array (column-major order).
 */
void Matrix::toArray(float *array) {
    for (int j=0; j<4; ++j)
        for (int i=0; i<4; ++i)
            array[j*4+i] = (*this)(i,j);
}

//----------------------------------------
// Operators
//

/**
 * Returns one of the elements in the matrix.
 */
float& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= 4)
        throw Exception("[Matrix] Index out of bounds.");
    if (j < 0 || j >= 4)
        throw Exception("[Matrix] Index out of bounds.");
    return arr[i][j];
}

/**
 * Returns one of the elements in the matrix.
 */
float Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= 4)
        throw Exception("[Matrix] Index out of bounds.");
    if (j < 0 || j >= 4)
        throw Exception("[Matrix] Index out of bounds.");
    return arr[i][j];
}

//----------------------------------------
// Friends
//

/**
 * Pretty prints a matrix to standard out.
 * 
 * @param mat Matrix to print
 */
void print(const Matrix &mat) {
    
    // Print all entries
    cout << fixed << setprecision(3) << right;
    for (int i=0; i<4; i++) {
        int j=0;
        cout << "  ";
        cout << "[" << setw(7) << mat.arr[i][j];
        for (j=1; j<4; j++)
            cout << ", " << setw(7) << mat.arr[i][j];
        cout << "]" << endl;
    }
    
    // Reset
    cout << resetiosflags(ios_base::floatfield) << setprecision(6);
}

} /* namespace Ggl */

/**
 * Multiplies two matrices together.
 * 
 * @param A Matrix to multiply
 * @param B Matrix to multiply by
 * @return Copy of resulting matrix
 */
Matrix operator*(const Matrix &A, const Matrix &B) {
    
    float arr[4][4];
    
    // Multiply rows of A with columns in B
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            arr[i][j] = 0.0;
            for (int k=0; k<4; ++k)
                arr[i][j] += A(i,k) * B(k,j);
        }
    }
    return Matrix(arr);
}

/**
 * Multiplies a matrix with a vector.
 */
Vec4 operator*(const Matrix &A, const Vec4 &B) {
    
    Vec4 C;
    
    // Multiply rows of A with columns in B
    for (int i=0; i<4; ++i) {
        C[i] = 0.0;
        for (int k=0; k<4; ++k)
            C[i] += A(i,k) * B[k];
    }
    return C;
}
