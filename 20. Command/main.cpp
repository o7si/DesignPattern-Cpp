#include <iostream>

using namespace std;

/**
 * Command
 * 将一个请求封装为一个对象，使发出请求的责任和执行请求的责任分割开。
 * 这样两者之间通过命令对象进行沟通，这样方便将命令对象进行储存、传递、调用、增加与管理。
 */

/************************************************************/
// 接收者：进行外套的生产
class CoatReceiver {
public:
    void product() {
        cout << "Coat" << endl;
    }
};

// 接收者：进行帽子的生产
class HatReceiver {
public:
    void product() {
        cout << "Hat" << endl;
    }
};
/************************************************************/


/************************************************************/
// 生产命令
class Command {
public:
    // 执行命令
    virtual void execute() = 0;

    // 为多态基类编写虚析构函数
    virtual ~Command() = default;
};

// 生产外套命令
class CoatCommand : public Command {
public:
    explicit CoatCommand(const CoatReceiver &cr)
            : receiver(cr) {
    }

    // 执行命令
    void execute() override {
        receiver.product();
    }

private:
    // 接收者：负责生产外套
    CoatReceiver receiver;
};

// 生产帽子命令
class HatCommand : public Command {
public:
    explicit HatCommand(const HatReceiver &hr)
            : receiver(hr) {
    }

    // 执行命令
    void execute() override {
        receiver.product();
    }

private:
    // 接收者：负责生产帽子
    HatReceiver receiver;
};
/************************************************************/


/************************************************************/
// 顾客：调用者
class Customer {
public:

    Customer(const CoatCommand &cc, const HatCommand &hc)
            : coatCommand(cc), hatCommand(hc) {
    }

    // 购买外套
    void buyCoat() {
        // 执行生产外套指令
        coatCommand.execute();
    }

    // 购买帽子
    void buyHat() {
        // 执行生产帽子指令
        hatCommand.execute();
    }

private:
    // 购买外套命令
    CoatCommand coatCommand;
    // 购买帽子命令
    HatCommand hatCommand;
};
/************************************************************/

int main() {

    // 接收者：负责外套的生产
    CoatReceiver coatReceiver;
    // 接收者：负责帽子的生产
    HatReceiver hatReceiver;

    // 命令：生产外套
    CoatCommand coatCommand(coatReceiver);
    // 命令：生产帽子
    HatCommand hatCommand(hatReceiver);

    // 顾客：负责发出命令
    Customer customer(coatCommand, hatCommand);

    // 顾客发出命令：我要购买一件外套
    customer.buyCoat();

    // 顾客发出命令：我要购买一个帽子
    customer.buyHat();

    return 0;
}