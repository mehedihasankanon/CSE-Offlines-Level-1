#include <iostream>

using namespace std;

/**
 * custom GCD function
 * @param int a
 * @param int b
 * @return int GCD of a and b
 */
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

/**
 * Fraction class
 * Member variables:
 * - numerator: int - the numerator of the fraction
 * - denominator: int - the denominator of the fraction (1 by default)
 *
 * Constructors:
 * - Default constructor: initializes numerator to 0 and denominator to 1
 * - Single parameter constructor: initializes numerator to the given value and denominator to 1
 * - Two parameters constructor: initializes numerator and denominator to the given values, checks for zero denominator, and reduces the fraction
 *
 * Member functions:
 * - add: adds another Fraction or an integer to the current Fraction
 * - sub: subtracts another Fraction or an integer from the current Fraction
 * - mul: multiplies the current Fraction by another Fraction or an integer
 * - div: divides the current Fraction by another Fraction or an integer, checks for division by zero
 * - print: prints the Fraction in the format "numerator/denominator"
 */
class Fraction
{
private:
    int numerator = 0, denominator = 1;

public:
    /**
     * Default constructor
     * Initializes numerator to 0 and denominator to 1
     */
    Fraction() = default;

    /**
     * Single parameter constructor
     * Initializes numerator to the given value and denominator to 1
     * @param a The numerator value
     */
    Fraction(int a)
    {
        numerator = a;
        denominator = 1;
    }

    /**
     * Two parameters constructor
     * Initializes numerator and denominator to the given values, checks for zero denominator, and reduces the fraction
     * @param num The numerator value
     * @param denum The denominator value
     */
    Fraction(int num, int denum)
    {
        if (denum == 0)
        {
            cout << "Denominator cannot be zero. Setting to default values" << endl;
            numerator = 0;
            denominator = 1;
        }

        if (denum < 0)
        {
            num *= -1;
            denum *= -1;
        }

        numerator = num;
        denominator = denum;

        int g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
    }

    /**
     * Destructor
     */
    ~Fraction() {}

    /**
     * `add` method
     * Adds another Fraction or an integer to the current Fraction
     * @param f The Fraction object to add (pass by reference)
     * @return A new Fraction that is the result of the addition
     */
    Fraction add(Fraction &f)
    {
        int new_den = this->denominator * f.denominator;
        int new_num = this->numerator * f.denominator + this->denominator * f.numerator;

        int g = gcd(new_den, new_num);

        new_den /= g;
        new_num /= g;

        return Fraction(new_num, new_den);
    }

    /**
     * `add` method
     * adds an integer to the current Fraction. First converts the integer to a Fraction, then calls
     * the `add` method of adding two Fractions
     * @param n The integer to add
     * @return A new Fraction that is the result of the addition
     */
    Fraction add(int n)
    {
        Fraction f(n);

        return (*this).add(f);
    }

    /**
     * `sub` method
     * Subtracts another Fraction or an integer from the current Fraction
     * @param f The Fraction object to subtract (pass by reference)
     * @return A new Fraction that is the result of the subtraction
     */
    Fraction sub(Fraction &f)
    {
        int new_den = this->denominator * f.denominator;
        int new_num = this->numerator * f.denominator - this->denominator * f.numerator;

        int g = gcd(new_den, abs(new_num));

        new_den /= g;
        new_num /= g;

        return Fraction(new_num, new_den);
    }

    /**
     * `sub` method
     * Subtracts an integer from the current Fraction. First converts the integer to a Fraction, then calls
     * the `sub` method of subtracting two Fractions
     * @param n The integer to subtract
     * @return A new Fraction that is the result of the subtraction
     */
    Fraction sub(int n)
    {
        Fraction f(n);

        return (*this).sub(f);
    }

    /**
     * `mul` method
     * Multiplies the current Fraction by another Fraction or an integer
     * @param f The Fraction object to multiply (pass by reference)
     * @return A new Fraction that is the result of the multiplication
     */
    Fraction mul(Fraction &f)
    {
        int new_denom = this->denominator * f.denominator;
        int new_num = this->numerator * f.numerator;

        int g = gcd(new_denom, abs(new_num));

        new_denom /= g;
        new_num /= g;

        return Fraction(new_num, new_denom);
    }

    /**
     * `mul` method
     * Multiplies the current Fraction by an integer. First converts the integer to a Fraction, then calls
     * the `mul` method of multiplying two Fractions
     * @param n The integer to multiply
     * @return A new Fraction that is the result of the multiplication
     */
    Fraction mul(int n)
    {
        Fraction f(n);

        return (*this).mul(f);
    }

    /**
     * `div` method
     * Divides the current Fraction by another Fraction or an integer, checks for division by zero
     * @param f The Fraction object to divide by (pass by reference)
     * @return A new Fraction that is the result of the division
     */
    Fraction div(Fraction &f)
    {

        if (f.numerator == 0)
        {
            cout << "Cannot divide by zero" << endl;
            return *this;
        }

        int new_num = this->numerator * f.denominator;
        int new_den = this->denominator * f.numerator;

        int g = gcd(abs(new_num), abs(new_den));

        new_num /= g;
        new_den /= g;

        if (new_den < 0)
        {
            new_num *= -1;
            new_den *= -1;
        }

        return Fraction(new_num, new_den);
    }

    /**
     * `div` method
     * Divides the current Fraction by an integer. First converts the integer to a Fraction, then calls
     * the `div` method of dividing two Fractions. CChecks for division by zero
     * @param n The integer to divide by
     * @return A new Fraction that is the result of the division
     */
    Fraction div(int n)
    {
        if (n == 0)
        {
            cout << "Cannot divide by zero" << endl;
            return *this;
        }

        Fraction f(n);

        return (*this).div(f);
    }

    /**
     * `print` method
     * Prints the Fraction in the format "numerator/denominator"
     */
    void print()
    {
        cout << numerator << "/" << denominator << endl;
    }

    void setNum(int x) { this->numerator = x; }
    void setDenom(int x) { this->denominator = x; }
    int getNum() { return this->numerator; }
    int getDenom() { return this->denominator; }

    /**
     * Assignment operator overload
     * Assigns the values of another Fraction to the current Fraction
     * @param f The Fraction object to assign from (pass by reference)
     */
    void operator=(const Fraction &f)
    {
        this->denominator = f.denominator;
        this->numerator = f.numerator;
    }
};

/**
 * `FractionCollection` class
 * A collection class to manage multiple Fraction objects
 *
 * Members:
 * - fractions: Fraction* - dynamic array of Fraction objects
 * - maxlength: int - maximum size of the collection (by default 10)
 * - length: int - current number of Fraction objects in the collection
 */
class FractionCollection
{
private:
    Fraction *fractions = nullptr;
    int maxlength;
    int length;

public:
    /**
     * Default constructor
     * Initializes a collection with a maximum size of 10
     */
    FractionCollection()
    {
        fractions = new Fraction[10];
        maxlength = 10;
        length = 0;
    }

    /**
     * Parameterized constructor.
     *
     * Initializes a collection with a specified maximum size
     * @param maxSize The maximum size of the collection
     */
    FractionCollection(int maxSize)
    {
        fractions = new Fraction[maxSize];
        maxlength = maxSize;
        length = 0;
    }

    /**
     * getter method for current collection length
     * @return int - the current number of `Fraction` objects in the collection
     */
    int getLen() { return length; }

    /**
     * Destructor
     * Ensures proper cleanup of allocated memory from heap
     */
    ~FractionCollection()
    {
        delete[] fractions;
    }

    /**
     * Inserts a Fraction at a specific position.
     *
     * Checks for out of bounds access and resizes the collection if necessary.
     * @param pos The position to insert the Fraction
     * @param f The Fraction object to insert
     */
    void insert(int pos, Fraction f)
    {

        if (pos > length)
        {
            cout << "Error: Out of bound access" << endl;
            return;
        }

        for (int i = length; i > pos; i--)
        {
            fractions[i].setNum(fractions[i - 1].getNum());
            fractions[i].setDenom(fractions[i - 1].getDenom());
        }

        fractions[pos].setNum(f.getNum());
        fractions[pos].setDenom(f.getDenom());

        length++;

        if (length == maxlength)
        {
            Fraction *new_fracs = new Fraction[length * 2];

            for (int i = 0; i < length; i++)
            {
                new_fracs[i].setNum(fractions[i].getNum());
                new_fracs[i].setDenom(fractions[i].getDenom());
            }

            delete[] fractions;
            fractions = new_fracs;
        }
    }

    /**
     * Inserts a Fraction at the end of the collection.
     * Checks for out of bounds access and resizes the collection if necessary.
     * @param f The Fraction object to insert
     */
    void insert(Fraction f)
    {
        (*this).insert(length, f);
    }

    /**
     * Removes a `Fraction` object from the specified position.
     *
     * Checks for out of bounds access and shifts the remaining elements.
     * @param pos The position of the `Fraction` object to remove
     */
    void remove(int pos)
    {

        if (pos > length || pos < 0)
        {
            cout << "Error: Out of bound access" << endl;
            return;
        }

        for (int i = pos + 1; i < length; i++)
        {
            fractions[i - 1].setNum(fractions[i].getNum());
            fractions[i - 1].setDenom(fractions[i].getDenom());
        }
        length--;
    }

    /**
     * Removes a `Fraction` object from the collection by value.
     *
     * Searches for the first occurrence of the specified `Fraction` and removes it.
     * If multiple occurrences are found, only the first one is removed.
     * @param f The `Fraction` object to remove
     */
    void remove(Fraction f)
    {
        int idx = 0;
        while (idx < length)
        {
            if (fractions[idx].getNum() == f.getNum() && fractions[idx].getDenom() == f.getDenom())
            {
                (*this).remove(idx);
                return;
            }
            idx++;
        }

        /**
         * remove all occurrences:
         * - while(idx < this->getLen()) on line 266
         * - continue instead of return statement on line 271
         */
    }

    /**
     * Removes the last `Fraction` object from the collection.
     */
    void remove()
    {
        (*this).remove(length - 1);
    }

    /**
     * Returns the maximum `Fraction` in the collection.
     *
     * Compares the 64-bit double values of the fractions and returns the one with the highest value.
     * @return Fraction - the maximum `Fraction` object
     */
    Fraction getMax()
    {
        Fraction ans(fractions[0].getNum(), fractions[0].getDenom());
        double mx = (fractions[0].getNum() * 1.0 / fractions[0].getDenom());

        for (int i = 1; i < length; i++)
        {
            double temp = (fractions[i].getNum() * 1.0 / fractions[i].getDenom());
            if (temp > mx)
            {
                mx = temp;
                ans.setDenom(fractions[i].getDenom());
                ans.setNum(fractions[i].getNum());
            }
        }

        return ans;
    }

    /**
     * Returns the minimum `Fraction` in the collection.
     *
     * Compares the 64-bit double values of the fractions and returns the one with the lowest value.
     * @return Fraction - the minimum `Fraction` object
     */
    Fraction getMin()
    {
        Fraction ans(fractions[0].getNum(), fractions[0].getDenom());
        double mx = (fractions[0].getNum() * 1.0 / fractions[0].getDenom());

        for (int i = 1; i < length; i++)
        {
            double temp = (fractions[i].getNum() * 1.0 / fractions[i].getDenom());
            if (temp < mx)
            {
                mx = temp;
                ans.setDenom(fractions[i].getDenom());
                ans.setNum(fractions[i].getNum());
            }
        }

        return ans;
    }

    /**
     * Adds all `Fraction` objects in the specified range. Assumes valid index input.
     *
     * @param start The starting index of the range
     * @param end The ending index of the range
     * @return Fraction - the result of the addition of all `Fraction` objects in the range
     */
    Fraction add(int start, int end)
    {
        Fraction ans(fractions[start].getNum(), fractions[start].getDenom());

        for (int i = start + 1; i <= end; i++)
        {
            ans = ans.add(fractions[i]);
        }

        return ans;
    }

    /**
     * Multiplies all `Fraction` objects in the specified range. Assumes valid index input.
     *
     * @param start The starting index of the range
     * @param end The ending index of the range
     * @return Fraction - the result of the multiplication of all `Fraction` objects in the range
     */
    Fraction mul(int start, int end)
    {
        Fraction ans(fractions[start].getNum(), fractions[start].getDenom());

        for (int i = start + 1; i <= end; i++)
        {
            ans = ans.mul(fractions[i]);
        }

        return ans;
    }

    /**
     * Subtracts the `Fraction` at pos2 from the `Fraction` at pos1.
     *
     * @param pos1 The position of the first `Fraction`
     * @param pos2 The position of the second `Fraction`
     * @return Fraction - the result of the subtraction
     */
    Fraction sub(int pos1, int pos2)
    {
        Fraction ans;

        return ans.add(fractions[pos1]).sub(fractions[pos2]);
    }

    /**
     * Divides the `Fraction` at pos1 by the `Fraction` at pos2.
     *
     * @param pos1 The position of the first `Fraction`
     * @param pos2 The position of the second `Fraction`
     * @return Fraction - the result of the division
     */
    Fraction div(int pos1, int pos2)
    {
        Fraction ans(1, 1);

        return ans.mul(fractions[pos1]).div(fractions[pos2]);
    }

    /**
     * Prints all `Fraction` objects in the collection. Properly formatted to improve readability.
     */
    void print()
    {

        cout << "Fractions" << endl
             << "-------------------------------" << endl;
        for (int i = 0; i < length; i++)
        {
            cout << "Fraction " << i << ": " << fractions[i].getNum() << "/" << fractions[i].getDenom() << endl;
        }
        return;
    }
};

int main()
{
    // create Fraction with numerator, denominator
    Fraction a(5, 2), b(7, 2), c(9, 2), d(28, 5);
    cout << "Fraction" << endl;
    cout << "-------------------------------" << endl;
    cout << "A: ";
    a.print();
    cout << "B: ";
    b.print();
    cout << endl;

    cout << "Add(a,b): ";
    a.add(b).print();
    cout << "Add(a,2): ";
    a.add(2).print();

    cout << "Sub(a,b) ";
    a.sub(b).print();
    cout << "Sub(a,2) ";
    a.sub(2).print();

    cout << "Mul(a,b): ";
    a.mul(b).print();
    cout << "Mul(a,2): ";
    a.mul(2).print();

    cout << "Div(a,b): ";
    a.div(b).print();
    cout << "Div(a,2): ";
    a.div(2).print();
    cout << "Div(a,0): ";
    a.div(0).print();

    cout << endl;

    // Collection of Fractions
    Fraction e, f(5), g(10);
    FractionCollection fc(10);
    fc.insert(a);
    fc.insert(b);
    fc.insert(c);
    fc.print();

    cout << "Max: ";
    fc.getMax().print();

    cout << "Min: ";
    fc.getMin().print();

    cout << "Summation: ";
    fc.add(0, fc.getLen() - 1).print();

    cout << "Multiplication: ";
    fc.mul(0, fc.getLen() - 1).print();

    cout << "Sub(Pos0, Pos1): ";
    fc.sub(0, 1).print(); // subtracts the fraction at pos1 from fraction at pos0
    cout << "Div(Pos0, Pos1): ";
    fc.div(0, 1).print(); // divides the fraction at pos0 by the fraction at pos1

    cout << endl;

    fc.remove(1); // removed 'b'
    fc.print();

    cout << "Max: ";
    fc.getMax().print();

    cout << "Min: ";
    fc.getMin().print();

    cout << "Summation: ";
    fc.add(0, fc.getLen() - 1).print();

    cout << "Multiplication: ";
    fc.mul(0, fc.getLen() - 1).print();

    cout << endl;

    fc.remove(a);
    fc.print();

    cout << "Max: ";
    fc.getMax().print();

    cout << "Min: ";
    fc.getMin().print();

    cout << "Summation: ";
    fc.add(0, fc.getLen() - 1).print();

    cout << "Multiplication: ";
    fc.mul(0, fc.getLen() - 1).print();

    cout << endl;

    fc.insert(d);
    fc.insert(0, e); // insert at pos0
    fc.insert(f);
    fc.insert(g);
    fc.print();

    cout << "Max: ";
    fc.getMax().print();

    cout << "Min: ";
    fc.getMin().print();

    cout << "Summation: ";
    fc.add(0, fc.getLen() - 1).print();

    cout << "Multiplication: ";
    fc.mul(0, fc.getLen() - 1).print();

    cout << endl;

    fc.remove(); // removed the last fraction
    fc.print();  // notice the output

    cout << "Max: ";
    fc.getMax().print();

    cout << "Min: ";
    fc.getMin().print();

    cout << "Summation: ";
    fc.add(0, fc.getLen() - 1).print();

    cout << "Multiplication: ";
    fc.mul(0, fc.getLen() - 1).print();

    cout << endl;

    return 0;
}