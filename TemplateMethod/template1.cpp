#include <stdio.h>
#include <iostream>

using namespace std;

/**
 * 库开发
 */
class Library 
{
public:
    void step1() {
        cout << "Library.step1()" << endl;
    }

    void step3() {
        cout << "Library.step3()" << endl;
    }

    void step5() {
        cout << "Library.step5()" << endl;
    }
};

/**
 * 应用开发
 */
class App 
{
public:
    bool step2() {
        cout << "App.step2()" << endl;
        number++;
        return number >= 4;
    }

    int step4() {
        cout << "App.step4()" << endl;
        return number;
    }

    int number{0};
};

int main() {
    Library lib;
    App app;

    // 应用程序开发 还需要把这5个步骤连起来
    lib.step1();
    while (!app.step2()) {
        lib.step3();
    }
    app.step4();
    lib.step5();

    return 0;
}