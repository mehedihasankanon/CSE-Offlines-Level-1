#include <iostream>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <cassert>

using namespace std;

const int PRECISION = 100;

class Fraction
{
    int numerator, denominator;

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
    static Fraction toFrac(float fl)
    {
        return Fraction((int)round(fl * PRECISION), PRECISION);
    }

    Fraction()
    {
        numerator = 0;
        denominator = 1;
    }
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

    Fraction operator+(const Fraction &f) const
    {
        return Fraction(this->numerator * f.denominator + this->denominator * f.numerator, this->denominator * f.denominator);
    }

    Fraction operator+(float fl) const
    {
        return (*this + toFrac(fl));
    }
    friend Fraction operator+(float f, Fraction fr);

    Fraction operator-(const Fraction &f) const
    {
        return Fraction(this->numerator * f.denominator - this->denominator * f.numerator, this->denominator * f.denominator);
    }

    Fraction operator-(float fl) const
    {
        return (*this - toFrac(fl));
    }
    friend Fraction operator-(float f, Fraction fr);

    Fraction operator*(const Fraction &f) const
    {
        return Fraction(this->numerator * f.numerator, this->denominator * f.denominator);
    }

    Fraction operator*(float fl) const
    {
        return (*this * toFrac(fl));
    }
    friend Fraction operator*(float f, Fraction fr);

    Fraction operator/(const Fraction &f) const
    {
        if (f.numerator == 0)
        {
            throw runtime_error("Fraciton Division: division by zero");
        }
        return Fraction(this->numerator * f.denominator, this->denominator * f.numerator);
    }

    Fraction operator/(float fl) const
    {
        if (fabs(fl) < 1e-7)
            throw runtime_error("Fraction Division: Division by zero");

        return ((*this) / toFrac(fl));
    }
    friend Fraction operator/(float f, Fraction fr);

    friend ostream &operator<<(ostream &os, const Fraction &fr);

    void operator+=(const Fraction &fr)
    {
        *this = (*this + fr);
    }
    void operator+=(float fl)
    {
        *this += toFrac(fl);
    }

    void operator-=(const Fraction &fr)
    {
        *this = (*this - fr);
    }
    void operator-=(float fl)
    {
        *this -= toFrac(fl);
    }

    void operator*=(const Fraction &fr)
    {
        *this = (*this * fr);
    }
    void operator*=(float fl)
    {
        *this *= toFrac(fl);
    }

    void operator/=(const Fraction &fr)
    {
        *this = (*this / fr);
    }
    void operator/=(float fl)
    {
        *this /= toFrac(fl);
    }
};

Fraction operator+(float fl, Fraction fr)
{
    return (fr + Fraction::toFrac(fl));
}

Fraction operator-(float fl, Fraction fr)
{
    return (Fraction::toFrac(fl) - fr);
}

Fraction operator*(float fl, Fraction fr)
{
    return (fr * Fraction::toFrac(fl));
}

Fraction operator/(float fl, Fraction fr)
{
    if (fr.getNum() == 0)
        throw runtime_error("Float division by Fraction: Division by zero");
    return (Fraction::toFrac(fl)) / fr;
}

ostream &operator<<(ostream &os, const Fraction &fr)
{
    os << fr.numerator << "/" << fr.denominator;
    return os;
}

class FractionVector
{
    Fraction *fractions = nullptr;
    int size;

public:
    FractionVector()
    {
        size = 0;
        fractions = nullptr;
    }
    FractionVector(int size)
    {
        this->size = size;
        fractions = new Fraction[size];
        assert(fractions != nullptr);
    }
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

    ~FractionVector()
    {
        if (fractions)
            delete[] fractions;
    }

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

    Fraction &operator[](int index) const
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("Error: Out of bounds access");
        }
        return fractions[index];
    }

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

FractionVector operator*(const Fraction &fr, const FractionVector &fv)
{
    return fv * fr;
}

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

class FractionMatrix
{
    FractionVector *rows, *cols;
    int rowCnt, colCnt;

    // void modifyCols()
    // {
    //     if (cols)
    //         delete[] cols;
    //     cols = new FractionVector(colCnt);
    //     assert(cols != nullptr);
    //     for (int i = 0; i < colCnt; i++)
    //     {
    //         cols[i] = FractionVector(rowCnt);
    //         cols[i] = getColumn(i);
    //     }
    // }

public:
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

    ~FractionMatrix()
    {
        delete[] rows;
        delete[] cols;
    }

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

    FractionVector &operator[](int i)
    {
        if (i < 0 || i >= rowCnt)
            throw out_of_range("[] operator: our of bounds access");
        return rows[i];
    }

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

void modifyCols(FractionMatrix &fm)
{
    for (int i = 0; i < fm.colCnt; i++)
        fm.cols[i] = fm.getColumn(i);
}

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

    cout << "D * 2.5\n" << D * 2.5 << endl;
    cout << "2.5 * D\n" << 2.5 * D << endl;

    cout << "D * 5/2\n" << D * Fraction(5,2) << endl;
    cout << "5/2 * D\n" << Fraction(5,2) * D << endl;
    cout << "5/2 * D * 2/5\n" << Fraction(5,2) * D * Fraction(2,5) << endl;
 
    return 0;
}