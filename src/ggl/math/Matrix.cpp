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
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            array[i][j] = 0.0;
        }
    }
    
    // Set ones on diagonal
    for (int i=0; i<4; ++i) {
        array[i][i] = 1.0;
    }
}

/**
 * Creates a matrix from a two-dimensional array.
 * 
 * @param arr Two-dimensional array
 */
Matrix::Matrix(float arr[4][4]) {
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            this->array[i][j] = arr[i][j];
        }
    }
}

/**
 * Creates a matrix from a one-dimensional array.
 * 
 * @param arr One-dimensional array in column-major order
 */
Matrix::Matrix(float arr[16]) {
    for (int j=0; j<4; j++) {
        for (int i=0; i<4; i++) {
            this->array[i][j] = arr[j*4+i];
        }
    }
}

/**
 * Copies the matrix into a two-dimensional array.
 * 
 * @param arr Array to store matrix values in
 */
void Matrix::toArray(float arr[4][4]) {
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            arr[i][j] = this->array[i][j];
        }
    }
}

/**
 * Copies the matrix into a one-dimensional array in column-major order.
 * 
 * @param arr Array to store matrix values in
 */
void Matrix::toArray(float arr[16]) {
    for (int j=0; j<4; ++j) {
        for (int i=0; i<4; ++i) {
            arr[j*4+i] = this->array[i][j];
        }
    }
}

/* Operators */

/**
 * Multiplies this matrix by another matrix.
 * 
 * @param mat Matrix to multiply by
 * @return Copy of resulting matrix
 */
Matrix Matrix::operator*(const Matrix &mat) const {
    
    float result[4][4];
    
    // Multiply rows of this matrix with columns of other matrix
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            result[i][j] = 0.0;
            for (int k=0; k<4; ++k)
                result[i][j] += array[i][k] * mat(k,j);
        }
    }
    return Matrix(result);
}

/**
 * Multiplies this matrix by a vector.
 * 
 * @param vec Vector to multiply by
 * @return Copy of resulting vector
 */
Vec4 Matrix::operator*(const Vec4 &vec) const {
    
    Vec4 result;
    
    // Multiply rows of matrix by vector
    for (int i=0; i<4; ++i) {
        result[i] = 0.0;
        for (int k=0; k<4; ++k) {
            result[i] += array[i][k] * vec[k];
        }
    }
    return result;
}

/* Friends */

/**
 * Computes the inverse of a matrix.
 * 
 * @param mat Matrix to invert
 * @return Copy of inverted matrix
 */
Matrix inverse(const Matrix &mat) {
    
    float arr[4][4];
    float determinant;
    float determinantReciprocal;
    
    // Find cofactors
    Matrix::findCofactors(mat, arr);
    
    // Find determinant using first row of cofactors
    determinant = 0;
    for (int j=0; j<4; ++j) {
        determinant += mat(0,j) * arr[0][j];
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
        cout << "[" << setw(7) << mat(i,j);
        for (j=1; j<4; j++)
            cout << ", " << setw(7) << mat(i,j);
        cout << "]" << endl;
    }
    
    // Reset
    cout << resetiosflags(ios_base::floatfield) << setprecision(6);
}

/**
 * Transposes a matrix.
 * 
 * @param mat Matrix to transpose
 * @return Copy of the transposed matrix
 */
Matrix transpose(const Matrix &mat) {
    
    float transposed[4][4];
    
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            transposed[i][j] = mat(j,i);
        }
    }
    return Matrix(transposed);
}

/* Helpers */

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
 * @param mat Matrix to find cofactors of
 * @param cofactors 4x4 array to store cofactors in
 */
void Matrix::findCofactors(const Matrix &mat,
                           float cofactors[4][4]) {
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            cofactors[i][j] = findMinor(mat, i, j) * chart[i][j];
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
 * @param mat Matrix to compute minor of
 * @param row Row of element
 * @param col Column of element
 */
float Matrix::findMinor(const Matrix &mat,
                        int row,
                        int col) {
    
    float minor[3][3];
    int ii;
    int jj;
    
    ii = 0;
    for (int i=0; i<4; ++i) {
        if (i != row) {
            jj = 0;
            for (int j=0; j<4; ++j) {
                if (j != col) {
                    minor[ii][jj] = mat(i,j);
                    ++jj;
                }
            }
            ++ii;
        }
    }
    
    return findDeterminant(minor);
}

} /* namespace Ggl */
