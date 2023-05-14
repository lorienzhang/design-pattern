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

// 可调用对象
struct ConsoleProgressObserver
{
    int _id;
    ConsoleProgressObserver(int id) : _id(id) {}

    friend bool operator==(const ConsoleProgressObserver& left, const ConsoleProgressObserver& right) {
        return left._id == right._id;
    }

    // 重载了()，这个对象就满足可调用对象
    void operator()(float value) {
        cout << ".";
    }
};

// 可调用对象
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