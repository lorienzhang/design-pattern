
#include <iostream>

// 想藏的东西在cpp文件中
class MyClass::Impl
{
public:
    virtual void invoke() {
        std::cout << "invoke" << endl;
    }

    virtual ~Impl() {
        std::cout << "~Impl" << endl;
    }

    Impl() {
        std::cout << "Impl" << endl;
    }

    String text;
    int data;
};

MyClass::MyClass() : pimpl(new Impl())
{

}

MyClass::~MyClass()
{
    delete pimpl;
}

// 赋值与拷贝
MyClass::MyClass(const MyClass& other) : pimpl(new Impl(*other.pimpl)) {

}

MyClass& MyClass::operator=(const MyClass& rhs) {
    if (this == &rhs) {
        return *this;
    }

    // copy & swap
    MyClass temp(rhs);
    swap(this->pimpl, temp.pimp);
    return *this;
}

// 移动
MyClass::MyClass(MyClass&& other) : pimpl(other.pimpl) {
    other.pimpl = nullptr;
}

MyClass& MyClass::operator=(MyClass&& rhs) {
    if (this == &rhs) {
        return *this;
    }

    MyClass temp(std::move(rhs));
    swap(this->pimpl, temp.pimpl);
    return *this;
}

void MyClass::process() {
    return pimpl->invoke();
}