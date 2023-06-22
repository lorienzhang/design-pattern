#include <iostream>
#include <memory>

using namespace std;


template <typename Derived>
class Shape 
{
public:
    virtual ~Shape() {}
    Shape(const std::string& color) : color_(color) {}
    const std::string& color() const { return color_; }

    template <typename Visitor>
    void accept(Visitor &v) {
        v.visit(static_cast<Derived&>(*this));
    }

private:
    std::string color_;
};

class Circle : public Shape<Circle>
{
public:
    using Shape::Shape;
};

class Triangle : public Shape<Triangle>
{
public:
    using Shape::Shape;
};

// 以上是稳定的，类库开发人员编写
// =================================================================================
// 以下是变化的，应用开发人员编写

class DrawingVisitor
{
public:
    void visit(Circle* c) {
        cout << "drawing to the " << c->color() << "circle" << endl;
    }

    void visit(Triangle* c) {
        cout << "drawing to the " << c->color() << "triangle" << endl;
    }
};

class ZoomingVisitor
{
public:
    void visit(Circle* c) {
        cout << "zoom to the " << c->color() << "circle" << endl;
    }

    void visit(Triangle* c) {
    }
};

int main () {
    Circle c("pie");
    Triangle t("hill");

    DrawingVisitor dv;
    c.accept(dv);  // 双重分发
    t.accept(dv);

    ZoomingVisitor zv;
    c.accept(zv);
    t.accept(zv);
}