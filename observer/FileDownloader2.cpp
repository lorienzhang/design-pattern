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

        // shared_ptr<IProgress> ip = make_shared<ConsoleNotifer>();
        // downloader.setProgress(ip);

        // 这里有个问题：不能对this指针构造shared_ptr，会导致this指针被析构两次
        // shared_ptr<IProgress> ip{this};
        // downloader.setProgress(ip);
        shared_ptr<IProgress> ip = shared_from_this();
        downloader.setProgress(ip);

        downloader.download();
    }

    void doProgress(float value) override {
        // 更新进度条
        progressBar->setValue(value);
    }
};