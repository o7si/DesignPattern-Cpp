#include <iostream>

using namespace std;

/**
 * State
 * 对于一个有状态的对象，把复杂的判断逻辑提取到不同的状态对象中，允许状态对象在其内部状态发生改变时改变其行为。
 */

// 手机状态
class MobileState {
public:
    // 操作：拨打电话
    virtual void call() = 0;

    // 操作：接听电话
    virtual void answer() = 0;

    // 为抽象基类编写虚析构函数
    virtual~MobileState() = default;
};

// 正常状态（可接听电话，可拨打电话）
class NormalState : public MobileState {
public:
    // 操作：拨打电话
    void call() override {
        // 可以拨打电话
        cout << "NormalState(call) : success." << endl;
    }

    // 操作：接听电话
    void answer() override {
        // 可以接听电话
        cout << "NormalState(answer) : success." << endl;
    }
};

// 欠费状态（可接听电话，不可拨打电话）
class OverdueState : public MobileState {
public:
    // 操作：拨打电话
    void call() override {
        // 不可拨打电话
        cout << "OverdueState(call) : failure." << endl;
    }

    // 操作：接听电话
    void answer() override {
        // 可以接听电话
        cout << "OverdueState(answer) : success." << endl;
    }
};

// 停机状态（不可接听电话，不可拨打电话）
class SuspendState : public MobileState {
public:
    // 操作：拨打电话
    void call() override {
        // 不可拨打电话
        cout << "SuspendState(call) : failure." << endl;
    }

    // 操作：接听电话
    void answer() override {
        // 不可接听电话
        cout << "SuspendState(answer) : failure." << endl;
    }
};

// 手机
class Mobile {
public:
    // 默认为普通状态，可接听电话，可拨打电话
    explicit Mobile(MobileState *ms = new NormalState)
            : state(ms) {
    }

    // 操作：拨打电话
    void call() {
        state->call();
    }

    // 操作：接听电话
    void answer() {
        state->answer();
    }

    // 设置手机状态
    void setState(MobileState *mobileState) {
        delete state;
        state = mobileState;
    }

    ~Mobile() {
        delete state;
    }
private:
    MobileState *state;
};

int main() {

    Mobile mobile;

    // 测试：普通状态下拨打和接听电话
    mobile.setState(new NormalState);
    mobile.call();
    mobile.answer();

    // 测试：欠费状态下拨打和接听电话
    mobile.setState(new OverdueState);
    mobile.call();
    mobile.answer();

    // 测试：停机状态下拨打和接听电话
    mobile.setState(new SuspendState);
    mobile.call();
    mobile.answer();

    return 0;
}