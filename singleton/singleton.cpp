#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Singleton 
{
private:
    Singleton(int data) : m_data(data) {

    }

    Singleton(const Singleton& rhs) = delete;
    Singleton& operator=(const Singleton& rhs) = delete;

public:
    void print() {
        cout << m_data << endl;
    }

    static Singleton& getSingleton();

private:
    int m_data;
};

Singleton& Singleton::getSingleton() {
    // C++11: 静态对象初始化本身不会导致数据竞争
    // 但如果构造器内部使用共享数据，仍然有线程安全问题
    static Singleton instance(100);
    return instance;
}

int main() {
    Singleton& s1 = Singleton::getSingleton();
    Singleton& s2 = Singleton::getSingleton();

    cout << &s1 << endl;
    cout << &s2 << endl;
}
