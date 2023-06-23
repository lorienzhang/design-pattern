#include <iostream>
#include <vector>

using namespace std;

struct Header {};
struct Page {};
struct Body {
    vector<Page> pages;
};
struct Footer {};

class Document
{
    Header header;
    Body body;
    Footer footer;

protected:
    virtual Header buildHeader() = 0;
    virtual Body buildBody() = 0;
    virtual Page buildPage(int index) = 0;
    virtual Footer buildFooter() = 0;

public:
    Document() {
        // 注意：c++构造函数调用虚函数是静态绑定，没有多态效应
        header = buildHeader(); // 静态绑定

        int pageNum = readPageNumber(); // 静态绑定
        body = buildBody();

        for (int i = 0; i < pageNum; i++) {
            body.pages[i] = buildPage(i); // 静态绑定
        }
        footer = buildFooter(); // 静态绑定

        return doc;
    }
};

class HTMLDocument : public Document
{
protected:
    Header buildHeader() override {

    }
    Body buildBody() override {

    }
    Page buildPage(int index) override {

    }
    Footer buildFooter() override {

    }
};

class MarkDownDocument : public Document
{
protected:
    Header buildHeader() override {

    }
    Body buildBody() override {

    }
    Page buildPage(int index) override {

    }
    Footer buildFooter() override {
        
    }
};