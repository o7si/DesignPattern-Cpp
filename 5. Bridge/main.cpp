#include <iostream>

using namespace std;

// ������ʹ������5������ʾ��ģʽ

// ���ݿ����ӳ�����ࣨ�ȶ����֣�
class ConnectionBase;

// ���ݿ����ӳ�����ࣨ�ȶ����֣�
class Driver;

// ���ݿ�����ʵ���ࣨ�仯���֣�
class Connection;

// A��˾�����ݿ��������仯���֣�
class ADriver;

// B��˾�����ݿ��������任���֣�
class BDriver;

// ���ݿ����ӳ�����ࣺ����е��ȶ�����
// ������ز����Ľӿڡ�
// ��ģʽ�Ĺؼ��㣺�������һ��Driver���͵�ָ�룬������ʱ����װ�䡣
class ConnectionBase {
public:
    // ��������
    virtual void createConnection() = 0;

    // �ͷ�����
    virtual void releaseConnection() = 0;

    // Ϊ������������������
    virtual ~ConnectionBase() = default;

protected:
    // �������޷���ʵ�������������γ�public��ֻ�����γ�protected��������ʹ�ü���
    explicit ConnectionBase(Driver *driver)
            : driverImpl(driver) {
    }

    // �ؼ��㣺�����ʵ���ɸ�ָ����ָ�����ṩ
    Driver *driverImpl;
};

// ���ݿ����ӳ�����ࣺ����е��ȶ�����
class Driver {
public:
    // ��������
    virtual void create() = 0;

    // �ͷ�����
    virtual void release() = 0;

    // Ϊ������������������
    virtual ~Driver() = default;
};

// ���ݿ�����ʵ����
class Connection : public ConnectionBase {
public:
    explicit Connection(Driver *driver)
            : ConnectionBase(driver) {
    }

    // ��������
    void createConnection() override {
        driverImpl->create();
    }

    // �ͷ�����
    void releaseConnection() override {
        driverImpl->release();
    }

    ~Connection() override {
        delete driverImpl;
    }
};


// A��˾�����ݿ�����
class ADriver : public Driver {
public:
    // ��������
    void create() override {
        cout << "ADriver, CreateConnection." << endl;
    }

    // �ͷ�����
    void release() override {
        cout << "ADriver, ReleaseConnection" << endl;
    }
};

// B��˾�����ݿ�����
class BDriver : public Driver {
public:
    // ��������
    void create() override {
        cout << "BDriver, CreateConnection." << endl;
    }

    // �ͷ�����
    void release() override {
        cout << "BDriver, ReleaseConnection" << endl;
    }
};

int main() {

    // ʹ��A��˾�����ݿ�������������
    Connection *aConnection = new Connection(new ADriver);
    aConnection->createConnection();
    aConnection->releaseConnection();
    delete aConnection;

    // ʹ��B��˾�����ݿ�������������
    Connection *bConnection = new Connection(new BDriver);
    bConnection->createConnection();
    bConnection->releaseConnection();
    delete bConnection;

    return 0;
}