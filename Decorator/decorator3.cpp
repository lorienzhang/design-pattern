// 业务操作
#include <bits/types/FILE.h>
#include <iostream>
#include <memory>

class Stream {
public:
    virtual char read(int number)=0;
    virtual void seek(int position)=0;
    virtual void write(char data)=0;
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

// 中间基类，去除构造函数重复代码
class DecoratorStream: public Stream {

protected:
    std::unique_ptr<Stream> s; // 运行时装配：new FileStream? new NetworkStream? new MemoryStream

    DecoratorStream(std::unique_ptr<Stream> _s) : s(std::move(_s)) {

    }

};

// 扩展操作1: 比如需要对流进行加密
class CryptoStream : public DecoratorStream { 

public:

    // 使用父类构造器
    using DecoratorStream::DecoratorStream;

    char read(int number) override {
        // 额外的加密操作

        s->read(number);

        // 额外的加密操作
    }

    void seek(int position) override {
        // 额外的加密操作

        s->seek(position); 

        // 额外的加密操作
    }

    void write(char data) override {
        // 额外的加密操作

        s->write(data);

        // 额外的加密操作
    }
};

// 扩展操作2: 比如需要对流进行缓存
class BufferedStream : public DecoratorStream {

public:

    // 使用父类构造器
    using DecoratorStream::DecoratorStream;

    char read(int number) override {
        // 额外的缓存操作

        s->read(number);

        // 额外的缓存操作
    }

    void seek(int position) override {
        // 额外的缓存操作

        s->seek(position); 

        // 额外的缓存操作
    }

    void write(char data) override {
        // 额外的缓存操作

        s->write(data);

        // 额外的缓存操作
    }
};


void process() {
    
    /** 运行时装配 */ 

    std::unique_ptr<Stream> ps = make_unique<FileStream>();
    std::unique_ptr<CryptoStream> cs = make_unique<FileStream>(ps);
    std::unique_ptr<BufferedStream> bcs = make_unique<FileStream>(cs);
    
}