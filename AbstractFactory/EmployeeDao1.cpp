#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class SqlConnection {};

class SqlCommand {};

class SqlDataReader {};

class EmployeeDao 
{
public:
    // 伪代码：模拟数据库访问
    vector<Employee> getEmployees() {
        unique_ptr<SqlConnection> connection { new SqlConnection() };
        connection->open();

        unique_ptr<SqlCommand> command { new SqlCommand() };
        command->commandText("select...");
        command->setConnection(std::move(connection)); //关联性

        vector<Employee> employees;

        unique_ptr<SqlDataReader> reader = command->executeReader();
        while (reader->read()) {
            // ....
        }

    }
};