/*
 * Mat4.hpp
 * 
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/math/Mat4.hpp"
using namespace std;
using namespace Ggl;
namespace Ggl {

/* Static fields */
int **Mat4::chart = createChart();

/**
 * Creates an empty matrix.
 */
Mat4::Mat4() {
    array[0][0] = 0.0;
    array[0][1] = 0.0;
    array[0][2] = 0.0;
    array[0][3] = 0.0;
    array[1][0] = 0.0;
    array[1][1] = 0.0;
    array[1][2] = 0.0;
    array[1][3] = 0.0;
    array[2][0] = 0.0;
    array[2][1] = 0.0;
    array[2][2] = 0.0;
    array[2][3] = 0.0;
    array[3][0] = 0.0;
    array[3][1] = 0.0;
    array[3][2] = 0.0;
    array[3][3] = 0.0;
}

/**
 * Creates a matrix with a value across the diagonal.
 * 
 * @param value Value to copy to each element on diagonal
 */
Mat4::Mat4(float value) {
    array[0][0] = value;
    array[0][1] = 0.0;
    array[0][2] = 0.0;
    array[0][3] = 0.0;
    array[1][0] = 0.0;
    array[1][1] = value;
    array[1][2] = 0.0;
    array[1][3] = 0.0;
    array[2][0] = 0.0;
    array[2][1] = 0.0;
    array[2][2] = value;
    array[2][3] = 0.0;
    array[3][0] = 0.0;
    array[3][1] = 0.0;
    array[3][2] = 0.0;
    array[3][3] = value;
}

/**
 * Creates a matrix from a two-dimensional array.
 * 
 * @param arr Two-dimensional array
 */
Mat4::Mat4(float arr[4][4]) {
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
Mat4::Mat4(float arr[16]) {
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
void Mat4::toArray(float arr[4][4]) {
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
void Mat4::toArray(float arr[16]) {
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
Mat4 Mat4::operator*(const Mat4 &mat) const {
    
    Mat4 result;
    
    // Multiply rows of this matrix with columns of other matrix
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            for (int k=0; k<4; ++k) {
                result(i,j) += array[i][k] * mat(k,j);
            }
        }
    }
    return result;
}

/**
 * Multiplies this matrix by a vector.
 * 
 * @param vec Vector to multiply by
 * @return Copy of resulting vector
 */
Vec4 Mat4::operator*(const Vec4 &vec) const {
    
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
 * @param mat Matrix to compute inverse of
 * @return Copy of matrix's inverse
 * @throw std::exception if matrix cannot be inverted
 */
Mat4 inverse(const Mat4 &mat) {
    
    float arr[4][4];
    float determinant;
    float determinantReciprocal;
    
    // Find cofactors
    Mat4::findCofactors(mat, arr);
    
    // Find determinant using first row of cofactors
    determinant = 0;
    for (int j=0; j<4; ++j) {
        determinant += mat(0,j) * arr[0][j];
    }
    
    // Check if determinant is zero
    if (fabs(determinant) < Mat4::EPSILON) {
        throw Exception("[Mat4] Matrix cannot be inverted!");
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
    
    return Mat4(arr);
}

/**
 * Pretty prints a matrix to standard out.
 * 
 * @param mat Matrix to print
 */
void print(const Mat4 &mat) {
    
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
 * Computes the transpose of a matrix.
 * 
 * @param mat Matrix to compute transpose of
 * @return Copy of matrix's transpose
 */
Mat4 transpose(const Mat4 &mat) {
    
    float transposed[4][4];
    
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            transposed[i][j] = mat(j,i);
        }
    }
    return Mat4(transposed);
}

/* Helpers */

/**
 * Creates a sign chart for use in calculating cofactors.
 * 
 * @return Pointer to chart on heap
 * @throw std::exception if could not allocate chart
 */
int** Mat4::createChart() {
    
    int **chart;
    
    // Allocate
    chart = new int*[4];
    if (chart == NULL) {
        throw Exception("[Mat4] Could not allocate chart!");
    } else {
        for (int i=0; i<4; ++i) {
            chart[i] = new int[4];
            if (chart[i] == NULL) {
                throw Exception("[Mat4] Could not allocate chart row!");
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
void Mat4::findCofactors(const Mat4 &mat,
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
float Mat4::findDeterminant(float mat[3][3]) {
    
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
float Mat4::findMinor(const Mat4 &mat,
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
