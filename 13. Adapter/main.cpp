#include <iostream>

using namespace std;

/**
 * Adapter模式
 * 将一个类的接口转换成客户希望的另一个接口。
 */

// 本例采用伪码形式，不涉及实现，只说明思想

// 双端队列：支持查看队首/队尾元素，向队首/队尾插入元素，删除队首/队尾元素等操作
class Deque {
public:
    // 在队尾插入元素
    void push_back() {
        cout << "Deque.push_back" << endl;
    }
    // 在队首插入元素
    void push_front() {
        cout << "Deque.push_front" << endl;
    }
    // 查看队首元素
    void front() {
        cout << "Deque.front" << endl;
    }
    // 查看队尾元素
    void back() {
        cout << "Deque.back" << endl;
    }
    // 删除队首元素
    void pop_front() {
        cout << "Deque.pop_front" << endl;
    }
    // 删除队尾元素
    void pop_back() {
        cout << "Deque.pop_back" << endl;
    }
};

// 队列（Deque的一个适配器）：先进先出，只支持队尾插入元素，队首取出元素等操作
class Queue {
public:
    // 在队尾插入元素
    void push() {
        container.push_back();
    }
    // 查看队首元素
    void front() {
        container.front();
    }
    // 删除队首元素
    void pop() {
        container.pop_front();
    }
private:
    Deque container;
};

// 栈（Deque的另一个适配器）：后进先出，只支持栈顶压入元素，弹出栈顶元素等操作
class Stack {
public:
    // 向栈顶压入元素
    void push() {
        container.push_back();
    }
    // 查看栈顶元素
    void top() {
        container.back();
    }
    // 弹出栈顶元素
    void pop() {
        container.pop_back();
    }
private:
    Deque container;
};


int main() {

    // Queue内部使用Deque实现，Queue相当于Deque的适配器
    cout << "Queue Test : " << endl;
    Queue queue;
    queue.push();
    queue.front();
    queue.pop();
    cout << endl;

    // Stack内部使用Deque实现，Stack相当于Deque的适配器
    cout << "Stack Test : " << endl;
    Stack stack;
    stack.push();
    stack.top();
    stack.pop();
    cout << endl;

    return 0;
}