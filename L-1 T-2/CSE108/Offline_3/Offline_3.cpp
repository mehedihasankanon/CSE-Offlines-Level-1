#include <iostream>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <cassert>

using namespace std;

const int PRECISION = 100;

/**
 * @class Fraction
 * Fraction class with comprehensive operator overloading
 *
 * This class represents rational numbers (fractions) and provides
 * operator overloading for mathematical operations. It supports operations
 * with both other fractions and floating-point numbers.
 */
class Fraction
{
    int numerator, denominator;

    /**
     * Reduces the fraction to its lowest terms and handles negative signs
     *
     * This private method:
     * 1. Moves negative signs to the numerator (denominators are always positive)
     * 2. Calculates the GCD of numerator and denominator
     * 3. Divides both by the GCD to get the reduced form
     *
     */
    void reduce()
    {
        if (denominator < 0)
        {
            numerator *= -1;
            denominator *= -1;
        }

        int g = gcd(abs(numerator), abs(denominator));

        numerator /= g;
        denominator /= g;
    }

public:
    /**
     * Converts a floating-point number to a Fraction
     *
     * This static method converts floating-point numbers to fractions using
     * the PRECISION constant. The conversion multiplies the float by PRECISION
     * and uses PRECISION as the denominator, then reduces the result.
     *
     * @param fl The floating-point number to convert
     * @return Fraction representation of the floating-point number
     *
     */
    static Fraction toFrac(float fl)
    {
        return Fraction((int)round(fl * PRECISION), PRECISION);
    }

    /**
     * Default constructor
     *
     * Creates a fraction representing 0/1 (zero).
     */
    Fraction()
    {
        numerator = 0;
        denominator = 1;
    }

    /**
     * Parameterized constructor
     *
     * Creates a fraction with specified numerator and denominator.
     * Automatically reduces the fraction and handles zero denominators.
     *
     * @param a The numerator
     * @param b The denominator (default: 1)
     */
    Fraction(int a, int b = 1)
    {
        numerator = a;
        denominator = b;
        if (denominator == 0)
        {
            cout << "Error: denominator cannot be zero. Setting to 0/1" << endl;
            numerator = 0, denominator = 1;
        }
        reduce();
    }

    int getNum() const { return numerator; }

    int getDenom() const { return denominator; }

    /**
     * Addition operator for two fractions
     *
     * Performs fraction addition using the formula:
     * a/b + c/d = (a*d + b*c) / (b*d)
     *
     * @param f The fraction to add
     * @return Fraction The sum of the two fractions (automatically reduced)
     */
    Fraction operator+(const Fraction &f) const
    {
        return Fraction(this->numerator * f.denominator + this->denominator * f.numerator, this->denominator * f.denominator);
    }

    /**
     * Addition operator for fraction and float
     *
     * Converts the float to a fraction and performs addition.
     *
     * @param fl The floating-point number to add
     * @return Fraction The sum of the fraction and float
     */
    Fraction operator+(float fl) const
    {
        return (*this + toFrac(fl));
    }
    friend Fraction operator+(float f, Fraction fr);

    /**
     * Subtraction operator for two fractions
     *
     * Performs fraction subtraction using the formula:
     * a/b - c/d = (a*d - b*c) / (b*d)
     *
     * @param f The fraction to subtract
     * @return Fraction The difference of the two fractions (automatically reduced)
     */
    Fraction operator-(const Fraction &f) const
    {
        return Fraction(this->numerator * f.denominator - this->denominator * f.numerator, this->denominator * f.denominator);
    }

    /**
     * Subtraction operator for fraction and float
     *
     * Converts the float to a fraction and performs subtraction.
     *
     * @param fl The floating-point number to subtract
     * @return Fraction The difference of the fraction and float
     */
    Fraction operator-(float fl) const
    {
        return (*this - toFrac(fl));
    }
    friend Fraction operator-(float f, Fraction fr);

    /**
     * Multiplication operator for two fractions
     *
     * Performs fraction multiplication using the formula:
     * a/b * c/d = (a*c) / (b*d)
     *
     * @param f The fraction to multiply by
     * @return Fraction The product of the two fractions (automatically reduced)
     */
    Fraction operator*(const Fraction &f) const
    {
        return Fraction(this->numerator * f.numerator, this->denominator * f.denominator);
    }

    /**
     * Multiplication operator for fraction and float
     *
     * Converts the float to a fraction and performs multiplication.
     *
     * @param fl The floating-point number to multiply by
     * @return Fraction The product of the fraction and float
     */
    Fraction operator*(float fl) const
    {
        return (*this * toFrac(fl));
    }
    friend Fraction operator*(float f, Fraction fr);

    /**
     * Division operator for two fractions
     *
     * Performs fraction division using the formula:
     * a/b ÷ c/d = (a*d) / (b*c)
     *
     * @param f The fraction to divide by
     * @return Fraction The quotient of the two fractions (automatically reduced)
     * @throws runtime_error If the divisor fraction has a numerator of 0
     */
    Fraction operator/(const Fraction &f) const
    {
        if (f.numerator == 0)
        {
            throw runtime_error("Fraciton Division: division by zero");
        }
        return Fraction(this->numerator * f.denominator, this->denominator * f.numerator);
    }

    /**
     * Division operator for fraction and float
     *
     * Converts the float to a fraction and performs division.
     *
     * @param fl The floating-point number to divide by
     * @return Fraction The quotient of the fraction and float
     * @throws runtime_error If the float is effectively zero (< 1e-7)
     */
    Fraction operator/(float fl) const
    {
        if (fabs(fl) < 1e-7)
            throw runtime_error("Fraction Division: Division by zero");

        return ((*this) / toFrac(fl));
    }
    friend Fraction operator/(float f, Fraction fr);

    friend ostream &operator<<(ostream &os, const Fraction &fr);

    /**
     * Compound addition assignment operator for fractions
     * @param fr The fraction to add to this fraction
     */
    void operator+=(const Fraction &fr)
    {
        *this = (*this + fr);
    }

    /**
     * Compound addition assignment operator for floats
     * @param fl The float to add to this fraction
     */
    void operator+=(float fl)
    {
        *this += toFrac(fl);
    }

    /**
     * Compound subtraction assignment operator for fractions
     * @param fr The fraction to subtract from this fraction
     */
    void operator-=(const Fraction &fr)
    {
        *this = (*this - fr);
    }

    /**
     * Compound subtraction assignment operator for floats
     * @param fl The float to subtract from this fraction
     */
    void operator-=(float fl)
    {
        *this -= toFrac(fl);
    }

    /**
     * Compound multiplication assignment operator for fractions
     * @param fr The fraction to multiply this fraction by
     */
    void operator*=(const Fraction &fr)
    {
        *this = (*this * fr);
    }

    /**
     * Compound multiplication assignment operator for floats
     * @param fl The float to multiply this fraction by
     */
    void operator*=(float fl)
    {
        *this *= toFrac(fl);
    }

    /**
     * Compound division assignment operator for fractions
     * @param fr The fraction to divide this fraction by
     */
    void operator/=(const Fraction &fr)
    {
        *this = (*this / fr);
    }

    /**
     * Compound division assignment operator for floats
     * @param fl The float to divide this fraction by
     */
    void operator/=(float fl)
    {
        *this /= toFrac(fl);
    }
};

/**
 * Friend function for float + fraction addition
 *
 * Enables operations like: 3.5 + fraction_obj
 * Converts the float to a fraction and performs addition.
 *
 * @param fl The floating-point number (left operand)
 * @param fr The fraction (right operand)
 * @return Fraction The sum of the float and fraction
 */
Fraction operator+(float fl, Fraction fr)
{
    return (fr + Fraction::toFrac(fl));
}

/**
 * Friend function for float - fraction subtraction
 *
 * Enables operations like: 3.5 - fraction_obj
 * Converts the float to a fraction and performs subtraction.
 *
 * @param fl The floating-point number (left operand)
 * @param fr The fraction (right operand)
 * @return Fraction The difference of the float and fraction
 */
Fraction operator-(float fl, Fraction fr)
{
    return (Fraction::toFrac(fl) - fr);
}

/**
 * Friend function for float * fraction multiplication
 *
 * Enables operations like: 3.5 * fraction_obj
 * Converts the float to a fraction and performs multiplication.
 *
 * @param fl The floating-point number (left operand)
 * @param fr The fraction (right operand)
 * @return Fraction The product of the float and fraction
 */
Fraction operator*(float fl, Fraction fr)
{
    return (fr * Fraction::toFrac(fl));
}

/**
 * Friend function for float / fraction division
 *
 * Enables operations like: 3.5 / fraction_obj
 * Converts the float to a fraction and performs division.
 *
 * @param fl The floating-point number (left operand)
 * @param fr The fraction (right operand)
 * @return Fraction The quotient of the float and fraction
 * @throws runtime_error If the fraction has a numerator of 0
 */
Fraction operator/(float fl, Fraction fr)
{
    if (fr.getNum() == 0)
        throw runtime_error("Float division by Fraction: Division by zero");
    return (Fraction::toFrac(fl)) / fr;
}

/**
 * Stream insertion operator for Fraction output
 *
 * Formats the fraction as "numerator/denominator" for output.
 *
 * @param os The output stream
 * @param fr The fraction to output
 * @return ostream& Reference to the output stream for chaining
 */
ostream &operator<<(ostream &os, const Fraction &fr)
{
    os << fr.numerator << "/" << fr.denominator;
    return os;
}

/**
 * @class FractionVector
 * Dynamic vector of fractions with comprehensive mathematical operations
 *
 * This class represents a mathematical vector where each element is a Fraction.
 * It provides extensive operator overloading for vector operations including
 * element-wise arithmetic, scalar operations, dot products, and vector norms.
 */
class FractionVector
{
    Fraction *fractions = nullptr;
    int size;

public:
    /**
     * Default constructor
     *
     * Creates an empty vector with size 0 and null pointer.
     */
    FractionVector()
    {
        size = 0;
        fractions = nullptr;
    }

    /**
     * Parameterized constructor
     *
     * Creates a vector with specified size and allocates memory for fractions.
     * All fractions are initialized to their default values (0/1).
     *
     * @param size The number of elements in the vector
     */
    FractionVector(int size)
    {
        this->size = size;
        fractions = new Fraction[size];
        assert(fractions != nullptr);
    }

    /**
     * Copy constructor
     *
     * Creates a deep copy of another FractionVector. Allocates new memory
     * and copies all elements from the source vector.
     *
     * @param fv The FractionVector to copy from
     */
    FractionVector(const FractionVector &fv)
    {
        fractions = new Fraction[fv.size];
        assert(fractions != nullptr);
        size = fv.size;
        for (int i = 0; i < fv.size; i++)
        {
            fractions[i] = fv.fractions[i];
        }
    }

    /**
     * Destructor
     *
     * Deallocates the dynamic memory used by the fractions array.
     * Prevents memory leaks by properly cleaning up resources.
     */
    ~FractionVector()
    {
        if (fractions)
            delete[] fractions;
    }

    /**
     * Assignment operator
     *
     * Performs deep copy assignment, handling self-assignment safely.
     * Deallocates existing memory and allocates new memory for the copy.
     *
     * @param fv The FractionVector to assign from
     * @return FractionVector& Reference to this object for chaining
     */
    FractionVector &operator=(const FractionVector &fv)
    {
        if (&fv == this)
            return *this;

        delete[] fractions;
        fractions = new Fraction[fv.size];
        assert(fractions != nullptr);
        size = fv.size;
        for (int i = 0; i < size; i++)
        {
            fractions[i] = fv.fractions[i];
        }

        return *this;
    }

    /**
     * Subscript operator for element access
     *
     * Provides safe access to vector elements with bounds checking.
     * Allows both reading and writing of elements.
     *
     * @param index The index of the element to access
     * @return Fraction& Reference to the fraction at the specified index
     * @throws out_of_range If index is negative or >= size
     */
    Fraction &operator[](int index) const
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("Error: Out of bounds access");
        }
        return fractions[index];
    }

    /**
     * Vector addition operator
     *
     * Performs element-wise addition of two vectors.
     * Result[i] = this[i] + other[i] for all i
     *
     * @param fv The vector to add
     * @return FractionVector The sum of the two vectors
     * @throws invalid_argument If vectors have different sizes
     */
    FractionVector operator+(const FractionVector &fv) const
    {
        if (size != fv.size)
        {
            throw invalid_argument("FractionVector addition: Vectors not of the same size");
        }

        FractionVector sum(size);
        for (int i = 0; i < size; i++)
        {
            sum[i] = fractions[i] + fv.fractions[i];
        }

        return sum;
    }

    /**
     * Vector subtraction operator
     *
     * Performs element-wise subtraction of two vectors.
     * Result[i] = this[i] - other[i] for all i
     *
     * @param fv The vector to subtract
     * @return FractionVector The difference of the two vectors
     * @throws invalid_argument If vectors have different sizes
     */
    FractionVector operator-(const FractionVector &fv) const
    {
        if (size != fv.size)
        {
            throw invalid_argument("FractionVector subtraction: Vectors not of the same size");
        }

        FractionVector sum(size);
        for (int i = 0; i < size; i++)
        {
            sum[i] = fractions[i] - fv.fractions[i];
        }

        return sum;
    }

    /**
     * Scalar multiplication operator (vector * scalar)
     *
     * Multiplies each element of the vector by the given fraction.
     * Result[i] = this[i] * scalar for all i
     *
     * @param fr The fraction to multiply by
     * @return FractionVector The scaled vector
     */
    FractionVector operator*(const Fraction &fr) const
    {
        FractionVector mul(size);
        for (int i = 0; i < size; i++)
        {
            mul[i] = fractions[i] * fr;
        }

        return mul;
    }
    friend FractionVector operator*(const Fraction &fr, const FractionVector &fv);

    /**
     * Scalar division operator
     *
     * Divides each element of the vector by the given fraction.
     * Result[i] = this[i] / scalar for all i
     *
     * @param fr The fraction to divide by
     * @return FractionVector The scaled vector
     * @throws runtime_error If the fraction has a numerator of 0
     */
    FractionVector operator/(const Fraction &fr) const
    {
        if (fr.getNum() == 0LL)
        {
            throw runtime_error("FractionVector division by Fraction: Division by zero");
        }

        FractionVector div(size);
        for (int i = 0; i < size; i++)
        {
            div[i] = fractions[i] / fr;
        }
        return div;
    }

    /**
     * Dot product operator
     *
     * Calculates the dot product of two vectors.
     * Result = Σ(this[i] * other[i]) for i = 0 to size-1
     *
     * @param fv The vector to compute dot product with
     * @return Fraction The dot product of the two vectors
     * @throws invalid_argument If vectors have different dimensions
     */
    Fraction operator*(FractionVector fv) const
    {
        if (size != fv.size)
        {
            throw invalid_argument("FractionVector dot product: dimensions do not match");
        }

        Fraction fr;
        for (int i = 0; i < size; i++)
        {
            fr += fractions[i] * fv[i];
        }
        return fr;
    }

    /**
     * Calculates the magnitude (L2 norm) of the vector
     *
     * Computes ||v|| = √(Σ(v[i]²)) for i = 0 to size-1
     * Uses floating-point arithmetic for the square root calculation.
     *
     * @return Fraction Approximation of the vector's magnitude as a fraction
     */
    Fraction value() const
    {
        double ans = 0;
        for (int i = 0; i < size; i++)
        {
            Fraction fr = fractions[i] * fractions[i];
            ans += (double)((fr.getNum() * 1.0) / fr.getDenom());
        }

        return Fraction::toFrac((float)sqrt(ans));
    }

    friend ostream &operator<<(ostream &os, FractionVector &fv);
};

/**
 * Friend function for scalar * vector multiplication
 *
 * Enables operations like: fraction_obj * vector_obj
 * Provides commutative scalar multiplication.
 *
 * @param fr The fraction scalar (left operand)
 * @param fv The vector (right operand)
 * @return FractionVector The scaled vector
 */
FractionVector operator*(const Fraction &fr, const FractionVector &fv)
{
    return fv * fr;
}

/**
 * Stream insertion operator for FractionVector output
 *
 * Formats the vector as "[ fraction1 fraction2 ... fractionN ]"
 * Each fraction is displayed in its reduced form.
 *
 * @param os The output stream
 * @param fv The vector to output
 * @return ostream& Reference to the output stream for chaining
 */
ostream &operator<<(ostream &os, FractionVector &fv)
{
    os << "[ ";
    for (int i = 0; i < fv.size; i++)
    {
        os << fv[i] << " ";
    }
    os << "]" << endl;
    return os;
}

/**
 * @class FractionMatrix
 * Matrix of fractions with comprehensive linear algebra operations
 *
 * This class represents a mathematical matrix where each element is a Fraction.
 * It provides extensive operator overloading for matrix operations including
 * matrix arithmetic, scalar operations, matrix multiplication, transposition,
 * and Hadamard products. The implementation uses dual storage (rows and columns)
 * for efficient access patterns.
 */
class FractionMatrix
{
private:
    FractionVector *rows, *cols;
    int rowCnt, colCnt;

public:
    /**
     * Constructor with specified dimensions
     *
     * Creates a matrix with the specified number of rows and columns.
     * Allocates memory for both row and column vector arrays and initializes
     * all elements to default fraction values (0/1).
     *
     * @param row Number of rows in the matrix
     * @param col Number of columns in the matrix
     */
    FractionMatrix(int row, int col)
    {
        rowCnt = row;
        colCnt = col;

        rows = new FractionVector[rowCnt];
        assert(rows != nullptr);
        for (int i = 0; i < rowCnt; i++)
        {
            rows[i] = FractionVector(colCnt);
        }
        cols = new FractionVector[colCnt];
        assert(cols != nullptr);
        for (int i = 0; i < colCnt; i++)
        {
            cols[i] = FractionVector(rowCnt);
        }
    }

    /**
     *  Copy constructor
     *
     * Creates a deep copy of another FractionMatrix. Allocates new memory
     * and copies all row and column vectors from the source matrix.
     *
     * @param fm The FractionMatrix to copy from
     */
    FractionMatrix(const FractionMatrix &fm)
    {
        rowCnt = fm.rowCnt;
        colCnt = fm.colCnt;

        rows = new FractionVector[rowCnt];
        assert(rows != nullptr);
        for (int i = 0; i < rowCnt; i++)
            rows[i] = fm.rows[i];

        cols = new FractionVector[colCnt];
        assert(cols != nullptr);
        for (int i = 0; i < colCnt; i++)
            cols[i] = fm.cols[i];
    }

    /**
     * Destructor
     *
     * Deallocates the dynamic memory used by the row and column vector arrays.
     * Prevents memory leaks by properly cleaning up resources.
     */
    ~FractionMatrix()
    {
        delete[] rows;
        delete[] cols;
    }

    /**
     * Assignment operator
     *
     * Performs deep copy assignment, handling self-assignment safely.
     * Note: This implementation has a potential issue - it doesn't properly
     * deallocate existing memory before reassignment.
     *
     * @param fm The FractionMatrix to assign from
     * @return FractionMatrix& Reference to this object for chaining
     * @warning Current implementation may have memory management issues
     */
    FractionMatrix &operator=(const FractionMatrix &fm)
    {
        if (&fm == this)
            return *this;

        rowCnt = fm.rowCnt;
        colCnt = fm.colCnt;
        rows = new FractionVector[rowCnt];
        assert(rows != nullptr);
        for (int i = 0; i < rowCnt; i++)
        {
            rows[i] = FractionVector(colCnt);
            rows[i] = fm.rows[i];
        }

        // modifyCols();
        return *this;
    }

    /**
     * Subscript operator for row access
     *
     * Provides access to matrix rows as FractionVector objects.
     * Allows operations like matrix[i][j] for element access.
     *
     * @param i The row index
     * @return FractionVector& Reference to the specified row
     * @throws out_of_range If row index is out of bounds
     */
    FractionVector &operator[](int i)
    {
        if (i < 0 || i >= rowCnt)
            throw out_of_range("[] operator: our of bounds access");
        return rows[i];
    }

    /**
     * Gets a column vector from the matrix
     *
     * Creates and returns a copy of the specified column as a FractionVector.
     * This is useful for operations that need column-wise access.
     *
     * @param index The column index
     * @return FractionVector A copy of the specified column
     * @throws out_of_range If column index is out of bounds
     */
    /**
     * Gets a column vector from the matrix
     *
     * Creates and returns a copy of the specified column as a FractionVector.
     * This is useful for operations that need column-wise access.
     *
     * @param index The column index
     * @return FractionVector A copy of the specified column
     * @throws out_of_range If column index is out of bounds
     */
    FractionVector getColumn(int index) const
    {
        if (index < 0 || index >= colCnt)
            throw out_of_range("getColumn: index out of range");

        FractionVector col(rowCnt);
        for (int i = 0; i < rowCnt; i++)
        {
            col[i] = rows[i][index];
        }

        return col;
    }

    /**
     * Matrix addition operator
     *
     * Performs element-wise addition of two matrices.
     * Result[i][j] = this[i][j] + other[i][j] for all i,j
     *
     * @param fm The matrix to add
     * @return FractionMatrix The sum of the two matrices
     * @throws invalid_argument If matrices have different dimensions
     */
    FractionMatrix operator+(const FractionMatrix &fm) const
    {
        if (rowCnt != fm.rowCnt || colCnt != fm.colCnt)
            throw invalid_argument("Matrix addition: dimensions do not match.");

        FractionMatrix ans(rowCnt, colCnt);
        for (int i = 0; i < rowCnt; i++)
        {
            ans[i] = this->rows[i] + fm.rows[i];
        }
        // ans.modifyCols();

        return ans;
    }

    /**
     * Matrix subtraction operator
     *
     * Performs element-wise subtraction of two matrices.
     * Result[i][j] = this[i][j] - other[i][j] for all i,j
     *
     * @param fm The matrix to subtract
     * @return FractionMatrix The difference of the two matrices
     * @throws invalid_argument If matrices have different dimensions
     */
    FractionMatrix operator-(const FractionMatrix &fm) const
    {
        if (rowCnt != fm.rowCnt || colCnt != fm.colCnt)
            throw invalid_argument("Matrix subtraction: dimensions do not match.");

        FractionMatrix ans(rowCnt, colCnt);
        for (int i = 0; i < rowCnt; i++)
        {
            ans[i] = this->rows[i] - fm.rows[i];
        }
        // ans.modifyCols();

        return ans;
    }

    /**
     * Scalar multiplication operator (matrix * fraction)
     *
     * Multiplies each element of the matrix by the given fraction.
     * Result[i][j] = this[i][j] * scalar for all i,j
     *
     * @param fr The fraction to multiply by
     * @return FractionMatrix The scaled matrix
     */
    FractionMatrix operator*(Fraction fr) const
    {
        FractionMatrix ans(rowCnt, colCnt);
        for (int i = 0; i < rowCnt; i++)
        {
            ans[i] = rows[i] * fr;
        }
        // ans.modifyCols();

        return ans;
    }

    /**
     * Scalar multiplication operator (matrix * float)
     *
     * Multiplies each element of the matrix by the given float.
     * Converts the float to a fraction first.
     *
     * @param fl The float to multiply by
     * @return FractionMatrix The scaled matrix
     */
    FractionMatrix operator*(float fl) const
    {
        return (*this) * Fraction::toFrac(fl);
    }

    friend FractionMatrix operator*(Fraction fr, FractionMatrix &fm)
    {
        return fm * fr;
    }
    friend FractionMatrix operator*(float fl, FractionMatrix &fm)
    {
        return fm * Fraction::toFrac(fl);
    }

    /**
     * Scalar division operator
     *
     * Divides each element of the matrix by the given fraction.
     * Result[i][j] = this[i][j] / scalar for all i,j
     *
     * @param fr The fraction to divide by
     * @return FractionMatrix The scaled matrix
     * Division by zero checking is handled by the Fraction class
     */
    FractionMatrix operator/(Fraction fr) const
    {
        FractionMatrix ans(rowCnt, colCnt);
        for (int i = 0; i < rowCnt; i++)
        {
            ans[i] = rows[i] / fr;
        }
        // ans.modifyCols();

        return ans;
    }

    /**
     * Matrix multiplication operator
     *
     * Performs standard matrix multiplication using dot products.
     * Updates column vectors of the right matrix for efficiency.
     * Result[i][j] = Σ(this[i][k] * other[k][j]) for k = 0 to this.colCnt-1
     *
     * @param fm The matrix to multiply by (modified to update column vectors)
     * @return FractionMatrix The product of the two matrices
     * @throws invalid_argument If matrix dimensions are incompatible (this.colCnt != fm.rowCnt)
     */
    FractionMatrix operator*(FractionMatrix &fm) const
    {
        for (int i = 0; i < fm.colCnt; i++)
            fm.cols[i] = fm.getColumn(i);
        if (colCnt != fm.rowCnt)
            throw invalid_argument("Matrix multiplication: invalid dimensions");

        FractionMatrix ans(rowCnt, fm.colCnt);
        for (int i = 0; i < rowCnt; i++)
        {
            for (int j = 0; j < fm.colCnt; j++)
            {
                ans[i][j] = rows[i] * fm.cols[j];
                // Fraction sum;
                // for (int k = 0; k < colCnt; ++k)
                //     sum += rows[i][k] * fm.rows[k][j];
                // ans[i][j] = sum;
            }
        }
        // ans.modifyCols();
        return ans;
    }

    /**
     * Hadamard product operator (element-wise multiplication)
     *
     * Performs element-wise multiplication of two matrices.
     * Result[i][j] = this[i][j] * other[i][j] for all i,j
     *
     * @param fm The matrix to multiply element-wise
     * @return FractionMatrix The Hadamard product of the two matrices
     * @throws invalid_argument If matrices have different dimensions
     */
    FractionMatrix operator%(const FractionMatrix &fm) const
    {
        if (colCnt != fm.colCnt || rowCnt != fm.rowCnt)
            throw invalid_argument("Hadamard Product: dimensions must be same");

        FractionMatrix ans(rowCnt, colCnt);
        for (int i = 0; i < rowCnt; i++)
        {
            for (int j = 0; j < fm.colCnt; j++)
            {
                ans.rows[i][j] = rows[i][j] * fm.rows[i][j];
            }
        }
        // ans.modifyCols();
        return ans;
    }

    /**
     * Matrix transpose operation
     *
     * Returns the transpose of the matrix (rows become columns and vice versa).
     * Updates column vectors before creating the transpose.
     *
     * @return FractionMatrix The transposed matrix (colCnt x rowCnt)
     */
    FractionMatrix transpose() const
    {
        for (int i = 0; i < colCnt; i++)
            cols[i] = getColumn(i);

        FractionMatrix ans(colCnt, rowCnt);
        for (int i = 0; i < colCnt; i++)
            ans.rows[i] = cols[i];

        return ans;
    }

    friend ostream &operator<<(ostream &os, const FractionMatrix &fm);
    friend void modifyCols(FractionMatrix &fm);
};

/**
 * Friend function to update column vectors
 *
 * Updates all column vectors in the matrix to reflect current row data.
 * This is useful when the matrix has been modified and column vectors
 * need to be synchronized.
 *
 * @param fm The matrix whose column vectors need updating
 */
void modifyCols(FractionMatrix &fm)
{
    for (int i = 0; i < fm.colCnt; i++)
        fm.cols[i] = fm.getColumn(i);
}

/**
 * Stream insertion operator for FractionMatrix output
 *
 * Formats the matrix by printing each row on a separate line.
 * Each row is formatted as a FractionVector: "[ fraction1 fraction2 ... ]"
 *
 * @param os The output stream
 * @param fm The matrix to output
 * @return ostream& Reference to the output stream for chaining
 */
ostream &operator<<(ostream &os, const FractionMatrix &fm)
{
    for (int i = 0; i < fm.rowCnt; i++)
    {
        os << fm.rows[i] << endl;
    }
    return os;
}

int main()
{
    // freopen("out.txt", "w", stdout);

    cout << "----- Fraction Operations -----" << endl;
    Fraction fr1(1, 0), fr2(2, 3), fr3(5, 7);
    float fl1 = 0.0, fl2 = 3.5, fl3 = 2.5;

    cout << endl;
    cout << "fr1: " << fr1 << endl;
    cout << "fr2: " << fr2 << endl;
    cout << "fr3: " << fr3 << endl;
    cout << endl;

    cout << endl;
    cout << "fr1 + fr2: " << fr1 + fr2 << endl;
    cout << "fr1 + fr2: " << fr1 + fr2 << endl;

    cout << "fr3 + " << fl2 << ": " << fr3 + fl2 << endl;
    cout << fl3 << " + fr2: " << fl3 + fr2 << endl;
    cout << endl;

    cout << endl;
    cout << "fr1 - fr2: " << fr1 - fr2 << endl;
    cout << "fr2 - fr3: " << fr2 - fr3 << endl;

    cout << "fr3 + " << fl2 << ": " << fr3 + fl2 << endl;
    cout << fl3 << " - fr2: " << fl3 - fr2 << endl;
    cout << endl;

    cout << endl;
    cout << "fr1 * fr2: " << fr1 * fr2 << endl;
    cout << "fr2 * fr3: " << fr2 * fr3 << endl;

    cout << "fr3 * " << fl2 << ": " << fr3 * fl2 << endl;
    cout << fl3 << " * fr2: " << fl3 * fr2 << endl;
    cout << endl;

    cout << endl;
    cout << "fr2 / fr3: " << fr2 / fr3 << endl;
    cout << "fr2 / " << fl2 << ": " << fr2 / fl2 << endl;

    try
    {
        cout << "fr2 / fr1: " << fr2 / fr1 << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    try
    {
        cout << fl2 << " / fr1: " << fl1 / fr1 << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    cout << endl;

    cout << "----- FractionVector Operations -----" << endl;

    FractionVector fv1(3);
    fv1[0] = fr1;
    fv1[1] = fr2;
    fv1[2] = fr3;
    cout << "fv1" << endl
         << fv1 << endl;

    FractionVector fv2 = (fv1 * fr2);
    cout << "fv2 = fv1 * " << fr2 << endl
         << fv2 << endl;

    FractionVector fv3 = fv1 + fv2;
    fv3 = fr2 * fv1;
    cout << fr2 << " * fv1" << endl
         << fv3 << endl;

    fv3 = fl2 * fv1;
    cout << fl2 << " * fv1" << endl
         << fv3 << endl;

    cout << "fv3 = fv1 + fv2" << endl
         << fv3 << endl;

    fv3 = fv1 - fv2;
    cout << "fv3 = fv1 - fv2" << endl
         << fv3 << endl;

    fv3 = fv1 / fr3;
    cout << "fv3 = fv1 / " << fr3 << endl
         << fv3 << endl;

    fv3 = fv1 / fl2;
    cout << "fv3 = fv1 / " << fl2 << endl
         << fv3 << endl;

    try
    {
        cout << "fv3 = fv1 / " << fr1 << endl;
        fv3 = fv1 / fr1;
        cout << fv3 << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }

    cout << endl
         << "fv1 DOT fv2 = "
         << fv1 * fv2 << endl;

    cout << endl
         << "value of fv1 = "
         << fv1.value() << endl;

    cout << "\n----- FractionMatrix Operations -----" << endl;

    FractionMatrix A(2, 2), B(2, 2);
    A[0][0] = Fraction(1, 2);
    A[0][1] = Fraction(2, 3);
    A[1][0] = Fraction(3, 4);
    A[1][1] = Fraction(4, 5);

    B[0][0] = Fraction(5, 6);
    B[0][1] = Fraction(6, 7);
    B[1][0] = Fraction(7, 8);
    B[1][1] = Fraction(8, 9);

    cout << "\nMatrix A:\n"
         << A;
    cout << "Matrix B:\n"
         << B;

    FractionMatrix C = A + B;
    cout << "A + B" << endl
         << C;

    C = A - B;
    cout << "A - B" << endl
         << C;

    C = A * fr2;
    cout << "A * " << fr2 << endl
         << C;

    C = A / fr2;
    cout << "A / " << fr2 << endl
         << C;

    C = B.transpose();
    cout << "transpose(B)\n"
         << C;

    C = A % B;
    cout << "A % B (Hadamard product)\n"
         << C;

    FractionMatrix D(3, 2);
    D[0][0] = Fraction(1, 2);
    D[0][1] = Fraction(2, 3);
    D[1][0] = Fraction(3, 4);
    D[1][1] = Fraction(4, 5);
    D[2][0] = Fraction(1, 3);
    D[2][1] = Fraction(3, 5);

    cout << "D\n"
         << D << endl;

    try
    {
        cout << "A * D" << endl;
        C = A * D;
        cout << C << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl
             << endl;
    }

    try
    {
        cout << "D * A\n";
        C = D * A;
        cout << C << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl
             << endl;
    }

    C = D.transpose();
    cout << "transpose(D)\n"
         << C << endl;

    cout << "D * 2.5\n"
         << D * 2.5 << endl;
    cout << "2.5 * D\n"
         << 2.5 * D << endl;

    cout << "D * 5/2\n"
         << D * Fraction(5, 2) << endl;
    cout << "5/2 * D\n"
         << Fraction(5, 2) * D << endl;
    cout << "5/2 * D * 2/5\n"
         << Fraction(5, 2) * D * Fraction(2, 5) << endl;

    return 0;
}