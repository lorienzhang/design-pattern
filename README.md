# 设计模式

## 一、任何设计模式的最高宗旨（金科玉律）：高内聚，低耦合

## 二、正交设计
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

## 三、软件设计复杂的根本原因:  变化
* 客户需求的变化
* 技术平台的变化
* 开发团队的变化
* 市场环境的变化
* ……

其实，只要明白虚函数调用机、运行时多态的机制，大家去阅读23种设计模式的代码，都能读懂，而这种懂也仅仅是能懂代码结构的调用关系，但你深入思考：为什么这么做呢？这个时候你通常是不太理解的。

其实就是缺乏对变化经验性的判断，缺少设计模式的最高宗旨的指导，这个时候你去看设计模式的代码往往把它们当作算法去学习。这就陷入了一种误区。

## 四、面向对象设计三原则
从抽象设计角度重新认识“面向对象”的设计内涵：
* 封装：封装责任，隔离变化；建立责任的边界
* 继承：优先使用对象组合，而不是类继承（实现继承）。
* 多态：针对接口编程，而不是针对实现编程


## 五、软件设计五大原则（SOLID）
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

## 六、设计习语
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