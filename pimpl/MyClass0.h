
class MyClass {
public:
    ~MyClass();
    MyClass();

    MyClass::MyClass(const MyClass& other);
    MyClass& MyClass::operator=(MyClass rhs);

    void process();

private:
    string text;
    int data;

};