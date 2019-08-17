#include <iostream>

using namespace std;

/**
 * Chain of Responsibility
 * ʹ��������л��ᴦ�����󣬴Ӷ���������ķ����ߺͽ�����֮�����Ϲ�ϵ��
 * ����Щ��������һ��������������������������ֱ����һ����������Ϊֹ��
 */

// �쳣
class Exception {
public:
    // �쳣����
    enum EType {
        Overflow_Error,     // ���������쳣
        Range_Error,        // Խ���쳣
        Underflow_Error     // ���������쳣
    };

    explicit Exception(EType type) {
        this->eType = type;
    }

    EType type() const {
        return eType;
    }

private:
    EType eType;
};

// �쳣��ְ����
class ChainException {
public:
    // ������һ���쳣����ڵ�
    void setNextChain(ChainException *next) {
        nextChain = next;
    }

    // �����쳣
    virtual void processException(const Exception &exception) = 0;

    // Ϊ�����ṩ����������
    virtual ~ChainException() = default;

protected:
    // ��һ���쳣����ڵ�
    ChainException *nextChain = nullptr;

    // ���쳣������һ������ڵ�
    void sendExceptionToNextHandler(const Exception &exception) {
        if (nextChain != nullptr) {
            nextChain->processException(exception);
        } else {
            // ���û����һ������ڵ㣬�ṩĬ�ϵĴ���ʽ����ֹ����
            cout << "abort()" << endl;
            abort();
        }
    }
};

// �쳣����ְ�����и�����OverflowError����
class OverflowErrorHandler : public ChainException {
public:
    void processException(const Exception &exception) override {
        if (exception.type() != Exception::Overflow_Error) {
            // ����쳣���Ͳ���OverflowError�������޷�����������һ������ڵ�
            sendExceptionToNextHandler(exception);
        } else {
            // ����쳣������OverflowError��������д���
            cout << "Processor -> OverflowErrorHandler" << endl;
        }
    }
};

// �쳣����ְ�����и�����OverflowError����
class RangeErrorHandler : public ChainException {
public:
    void processException(const Exception &exception) override {
        if (exception.type() != Exception::Range_Error) {
            // ����쳣���Ͳ���RangeError�������޷�����������һ������ڵ�
            sendExceptionToNextHandler(exception);
        } else {
            // ����쳣������RangeError��������д���
            cout << "Processor -> RangeErrorHandler" << endl;
        }
    }
};

// �쳣����ְ�����и�����UnderflowError����
class UnderflowErrorHandler : public ChainException {
public:
    void processException(const Exception &exception) override {
        if (exception.type() != Exception::Underflow_Error) {
            // ����쳣���Ͳ���UnderflowError�������޷�����������һ������ڵ�
            sendExceptionToNextHandler(exception);
        } else {
            // ����쳣������UnderflowError��������д���
            cout << "Processor -> UnderflowErrorHandler" << endl;
        }
    }
};

int main() {

    ChainException* oe = new OverflowErrorHandler();
    ChainException* re = new RangeErrorHandler();
    ChainException* ue = new UnderflowErrorHandler();

    oe->setNextChain(re);
    re->setNextChain(ue);

    Exception e1(Exception::Overflow_Error);
    oe->processException(e1);

    Exception e2(Exception::Range_Error);
    oe->processException(e2);

    Exception e3(Exception::Underflow_Error);
    oe->processException(e3);

    delete ue;
    delete re;
    delete oe;

    return 0;
}