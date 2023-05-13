#include <stdio.h>
#include <iostream>

using namespace std;

/**
 * 库开发
 */
class Library 
{
public:
    void run() 
    {
        step1();
        while (!step2()) {  // 多态调用
            step3();
        }
        step4();    // 多态调用
        step5();
    }

    virtual ~Library(){}

protected:
    void step1() 
    {
        cout << "Library.step1()" << endl;
    }

    void step3() 
    {
        cout << "Library.step3()" << endl;
    }

    void step5() 
    {
        cout << "Library.step5()" << endl;
    }

private:    // 设计习语：NVI：Non-Virtual Interface
    virtual bool step2() = 0;
    virtual int step4() = 0;
};

/**
 * 应用开发
 */
class App : public Library
{
private:
    bool step2() override 
    {
        // Library::step2();

        cout << "App.step2()" << endl;
        number++;
        return number >= 4;
    }

    int step4() override     
    {
        cout << "App.step4()" << endl;
        return number;
    }

    int number{0};
};

int main() 
{
    Library *pLib = new App();

    // 1. 存储成本：虚表指针 + 虚表结构(共享)
    // 2. 调用成本：间接指针，无法inline
    pLib->run();

    delete pLib;

    return 0;
}