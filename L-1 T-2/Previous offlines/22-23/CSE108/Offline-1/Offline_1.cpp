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
    Rectangle Rects[100];
    int idxRec = 0;
    Triangle Tris[100];
    int idxTri = 0;
    Circle Circs[100];
    int idxCir = 0;

public:
    void addRectangle(Rectangle &Rec)
    {
        Rects[idxRec].setWidth(Rec.getWidth());
        Rects[idxRec].setHeight(Rec.getHeight());
        char new_s[100];
        strcpy(new_s, Rec.getColor());
        Rects[idxRec].setColor(new_s);
        idxRec++;
    }
    void addTriangle(Triangle &Tri)
    {
        Tris[idxTri].setA(Tri.getA());
        Tris[idxTri].setB(Tri.getB());
        Tris[idxTri].setC(Tri.getC());
        char new_s[100];
        strcpy(new_s, Tri.getColor());
        Tris[idxTri].setColor(new_s);
        idxTri++;
    }
    void addCircle(Circle &Cir)
    {
        Circs[idxCir].setRad(Cir.getRad());
        char new_s[100];
        strcpy(new_s, Cir.getColor());
        Circs[idxCir].setColor(new_s);
        idxCir++;
    }

    int getRectCount() { return idxRec; }
    int getTriCount() { return idxTri; }
    int getCircCount() { return idxCir; }

    void printRectangles()
    {
        for (int i = 0; i < idxRec; i++)
        {
            cout << "Rectangle " << i << ": " << "length: " << Rects[i].getHeight() << " " << "width: " << Rects[i].getWidth() << endl;
        }
    }

    void printTriangles()
    {
        for (int i = 0; i < idxTri; i++)
        {
            cout << "Triangle " << i << ": " << "a: " << Tris[i].getA() << " " << "b: " << Tris[i].getB() << "c: " << Tris[i].getC() << endl;
        }
    }

    void printCircles()
    {
        for (int i = 0; i < idxCir; i++)
        {
            cout << "Circle " << i << ": " << "radius: " << Circs[i].getRad() << endl;
        }
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

    shapes.addRectangle(r1);
    shapes.addTriangle(t1);
    shapes.addCircle(c1);

    Rectangle r2(15, 25, "Black");
    shapes.addRectangle(r2);
    Triangle t2(5, 12, 13, "White");
    shapes.addTriangle(t2);

    cout << "Number of Rectangles: " << shapes.getRectCount() << endl;
    cout << "Number of Triangles: " << shapes.getTriCount() << endl;
    cout << "Number of Circles: " << shapes.getCircCount() << endl;
    cout << "--------------------------------------" << endl;

    shapes.printRectangles();
    shapes.printTriangles();
    shapes.printCircles();

    return 0;
}
