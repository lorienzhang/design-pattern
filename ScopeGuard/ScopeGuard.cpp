#include <stack>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

template <typename F>
class ScopeGuard 
{
public:
    explicit ScopeGuard(F&& f) : m_func(std::move(f)), m_dismiss(false){
        
    }

    explicit ScopeGuard(const F& f) : m_func(f), m_dismiss(false) {}

    ~ScopeGuard() {
        if (!m_dismiss) {
            m_func();
        }
    }

    // 移动构造
    ScopeGuard(ScopeGuard && rhs) : m_func(std::move(rhs.m_func)), m_dismiss(rhs.m_dismiss) {
        // 移动完，rhs要失效
        rhs.dismiss();
    }

    // 禁掉默认构造器
    ScopeGuard()=delete;
    // 禁掉拷贝构造器
    ScopeGuard(const ScopeGuard&)=delete;
    // 禁掉赋值运算符
    ScopeGuard& operator=(const ScopeGuard&)=delete;

    void dismiss() {
        m_dismiss = true;
    }
    
private:
    F m_func;
    bool m_dismiss;
};

// ************************************************************************************************

// 示例 1：资源的确定性释放
void file_process() 
{
    FILE* fp = fopen("filename", "wb");

    auto lam =  [&]() {fclose(fp);};

    // 这里lam是左值，调用ScopeGuard 第15行构造
    ScopeGuard<decltype(lam)> scopeGuard(lam);

    // 文件处理...

    // 关闭文件 
    // fclose(fp);
}

// 示例 2：当异常出现的时候，我想回退rollback
void process() {
    {
        stack<string> cityStack;
        cityStack.push("shanghai");

        auto lam = [&](){
            string s = cityStack.top();
            // 回退
            cityStack.pop();
            cout << "roll back: " << s << endl;
        };
        ScopeGuard<decltype(lam)> scopeGuard(lam);

        cout << "invoke..." << endl;

        // 如果代码执行这一行，说明一切正常，解除回退
        scopeGuard.dismiss();
    }
}

int main() {
    file_process();

    return 0;
}