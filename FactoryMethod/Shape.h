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
    void draw() override {
        cout << "draw the line" << endl;
    }
};

struct Rectangle : Shape
{
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