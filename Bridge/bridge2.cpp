// 业务抽象
class Messager 
{
protected:
    MessagerImp *messageImp;  // 指针，具体是PC平台还是Mobile平台，由未来运行时决定

public:
    virtual void login(string username, string password)=0;
    virtual void sendMessage(string message)=0;
    virtual void sendPicture(Image image)=0;

    virtual ~Messager() {}
};

// 平台实现
class MessagerImp
{
public:

    virtual void playSound()=0;
    virtual void drawShape()=0;
    virtual void writeText()=0;
    virtual void connect()=0;

    virtual ~MessagerImp() {}
};

// Messager有一些功能需要去实现

// 平台 (PC) 实现
class PCMessagerImp : public MessagerImp
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
class MobileMessagerImp : public MessagerImp
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

// 业务抽象
class MessagerLite : public Messager
{
    virtual void login(string username, string password) {
        messageImp->connect();
        // ................
    }

    virtual void sendMessage(string message) {
        messageImp->writeText();
        // ................
    }

    virtual void sendPicture(Image image) {
        messageImp->drawShape();
        // ................
    }
};

class MessagerPerfect : public Messager
{
    virtual void login(string username, string password) {
        // 比Lite版多了一些功能
        messageImp->playSound();
        // ****************

        messageImp->connect();
        // ................
    }

    virtual void sendMessage(string message) {
        // 比Lite版多了一些功能
        messageImp->playSound();
        // ****************

        messageImp->writeText();
        // ................
    }

    virtual void sendPicture(Image image) {
        // 比Lite版多了一些功能
        messageImp->playSound();
        // ****************
        
        messageImp->drawShape();
        // ................
    }
};

void process() {

    // 使用：运行时装配，即运行时组合在一起
    MessagerImp *mImp = new PCMessagerImp()
    Messager *m = new MessagerPerfect(mImp);

}