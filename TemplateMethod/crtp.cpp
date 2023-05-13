#include <iostream>

using namespace std;
template <typename T>
class Base 
{
public:
    Base() : i_(0) {}

    void process() { sub()->process_imp();}
    void process_imp() 
    {
        cout<<"Base::process()"<<endl;
    }

    T* sub() { return static_cast<T*>(this); }

    int get() const {return i_; }

    ~Base() {}

    // CRTP 析构需要单独实现。因为析构函数非虚
    void destroy() {
        delete sub();
    }

private:
    int i_;
};

class Sub1 : public Base<Sub1>
{
public:
    ~Sub1() {}

    void process_imp() {
        cout << "Sub1::process()" << endl;
    }
};

class Sub2 : public Base<Sub2>
{
public:
    ~Sub2() {}

    void process_imp() {
        cout << "Sub2::process()" << endl;
    }
};

int main()
{
    // 基类里面注入子类信息。编译时注入（虚函数是运行时注入子类：虚表里面）。
    Base<Sub1> *ps1 = new Sub1();
    // 全程没用虚函数，效果和虚函数一样
    ps1->process();

    Base<Sub2> *ps2 = new Sub2();
    ps2->process();

    // crtp模式析构，需要单独实现。
    // 因为crtp要取消虚函数，所以析构函数不是virtual的。不能通过delete ps1去析构
    ps1->destroy();
    ps2->destroy();
}