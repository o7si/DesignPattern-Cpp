#include <iostream>
#include <vector>

using namespace std;

/**
 * Memento
 * �ڲ��ƻ���װ�Ե�ǰ���£�����һ��������ڲ�״̬�����ڶ���֮�Ᵽ�����״̬��
 * �����Ժ�Ϳ��Խ��ö���ָ���ԭ�ȱ����״̬��
 */

// ����¼
class Memento {
public:
    explicit Memento(const string &s)
            : state(s) {
    }

    string getState() const {
        return state;
    }

private:
    // ����ĳһʱ�̵�״̬
    string state;
};

// �ı�
class Text {
public:
    explicit Text(const string &t)
            : content(t) {
    }

    // ����һ������¼������һ�����գ�
    Memento createMemento() {
        return Memento(content);
    }

    // �ָ�������¼�����ĳһʱ�̵�״̬
    void setMemento(const Memento &m) {
        content = m.getState();
    }

    // ���ı���׷������
    void append(const string &s) {
        content += s;
    }

    // ����ı�����
    void print() const {
        cout << content << endl;
    }

private:
    // �ı�����
    string content;
};

int main() {

    // ����һϵ�еı���
    vector<Memento> mementos;

    Text text("Hello");
    mementos.push_back(text.createMemento());
    text.print();

    text.append("World");
    mementos.push_back(text.createMemento());
    text.print();

    text.append("~~~");
    mementos.push_back(text.createMemento());
    text.print();

    // �ָ�
    for (auto iter = mementos.crbegin(); iter != mementos.crend(); ++iter) {
        text.setMemento(*iter);
        text.print();
    }

    return 0;
}