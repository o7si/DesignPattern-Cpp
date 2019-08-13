#include <iostream>
#include <map>

using namespace std;

/**
 * �н���ģʽ��Mediator��
 * ��һ���н��������װһϵ�еĶ��󽻻���
 * �н���ʹ��������Ҫ��ʾ���໥���ã��Ӷ�ʹ�������ɢ�����ҿ��Զ����ظı�����֮��Ľ�����
 */

class Router;

// �����豸
class Computer {
    friend Router;
public:
    explicit Computer(const string& name, const string &address, Router *router);

    // ������Ϣ����Ҫָ�����շ��Լ���Ϣ�����ݣ�
    void send(const string &receiver, const string &message);

    // ������Ϣ����Ҫָ�����ͷ��Լ���Ϣ�����ݣ�
    void receive(const string &sender, const string &message);

private:
    // �н��ߣ�·������
    Router *mediator;
    // ������
    string hostname;
    // IP��ַ
    string ipAddress;
};

// ·��������Ϊ�н��ߣ�������������֮������ݴ���
class Router {
public:
    // �ⲿ�豸��������·����
    void connection(Computer* computer) {
        // ���δ��¼���豸�����ݣ���ʾ�豸δ���ӣ����¼���豸
        if (data.find(computer->ipAddress) == data.end())
            data.insert(make_pair(computer->ipAddress, computer));
    }

    // �ⲿ�豸�����ͷ�����
    void release(Computer* computer) {
        // ����Ѽ�¼���豸��������ɾ�����豸
        if (data.find(computer->ipAddress) != data.end())
            data.erase(computer->ipAddress);
    }

    // ������Ϣ��ת��
    void forward(const string &sender, const string &receiver, const string &message) {

        // ������ͷ��ͽ��շ�δ����¼��·�����У���������
        if (data.find(sender) == data.end() || data.find(receiver) == data.end()) {

            cout << "Forward Error." << endl;
        } else {

            // ������Ϣ�ķ���
            data[receiver]->receive(sender, message);
        }
    }

private:
    map<string, Computer *> data;
};


inline Computer::Computer(const string& name, const string &address, Router *router)
        : hostname(name), ipAddress(address), mediator(router) {
}

// ������Ϣ����Ҫָ�����շ��Լ���Ϣ�����ݣ�
inline void Computer::send(const string &receiver, const string &message) {
    mediator->forward(ipAddress, receiver, message);
}

// ������Ϣ����Ҫָ�����ͷ��Լ���Ϣ�����ݣ�
inline void Computer::receive(const string &sender, const string &message) {
    cout << hostname << " | " << message << " [" <<sender << "]" << endl;
}

int main() {

    // �н���
    Router* router = new Router();
    // �����豸
    Computer* c1 = new Computer("c1", "172.168.1.70", router);
    Computer* c2 = new Computer("c2", "172.168.2.80", router);
    Computer* c3 = new Computer("c3", "172.168.3.90", router);

    // ����Router
    router->connection(c1);
    router->connection(c2);
    router->connection(c3);

    // ģ�ⷢ����Ϣ
    c1->send("172.168.2.80", "Hello c2, I'm c1.");
    c1->send("172.168.3.90", "Hello c3, I'm c1.");
    c2->send("172.168.3.90", "Hello c3, I'm c2.");

    // �ͷ�����
    router->release(c1);
    router->release(c2);
    router->release(c3);

    // �ͷ���Դ
    delete c1;
    delete c2;
    delete c3;
    delete router;

    return 0;
}