#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;

/** 基类控件 */
class Control
{
public:
    virtual ~Control() {}

    virtual bool isComposite() {
        return false;
    }

    // 业务逻辑方法：可能是坐标移动、可能是背景色更改
    virtual void process() = 0;
};

class Label : public Control
{
public:
    void process() override {
        cout << "...Label" << endl;
    }

    virtual ~Label() {
        cout << "~Label" << endl;
    }
};

class TexBox : public Control
{
public:
    void process() override {
        cout << "...TexBox" << endl;
    }

    virtual ~TexBox() {
        cout << "~TexBox" << endl;
    }
};

class Button : public Control
{
public:
    void process() override {
        cout << "...Button" << endl;
    }

    virtual ~Button() {
        cout << "~Button" << endl;
    }
};

/** 树形控件 */
class ControlComposite : public Control
{
protected:
    list<shared_ptr<Control>> children_;

public:
    list<shared_ptr<Control>> getChildren() {
        return children_;
    }

    void add(const shared_ptr<Control>& component) {
        this->children_.push_back(component);
    }

    void remove(const shared_ptr<Control>& component) {
        children_.remove(component);
    }

    bool isComposite() override {
        return true;
    }

    void process() override {
        // 1. 处理当前树节点
        cout << "...ControlComposite" << endl;

        // 2. 处理所有子节点
        for (auto& c : children_) {
            c->process();   // 多态调用
        }
    }

    virtual ~ControlComposite() {
        cout << "~ControlComposite" << endl;
    }
};

int main() {
    auto composite = make_shared<ControlComposite>();
    {
        auto c1 = make_shared<Label>();
        auto c2 = make_shared<TexBox>();
        auto c3 = make_shared<Button>();

        composite->add(c1);
        composite->add(c2);
        composite->add(c3);

        auto composite2 = make_shared<ControlComposite>();
        composite2->add(c2);
        composite->add(composite2);
    }

    cout << "------------process start" << endl;

    composite->process();

    cout << "------------process end" << endl;

}