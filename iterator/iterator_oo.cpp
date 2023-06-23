#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Iterator
{
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual void iSDone() = 0;
    virtual T& current() = 0;
};

/** 集合 */
template<typename T>
class MyCollection
{
public:
    Iterator<T> getIterator() {
        // ....
    }
};

/** 迭代器实现 */
template<typename T>
class CollectionIterator : public Iterator<T>
{
    // 集合
    MyCollection<T> mc;

public:
    CollectionIterator(const MyCollection<T> & c) : mc(c) {}

    void first() override {

    }

    void next() override {

    }

    bool isDone() override {

    }

    T& current() override {

    }
};

void myAlgorithm() {
    MyCollection<int> mc;
    Iterator<int> iter = mc.getIterator();
    for (iter.first(); !iter.isDone(); iter.next()) {
        cout << iter.current() << endl;
    }
}