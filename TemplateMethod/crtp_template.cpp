#include <iostream>
#include <type_traits>

using namespace std;

template <typename T> 
class Library
{
public:
    void run() {
        step1();
        while(!sub()->step2())  // 子类调用
            step3();
        sub()->step4();     // 子类调用
        step5();
    }

    void destroy() {
        delete sub();
    }

protected:
    // 获取子类信息
    T* sub() {
        return static_cast<T*>(this);
    }

    void step1() {
        cout << "Library.step1()" << endl;
    }

    void step3() {
        cout << "Library.step3()" << endl;
    }

    void step5() {
        cout << "Library.step5()" << endl;
    }

    int number {0};

public:
    bool step2() { return false; }
    int step4() { return 0; }

    ~Library() {}
};


class App : public Library<App>
{
public:
    // 不是虚函数
    bool step2() {
        cout << "App.step2()" << endl;
        number++;
        return number >= 4;
    }

    // 不是虚函数
    int step4() {
        cout << "App.step4()" << endl;
        return number;
    }
};

int main() {
    // 父类注入子类信息，new一个子类对象
    Library<App> *pLib = new App();
    pLib->run();
    pLib->destroy();
    return 0;
}