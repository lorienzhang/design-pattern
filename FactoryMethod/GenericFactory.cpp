#include <memory>
#include <utility>
#include "GenericShape.h"

using namespace std;

// 一个工厂解决所有的对象创建问题
template<typename T>
struct ShapeFactory
{
    template<typename... Args>
    unique_ptr<Shape> create(Args&& ... args) {
        T* p_shape = new T(std::forward<Args>(args)...);
        unique_ptr<T> uptr_shape = unique_ptr<T>(p_shape);
        return uptr_shape;
    }
};

int main() {
    ShapeFactory<Line> s1;
    unique_ptr<Shape> p1 = s1.create(10, 20);
    p1->draw();

    cout << endl;

    ShapeFactory<Rectangle> s2;
    unique_ptr<Shape> p2 = s2.create(10, 20, 100);
    p2->draw();

}