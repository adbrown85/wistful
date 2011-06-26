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

/* Static fields */
int **Matrix::chart = createChart();

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
 * Computes the inverse of a matrix.
 * 
 * @param matrix Matrix to invert
 * @return Copy of inverted matrix
 */
Matrix inverse(const Matrix &matrix) {
    
    float arr[4][4];
    float determinant;
    float determinantReciprocal;
    
    // Find cofactors
    Matrix::findCofactors(matrix, arr);
    
    // Find determinant using first row of cofactors
    determinant = 0;
    for (int j=0; j<4; ++j) {
        determinant += matrix.arr[0][j] * arr[0][j];
    }
    
    // Transpose the array in place
    for (int i=0; i<3; ++i) {
        for (int j=i+1; j<4; ++j) {
            swap(arr[i][j], arr[j][i]);
        }
    }
    
    // Compute inverse using determinant
    determinantReciprocal = 1.0f / determinant;
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            arr[i][j] *= determinantReciprocal;
        }
    }
    
    return Matrix(arr);
}

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

/**
 * Transposes a matrix.
 * 
 * @param matrix Matrix to transpose
 * @return Copy of the transposed matrix
 */
Matrix transpose(const Matrix &matrix) {
    
    float transposed[4][4];
    
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            transposed[i][j] = matrix.arr[j][i];
        }
    }
    return Matrix(transposed);
}

//----------------------------------------
// Helpers
//

/**
 * Creates a sign chart for use in calculating cofactors.
 * 
 * @return Pointer to chart on heap
 * @throw Ggl::Exception if could not allocate chart
 */
int** Matrix::createChart() {
    
    int **chart;
    
    // Allocate
    chart = new int*[4];
    if (chart == NULL) {
        throw Exception("Could not allocate chart!");
    } else {
        for (int i=0; i<4; ++i) {
            chart[i] = new int[4];
            if (chart[i] == NULL) {
                throw Exception("Could not allocate chart row!");
            }
        }
    }
    
    // Fill the chart
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            chart[i][j] = ((i + j) % 2) ? -1 : +1;
        }
    }
    
    return chart;
}

/**
 * Computes cofactors of a matrix.
 * 
 * @param matrix Matrix to find cofactors of
 * @param cofactors 4x4 array to store cofactors in
 */
void Matrix::findCofactors(const Matrix &matrix,
                           float cofactors[4][4]) {
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            cofactors[i][j] = findMinor(matrix, i, j) * chart[i][j];
        }
    }
}

/**
 * Computes the determinant of a 3x3 matrix.
 * 
 * Calculated by aei - afh - bdi + bfg + cdh - ceg, where:
 * 
 * | a b c |
 * | d e f |
 * | g h i |
 * 
 * a = mat[0][0]
 * b = mat[0][1]
 * c = mat[0][2]
 * d = mat[1][0]
 * e = mat[1][1]
 * f = mat[1][2]
 * g = mat[2][0]
 * h = mat[2][1]
 * i = mat[2][2]
 * 
 * @param mat Matrix stored in a 3x3 array
 * @return Determinant of matrix
 */
float Matrix::findDeterminant(float mat[3][3]) {
    
    float aei = mat[0][0] * mat[1][1] * mat[2][2];
    float afh = mat[0][0] * mat[1][2] * mat[2][1];
    float bdi = mat[0][1] * mat[1][0] * mat[2][2];
    float bfg = mat[0][1] * mat[1][2] * mat[2][0];
    float cdh = mat[0][2] * mat[1][0] * mat[2][1];
    float ceg = mat[0][2] * mat[1][1] * mat[2][0];
    
    return aei - afh - bdi + bfg + cdh - ceg;
}

/**
 * Computes the minor of a matrix element.
 * 
 * Notes:
 *  - Both row and column are unchecked
 * 
 * @param matrix Matrix to compute minor of
 * @param row Row of element
 * @param column Column of element
 */
float Matrix::findMinor(const Matrix &matrix,
                        int row,
                        int column) {
    
    float minor[3][3];
    int ii;
    int jj;
    
    ii = 0;
    for (int i=0; i<4; ++i) {
        if (i != row) {
            jj = 0;
            for (int j=0; j<4; ++j) {
                if (j != column) {
                    minor[ii][jj] = matrix.arr[i][j];
                    ++jj;
                }
            }
            ++ii;
        }
    }
    
    return findDeterminant(minor);
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
