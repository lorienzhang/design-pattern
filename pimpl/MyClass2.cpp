
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

MyClass::MyClass() : pimpl(make_unique<Impl>())
{

}

// 析构
MyClass::~MyClass()=default; // 这里生成的析构器可以看到Impl的定义

// 移动构造，unique_ptr只支持移动
MyClass::MyClass(MyClass&& other)=default;

// 移动赋值
MyClass& MyClass::operator=(MyClass&& rhs)=default;

/** unique_ptr不支持拷贝构造和赋值操作符，需要自己实现 */ 

// 拷贝构造
MyClass::MyClass(const MyClass& other) : pimpl(make_unique<Impl>(*other.pimpl)) {

}

// 赋值
MyClass& MyClass::operator=(const MyClass& rhs) {
    if (this == &rhs) {
        return *this;
    }

    *pimpl=*rhs.pimpl;
    return *this;
}

void MyClass::process() {
    return pimpl->invoke();
}