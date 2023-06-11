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

/*
1: Stream

n=3: FileStream, MemoryStream, NetworkStream  主体类

m=2： Crypto，Buffered  扩展

子类个数：3*2 + 3*1 = 9


*/

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
class CryptoFileStream: public FileStream {
public:
    char read(int number) override {
        // 额外的加密操作

        FileStream::read(number); // 读文件流

        // 额外的加密操作
    }

    void seek(int position) override {
        // 额外的加密操作

        FileStream::seek(position); // 读文件流

        // 额外的加密操作
    }

    void write(char data) override {
        // 额外的加密操作

        FileStream::write(data); // 读文件流

        // 额外的加密操作
    }
};

class CryptoNetworkStream: public NetworkStream {
public:
    char read(int number) override {
        // 额外的加密操作

        NetworkStream::read(number); // 读网络流

        // 额外的加密操作
    }

    void seek(int position) override {
        // 额外的加密操作

        NetworkStream::seek(position); // 读网络流

        // 额外的加密操作
    }

    void write(char data) override {
        // 额外的加密操作

        NetworkStream::write(data); // 读网络流

        // 额外的加密操作
    }
};

class CryptoMemoryStream: public MemoryStream {
public:
    char read(int number) override {
        // 额外的加密操作

        MemoryStream::read(number); // 读内存流

        // 额外的加密操作
    }

    void seek(int position) override {
        // 额外的加密操作

        MemoryStream::seek(position); // 读内存流

        // 额外的加密操作
    }

    void write(char data) override {
        // 额外的加密操作

        MemoryStream::write(data); // 读内存流

        // 额外的加密操作
    }
};

// 扩展操作2: 比如需要对流进行缓存
class BufferedFileStream : public FileStream {
    // ...
};

class BufferedNetworkStream : public NetworkStream {
    // ...
};

class BufferedMemoryStream : public MemoryStream {
    // ...
};

// 扩展操作3: 同时加密+缓存
class CyptoBufferedFileStream : public BufferedFileStream {
    // ...
};

class CyptoBufferedNetworkStream : public BufferedNetworkStream {
    // ...
};

class CyptoBufferedMemoryStream : public BufferedMemoryStream {
    // ...
};

void process() {
    
    // 编译时装配
    CryptoFileStream *fs1 = new CryptoFileStream();
    BufferedFileStream *fs2 = new BufferedFileStream();
    CyptoBufferedFileStream *fs3 = new CyptoBufferedFileStream();

    delete fs1;
    delete fs2;
    delete fs3;
}