#include <iostream>

using namespace std;

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