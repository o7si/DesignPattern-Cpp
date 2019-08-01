#include <iostream>
#include <string>
#include <map>

using namespace std;

// 观察者：窗口的焦点监听器
class IFocusListener {
public:
    // 当窗口获得焦点
    virtual void focusGained() = 0;

    // 当窗口失去焦点
    virtual void focusLost() = 0;

    // 为多态基类声明虚析构函数，保证基类指针能够正确释放资源
    virtual ~IFocusListener() = default;
};

// 窗口基类：用于管理监听器（观察者）
class FrameBase {
public:
    // 添加窗口的焦点事件监听器，使用identity标识监听器
    void addFocusListener(const string &identity, IFocusListener *focusListener) {
        focusListeners.insert(make_pair(identity, focusListener));
    }

    // 移除窗口的焦点事件监听器，通过identity移除监听器
    void removeFocusListener(const string &identity) {

        // 释放identity所对应监听器的资源
        auto begin = focusListeners.lower_bound(identity);
        auto end = focusListeners.upper_bound(identity);
        for (auto iter = begin; iter != end; ++iter)
            delete iter->second;
        // 移除identity所对应的监听器
        focusListeners.erase(identity);
    }

    // 当窗口获得焦点时调用此方法通知监听器（观察者）
    void doFocusGainedNotify() {

        for (const auto &elem : focusListeners) {
            // 将窗口获得了焦点的信息通知给每一个观察者
            elem.second->focusGained();
        }
    }

    // 当窗口失去焦点时调用此方法通知监听器（观察者）
    void doFocusLostNotify() {

        for (const auto &elem : focusListeners) {
            // 将窗口失去了焦点的信息通知给每一个观察者
            elem.second->focusLost();
        }
    }

    // 为多态基类声明虚析构函数，保证基类指针能够正确释放资源
    virtual ~FrameBase() {

        // 释放所管理监听器的资源
        for (auto &elem : focusListeners) {

            delete elem.second;
        }
    }

private:
    // 对观察者（窗口焦点事件监听器）进行管理
    // 使用multimap表示一个标识符可同时对应多个监听器
    // 例如：标识符"test"可能同时对应监听器"focusListener1"和"focusListener2"
    multimap<const string, IFocusListener *> focusListeners;
};

// 窗口类：省略了与该模式不相关的方法
class Frame : public FrameBase {
public:
    //...

    // 窗口获得焦点
    void onFocusGained() {

        // 通知观察者该窗口获得了焦点
        doFocusGainedNotify();
    }

    // 窗口失去焦点
    void onFocusLost() {

        // 通知观察者该窗口失去了焦点
        doFocusLostNotify();
    }

    // ...
};

// 测试用：继承监听器接口，并实现其方法
class MyFocusListener1 : public IFocusListener {
public:
    // 收到通知：窗口获得了焦点
    void focusGained() override {
        cout << "FocusGained1" << endl;
    }

    // 收到通知：窗口失去了焦点
    void focusLost() override {
        cout << "FocusLost1" << endl;
    }
};

// 测试用：继承监听器接口，并实现其方法
class MyFocusListener2 : public IFocusListener {
public:
    // 收到通知：窗口获得了焦点
    void focusGained() override {
        cout << "FocusGained2" << endl;
    }

    // 收到通知：窗口失去了焦点
    void focusLost() override {
        cout << "FocusLost2" << endl;
    }
};

int main() {

    // 实例化一个窗口对象
    Frame *frame = new Frame;

    // 为窗口绑定两个标识为"test"监听器
    frame->addFocusListener("test", new MyFocusListener1);
    frame->addFocusListener("test", new MyFocusListener2);

    // 此时窗口绑定了两个监听器
    // 当窗口获得焦点
    frame->onFocusGained();
    // 当窗口失去焦点
    frame->onFocusLost();

    // 移除窗口中标识为"test"的监听器
    frame->removeFocusListener("test");

    // 此时窗口未绑定任何监听器
    // 当窗口获得焦点
    frame->onFocusGained();
    // 当窗口失去焦点
    frame->onFocusLost();

    delete frame;
    return 0;
}