#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// 数据库访问有关的基类
class IDBConnection {
};
class IDBCommand{
};
class IDBReader{
};

// 系列工厂（对象之间相互依赖）
// 把这些相互依赖，有关联关系的对象放到一个工厂中
class IDBFactory    
{
public:
    virtual unique_ptr<IDBConnection> createDBConnection()=0;
    virtual unique_ptr<IDBCommand> createDBCommand()=0;
    virtual unique_ptr<IDBReader> createDBReader()=0;
};

// ************* 支持MySql *****************
class SqlConnection : public IDBConnection{
};
class SqlCommand : public IDBCommand{
};
class SqlDataReader : public IDBReader{
};


class SqlDBFactory : public IDBFactory 
{
public:
    unique_ptr<IDBConnection> createDBConnection() override {

    }

    unique_ptr<IDBCommand> createDBCommand() override {

    }

    unique_ptr<IDBReader> createDBReader() override {

    }
};


// ************* 支持Oracle *****************
class OracleConnection : public IDBConnection{
};
class OracleCommand : public IDBCommand{
};
class OracleDataReader : public IDBReader{
};
class OracleDBFactory : public IDBFactory 
{
public:
    unique_ptr<IDBConnection> createDBConnection() override {

    }

    unique_ptr<IDBCommand> createDBCommand() override {

    }

    unique_ptr<IDBReader> createDBReader() override {
        
    }
};


// --------------------------------------------------------------

class EmployeeDAO
{
    // 通过抽象的工厂基类创建对象
    unique_ptr<IDBFactory> dbFactory;   // SqlDBFactory, OracleDBFactory...

    EmployeeDAO(unique_ptr<IDBFactory> dbFactory) : dbFactory(std::move(dbFactory)) {
        
    } 

public:
    vector<Employee> getEmployees() {
        unique_ptr<IDBConnection> connection = dbFactory->createDBConnection();
        connection->connectString("...");

        unique_ptr<IDBCommand> command = dbFactory->createDBCommand();
        command->commandText("...");
        command->setConnection(std::move(connection));  //关联性，这里关联就可以保证一致性。

        unique_ptr<IDBReader> reader = dbFactory->createDBReader();
        while (reader->read()) {
            // ...
        }
    }
};