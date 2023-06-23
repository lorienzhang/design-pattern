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
    void buildDocument() {  // 单独整个方法去build

        header = buildHeader();     // 动态绑定

        int pageNum = readPageNumber(); 
        body = buildBody();

        for (int i = 0; i < pageNum; i++) {
            body.pages[i] = buildPage(i); 
        }
        footer = buildFooter();

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

int main() {
    MarkDownDocument doc{};
    doc.buildDocument();
}