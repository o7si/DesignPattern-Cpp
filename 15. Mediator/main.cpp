#include <iostream>
#include <map>

using namespace std;

/**
 * 中介者模式（Mediator）
 * 用一个中介对象来封装一系列的对象交互。
 * 中介者使各对象不需要显示的相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。
 */

class Router;

// 电脑设备
class Computer {
    friend Router;
public:
    explicit Computer(const string& name, const string &address, Router *router);

    // 发送消息（需要指定接收方以及消息的内容）
    void send(const string &receiver, const string &message);

    // 接收消息（需要指定发送方以及消息的内容）
    void receive(const string &sender, const string &message);

private:
    // 中介者（路由器）
    Router *mediator;
    // 主机名
    string hostname;
    // IP地址
    string ipAddress;
};

// 路由器：作为中介者，负责各个计算机之间的数据传递
class Router {
public:
    // 外部设备请求连接路由器
    void connection(Computer* computer) {
        // 如果未记录该设备的数据（表示设备未连接）则记录该设备
        if (data.find(computer->ipAddress) == data.end())
            data.insert(make_pair(computer->ipAddress, computer));
    }

    // 外部设备请求释放连接
    void release(Computer* computer) {
        // 如果已记录该设备的数据则删除该设备
        if (data.find(computer->ipAddress) != data.end())
            data.erase(computer->ipAddress);
    }

    // 负责消息的转发
    void forward(const string &sender, const string &receiver, const string &message) {

        // 如果发送方和接收方未被记录在路由器中，不允许发送
        if (data.find(sender) == data.end() || data.find(receiver) == data.end()) {

            cout << "Forward Error." << endl;
        } else {

            // 进行消息的发送
            data[receiver]->receive(sender, message);
        }
    }

private:
    map<string, Computer *> data;
};


inline Computer::Computer(const string& name, const string &address, Router *router)
        : hostname(name), ipAddress(address), mediator(router) {
}

// 发送消息（需要指定接收方以及消息的内容）
inline void Computer::send(const string &receiver, const string &message) {
    mediator->forward(ipAddress, receiver, message);
}

// 接收消息（需要指定发送方以及消息的内容）
inline void Computer::receive(const string &sender, const string &message) {
    cout << hostname << " | " << message << " [" <<sender << "]" << endl;
}

int main() {

    // 中介者
    Router* router = new Router();
    // 电脑设备
    Computer* c1 = new Computer("c1", "172.168.1.70", router);
    Computer* c2 = new Computer("c2", "172.168.2.80", router);
    Computer* c3 = new Computer("c3", "172.168.3.90", router);

    // 连接Router
    router->connection(c1);
    router->connection(c2);
    router->connection(c3);

    // 模拟发送消息
    c1->send("172.168.2.80", "Hello c2, I'm c1.");
    c1->send("172.168.3.90", "Hello c3, I'm c1.");
    c2->send("172.168.3.90", "Hello c3, I'm c2.");

    // 释放连接
    router->release(c1);
    router->release(c2);
    router->release(c3);

    // 释放资源
    delete c1;
    delete c2;
    delete c3;
    delete router;

    return 0;
}