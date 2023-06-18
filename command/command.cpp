
#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

/** 假设我们设计一个菜单，每个菜单关联各种各样的命令 */

class Command
{
public:
    virtual void execute()=0;
};

class CopyCommand : public Command 
{
    int id;
    string arg;
public:
    CopyCommand(const string& a) : arg(a) {}

    void execute() override {
        cout << "#1 process..." << arg << endl;
    }
};

class CutCommand : public Command 
{
    int arg;
public:
    CutCommand(const int& a) : arg(a) {}

    void execute() override {
        cout << "#2 process..." << arg << endl;
    }
};

class PasteCommand : public Command 
{
    int arg;
public:
    PasteCommand(const int& a) : arg(a) {}

    void execute() override {
        cout << "#2 process..." << arg << endl;
    }
};

class MacroCommand : public Command 
{
    vector<unique_ptr<Command>> commands;

public:
    void addCommand(unique_ptr<Command> c) {
        // unique_ptr不支持拷贝，需要使用的移动的方式将所有权转进来
        commands.push_back(std::move(c));
    }

    void execute() override {
        for (auto &c : commands) {
            c->execute();
        }
    }
};

int main() {

    // cmd1, cmd2, macro都是对象，但本质上表征的是行为
    auto cmd1 = make_unique<CopyCommand>("Arg ###");
    auto cmd2 = make_unique<CutCommand>(100);

    MacroCommand macro;
    macro.addCommand(std::move(cmd1));
    macro.addCommand(std::move(cmd2));

    macro.execute();
}

// C++本身的语言机制，天然支持command模式，即：函数对象
// 函数对象的多态性靠模板参数实现的，函数对象本质上也是：行为对象化

// 所以，C++出现函数对象后，以虚函数设计为基础的command就不是很流行了。
template<typename T>
class FunctionObject
{
public:
    void operator()(T data) {

    }
};