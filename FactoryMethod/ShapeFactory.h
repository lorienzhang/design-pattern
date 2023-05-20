#include "Shape.h"
#include <memory>
#include <type_traits>

struct ShapeFactory
{
    // 这个不可取，返回抽象类，对象会被切割
    // virtual Shape create() = 0;
    
    // 在智能指针之前，智能用这种方法。这里有个所有权问题，要把指针所有权交出去。容易出现内存错误
    // virtual Shape* create() = 0;

    // 工厂函数和unique_ptr天然是一个好的搭配
    virtual unique_ptr<Shape> create() = 0;
    virtual ~ShapeFactory() {}
};

struct LineFactory : ShapeFactory
{
    unique_ptr<Shape> create() override {
        Line *p = new Line();
        auto pLine = unique_ptr<Line>(p);
        return pLine;
    }
};

struct RectangleFactory : ShapeFactory
{
    unique_ptr<Shape> create() override {
        Rectangle *p = new Rectangle();
        auto pRectangle = unique_ptr<Rectangle>(p);
        return pRectangle;
    }
};

struct CircleFactory : ShapeFactory
{
    unique_ptr<Shape> create() override {
        Circle *p = new Circle();
        auto pCircle = unique_ptr<Circle>(p);
        return pCircle;
    }
};