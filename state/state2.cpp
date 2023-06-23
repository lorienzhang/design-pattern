#include <iostream>
#include <string>

using namespace std;

/** 
 * 1. 把以前枚举类型转换成抽象基类 
 * 2. 把所有和状态有关的操作，operation1，operation2 全部变成状态对象的行为
 */
class NetworkState 
{
public:
    NetworkState* pNext;
    
    // 和状态有关的操作，变成状态对象的行为
    virtual void operation1() = 0;
    // 和状态有关的操作，变成状态对象的行为
    virtual void operation2() = 0;
    
    virtual ~NetworkState() {}
};

class OpenState : public NetworkState
{
    static NetworkState *m_instance;

public:
    static NetworkState* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new OpenState();
        }
        return m_instance;
    }

    void operation1() override {
        // 1. operation1 for Network_Open

        // 2. change state，换的对象，不是枚举
        pNext = CloseState::getInstance();
    }

    void operation2() override {
        // 1. operation2 for Network_Open

        // 2. change state，换的对象，不是枚举
        pNext = ConnectState::getInstance();
    }
};

class CloseState : public NetworkState
{
    static NetworkState *m_instance;

public:
    static NetworkState* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new CloseState();
        }
        return m_instance;
    }

    void operation1() override {
        // 1. operation1 for Network_Close

        // 2. change state
        pNext = ConnectState::getInstance();
    }

    void operation2() override {
        // 1. operation2 for Network_Close

        // 2. change state
        pNext = OpenState::getInstance();
    }
};

class ConnectState : public NetworkState
{
    static NetworkState *m_instance;

public:
    static NetworkState* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new ConnectState();
        }
        return m_instance;
    }

    void operation1() override {
        // 1. operation1 for Network_Connect

        // 2. change state
        pNext = OpenState::getInstance();
    }

    void operation2() override {
        // 1. operation2 for Network_Connect

        // 2. change state
        pNext = CloseState::getInstance();
    }
};

// ====================================================================

class NetworkProcessor
{
    // 状态对象，不是枚举了。
    NetworkState *pState;

public:
    NetworkProcessor(NetworkState *pState) {
        this->pState = pState;
    }

    void operation1() {
        // ...

        pState->operation1();
        // update状态对象
        pState = pState->pNext;

        // ...
    }

    void operation2() {
        // ...
        
        pState->operation2();
        // update状态对象
        pState = pState->pNext;

        // ...
    }
};
