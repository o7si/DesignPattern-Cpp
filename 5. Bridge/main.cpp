#include <iostream>

using namespace std;

// 本例中使用以下5个类演示桥模式

// 数据库连接抽象基类（稳定部分）
class ConnectionBase;

// 数据库连接抽象基类（稳定部分）
class Driver;

// 数据库连接实现类（变化部分）
class Connection;

// A公司的数据库驱动（变化部分）
class ADriver;

// B公司的数据库驱动（变换部分）
class BDriver;

// 数据库连接抽象基类：设计中的稳定部分
// 定义相关操作的接口。
// 桥模式的关键点：该类包含一个Driver类型的指针，在运行时进行装配。
class ConnectionBase {
public:
    // 创建连接
    virtual void createConnection() = 0;

    // 释放连接
    virtual void releaseConnection() = 0;

    // 为基类生成虚析构函数
    virtual ~ConnectionBase() = default;

protected:
    // 抽象类无法被实例化，无需修饰成public，只需修饰成protected供派生类使用即可
    explicit ConnectionBase(Driver *driver)
            : driverImpl(driver) {
    }

    // 关键点：具体的实现由该指针所指对象提供
    Driver *driverImpl;
};

// 数据库连接抽象基类：设计中的稳定部分
class Driver {
public:
    // 创建连接
    virtual void create() = 0;

    // 释放连接
    virtual void release() = 0;

    // 为基类声明虚析构函数
    virtual ~Driver() = default;
};

// 数据库连接实现类
class Connection : public ConnectionBase {
public:
    explicit Connection(Driver *driver)
            : ConnectionBase(driver) {
    }

    // 创建连接
    void createConnection() override {
        driverImpl->create();
    }

    // 释放连接
    void releaseConnection() override {
        driverImpl->release();
    }

    ~Connection() override {
        delete driverImpl;
    }
};


// A公司的数据库驱动
class ADriver : public Driver {
public:
    // 创建数据
    void create() override {
        cout << "ADriver, CreateConnection." << endl;
    }

    // 释放连接
    void release() override {
        cout << "ADriver, ReleaseConnection" << endl;
    }
};

// B公司的数据库驱动
class BDriver : public Driver {
public:
    // 创建数据
    void create() override {
        cout << "BDriver, CreateConnection." << endl;
    }

    // 释放连接
    void release() override {
        cout << "BDriver, ReleaseConnection" << endl;
    }
};

int main() {

    // 使用A公司的数据库驱动进行连接
    Connection *aConnection = new Connection(new ADriver);
    aConnection->createConnection();
    aConnection->releaseConnection();
    delete aConnection;

    // 使用B公司的数据库驱动进行连接
    Connection *bConnection = new Connection(new BDriver);
    bConnection->createConnection();
    bConnection->releaseConnection();
    delete bConnection;

    return 0;
}