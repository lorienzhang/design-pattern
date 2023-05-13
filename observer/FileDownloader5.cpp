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