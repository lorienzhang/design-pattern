#include <stack>
#include <stdio.h>
#include <cstdio>

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

int main() {
    file_process();

    return 0;
}