#include <iostream>
#include <vector>

using namespace std;

/**
 * Memento
 * 在不破坏封装性的前提下，捕获一个对象的内部状态，并在对象之外保存这个状态。
 * 这样以后就可以将该对象恢复到原先保存的状态。
 */

// 备忘录
class Memento {
public:
    explicit Memento(const string &s)
            : state(s) {
    }

    string getState() const {
        return state;
    }

private:
    // 保存某一时刻的状态
    string state;
};

// 文本
class Text {
public:
    explicit Text(const string &t)
            : content(t) {
    }

    // 创建一个备忘录（创建一个快照）
    Memento createMemento() {
        return Memento(content);
    }

    // 恢复到备忘录保存的某一时刻的状态
    void setMemento(const Memento &m) {
        content = m.getState();
    }

    // 向文本内追加内容
    void append(const string &s) {
        content += s;
    }

    // 输出文本内容
    void print() const {
        cout << content << endl;
    }

private:
    // 文本内容
    string content;
};

int main() {

    // 保存一系列的备份
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

    // 恢复
    for (auto iter = mementos.crbegin(); iter != mementos.crend(); ++iter) {
        text.setMemento(*iter);
        text.print();
    }

    return 0;
}