#include <iostream>
#include <memory>
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
public:
    Header header;
    Body body;
    Footer footer;
};

// *******************************

/** 专门做文档的构建工作 */
class DocumentBuilder
{
public:
    virtual Header buildHeader() = 0;
    virtual Body buildBody() = 0;
    virtual Page buildPage(int index) = 0;
    virtual Footer buildFooter() = 0;
};

class Director
{
    unique_ptr<DocumentBuilder> builder;
public:
    void setBuilder(unique_ptr<DocumentBuilder> newBuilder) {
        builder = std::move(newBuilder);
    }

    unique_ptr<Document> buildDocument() {

        unique_ptr<Document> doc(new Document());

        doc->header = builder->buildHeader();
        
        int pageNum = readPageNumber();
        doc->body = builder->buildBody();

        for (int i = 0; i < pageNum; i++) {
            doc->body.pages[i] = builder->buildPage(i);
        }

        doc->footer = builder->buildFooter();

        return doc;
    }
};

class HTMLBuilder : public DocumentBuilder
{
protected:
    Header buildHeader() override {
        // **********************
    }
    Body buildBody() override {
        // **********************
    }
    Page buildPage(int index) override {
        // **********************
    }
    Footer buildFooter() override {
        // **********************
    }
};

class MarkDownBuilder : public DocumentBuilder
{
protected:
    Header buildHeader() override {
        // #######################
    }
    Body buildBody() override {
        // #######################
    }
    Page buildPage(int index) override {
        // #######################
    }
    Footer buildFooter() override {
        // #######################
    }
};

int main() {
    Director director;

    unique_ptr<DocumentBuilder> builder(new HTMLBuilder);
    director.setBuilder(std::move(builder));
    
    director.buildDocument();
}