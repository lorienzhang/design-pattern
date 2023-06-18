/** 一个简单的通信模块 */
class Messager 
{
public:
    virtual void login(string username, string password)=0;
    virtual void sendMessage(string message)=0;
    virtual void sendPicture(Image image)=0;

    virtual void playSound()=0;
    virtual void drawShape()=0;
    virtual void writeText()=0;
    virtual void connect()=0;

    virtual ~Messager() {}
};

// Messager有一些功能需要去实现

// 平台 (PC) 实现
class PCMessagerBase : public Messager
{
public:
    virtual void playSound() {
        // *****************
    }

    virtual void drawShape() {
        // *****************
    }

    virtual void writeText() {
        // *****************
    }

    virtual void connect() {
        // *****************
    }
};

// 平台 (Mobile) 实现
class MobileMessagerBase : public Messager
{
public:
    virtual void playSound() {
        // =================
    }

    virtual void drawShape() {
        // =================
    }

    virtual void writeText() {
        // =================
    }

    virtual void connect() {
        // =================
    }
};

/** 业务抽象：对不同平台还需要支持不同的功能 */ 

// 业务抽象：PC
class PCMessagerLite : public PCMessagerBase
{
    virtual void login(string username, string password) {
        PCMessagerBase::connect();
        // ................
    }

    virtual void sendMessage(string message) {
        PCMessagerBase::writeText();
        // ................
    }

    virtual void sendPicture(Image image) {
        PCMessagerBase::drawShape();
        // ................
    }
};

// perfetct业务功能和lite版的业务功能是不一样的
class PCMessagerPerfect : public PCMessagerBase
{
    virtual void login(string username, string password) {
        // 比Lite版多了一些功能
        PCMessagerBase::playSound();
        // ****************

        PCMessagerBase::connect();
        // ................
    }

    virtual void sendMessage(string message) {
        // 比Lite版多了一些功能
        PCMessagerBase::playSound();
        // ****************

        PCMessagerBase::writeText();
        // ................
    }

    virtual void sendPicture(Image image) {
        // 比Lite版多了一些功能
        PCMessagerBase::playSound();
        // ****************
        
        PCMessagerBase::drawShape();
        // ................
    }
};

// 业务抽象：Mobile
class MobileMessagerLite : public MobileMessagerBase
{
    virtual void login(string username, string password) {
        MobileMessagerBase::connect();
        // ................
    }

    virtual void sendMessage(string message) {
        MobileMessagerBase::writeText();
        // ................
    }

    virtual void sendPicture(Image image) {
        MobileMessagerBase::drawShape();
        // ................
    }
};

// perfetct业务功能和lite版的业务功能是不一样的
class MobileMessagerPerfect : public MobileMessagerBase
{
    virtual void login(string username, string password) {
        // 比Lite版多了一些功能
        MobileMessagerBase::playSound();
        // ****************

        MobileMessagerBase::connect();
        // ................
    }

    virtual void sendMessage(string message) {
        // 比Lite版多了一些功能
        MobileMessagerBase::playSound();
        // ****************

        MobileMessagerBase::writeText();
        // ................
    }

    virtual void sendPicture(Image image) {
        // 比Lite版多了一些功能
        MobileMessagerBase::playSound();
        // ****************
        
        MobileMessagerBase::drawShape();
        // ................
    }
};

void process() {
    // 使用：编译时装配
    Messager *m = new MobileMessagerPerfect();
}