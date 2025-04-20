#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

class Rectangle
{
private:
    double width, height;
    char *color = nullptr;

public:
    Rectangle() = default;

    Rectangle(double a, double b, const char *col)
    {
        height = a;
        width = b;
        color = (char *)malloc(100);
        strcpy(color, col);
    }

    Rectangle(Rectangle &r1)
    {
        width = r1.width;
        height = r1.height;
        char new_s[100];
        strcpy(new_s, r1.color);
        color = (char *)malloc(100);
        strcpy(color, new_s);
    }

    ~Rectangle()
    {
        free(color);
    }

    double getPerimeter() { return 2 * (width + height); }

    double getArea() { return width * height; }

    char *getColor() { return color; }

    void setColor(const char *newCol)
    {
        free(color);
        color = (char *)malloc(100);
        strcpy(color, newCol);
    }

    void setWidth(double wid)
    {
        width = wid;
    }

    void setHeight(double hei)
    {
        height = hei;
    }

    double getHeight()
    {
        return height;
    }

    double getWidth()
    {
        return width;
    }
};

class Triangle
{
private:
    double a, b, c;
    char *color = nullptr;

public:
    Triangle() = default;

    Triangle(double a, double b, double c, const char *col)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        color = (char *)malloc(100);
        strcpy(color, col);
    }

    Triangle(Triangle &r1)
    {
        a = r1.a;
        b = r1.b;
        c = r1.c;
        char new_s[100];
        strcpy(new_s, r1.color);
        color = (char *)malloc(100);
        strcpy(color, new_s);
    }

    ~Triangle()
    {
        free(color);
    }

    double getPerimeter() { return a + b + c; }

    double getArea()
    {
        double s = 0.5 * (a + b + c);
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    char *getColor() { return color; }

    void setColor(const char *newCol)
    {
        free(color);
        color = (char *)malloc(100);
        strcpy(color, newCol);
    }

    double getA() { return a; }
    double getB() { return b; }
    double getC() { return c; }

    void setA(double A) { a = A; }
    void setB(double B) { b = B; }
    void setC(double C) { c = C; }
};

class Circle
{
private:
    const double PI = 3.14159265;
    double r;
    char *color = nullptr;

public:
    Circle() = default;

    Circle(double r, const char *col)
    {
        this->r = r;
        color = (char *)malloc(100);
        strcpy(color, col);
    }

    Circle(Circle &r1)
    {
        r = r1.r;
        char new_s[100];
        strcpy(new_s, r1.color);
        color = (char *)malloc(100);
        strcpy(color, new_s);
    }

    ~Circle()
    {
        free(color);
    }

    double getPerimeter() { return 2 * PI * r; }

    double getArea() { return PI * r * r; }

    char *getColor() { return color; }

    void setColor(const char *newCol)
    {
        free(color);
        color = (char *)malloc(100);
        strcpy(color, newCol);
    }

    void setRad(double rad) { r = rad; }

    double getRad() { return r; }
};

class ShapeCollection
{
private:
    Rectangle **Rects = new Rectangle *[1];
    int idxRec = 0, RecSize = 1;
    Triangle **Tris = new Triangle *[1];
    int idxTri = 0, TriSize = 1;
    Circle **Circs = new Circle *[1];
    int idxCir = 0, CircSize = 1;

public:
    void add(Rectangle Rec)
    {
        if (idxRec == RecSize)
        {
            cout << "Increasing capacity of rectangles from " << RecSize << " to " << 2 * RecSize << endl;
            RecSize *= 2;
            Rectangle **Rects1 = new Rectangle *[RecSize];
            for (int i = 0; i < RecSize / 2; i++)
            {
                Rects1[i] = clone(*Rects[i]);
                delete Rects[i];
            }
            delete Rects;
            Rects = Rects1;
        }
        Rects[idxRec++] = clone(Rec);
    }
    void add(Triangle Tri)
    {
        if (idxTri == TriSize)
        {
            cout << "Increasing capacity of triangles from " << TriSize << " to " << 2 * TriSize << endl;
            TriSize *= 2;
            Triangle **Tris1 = new Triangle *[TriSize];
            for (int i = 0; i < TriSize / 2; i++)
            {
                Tris1[i] = clone(*Tris[i]);
                delete Tris[i];
            }
            delete Tris;
            Tris = Tris1;
        }
        Tris[idxTri++] = clone(Tri);
    }
    void add(Circle Cir)
    {
        if (idxCir == CircSize)
        {
            cout << "Increasing capacity of circles from " << CircSize << " to " << 2 * CircSize << endl;
            CircSize *= 2;
            Circle **Circs1 = new Circle *[CircSize];
            for (int i = 0; i < CircSize / 2; i++)
            {
                Circs1[i] = clone(*Circs[i]);
                delete Circs[i];
            }
            delete Circs;
            Circs = Circs1;
        }
        Circs[idxCir++] = clone(Cir);
    }

    int getRectCount() { return idxRec; }
    int getTriCount() { return idxTri; }
    int getCircCount() { return idxCir; }

    void printRectangles()
    {
        for (int i = 0; i < idxRec; i++)
        {
            cout << "Rectangle " << i << ": " << "length: " << Rects[i]->getHeight() << " " << "width: " << Rects[i]->getWidth() << endl;
        }
    }

    void printTriangles()
    {
        for (int i = 0; i < idxTri; i++)
        {
            cout << "Triangle " << i << ": " << "a: " << Tris[i]->getA() << " " << "b: " << Tris[i]->getB() << " " << "c: " << Tris[i]->getC() << endl;
        }
    }

    void printCircles()
    {
        for (int i = 0; i < idxCir; i++)
        {
            cout << "Circle " << i << ": " << "radius: " << Circs[i]->getRad() << endl;
        }
    }

    Rectangle *clone(Rectangle &Rec)
    {
        return new Rectangle(Rec);
    }

    Triangle *clone(Triangle &Tri)
    {
        return new Triangle(Tri);
    }

    Circle *clone(Circle &Cir)
    {
        return new Circle(Cir);
    }

    ~ShapeCollection()
    {
        for (int i = 0; i < idxRec; i++)
            delete Rects[i];
        delete Rects;
        for (int i = 0; i < idxTri; i++)
            delete Tris[i];
        delete Tris;
        for (int i = 0; i < idxCir; i++)
            delete Circs[i];
        delete Circs;
    }
};

int main()
{
    Rectangle r1(10, 20, "Red");

    cout << "Rectangle Perimeter: " << r1.getPerimeter() << endl;
    cout << "Rectangle Area: " << r1.getArea() << endl;
    cout << "Rectangle Color: " << r1.getColor() << endl;

    r1.setColor("Yellow");
    cout << "Rectangle Color: " << r1.getColor() << endl;
    cout << "--------------------------------------" << endl;

    Triangle t1(3, 4, 5, "Blue");
    cout << "Triangle Perimeter: " << t1.getPerimeter() << endl;
    cout << "Triangle Color: " << t1.getColor() << endl;
    cout << "Triangle Area: " << t1.getArea() << endl;
    t1.setColor("Orange");
    cout << "Triangle Color: " << t1.getColor() << endl;
    cout << "--------------------------------------" << endl;

    Circle c1(7, "Green");
    cout << "Circle Perimeter: " << c1.getPerimeter() << endl;
    cout << "Circle Area: " << c1.getArea() << endl;
    cout << "Circle Color: " << c1.getColor() << endl;
    c1.setColor("Purple");
    cout << "Circle Color: " << c1.getColor() << endl;
    cout << "--------------------------------------" << endl;

    ShapeCollection shapes;

    shapes.add(r1);
    shapes.add(t1);
    shapes.add(c1);

    Rectangle r2(15, 25, "Black");
    Rectangle r3(150, 225, "Green");
    shapes.add(r2);
    shapes.add(r3);
    Triangle t2(5, 12, 13, "White");
    shapes.add(t2);

    cout << "Number of Rectangles: " << shapes.getRectCount() << endl;
    cout << "Number of Triangles: " << shapes.getTriCount() << endl;
    cout << "Number of Circles: " << shapes.getCircCount() << endl;
    cout << "--------------------------------------" << endl;

    shapes.printRectangles();
    shapes.printTriangles();
    shapes.printCircles();

    return 0;
}
