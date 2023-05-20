#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Shape
{
    string *p;

    Shape() {}

    virtual ~Shape() = default;

    virtual void draw() = 0;

    virtual unique_ptr<Shape> clone() = 0;
};

struct Line : Shape
{
    int data;
    string text;

    // 前提：拷贝构造函数得写正确
    //      1. 如果类中没有指针，使用编译器生成default拷贝构造函数即可
    //      2. 如果类中有指针，需要自己实现，完成深克隆
    Line(const Line& line)=default;

    // 赋值运算实现和拷贝构造一样
    Line& operator=(const Line& r) {

    }

    void draw() override {
        cout << "draw the line" << endl;
    }

    unique_ptr<Shape> clone() override {
        unique_ptr<Shape> p { new Line(*this) }; // 要求深拷贝，拷贝构造函数得写正确
        return p;
    }
};

struct Rectangle : Shape 
{
    void draw() override {
        cout  << "draw the circle" << endl;
    }

    unique_ptr<Shape> clone() override {
        // 调用深克隆
        unique_ptr<Shape> p {new Rectangle(*this) };
        return p;
    }
};

struct Circle : Shape 
{
    void draw() override {
        cout  << "draw the circle" << endl;
    }

    unique_ptr<Shape> clone() override {
        // 调用深克隆
        unique_ptr<Shape> p {new Circle(*this) };
        return p;
    }
};