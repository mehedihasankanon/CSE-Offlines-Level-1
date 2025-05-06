#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

class Fraction
{
private:
    int numerator = 0, denominator = 1;

public:
    Fraction() = default;

    Fraction(int a)
    {
        numerator = a;
        denominator = 1;
    }

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

    ~Fraction() {}

    Fraction add(Fraction &f)
    {
        int new_den = this->denominator * f.denominator;
        int new_num = this->numerator * f.denominator + this->denominator * f.numerator;

        int g = gcd(new_den, new_num);

        new_den /= g;
        new_num /= g;

        return Fraction(new_num, new_den);
    }

    Fraction add(int n)
    {
        Fraction f(n);

        return (*this).add(f);
    }

    Fraction sub(Fraction &f)
    {
        int new_den = this->denominator * f.denominator;
        int new_num = this->numerator * f.denominator - this->denominator * f.numerator;

        int g = gcd(new_den, abs(new_num));

        new_den /= g;
        new_num /= g;

        return Fraction(new_num, new_den);
    }

    Fraction sub(int n)
    {
        Fraction f(n);

        return (*this).sub(f);
    }

    Fraction mul(Fraction &f)
    {
        int new_denom = this->denominator * f.denominator;
        int new_num = this->numerator * f.numerator;

        int g = gcd(new_denom, abs(new_num));

        new_denom /= g;
        new_num /= g;

        return Fraction(new_num, new_denom);
    }

    Fraction mul(int n)
    {
        Fraction f(n);

        return (*this).mul(f);
    }

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

    void print()
    {
        cout << numerator << "/" << denominator << endl;
    }

    void setNum(int x) { this->numerator = x; }
    void setDenom(int x) { this->denominator = x; }
    int getNum() { return this->numerator; }
    int getDenom() { return this->denominator; }

    void operator=(const Fraction& f)
    {
        this->denominator = f.denominator;
        this->numerator = f.numerator;
    }
};

class FractionCollection
{
private:
    Fraction *fractions = nullptr;
    int maxlength;
    int length;

public:
    FractionCollection()
    {
        fractions = new Fraction[10];
        maxlength = 10;
        length = 0;
    }

    FractionCollection(int maxSize)
    {
        fractions = new Fraction[maxSize];
        maxlength = maxSize;
        length = 0;
    }

    int getLen() { return length; }

    ~FractionCollection()
    {
        delete[] fractions;
    }

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

    void insert(Fraction f)
    {
        (*this).insert(length, f);
    }

    void remove(int pos)
    {

        if (pos > length)
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

    void remove()
    {
        (*this).remove(length - 1);
    }

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

    Fraction add(int start, int end)
    {
        Fraction ans(fractions[start].getNum(), fractions[start].getDenom());

        for (int i = start + 1; i <= end; i++)
        {
            ans = ans.add(fractions[i]);
        }

        return ans;
    }

    Fraction mul(int start, int end)
    {
        Fraction ans(fractions[start].getNum(), fractions[start].getDenom());

        for (int i = start + 1; i <= end; i++)
        {
            ans = ans.mul(fractions[i]);
        }

        return ans;
    }

    Fraction sub(int pos1, int pos2)
    {
        Fraction ans;

        return ans.add(fractions[pos1]).sub(fractions[pos2]);
    }

    Fraction div(int pos1, int pos2)
    {
        Fraction ans(1, 1);

        return ans.mul(fractions[pos1]).div(fractions[pos2]);
    }

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