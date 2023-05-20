#include <iostream>
#include <string>

using namespace std;

struct Shape 
{
    virtual ~Shape() {}

    virtual void draw() = 0;
};


// ***********************************

struct Line : Shape 
{
    Line(int x, int y) {
        cout << "Line(int x, int y)" << endl;
    }

    void draw() override {
        cout << "draw the line" << endl;
    }
};

struct Rectangle : Shape
{
    Rectangle(int x, int y, int z) {
        cout << "Line(int x, int y, int z)" << endl;
    }

    void draw() override {
        cout << "draw the rectangle" << endl;
    }
};

struct Circle : Shape
{
    void draw() override {
        cout << "draw the circle" << endl;
    }
};