#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Circle;
class Triangle;

class ShapeVisitor
{
public:
    virtual void visit(Circle& c) = 0;
    virtual void visit(Triangle& t) = 0;
};

class Shape 
{
public:
    virtual ~Shape() {}
    Shape(const std::string& color) : color_(color) {}
    const std::string& color() const { return color_; }

    // accept提到基类
    virtual void accept(ShapeVisitor& v) = 0;

private:
    std::string color_;
};

/** 中间层：CRTP */
template<typename Derived>
class Visitable : public Shape
{
public:
    using Shape::Shape;
    void accept(ShapeVisitor& v) override {
        v.visit(static_cast<Derived&>(*this));
    }
};

class Circle : public Visitable<Circle>
{
public:
    using Visitable<Circle>::Visitable;
};

class Triangle : public Visitable<Triangle>
{
public:
    using Visitable<Triangle>::Visitable;
};

// 以上是稳定的，类库开发人员编写
// =================================================================================
// 以下是变化的，应用开发人员编写

class DrawingVisitor : public ShapeVisitor
{
public:
    void visit(Circle& c) override{
        cout << "drawing to the " << c.color() << "circle" << endl;
    }

    void visit(Triangle& c) override{
        cout << "drawing to the " << c.color() << "triangle" << endl;
    }
};

class ZoomingVisitor : public ShapeVisitor
{
public:
    void visit(Circle& c) override {
        cout << "zoom to the " << c.color() << "circle" << endl;
    }

    void visit(Triangle& c) override {
    }
};

int main () {
    
    vector<unique_ptr<Shape>> v;

    // make_unique返回的就是右值，不需要std::move
    v.push_back(make_unique<Circle>("pie"));

    unique_ptr<Triangle> p(new Triangle("hill"));
    v.push_back(std::move(p));

    v.push_back(make_unique<Circle>("ring"));

    DrawingVisitor dv;
    ZoomingVisitor zv;

    for_each(v.begin(), v.end(),
         [=](unique_ptr<Shape>& elem) mutable {
                elem->accept(zv);
            }
    );

}