class ISubject
{
public:
    virtual void process() = 0;
};

/** server-side object */
class RealSubject : public ISubject
{
public:
    void process() override {

    }
};

// ****************************************

// client-size 设计
// proxy设计
class SubjectProxy : public ISubject
{
public:
    void process() override {
        // 对RealSubject的一种间接访问
        // ...
    }
};

class ClientApp
{
    ISubject *subject;

public:
    ClientApp() {
        subject = new SubjectProxy(...);
    }

    void doTask() {
        // ...
        subject->process();
        // ...
    }
};