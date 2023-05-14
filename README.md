# 设计模式

[1. 设计模式最高宗旨](#1)

[2. 正交设计](#2)

[3. 软件设计复杂根本原因](#3)

[4. 面向对象设计三原则](#4)

[5. 软件设计五大原则](#5)

[6. 设计习语](#6)

[7. Template Method模式](#7)

[8. strategy模式](#8)

[9. observer观察者模式](#9)


## 1. 任何设计模式的最高宗旨（金科玉律）：高内聚，低耦合

## 2. 正交设计
### 软件设计正交性
* 正交意味着独立性，如果A的改变不影响B，那么A和B在设计上是正交的
* 设计正交，即设计解耦，通过解耦消除不相关属性的影响
### 正交设计四原则
* 消除重复性
    * 函数代码重复、数据成员重复、子父类重复、结构性重复……一切形式的重复都要革除
* 分离关注点
    * 不同关注点的变化方向不一样，分离是为了更好的隔离变化
* 减少不必要的依赖
    * 依赖总是会有的，不必要的依赖关系会带来变化中的脆弱性
* 向稳定方向依赖
    * 依赖稳定点，稳定点即编程契约：抽象类、接口

## 3. 软件设计复杂的根本原因:  变化
* 客户需求的变化
* 技术平台的变化
* 开发团队的变化
* 市场环境的变化
* ……

其实，只要明白虚函数调用机制、运行时多态的机制，大家去阅读23种设计模式的代码，都能读懂，而这种懂也仅仅是能懂代码结构的调用关系，但你深入思考：为什么这么做呢？这个时候你通常是不太理解的。

其实就是缺乏对变化经验性的判断，缺少设计模式的最高宗旨的指导，这个时候你去看设计模式的代码往往把它们当作算法去学习。这就陷入了一种误区。

## 4. 面向对象设计三原则
从抽象设计角度重新认识“面向对象”的设计内涵：
* 封装：封装责任，隔离变化；建立责任的边界
* 继承：优先使用对象组合，而不是类继承（实现继承）。
* 多态：针对接口编程，而不是针对实现编程


## 5. 软件设计五大原则（SOLID）
* SRP(Single Responsibility Principle)，单一职责原则
* OCP(Open Close Principle)，开闭原则
* LSP(Liskov Substitution Principle)，里氏替换原则
* ISP(Interface Segregation Principle)，接口隔离原则
* DIP(Dependency Inversion Principle)，依赖倒置原则

### SRP (Single Responsibility Principle)
* 一个类应该仅有一个引起它变化的原因
* 变化的方向隐含着类的责任

### OCP (Open Close Principle)
* 对扩展开放，对更改封闭
* 类模块应该是可扩展的（比如: 增加一个抽象类的子类），但是不可修改

### LSP (Liskov Substitution Principle)
* 子类必须能够替换它们的基类（IS-A）
* 继承表达类型抽象

### ISP (Interface Segregation Principle)
* 不应该强迫客户程序依赖它们不用的方法
* 接口应该小而完备

### DIP (Dependency Inversion Principle)
* 高层模块(稳定)不应该依赖低层模块(变化)，二者都应该依赖于抽象(稳定)
* 抽象(稳定)不应该依赖于实现细节(变化)，实现细节应该依赖于抽象(稳定)

## 6. 设计习语
### RAII (Resource Acquisition Is Initialization)
* RAII 是C++内存和资源管理最重要的机制之一
* RAII 通过三个环节保证内存或资源得到确定性释放
    1. 构造器获取内存
    2. 析构器释放内存
    3. 栈对象在作用域结束，即确定调用析构器，回收内存
* RAII的析构机制是由编译器根据对象生命周期销毁机制自动确保，无需手工干预。
* RAII更建议我们在声明对象时候声明成栈对象，如果非堆上对象，就用智能指针包起来

```C++
void process(int data) {
    cout<<"process start"<<endl;
    MyClass *p = new MyClass();
    if (data < 0) {
        invalid_argument exp("data");
        throw exp;
    }

    cout<<"process end"<<endl;
    delete p;
}
```
上面代码存在风险，delete p可能不会被执行。推荐的做法如下：
```C++
void process(int data) {
    cout<<"process start"<<endl;
    // 智能指针，栈对象包装堆上的对象。
    // 好处：异常出现时候，栈对象析构能正常执行
    SmartPtr p(new MyClass());

    if (data < 0) {
        invalid_argument exp("data");
        throw exp;
    }

    cout<<"process end"<<endl;
}
```

RAII核心优势：
* 异常免疫，即使异常，也确保析构
* 针对对象嵌套是递归进行的

### ScopeGuard 范围守卫
借助了RAII，在构造的时候注入一个可调用对象 
* 函数指针
* 函数对象
* Lambda
* std::function

如果我们有一段代码在函数里面想要 **确定调用**，可以使用ScopeGuard

[参考示例代码](./ScopeGuard/ScopeGuard.cpp)

## 7. Template Method模式
“组件和应用”通常有所谓的稳定点和扩展点，"晚期扩展"模式通过晚期绑定，来实现组件和应用之间的松耦合。是二者协作的常用模式。

"晚期扩展" 要点：
1. 稳定的整体结构 （这也是任何一个设计模式限制，TemplateMethod需要一个稳定的整体结构，如果这点无法满足，这个设计模式就破功了）
2. 各个子步骤需要变化或者晚期绑定

**场景描述**：一个完整功能需要，step1，step2，step3，step4，step5，5个步骤。其中1，3，5是库开发的。2，4需要应用开发者实现。也就是2，4是有改变的需求，不能写死。

### 结构化设计思路
如果不用Template Method模式，一种可能的实现如下 ( [完整示例代码](./TemplateMethod/template1.cpp) ) ：

```c++
using namespace std;

/**
 * 库开发
 */
class Library 
{
public:
    void step1() {
        cout << "Library.step1()" << endl;
    }

    void step3() {
        cout << "Library.step3()" << endl;
    }

    void step5() {
        cout << "Library.step5()" << endl;
    }

};

/**
 * 应用开发
 */
class App 
{
public:
    bool step2() {
        cout << "App.step2()" << endl;
        number++;
        return number >= 4;
    }

    int step4() {
        cout << "App.step4()" << endl;
        return number;
    }

    int number{0};
};

int main() {
    Library lib;
    App app;

    // 应用程序开发 还需要把这5个步骤连起来
    lib.step1();
    while (!app.step2()) {
        lib.step3();
    }
    app.step4();
    lib.step5();

    return 0;
}
```

流程如下图：

![](./TemplateMethod/template.png)

### Template Method方式实现

 [完整示例代码](./TemplateMethod/template2.cpp)

```c++
/**
 * 库开发
 */
class Library 
{
public:
    void run() 
    {
        step1();
        while (!step2()) {  // 多态调用
            step3();
        }
        step4();    // 多态调用
        step5();
    }

    virtual ~Library(){}

protected:
    void step1() 
    {
        cout << "Library.step1()" << endl;
    }

    void step3() 
    {
        cout << "Library.step3()" << endl;
    }

    void step5() 
    {
        cout << "Library.step5()" << endl;
    }

private:    // 设计习语：NVI：Non-Virtual Interface
    virtual bool step2() = 0;
    virtual int step4() = 0;
};

/**
 * 应用开发
 */
class App : public Library
{
private:
    bool step2() override 
    {
        cout << "App.step2()" << endl;
        number++;
        return number >= 4;
    }

    int step4() override     
    {
        cout << "App.step4()" << endl;
        return number;
    }

    int number{0};
};

int main() 
{
    Library *pLib = new App();

    // 1. 存储成本：虚表指针 + 虚表结构(共享)
    // 2. 调用成本：指针间接运算，无法inline（一些小函数代价过高）
    pLib->run();

    delete pLib;

    return 0;
}
```

程序流程如下图：

![](./TemplateMethod/template2.png)

模式要点总结：
1. 程序的主流程被复用了（稳定的结构），也就是run方法
2. step2和step4是扩展点，留给应用程序晚期扩展
3. Template Method的典型应用"不要调用我，让我来调用你"反向控制结构

#### 代码细节
问：虚函数step2，step4为什么private

答：**NVI：Non-Virtual Interface（公有接口非虚，虚函数尽量私有）**。因为虚函数作为整个程序骨架的一部分，不会被外界独立调用。所以要进行private，除非子类有调用需求，可以设为protected。

### 编译时多态实现TemplateMethod
#### 设计习语：CRTP
Curiously Recurring Template Pattern，奇异递归模板模式，简称CRTP。通过将基类的模板参数设为子类，从而实现了静态多态。CRTP用模板的方式模拟虚函数调用机制，让类没有任何虚函数。C++独有，其它语言没有。

虚函数成本：
1. 存储成本：虚表指针 + 虚表结构(共享)
2. 调用成本：指针间接运算，无法inline（一些小函数代价过高）

CRTP示例代码如下：

```c++
#include <iostream>

using namespace std;
template <typename T>
class Base 
{
public:
    Base() : i_(0) {}

    void process() { sub()->process_imp();}
    void process_imp() 
    {
        cout<<"Base::process()"<<endl;
    }

    T* sub() { return static_cast<T*>(this); }

    int get() const {return i_; }

    ~Base() {}

    // CRTP 析构需要单独实现。因为析构函数非虚
    void destroy() {
        // 析构子类，子类会自动调用父类析构
        delete sub();
    }

private:
    int i_;
};

class Sub1 : public Base<Sub1>
{
public:
    ~Sub1() {}

    void process_imp() {
        cout << "Sub1::process()" << endl;
    }
};

class Sub2 : public Base<Sub2>
{
public:
    ~Sub2() {}

    void process_imp() {
        cout << "Sub2::process()" << endl;
    }
};

int main()
{
    // 基类里面注入子类信息。编译时注入（虚函数是运行时注入子类：虚表里面）。
    Base<Sub1> *ps1 = new Sub1();
    // 全程没用虚函数，效果和虚函数一样
    ps1->process();

    Base<Sub2> *ps2 = new Sub2();
    ps2->process();

    // crtp模式析构，需要单独实现。
    // 因为crtp要取消虚函数，所以析构函数不是virtual的。不能通过delete ps1去析构
    ps1->destroy();
    ps2->destroy();
}
```

CRTP关键点：
1. 在编译时通过模板参数注入子类信息，从而实现编译时多态
2. CRTP的destroy需要特殊照顾下。因为CRTP的目的干掉虚函数，所以基类的析构函数不是virtual的。不能通过delete ps1去析构对象。
3. CRTP比虚函数的性能优势：十几倍~四十几倍

TemplateMethod CRTP示例代码如下:  [完整示例代码](./TemplateMethod/crtp_template.cpp)

```C++
template <typename T> 
class Library
{
public:
    void run() {
        step1();
        while(!sub()->step2())  // 子类调用
            step3();
        sub()->step4();     // 子类调用
        step5();
    }

    void destroy() {
        delete sub();
    }

protected:
    // 获取子类信息
    T* sub() {
        return static_cast<T*>(this);
    }

    void step1() {
        cout << "Library.step1()" << endl;
    }

    void step3() {
        cout << "Library.step3()" << endl;
    }

    void step5() {
        cout << "Library.step5()" << endl;
    }

    int number {0};

public:
    bool step2() { return false; }
    int step4() { return 0; }

    ~Library() {}
};


class App : public Library<App>
{
public:
    // 不是虚函数
    bool step2() {
        cout << "App.step2()" << endl;
        number++;
        return number >= 4;
    }

    // 不是虚函数
    int step4() {
        cout << "App.step4()" << endl;
        return number;
    }
};

int main() {
    // 父类注入子类信息，new一个子类对象
    Library<App> *pLib = new App();
    pLib->run();
    pLib->destroy();
    return 0;
}
```

CRTP要点解析：
1. 通过模板参数将子类类型在编译时注入基类，从而实现基类提前获取子类信息。
2. static_cast将基类指针转型为模板子类T的指针
3. 删除对象也要使用编译时多态删除，避免直接delete

## 8. strategy模式
某些对象的算法可能多种多样，经常改变，如果将这些算法编码到对象中，将会使对象变得异常复杂。

如何在运行时去透明的更改对象的算法，并且是它们可以互相替换，将算法和对象本身解耦。 

想象一个场景：订单税种计算，不同国家的税计算方法不同

最容易想到的做法：
```C++
enum TaxBase 
{
    CN_Tax, // 中国税计算
    US_Tax, // 美国税计算
    DE_Tax // 德国税计算
};

class SalesOrder
{
    TaxBase tax;

public:
    double calcTax() {
        if (tax == CN_Tax) {
            // CN****************
        } else if (tax == US_Tax) {
            // US****************
        } else if (tax == DE_Tax) {
            // DE****************
        }

        // ........
    }
};
```

如果从静态的角度看这段逻辑，没有任何问题。但如果加入时间维度，针对未来的变化，假设未来要支持法国税的计算，该怎么解决呢？


我们需要修改两个地方：
```C++
enum TaxBase 
{
    CN_Tax, 
    US_Tax, 
    DE_Tax, 
    FR_Tax // 更改
};

class SalesOrder
{
    TaxBase tax;

public:
    double calcTax() {
        if (tax == CN_Tax) {
            // CN****************
        } else if (tax == US_Tax) {
            // US****************
        } else if (tax == DE_Tax) {
            // DE****************
        } else if (tax == FR_Tax) {
            // 更改
        }

        // ........
    }
};
```

这个修改违背了一个设计原则：开闭原则。

类模块应该使用扩展的方式来支持未来的变化，而不是改源代码来应对未来的变化。

### Strategy模式实现
 [完整示例代码](./strategy/strategy2.cpp)
```C++
/**
 * 抽象出税收计算策略接口
 */
class TaxStrategy
{
public:
    virtual double calc(const Context& context) = 0;
    virtual ~TaxStrategy(){}
};

// 中国
class CNTax : public TaxStrategy
{
public:
    virtual double calc(const Context &context) override {

    }
};

// 美国
class USTax : public TaxStrategy
{
public:
    virtual double calc(const Context &context) override {

    }
};

// 德国
class DETax : public TaxStrategy
{
public:
    virtual double calc(const Context &context) override {

    }
};

class SalesOrder
{
private:
    TaxStrategy* strategy;

public:
    SalesOrder(StrategyFactory* strategyFactory) {
        this->strategy = strategyFactory->newStrategy();
    }
    ~SalesOrder() {
        delete this->strategy;
    }

    double calcTax() {
        // ...

        Context context();
        // 多态调用
        double val = strategy->calc(context);

        //...
    }
};
```

如果未来新增一个法国的税收计算，只需要新增一个法国计算实现即可。业务代码SalesOrder不需要改变。这就遵循了开闭原则。
```C++
// 扩展：法国
class FRTax : public TaxStrategy
{
public:
    virtual double calc(const Context &context) override {

    }
};
```

Strategty模式定义（GoF）：定义一系列算法，把他们一个个封装起来，并且是他们可以互相替换（变化）。该模式使得算法可独立于它们的客户程序（稳定）而变化（扩展方式）。

模式类图：

![](./strategy/strategy.png)

代码中出现了大量的if-else（bad smell），其实strategy模式的雏形就出现了。当这个不是绝对的，如果if-else的分支是稳定不变的，可以不用考虑strategy模式。比如：一周7天，7个分支，这个肯定不会变化。

从更抽象的层面来看，template method和strategty模式很类似，都是一种晚期绑定的实现。


## 9. observer观察者模式
观察者模式一种解决什么样的松耦合问题？

某些对象需要建立一种"通知依赖关系"；一个对象（目标对象）的状态发生改变，所有依赖对象（观察者对象）都将得到通知。如果这样的依赖过于紧密，将使软件不能很好的抵御变化。

考虑一个场景：文件下载，更新UI进度条
```C++
#include <iostream>

using namespace std;

// 文件下载
class FileDownloader
{
    string m_filePath;
    int m_fileNumber;
    ProgressBar* m_progressBar;

public:
    FileDownloader(const string& filePath, 
    int fileNumber,
    ProgressBar* progressBar):
        m_filePath(filePath),
        m_fileNumber(fileNumber),
        m_progressBar(progressBar)
    {
    }

    void download() {
        // 1. 网络下载准备

        // 2. 文件流处理

        // 3. 设置进度条
        for (int i = 0; i < m_fileNumber; i++) {
            // ...
            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;
            // 更新进度条
            m_progressBar->setValue(progressValue);
        }
    }
};

// UI视图
class MainForm : public MainForm
{
    ProgressBar *progressBar;

public:
    void button_click() {
        string file_path = "xxx";
        int number =5;
        FileDownloader downloader(file_path, number, progressBar);

        downloader.download();
    }
};
```

**这个设计最大的问题**：FileDownloader依赖了一个UI控件。违背设计原则：依赖倒置原则。

改进：解除FileDownloader对ProgressBar依赖，需要对进度通知进行抽象.
```C++
#include <iostream>
#include <memory>

using namespace std;

// 进度的抽象，供FileDownloader依赖
class IProgress 
{
public:
    virtual void doProgress(float value)=0;
    virtual ~IProgress(){}
};

// 控制台输出进度
class ConsoleNotifer : public IProgress
{
    void doProgress(float value) override {
        cout << ".";
    }
};

class FileDownloader
{
    string m_filePath;
    int m_fileNumber;
    shared_ptr<IProgress> m_iprogress;

public:
    FileDownloader(const string& filePath, 
    int fileNumber):
        m_filePath(filePath),
        m_fileNumber(fileNumber)
    {
    }

    void download() {
        // 1. 网络下载准备

        // 2. 文件流处理

        // 3. 设置进度条
        for (int i = 0; i < m_fileNumber; i++) {
            // ...
            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;
            // 对外通知
            m_iprogress->doProgress(progressValue);
        }
    }

    /**
     * 设置回调通知
     */
    void setProgress(shared_ptr<IProgress> progress) {
        m_iprogress = progress;
    }
};

class MainForm : public Form, public IProgress, public enable_shared_from_this<MainForm>
{
    shared_ptr<ProgressBar> progressBar;

public:
    void button_click() {
        string file_path = "xxx";
        int number =5;

        FileDownloader downloader(file_path, number);

        // 正确
        // shared_ptr<IProgress> ip = make_shared<ConsoleNotifer>();
        // downloader.setProgress(ip);

        // 错误：不能对this指针构造shared_ptr，会导致this指针被析构两次
        // shared_ptr<IProgress> ip{this};
        // downloader.setProgress(ip);

        // 正确
        shared_ptr<IProgress> ip = shared_from_this();
        downloader.setProgress(ip);

        // 执行下载
        downloader.download();
    }

    void doProgress(float value) override {
        // 更新进度条
        progressBar->setValue(value);
    }
};
```

使用shared_ptr对回调进行包装。这里有几个细节：
1. shared_ptr对this指针包装，要使用enable_shared_from_this
2. 一旦使用shared_from_this，外部就不能使用MainForm裸指针，必须用shared_ptr对MainForm进行包装使用。

接下来看下观察者模式**一对多**的版本:

```C++
#include <iostream>
#include <memory>
#include <list>

using namespace std;

// 进度的抽象，供FileDownloader依赖
class IProgress 
{
public:
    virtual void doProgress(float value)=0;
    virtual ~IProgress(){}
};

// 控制台输出进度
class ConsoleNotifer : public IProgress
{
    void doProgress(float value) override {
        cout << ".";
    }
};

class FileDownloader
{
    string m_filePath;
    int m_fileNumber;

    // 这里持有共享指针，可能导致MainForm生命周期被拉长
    // FileDownloader存在，如果MainForm不存在了，就会出错
    list<shared_ptr<IProgress>> m_iprorgressList;

public:
    FileDownloader(const string& filePath, 
    int fileNumber):
        m_filePath(filePath),
        m_fileNumber(fileNumber)
    {
    }

    void download() {
        // 1. 网络下载准备

        // 2. 文件流处理

        // 3. 设置进度条
        for (int i = 0; i < m_fileNumber; i++) {
            // ...
            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;

            // 对外通知
            onProgress(progressValue);
        }
    }

    void addIProgress(const shared_ptr<IProgress>& iprogress) {
        m_iprorgressList.push_back(iprogress);
    }

    void removeIProgress(const shared_ptr<IProgress>& iprogress) {
        m_iprorgressList.remove(iprogress);
    }

protected:
    void onProgress(float value) {
        for (auto& progress : m_iprorgressList) {
            progress->doProgress(value);
        }
    }
};

class MainForm : public Form, public IProgress, 
            public enable_shared_from_this<MainForm>
{
    shared_ptr<ProgressBar> progressBar;

public:
    void button_click() {
        string file_path = "xxx";
        int number =5;

        FileDownloader downloader(file_path, number);

        shared_ptr<IProgress> ip = make_shared<ConsoleNotifer>();
        downloader.addIProgress(ip);

        downloader.addIProgress(shared_from_this());

        downloader.download();
    }

    void doProgress(float value) override {
        // 更新进度条
        progressBar->setValue(value);
    }
};
```

这个版本观察者还有个问题：
1. FileDownloader通过shared_ptr持有外部MainForm、ConsoleNotifer。这导致MainForm、ConsoleNotifer生命周期被FileDownloader拉长了。

如果希望MainForm该释放就释放，不要因为我做了别人的观察者，把我的生命周期拉长。对于FileDownloader，如果观察者的生存周期结束，就不要去通知了。

使用weak_ptr改进：

[完整示例代码](./observer/FileDownloader4.cpp)
```C++
#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

using namespace std;

// 进度的抽象，供FileDownloader依赖
class IProgress 
{
public:
    virtual void doProgress(float value)=0;
    virtual ~IProgress(){}
};

// 控制台输出进度
class ConsoleNotifer : public IProgress
{
    void doProgress(float value) override {
        cout << ".";
    }
};

class FileDownloader
{
    string m_filePath;
    int m_fileNumber;

    list<weak_ptr<IProgress>> m_iprorgressList;

public:
    FileDownloader(const string& filePath, 
    int fileNumber):
        m_filePath(filePath),
        m_fileNumber(fileNumber)
    {
    }

    void download() {
        // 1. 网络下载准备

        // 2. 文件流处理

        // 3. 设置进度条
        for (int i = 0; i < m_fileNumber; i++) {
            // ...
            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;

            // 通知观察者
            onProgress(progressValue);
        }
    }

    void addIProgress(const shared_ptr<IProgress>& iprogress) {
        m_iprorgressList.push_back(iprogress);
    }

    void removeIProgress(const shared_ptr<IProgress>& iprogress) {
        remove_if(m_iprorgressList.begin(), m_iprorgressList.end(), 
            [](const weak_ptr<Observer>& wptr) {
                if (wptr.expired()) {
                    return true;
                } else {
                    shared_ptr<IProgress> sptr = wptr.lock();
                    return (sptr == iprogress);
                }
            });
    }

protected:
    virtual void onProgress(float value) {
        for (auto& progress : m_iprorgressList) {

            // 弱引用检查生命周期是否存在？
            shared_ptr<IProgress> s_progress = progress.lock();
            if (s_progress != nullptr) {
                s_progress->doProgress(value);
            }
        }

        // 记住：删除空的弱引用
        remove_if(m_iprorgressList.begin(), m_iprorgressList.end(), 
                [](const weak_ptr<Observer>& wptr) {
                    return wptr.expired();
                });
    }
};

class MainForm : public Form, public IProgress, 
            public enable_shared_from_this<MainForm>
{
    shared_ptr<ProgressBar> progressBar;

public:
    void button_click() {
        string file_path = "xxx";
        int number =5;

        FileDownloader downloader(file_path, number);

        shared_ptr<IProgress> ip = make_shared<ConsoleNotifer>();
        downloader.addIProgress(ip);

        downloader.addIProgress(shared_from_this());

        downloader.download();
    }

    void doProgress(float value) override {
        // 更新进度条
        progressBar->setValue(value);
    }
};
```

要点：
每次对观察者通知结束，要将空的弱引用删除，否则这些弱引用对象会一直存在list中，占内存。

还可以进一步优化：现在整个观察者模式的代码都揉在FileDownloader当中，这个不太好。比较好的做法是，把这套观察者模式的代码抽象到基类当中。

[完整示例代码](./observer/FileDownloader5.cpp)
```c++
#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

using namespace std;

// 进度的抽象，供FileDownloader依赖
class IProgress 
{
public:
    virtual void doProgress(float value)=0;
    virtual ~IProgress(){}
};

// 基类：专门管理观察者对象
class Subject
{
private:
    list<weak_ptr<IProgress>> m_iprogressList; //弱引用

protected:
    virtual void onProgress(float value) {
        for (auto& progress : m_iprogressList) {

            // 弱引用检查生命周期是否存在？
            shared_ptr<IProgress> s_progress = progress.lock();
            if (s_progress != nullptr) {
                s_progress->doProgress(value);
            }
        }

        // 记住：删除空的弱引用
        remove_if(m_iprogressList.begin(), m_iprogressList.end(), 
                [](const weak_ptr<Observer>& wptr) {
                    return wptr.expired();
                });
    }

public:
    void addIProgress(const shared_ptr<IProgress>& iprogress) {
        m_iprogressList.push_back(iprogress);
    }

    void removeIProgress(const shared_ptr<IProgress>& iprogress) {
        remove_if(m_iprogressList.begin(), m_iprogressList.end(), 
            [](const weak_ptr<Observer>& wptr) {
                if (wptr.expired()) {
                    return true;
                } else {
                    shared_ptr<IProgress> sptr = wptr.lock();
                    return (sptr == iprogress);
                }
            });
    }
};

// 控制台输出进度
class ConsoleNotifer : public IProgress
{
    void doProgress(float value) override {
        cout << ".";
    }
};

class FileDownloader : public Subject
{
    string m_filePath;
    int m_fileNumber;

    list<weak_ptr<IProgress>> m_iprorgressList;

public:
    FileDownloader(const string& filePath, 
    int fileNumber):
        m_filePath(filePath),
        m_fileNumber(fileNumber)
    {
    }

    void download() {
        // 1. 网络下载准备

        // 2. 文件流处理

        // 3. 设置进度条
        for (int i = 0; i < m_fileNumber; i++) {
            // ...
            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;

            // 调用基类，通知观察者
            onProgress(progressValue);
        }
    }

    void onProgress(float value) override {
        // 父类onProgress，通知观察者
        Subject::onProgress(value);

        // 子类扩展...
    }
};

class MainForm : public Form, public IProgress, 
            public enable_shared_from_this<MainForm>
{
    shared_ptr<ProgressBar> progressBar;

public:
    void button_click() {
        string file_path = "xxx";
        int number =5;

        FileDownloader downloader(file_path, number);

        shared_ptr<IProgress> ip = make_shared<ConsoleNotifer>();
        downloader.addIProgress(ip);

        downloader.addIProgress(shared_from_this());

        downloader.download();
    }

    void doProgress(float value) override {
        // 更新进度条
        progressBar->setValue(value);
    }
};
```

这就是观察者Observer模式的最经典的面向对象实现~

要点总结：
1. 使用面向对象抽象，Observer模式使得我们可以独立改变目标和观察者，从而使二者之间的依赖关系达到松耦合
2. 观察者自己决定是否需要订阅通知，目标对象对此一无所知
3. Observer模式对于观察者对象的生命周期管理，可以考虑使用shared_ptr+weak_ptr来支持无"生命周期依赖"的观察者

下面看下，**观察者模式的泛型版本，函数对象**

[完整示例代码](./observer/FileDownloader_Generic1.cpp)

```c++
#include <list>
#include <iostream>

using namespace std;

template<typename ProgressObserver>
class Subject
{
private:
    list<ProgressObserver> m_iprogressList;

public:
    void addIProgress(const ProgressObserver& iprogress) {
        m_iprogressList.push_back(iprogress);
    }

    void removeIProgress(const ProgressObserver& iprogress) {
        m_iprogressList.remove(iprogress);
    }

protected:
    void onProgress(float value) {
        for (auto& progress : m_iprogressList) {
            progress(value);    // 隐式约定，传入函数对象（仿函数）
        }
    }
};

template<typename ProgressObserver>
class FileDownloader : public Subject<ProgressObserver>
{
    string m_filePath;
    int m_fileNumber;

public:
    FileDownloader(const string& filePath, int fileNumber) :
        m_fileNumber(fileNumber),
        m_filePath(filePath) {
    }

    void download() {
        // 1. 网络下载准备

        // 2. 文件流处理

        // 3. 设置进度
        for (int i = 0; i < m_fileNumber; i++) {
            // ...
            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;
            
            this->onProgress(progressValue);  // 通知观察者
        }
    }
};

// 函数对象
struct ConsoleProgressObserver
{
    int _id;
    ConsoleProgressObserver(int id) : _id(id) {}

    friend bool operator==(const ConsoleProgressObserver& left, const ConsoleProgressObserver& right) {
        return left._id == right._id;
    }

    // 重载了()，这个对象就满足可调用对象，仿函数
    void operator()(float value) {
        cout << ".";
    }
};

// 函数对象
struct ProgressBarObserver
{
    void operator()(float value) {
        // ...
    }
};

int main() {
    // ConsoleProgressObserver
    FileDownloader<ConsoleProgressObserver> fd("http://xxx.xxx.com", 5);
    // ProgressBarObserver
    // FileDownloader<ProgressBarObserver> fd2("http://xxx.xxx.com", 5);

    ConsoleProgressObserver pob(101);
    fd.addIProgress(pob);
    fd.download();
}
```

要点：
1. 可调用对象的类型通过模板参数传入
2. 通知观察者：progress(value)，progress都是一些可调用对象。比如：ConsoleProgressObserver，ProgressBarObserver都重写了()运算符。
3. 函数对象、Lambda仅支持单一类型的policy。如需支持多态，即观察者容器支持添加多种回调结构，可用**std::function**

std::function及其灵活，配合lambda表达式可以传入更多的类型。

 [完整示例代码](./observer/FileDownloader_Generic2.cpp)

```c++
#include <list>
#include <iostream>
#include <functional>

using namespace std;

// std::function  支持多种类型的可调用对象
using ProgressListener = std::function<void(float)>;

class Subject
{
private:
    list<ProgressListener> m_iprogressList; // 共享引用

public:
    void addIProgress(const ProgressListener& iprogress) {
        m_iprogressList.push_back(iprogress);
    }

    // void removeIProgress(const ProgressListener& iprogress) {
    //     m_iprogressList.remove(iprogress);
    // }

protected:
    void onProgress(float value) {
        for (auto& progress : m_iprogressList) {
            progress(value);    // 隐式约定，传入函数对象（仿函数）
        }
    }
};

class FileDownloader : public Subject
{
    string m_filePath;
    int m_fileNumber;

public:
    FileDownloader(const string& filePath, int fileNumber) :
        m_fileNumber(fileNumber),
        m_filePath(filePath) {
    }

    void download() {
        // 1. 网络下载准备

        // 2. 文件流处理

        // 3. 设置进度
        for (int i = 0; i < m_fileNumber; i++) {
            // ...
            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;
            
            this->onProgress(progressValue);  // 通知观察者
        }
    }
};

// std::function 绑定仿函数
struct ConsoleProgressObserver
{
    int _id;
    ConsoleProgressObserver(int id) : _id(id) {}

    // 重载了()，这个对象就满足可调用对象
    void operator()(float value) {
        cout << "." << endl;
    }
};

// std::function 绑定静态函数
struct ProgressBarObserver
{
    static void update(float value) {
        cout << "ProgressBarObserver: " << value << endl;
    }
};

// std::function 绑定成员函数
struct LoggerObserver
{
    void update(float value) const {
        cout << "LoggerObserver: " << value << endl;
    }
};


int main() {
    FileDownloader fd("http://xxx.xxx.com", 10);

    ConsoleProgressObserver call1(101);
    fd.addIProgress(call1);   // 绑定函数对象(仿函数)

    ProgressListener call2 = &ProgressBarObserver::update; // 绑定类中静态函数
    fd.addIProgress(call2);

    LoggerObserver obj;
    ProgressListener call3 = [=](float value) {obj.update(value);}; // 借助lambda绑定实例对象
    fd.addIProgress(call3);

    fd.addIProgress([](float value) { cout << "lambda observer: " <<  value << endl;}); // 绑定lambda

    fd.download();

    return 0;
}
```

要点：
1. 使用std::function，可以传入仿函数，类中静态函数，实例对象，lambda等，及其灵活
2. 但是std::function没有重载==运算符，导致无法执行remove操作
3. 对于remove删除操作，如果使用函数对象，可以重载==运算符，借助id判断是否相等。