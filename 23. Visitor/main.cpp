#include <iostream>

using namespace std;

/**
 * Visitor
 * һ��������ĳ����ṹ�и�Ԫ�صĲ�����
 * ʹ�ÿ����ڲ��ı��Ԫ�ص����ǰ���¶�����������ЩԪ�ص��²�����
 */

class Customer;

// ����
class Service {
public:
    virtual void accept(Customer *visitor) = 0;

    // Ϊ��������������������
    virtual ~Service() = default;
};

// ������
class DepositService : public Service {
public:
    void accept(Customer *visitor) override;
};

// ȡ�����
class WithdrawalService : public Service {
public:
    void accept(Customer *visitor) override;
};

// �ͻ�
class Customer {
public:
    // ���ʴ�����
    virtual void visitDepositService(DepositService &deposit) = 0;

    // ����ȡ�����
    virtual void visitWithdrawalService(WithdrawalService &withdrawal) = 0;

    // Ϊ��������������������
    virtual ~Customer() = default;
};

// ��ͨ�ͻ�
class NormalCustomer : public Customer {
public:
    void visitDepositService(DepositService &deposit) override {
        cout << "NormalCustomer DepositService" << endl;
    }

    void visitWithdrawalService(WithdrawalService &withdrawal) override {
        cout << "NormalCustomer WithdrawalService" << endl;
    }
};

// ��Ա�ͻ�
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

    // ���ַ���
    Service *ds = new DepositService;
    Service *ws = new WithdrawalService;

    // ���ֿͻ�
    Customer *nc = new NormalCustomer;
    Customer *vc = new VipCustomer;

    // ��ͬ�ķ������
    ds->accept(nc);     // ��ͨ�ͻ����д�����
    ds->accept(vc);     // ��Ա�ͻ����д�����
    ws->accept(nc);     // ��ͨ�ͻ�����ȡ�����
    ws->accept(vc);     // ��Ա�ͻ�����ȡ�����

    // �ͷ���Դ
    delete nc;
    delete vc;
    delete ds;
    delete ws;

    return 0;
}