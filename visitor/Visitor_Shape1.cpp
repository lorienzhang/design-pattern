#include <iostream>

using namespace std;

/** visitor必须要Shape的子类都放进来，这里就是Visitor模式的缺点：要求太严格 */
class Circle;
class Triangle;

class ShapeVisitor
{
public:
    virtual void visit(Circle* c) = 0;
    virtual void visit(Triangle* t) = 0;
};

class Shape 
{
public:
    virtual ~Shape() {}
    Shape(const std::string& color) : color_(color) {}
    const std::string& color() const { return color_; }

    /** 预期到未来可能会增加若干行为 */
    virtual void accept(ShapeVisitor& v) = 0;

private:
    std::string color_;
};

class Circle : public Shape
{
public:
    Circle(const std::string &color) : Shape(color) {}

    void accept(ShapeVisitor& v) {
        // 重载，根据this指针找到对应的visit方法
        v.visit(this);
    }
};

class Triangle : public Shape
{
public:
    Triangle(const std::string &color) : Shape(color) {}

    void accept(ShapeVisitor& v) {
        // 重载，根据this指针找到对应的visit方法
        v.visit(this);
    }
};

// 以上是稳定的，类库开发人员编写
// =================================================================================
// 以下是变化的，应用开发人员编写

class DrawingVisitor : public ShapeVisitor
{
public:
    void visit(Circle* c) override {
        cout << "drawing to the " << c->color() << "circle" << endl;
    }

    void visit(Triangle* c) override {
        cout << "drawing to the " << c->color() << "triangle" << endl;
    }
};

class ZoomingVisitor : public ShapeVisitor
{
public:
    void visit(Circle* c) override {
        cout << "zoom to the " << c->color() << "circle" << endl;
    }

    void visit(Triangle* c) override {
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