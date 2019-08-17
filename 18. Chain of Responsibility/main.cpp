#include <iostream>

using namespace std;

/**
 * Chain of Responsibility
 * 使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。
 * 将这些对象连成一条链，并沿着这条链传递请求，直到有一个对象处理它为止。
 */

// 异常
class Exception {
public:
    // 异常类型
    enum EType {
        Overflow_Error,     // 数字上溢异常
        Range_Error,        // 越界异常
        Underflow_Error     // 数字下溢异常
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

// 异常的职责链
class ChainException {
public:
    // 设置下一个异常处理节点
    void setNextChain(ChainException *next) {
        nextChain = next;
    }

    // 处理异常
    virtual void processException(const Exception &exception) = 0;

    // 为基类提供序析构函数
    virtual ~ChainException() = default;

protected:
    // 下一个异常处理节点
    ChainException *nextChain = nullptr;

    // 将异常交个下一个处理节点
    void sendExceptionToNextHandler(const Exception &exception) {
        if (nextChain != nullptr) {
            nextChain->processException(exception);
        } else {
            // 如果没有下一个处理节点，提供默认的处理方式，终止程序
            cout << "abort()" << endl;
            abort();
        }
    }
};

// 异常处理职责链中负责处理OverflowError的类
class OverflowErrorHandler : public ChainException {
public:
    void processException(const Exception &exception) override {
        if (exception.type() != Exception::Overflow_Error) {
            // 如果异常类型不是OverflowError，自身无法处理，交给下一个处理节点
            sendExceptionToNextHandler(exception);
        } else {
            // 如果异常类型是OverflowError，自身进行处理
            cout << "Processor -> OverflowErrorHandler" << endl;
        }
    }
};

// 异常处理职责链中负责处理OverflowError的类
class RangeErrorHandler : public ChainException {
public:
    void processException(const Exception &exception) override {
        if (exception.type() != Exception::Range_Error) {
            // 如果异常类型不是RangeError，自身无法处理，交给下一个处理节点
            sendExceptionToNextHandler(exception);
        } else {
            // 如果异常类型是RangeError，自身进行处理
            cout << "Processor -> RangeErrorHandler" << endl;
        }
    }
};

// 异常处理职责链中负责处理UnderflowError的类
class UnderflowErrorHandler : public ChainException {
public:
    void processException(const Exception &exception) override {
        if (exception.type() != Exception::Underflow_Error) {
            // 如果异常类型不是UnderflowError，自身无法处理，交给下一个处理节点
            sendExceptionToNextHandler(exception);
        } else {
            // 如果异常类型是UnderflowError，自身进行处理
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