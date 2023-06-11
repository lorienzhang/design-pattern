// 业务操作
#include <bits/types/FILE.h>
#include <iostream>

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

// 扩展操作1: 比如需要对流进行加密

// 问：既然继承转组合，这里为什么又要继承Stream？
// 答：这是为了遵守接口的合约，属于接口继承

// decorator模式的特征：对Stream类，既继承又组合
class CryptoStream : public Stream {

    // 组合：复用实现
    Stream *stream;  // 运行时装配：new FileStream? new NetworkStream? new MemoryStream

public:
    CryptoStream(Stream *_ps) : stream(_ps) {

    }

    char read(int number) override {
        // 额外的加密操作

        stream->read(number);

        // 额外的加密操作
    }

    void seek(int position) override {
        // 额外的加密操作

        stream->seek(position); 

        // 额外的加密操作
    }

    void write(char data) override {
        // 额外的加密操作

        stream->write(data);

        // 额外的加密操作
    }
};

// 扩展操作2: 比如需要对流进行缓存
class BufferedStream : public Stream {

    Stream *stream;  // 运行时装配：new FileStream? new NetworkStream? new MemoryStream

public:
    BufferedStream(Stream *_ps) : stream(_ps) {

    }
    // ...
};


void process() {
    
    /** 运行时装配 */ 

    // 文件流
    Stream *fs0 = new FileStream();
    // 加密文件流
    Stream *fs1 = new CryptoStream(fs0);
    // 缓存文件流
    Stream *fs2 = new BufferedStream(fs0);
    // 既加密又缓存
    Stream *fs3 = new CryptoStream(fs2);

    delete fs0;
    delete fs1;
    delete fs2;
    delete fs3;
}