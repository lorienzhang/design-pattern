
class MyClass {
public:
    ~MyClass();
    MyClass();

    MyClass::MyClass(const MyClass& other);
    MyClass& MyClass::operator=(MyClass rhs);

    void process();

private:
    // 前置声明，类内类型（不想暴露给客户的数据成员，包装成另外一个类）
    class Impl;

    // 实现类指针，且必须为指针（指针有个特点：不要求Impl是完整类型）
    Impl* pimpl;    // Impl不完整类型

};