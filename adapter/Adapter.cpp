#include <memory>
#include <iostream>

using namespace std;

/** 目标接口（新接口） */
class ITarget
{
public:
    virtual void process() = 0;
};

/** 遗留接口（老接口） */
class IAdaptee
{
public:
    virtual void foo(int data) = 0;
    virtual int bar() = 0;
};

class OldClass : public IAdaptee 
{
    // ...
};

// 对象适配器（继承新接口，组合老接口）
class Adapter : public ITarget  // 继承--接口规约
{
protected:
    unique_ptr<IAdaptee> pAdaptee;  // 组合--复用实现

public:
    Adapter(unique_ptr<IAdaptee> p) :pAdaptee(std::move(p)) {

    }

    void process() override {
        int data = pAdaptee->bar();
        pAdaptee->foo(data);
    }
};

// 类适配器（多继承），不鼓励。
class Adapter2 : public ITarget, 
                protected OldClass {

};

int main() {
    unique_ptr<IAdaptee> pAdaptee(new OldClass());

    unique_ptr<ITarget> pTarget{std::move(pAdaptee)};

    pTarget->process();
}