#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Shape
{
    virtual void draw() = 0;
    virtual unique_ptr<Shape> clone() const = 0;
    virtual ~Shape()=default;
};

// 中间基类
template<typename T>
struct CloneShape: Shape
{
    // 中间基类：就这一个方法，目的是消除clone的重复代码，子类就不用再写clone了 
    unique_ptr<Shape> clone() const override {
        // 注意: 1.static_cast，
        //       2. 转成T&，为了减少拷贝构造
        //       3. const T&是clone函数后面const要求
        unique_ptr<T> p { new T(static_cast<const T&>(*this)) };
        return p;
    }
};

struct Line : CloneShape<Line>
{
    int data;
    string text;

    // 前提：拷贝构造函数需要正确实现
    //      1. 如果类中没有指针，使用编译器生成default拷贝构造函数即可
    //      2. 如果类中有指针，需要自己实现，完成深克隆
    Line(const Line& line) {
        
    }

    // 赋值运算实现和拷贝构造一样
    Line& operator=(const Line& r) {

    }

    void draw() override {
        cout << "draw the line" << endl;
    }
};

struct Rectangle : CloneShape<Rectangle>
{
    Rectangle() {}

    Rectangle(const Rectangle& rhs) {

    }

    void draw() override {
        cout  << "draw the circle" << endl;
    }
};

struct Circle : CloneShape<Circle>
{
    Circle() {}

    Circle(const Circle& chs) {

    } 

    void draw() override {
        cout  << "draw the circle" << endl;
    }
};

// 客户程序使用示例
struct client
{
    void invoke(const Shape& prototype) {
        unique_ptr<Shape> ps = prototype.clone();
        ps->draw();
    }
};