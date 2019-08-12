#include <iostream>

using namespace std;

/**
 * ����ģʽ
 * Ϊ���������ṩһ�ִ����Կ��ƶ��������ķ��ʡ�
 */

// ������ָ�루��ָͨ��Ĵ����ࣩ
template<typename Type>
class Shard_Ptr {
public:
    // ��������ʼֵΪһ
    explicit Shard_Ptr(Type *p)
            : ptr(p), cnt(new size_t(1)) {
    }

    // �������죺��һ���µĶ������ptrָ�룬��������һ
    Shard_Ptr(const Shard_Ptr &rhs) : ptr(rhs.ptr), cnt(rhs.cnt) {
        ++*cnt;
    }

    // ������ֵ�����
    Shard_Ptr &operator=(const Shard_Ptr &rhs) {

        // ������Ҹ�ֵ
        if (this == &rhs)
            return *this;

        if (this->ptr == rhs.ptr)
            return *this;

        // ���и�ֵ
        this->ptr = rhs.ptr;
        this->cnt = rhs.cnt;

        // ��������һ
        ++*cnt;

        return *this;
    }

    ~Shard_Ptr() {

        // ��������Ϊ�㣬��û�ж���ʹ�ø�ָ�룬���ͷ���Դ
        if (--*cnt <= 0) {
            delete ptr;
            delete cnt;
        }
    }

    // �������ü���
    size_t count() const {
        return *cnt;
    }

    // ����ָ����������

    Type *operator->() {
        return ptr;
    }

    const Type *operator->() const {
        return ptr;
    }

    Type &operator*() {
        return *ptr;
    }

    const Type &operator*() const {
        return *ptr;
    }

private:
    // ��ָͨ��
    Type *ptr;
    // ���ü���
    size_t *cnt;
};

// �������Ե���
class Test {
public:
    explicit Test(int v) : val(v) {}

    int value() const {
        return val;
    }
private:
    int val;
};


int main() {

    Shard_Ptr<Test> shardPtr1(new Test(2019));
    cout << "shardPtr1: value = " << shardPtr1->value() << ", count = " << shardPtr1.count() << endl;
    Shard_Ptr<Test> shardPtr2(shardPtr1);
    cout << "shardPtr2: value = " << (*shardPtr2).value() << ", count = " << shardPtr2.count() << endl;
    Shard_Ptr<Test> shardPtr3(shardPtr1);
    cout << "shardPtr3: value = " << shardPtr3->value() << ", count = " << shardPtr3.count() << endl;
    shardPtr3 = shardPtr2;
    cout << "shardPtr3: value = " << (*shardPtr2).value() << ", count = " << shardPtr3.count() << endl;

    return 0;
}