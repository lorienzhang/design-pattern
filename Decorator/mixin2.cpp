// 业务操作
#include <iostream>
#include <memory>

using namespace std;

class Stream {
public:
    virtual char read(int number) {
        cout << "Stream.read()" << endl;
    }
    virtual void seek(int position) {
        cout << "Stream.seek()" << endl;
    }
    virtual void write(char data) {
        cout << "Stream.write()" << endl;
    }
    virtual ~Stream() {}
};

// 主体类
class FileStream: public Stream {
public:
    char read(int number) override {
        // 读文件流
    }

    void seek(int position) override {
        // 定位文件流
    }

    void write(char data) override {
        // 写文件流
    }
};

// 主体类
class NetworkStream: public Stream {
public:
    char read(int number) override {
        // 读网络流
    }

    void seek(int position) override {
        // 定位网络流
    }

    void write(char data) override {
        // 写网络流
    }
};

// 主体类
class MemoryStream: public Stream {
public:
    char read(int number) override {
        // 读内存流
    }

    void seek(int position) override {
        // 定位内存流
    }

    void write(char data) override {
        // 写内存流
    }
};

/** 模板参数，解决了子类爆炸问题 */
template <typename StreamType>
class CryptoStream : public Stream, public StreamType  // 继承的是：模板参数
{
public:
    char read(int number) override {
        cout << "read 加密..." << endl;

        StreamType::read(number);
    }

    void seek(int position) override {
        cout << "seek 加密..." << endl;

        StreamType::seek(position);
    }

    void write(char data) override {
        cout << "write 加密..." << endl;

        StreamType::write(data);
    }
};


template <typename StreamType>
class BufferedStream : public StreamType  // 继承的是：模板参数
{
public:
    char read(int number) {
        cout << "read 缓存..." << endl;

        StreamType::read(number);
    }

    void seek(int position) {
        cout << "seek 缓存..." << endl;

        StreamType::seek(position);
    }

    void write(char data) {
        cout << "write 缓存..." << endl;

        StreamType::write(data);
    }
};

int main() {

    // 既加密又缓存的网络流
    CryptoStream<BufferedStream<NetworkStream>> stream;
    // 加密、缓存、网络流
    stream.read(0);
}