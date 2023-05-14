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