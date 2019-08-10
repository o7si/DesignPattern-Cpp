#include <iostream>

using namespace std;

/**
 * Adapterģʽ
 * ��һ����Ľӿ�ת���ɿͻ�ϣ������һ���ӿڡ�
 */

// ��������α����ʽ�����漰ʵ�֣�ֻ˵��˼��

// ˫�˶��У�֧�ֲ鿴����/��βԪ�أ������/��β����Ԫ�أ�ɾ������/��βԪ�صȲ���
class Deque {
public:
    // �ڶ�β����Ԫ��
    void push_back() {
        cout << "Deque.push_back" << endl;
    }
    // �ڶ��ײ���Ԫ��
    void push_front() {
        cout << "Deque.push_front" << endl;
    }
    // �鿴����Ԫ��
    void front() {
        cout << "Deque.front" << endl;
    }
    // �鿴��βԪ��
    void back() {
        cout << "Deque.back" << endl;
    }
    // ɾ������Ԫ��
    void pop_front() {
        cout << "Deque.pop_front" << endl;
    }
    // ɾ����βԪ��
    void pop_back() {
        cout << "Deque.pop_back" << endl;
    }
};

// ���У�Deque��һ�������������Ƚ��ȳ���ֻ֧�ֶ�β����Ԫ�أ�����ȡ��Ԫ�صȲ���
class Queue {
public:
    // �ڶ�β����Ԫ��
    void push() {
        container.push_back();
    }
    // �鿴����Ԫ��
    void front() {
        container.front();
    }
    // ɾ������Ԫ��
    void pop() {
        container.pop_front();
    }
private:
    Deque container;
};

// ջ��Deque����һ����������������ȳ���ֻ֧��ջ��ѹ��Ԫ�أ�����ջ��Ԫ�صȲ���
class Stack {
public:
    // ��ջ��ѹ��Ԫ��
    void push() {
        container.push_back();
    }
    // �鿴ջ��Ԫ��
    void top() {
        container.back();
    }
    // ����ջ��Ԫ��
    void pop() {
        container.pop_back();
    }
private:
    Deque container;
};


int main() {

    // Queue�ڲ�ʹ��Dequeʵ�֣�Queue�൱��Deque��������
    cout << "Queue Test : " << endl;
    Queue queue;
    queue.push();
    queue.front();
    queue.pop();
    cout << endl;

    // Stack�ڲ�ʹ��Dequeʵ�֣�Stack�൱��Deque��������
    cout << "Stack Test : " << endl;
    Stack stack;
    stack.push();
    stack.top();
    stack.pop();
    cout << endl;

    return 0;
}