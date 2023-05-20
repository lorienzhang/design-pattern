#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// 数据库访问有关的基类
class IDBConnection 
{};

class IDBConnectionFactory
{
public:
    virtual unique_ptr<IDBConnection> createDBConnection()=0;
};

class IDBCommand
{};
class IDBCommandFactory
{
public:
    virtual unique_ptr<IDBCommand> createDBCommand()=0;
};

class IDBReader
{};
class IDBReaderFactory
{
public:
    virtual unique_ptr<IDBReader> createDBReader()=0;
};

// ************* 支持MySql *****************
class SqlConnection : public IDBConnection
{};
class SqlConnectionFactory : public IDBConnectionFactory 
{
public:
    unique_ptr<IDBConnection> createDBConnection() override {

    }
};

class SqlCommand : public IDBCommand
{};
class SqlCommandFactory : public IDBCommandFactory
{
public:
    unique_ptr<IDBCommand> createDBCommand() override {

    }
};

class SqlDataReader : public IDBReader
{};
class SqlDataReaderFactory : public IDBReaderFactory
{
public:
    unique_ptr<IDBReader> createDBReader() {

    }
};

// ************* 支持Oracle *****************
class OracleConnection : public IDBConnection
{};
class OracleConnectionFactory : public IDBConnectionFactory 
{
public:
    unique_ptr<IDBConnection> createDBConnection() override {

    }
};

class OracleCommand : public IDBCommand
{};
class OracleCommandFactory : public IDBCommandFactory
{
public:
    unique_ptr<IDBCommand> createDBCommand() override {

    }
};

class OracleDataReader : public IDBReader
{};
class OracleDataReaderFactory : public IDBReaderFactory
{
public:
    unique_ptr<IDBReader> createDBReader() {

    }
};


// -----------------------------------------------------------
class EmployeeDAO
{
    // 通过抽象的工厂基类创建对象
    unique_ptr<IDBConnectionFactory> dbConnectionFactory;
    // 通过抽象的工厂基类创建对象
    unique_ptr<IDBCommandFactory> dbCommandFactory;
    // 通过抽象的工厂基类创建对象
    unique_ptr<IDBReaderFactory> dbReaderFactory;

    EmployeeDAO() {
        dbConnectionFactory = ...;
        dbCommandFactory = ...;
        dbReaderFactory = ...;
    } 

public:
    vector<Employee> getEmployees() {
        unique_ptr<IDBConnection> connection = dbConnectionFactory->createDBConnection();
        connection->connectString("...");

        unique_ptr<IDBCommand> command = dbCommandFactory->createDBCommand();
        command->commandText("...");
        command->setConnection(std::move(connection));  //关联性

        unique_ptr<IDBReader> reader = dbReaderFactory->createDBReader();
        while (reader->read()) {
            // ...
        }
    }
};