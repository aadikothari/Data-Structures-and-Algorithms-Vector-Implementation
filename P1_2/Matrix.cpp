// Header Files
#include "Matrix.hpp"
#include <iostream>;

using std::cout;

using namespace std;

/**
* Outputs this Matrix object on the given ostream (for debugging).
* @param out - the ostream object to use to output.
*/
void Matrix::output(std::ostream& out) const
{
    if ((this->size(1) == 0) && (this->size(1) == 0))
    {
        out << "Matrix is empty";
    }
    for (int i = 0; i < this->size(1); i++)
    {
        for (int j = 0; j < this->size(2); j++)
        {
            out << this->get(i, j) << " ";
        }
        out << std::endl;
    }
    return;
}
/**
 * Default constructor. It should create a 2-by-2 matrix will all elements set to zero.
 */
Matrix::Matrix() {
    // Sets all values to 0
    A = { 0,0,0,0 };
    // m gives the number of rows, while n gives the number of columns
    m = 2, n = 2;
}

/**
 * Parameterized constructor.  Use the parameters to set the matrix element; if parameters are inconsistent then create a 0-by-0 matrix.
 * @param A - values for matrix elements, specified column-wise.
 * @param n - number of columns for the new matrix.
 */
Matrix::Matrix(const std::vector<int>& A, unsigned int n) {
    // Checks if matrix isn't empty or number of columns matches the size with rows
    // (a 1x4 matrix cannot exist if user gives 3 columns)
    if ((n != 0) && (A.size() % n == 0)) {
        this->m = A.size() / n;
        this->n = n;
        this->A = A;
    }

    // if it is empty or inconsistent, then make a 0x0 matrix
    else {
        this->m = 0;
        this->n = 0;
        this->A = {};
    }
}

/**
 * Another parameterized constructor.  Use the parameters to set the matrix element; if parameters are inconsistent then create a 0-by-0 matrix.
 * @param A - values for matrix elements, specified column-wise.
 * @param m - number of rows for the new matrix.
 * @param n - number of columns for the new matrix.
 */
Matrix::Matrix(const std::vector<int>& A, unsigned int m, unsigned int n) {
    unsigned int sizeOfArray = m * n; // avoids overflow

    // if size matches the size of the passed array
    // then fill the values
    if (A.size() == sizeOfArray) {
        this->m = m;
        this->n = n;
        this->A = A;
    }

    // otherwise make it a 0x0 matrix
    else {
        this->m = 0;
        this->n = 0;
        this->A = {};
    }
}

/**
 * Returns the element at specified linear index.
 * @param i - column-wise (linear) index of object.
 * @return element at specified linear index or smallest possible value for int if index is invalid.
 */
int Matrix::get(unsigned int i) const {
    // smalles int value
    int minVal = -2147483648;

    // if given index is outside of A's range
    if (i >= this->A.size()) {
        return minVal;  // return the smallest int value
    }

    else {
        return A.at(i); // return the value at the specified index
    }
}

/**
 * Returns the element at specified row, column index.
 * @param i - row index of object.
 * @param j - column index of object.
 * @return element at specified row, column index or smallest possible value for int if index is invalid.
 */
int Matrix::get(unsigned int i, unsigned int j) const {
    // smalles int value
    int minVal = -2147483648;

    // if given indexes (i,j) are within the bounds of the size of the matrix (m,n)
    if (this->m > i && this->n > j) {
        int pos = (j * m) + i;
        return this->A[pos]; // return the value at the position
    }
    else {
        return minVal; // otherwise return the smallest int value
    }
}

/**
 * Sets the element at specified linear index i to given value; if index is invalid matrix should not be modified.
 * @param i - column-wise (linear) index of object to set.
 * @param ai - value for element at index i
 * @return true if set is successful, false otherwise.
 */
bool Matrix::set(unsigned int i, int ai) {
    int size = m * n;

    // if given index is within the size
    if (i < size) {
        A[i] = ai;
        return true;
    }
    else
        return false; // otherwise return false
}

/**
 * Sets the element at specified row, column index to given value; if either index is invalid matrix should not be modified.
 * @param i - row index of object to set.
 * @param j - column index of object to set.
 * @param aij - value for element at index i, j
 * @return true if set is successful, false otherwise.
 */
bool Matrix::set(unsigned int i, unsigned int j, int aij) {
    // computing the position of the index
    int arithmetic = (m * j) + i;

    // if the index is within the constraints of the size
    if (i < m && j < n) {
        A[arithmetic] = aij; // setting the value
        return true;
    }
    else
        return false; // otherwise return false
}

/**
* Returns the size of the matrix along a given dimension (i.e., numbers of elements in a row or column)
* @param dim - 1 for row, 2 for column
* @return the number of elements according to dimension specified, if dimension is not valid return 0
*/
unsigned int Matrix::size(unsigned int dim) const {
    unsigned int sizeOfArray = 0;

    // if user gives 1, then we return the size of row
    if (dim == 1) {
        sizeOfArray = m; // store size in 'size of array'
    }

    // if user gives 2, then we return the size of column
    else if (dim == 2) {
        sizeOfArray = n; // store size in 'size of array'
    }

    // return size of array
    return sizeOfArray;
}

/**
 * Returns true if the elements for this object and rhs are the same, false otherwise.
 * @param rhs - the Matrix object to compare to this object.
 * @return true if elements in both objects are the same, false otherwise.
 */
bool Matrix::equal(const Matrix& rhs) const {

    // if the dimensions for rows and columns match for both the matrices
    if (m == rhs.m && n == rhs.n) {

        // get into a loop and traverse through the size for all elements
        for (int i = 0; i < (m * n); i++) {
            // if it matches
            if (A[i] == rhs.A[i]) {
                if (i + 1 == m * n) { // continuing the loop.
                    return true;
                }
            }

            // if any instance doesn't match, return false and end the loop
            else {
                return false;
            }
        }
    }

    // if dimensions don't match, it's automatically a false
    else
    {
        return false;
    }
}

/**
 * Creates and returns a new Matrix object representing the matrix addition of two Matrix objects.
 * @return a new Matrix object that contains the appropriate summed elements, a 0-by-0 matrix if matrices can't be added.
 * @param rhs - the Matrix object to add to this object.
 */
const Matrix Matrix::add(const Matrix& rhs) const {

    // creating placeholder vector and filling it up with 0 as a temporary
    std::vector<int> placeHolder(A.size(), 0);
    Matrix result(placeHolder, m, n);

    // if size is inconsistent, make it a 0x0 matrix
    if (this->n != rhs.n || this->m != rhs.m) {
        return Matrix({}, 0, 0);
    }
    else {
        // otherwise if it is consistent
        // run a for loop to traverse thru elements
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // set result value to be sum of given and user-inputted
                result.set(i, j, this->get(i, j) + rhs.get(i, j));
            }
        }
        return result;
    }
}

/**
 * Creates and returns a new Matrix object representing the matrix subtraction of two Matrix objects.
 * @return a new Matrix object that contains the appropriate difference elements, a 0-by-0 matrix if matrices can't be subtracted.
 * @param rhs - the Matrix object to subtract from this object.
 */
const Matrix Matrix::sub(const Matrix& rhs) const {

    // placeholder empty vector that helps to store values
    std::vector<int> placeHolder(A.size(), 0);
    Matrix result(placeHolder, m, n);

    // if size is inconsistent, make it a 0x0 matrix
    if (this->n != rhs.n || this->m != rhs.m) {
        return Matrix({}, 0, 0);
    }
    else {
        // otherwise if it is consistent
        // run a for loop to traverse thru elements
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // set result value to be difference between given vs user-inputted
                result.set(i, j, this->get(i, j) - rhs.get(i, j));
            }
        }
        return result;
    }
}

/**
 * Creates and returns a new Matrix object that is the multiplication of this and the given Matrix object.
 * @return a new Matrix object that contains the multiplication of this and the given Matrix object, a 0-by-0 matrix if matrices can't be multiplied.
 * @param rhs - the Matrix object to multiply with this object.
 */
const Matrix Matrix::mult(const Matrix& rhs) const {
    // for multiplication, the columns of first matrix should match the rows of the second matrix
    // if it doesn't; return empty matrix
    if (n != rhs.m) {
        return Matrix({}, 0, 0);
    }
    else {
        int size = this->m * rhs.n;
        std::vector<int> placeHolder(size, 0);
        Matrix result(placeHolder, m, n);
        int temp = 0;
        // otherwise if it does, then traverse thru the values

        for (int i = 0; i < this->m; i++) {
            for (int j = 0; j < rhs.n; j++) {
                // traverse again to fill up the temp values
                temp = 0;
                for (int k = 0; k < this->n; k++) {
                    temp = temp + this->get(i, k) * rhs.get(k, j);
                }
                // set this result using the temp val
                result.set(i, j, temp);
            }
        }
        return result;
    }
}

/**
 * Creates and returns a new Matrix object that is the multiplication of this and the given scalar.
 * @return a new Matrix object that contains the multiplication of this and the given scalar.
 * @param rhs - the scalar value to multiply with this object.
 */
const Matrix Matrix::mult(int c) const {
    int size = m * n;
    // placeholder empty vector that helps to store values
    std::vector<int> placeHolder(size, 0);
    Matrix result(placeHolder, m, n);

    // traversing thru elements
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // scalar multiplication is simply multplying each element by the given scalar
            result.set(i, j, (c * this->get(i, j)));
        }
    }

    // return this result
    return result;
}

/**
* Creates and returns a new Matrix object that is the power of this.
* @return a new Matrix object that raises this and to the given power.
* @param n - the power to which this object should be raised.
*/
const Matrix Matrix::pow(unsigned int n) const {

    // if given power is 0, all elements will be 1
    if (n == 0) {
        int size = m * n;

        // elements are becoming 1
        std::vector<int> placeHolder(size, 0);
        Matrix result(placeHolder, this->m, this->n);

        for (int i = 0; i < this->m; i++) {
            for (int j = 0; j < this->n; j++) {
                if (i == j) {
                    result.set(i, j, 1);
                }
            }
        }
        return result;
    }

    // if number is anything other than 0
    else {
        // put all values from the matrix in the vector
        std::vector<int> placeHolder(this->A.begin(), this->A.end());
        Matrix result(placeHolder, this->m, this->n);

        // traverse thru loop for 'n' times, and multiply the result.
        // multiplying each result by itself 'n' amount of times is the power
        // 2^4 = 2x2x2x2
        for (int i = 0; i < n; i++) {
            result.mult(result);
        }

        // return this number
        return result;
    }
}

/**
* Creates and returns a new Matrix object that is the transpose of this.
* @return a new Matrix object that is the transpose of this object.
*/
const Matrix Matrix::trans() const {
    // placeholder empty vector that helps to store values
    Matrix placeHolder(this->A, this->m, this->n);
    Matrix result(this->A, this->n, this->m);

    // traversing thru all elements
    for (int i = 0; i < this->m; i++) {
        for (int j = 0; j < this->n; j++) {
            // rows become columns, and columns become row
            result.set(i, j, this->get(j, i));
        }
    }

    // return this number
    return result;
}