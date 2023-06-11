#include <iostream>

using namespace std;

template<typename... Mixins>
class Point : public Mixins...  // Point类有个：变参基类
{    
public:
    double x, y;
    // 调用多个基类的缺省构造函数
    Point() : Mixins()..., x(0.0), y(0.0) {}
    Point(double x, double y) : Mixins()..., x(x), y(y) {}
};


template<typename... Mixins>
class Line : public Mixins...  // Line类有个：变参基类
{    
public:
    double x, y;
    // 调用多个基类的缺省构造函数
    Line() : Mixins()..., x(0.0), y(0.0) {}
    Line(double x, double y) : Mixins()..., x(x), y(y) {}
};

/** 接下来要给Point和Line添加Label和Color功能 */

class Label
{
public:
    std::string label;
    Label() : label("") {}
};

class Color
{
public:
    unsigned char red = 0, green = 0, blue = 0;
};


/** Mixin设计 */

// LabelPoint就具有了Point和Label的双重功能
// 相当于：class LabelPoint : public Point, public Label {};
using LabelPoint = Point<Label>;

// ColorPoint 具有Point和Color的双重功能
// 相当于：class ColorPoint : public Point, public Color {};
using ColorPoint = Point<Color>;

// LabelColorPoint 具有Point，Label，Color三种功能
// 相当于：class LabelColorPoint : public Point, public Label, public Color {};
using LabelColorPoint = Point<Label, Color>;

int main () {
    LabelColorPoint pt;
    // Point属性
    pt.x = 100;
    pt.y = 200;
    // Label属性
    pt.label="2D";
    // Color属性
    pt.red=255;
    pt.green=255;
    pt.blue=255;
}