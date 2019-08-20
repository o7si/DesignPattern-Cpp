#include <iostream>

using namespace std;

/**
 * Visitor
 * 一个作用于某对象结构中各元素的操作。
 * 使得可以在不改变各元素的类的前提下定义作用于这些元素的新操作。
 */

class Customer;

// 服务
class Service {
public:
    virtual void accept(Customer *visitor) = 0;

    // 为抽象基类添加虚析构函数
    virtual ~Service() = default;
};

// 存款服务
class DepositService : public Service {
public:
    void accept(Customer *visitor) override;
};

// 取款服务
class WithdrawalService : public Service {
public:
    void accept(Customer *visitor) override;
};

// 客户
class Customer {
public:
    // 访问存款服务
    virtual void visitDepositService(DepositService &deposit) = 0;

    // 访问取款服务
    virtual void visitWithdrawalService(WithdrawalService &withdrawal) = 0;

    // 为抽象基类添加虚析构函数
    virtual ~Customer() = default;
};

// 普通客户
class NormalCustomer : public Customer {
public:
    void visitDepositService(DepositService &deposit) override {
        cout << "NormalCustomer DepositService" << endl;
    }

    void visitWithdrawalService(WithdrawalService &withdrawal) override {
        cout << "NormalCustomer WithdrawalService" << endl;
    }
};

// 会员客户
class VipCustomer : public Customer {
public:
    void visitDepositService(DepositService &deposit) override {
        cout << "VipCustomer DepositService" << endl;
    }

    void visitWithdrawalService(WithdrawalService &withdrawal) override {
        cout << "VipCustomer WithdrawalService" << endl;
    }
};

void DepositService::accept(Customer *visitor) {
    visitor->visitDepositService(*this);
}


void WithdrawalService::accept(Customer *visitor) {
    visitor->visitWithdrawalService(*this);
}

int main() {

    // 两种服务
    Service *ds = new DepositService;
    Service *ws = new WithdrawalService;

    // 两种客户
    Customer *nc = new NormalCustomer;
    Customer *vc = new VipCustomer;

    // 不同的访问情况
    ds->accept(nc);     // 普通客户进行存款服务
    ds->accept(vc);     // 会员客户进行存款服务
    ws->accept(nc);     // 普通客户进行取款服务
    ws->accept(vc);     // 会员客户进行取款服务

    // 释放资源
    delete nc;
    delete vc;
    delete ds;
    delete ws;

    return 0;
}