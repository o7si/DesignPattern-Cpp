#include <iostream>

using namespace std;

/**
 * 代理模式
 * 为其他对象提供一种代理以控制对这个对象的访问。
 */

// 计数型指针（普通指针的代理类）
template<typename Type>
class Shard_Ptr {
public:
    // 计数器初始值为一
    explicit Shard_Ptr(Type *p)
            : ptr(p), cnt(new size_t(1)) {
    }

    // 拷贝构造：有一个新的对象持有ptr指针，计数器加一
    Shard_Ptr(const Shard_Ptr &rhs) : ptr(rhs.ptr), cnt(rhs.cnt) {
        ++*cnt;
    }

    // 拷贝赋值运算符
    Shard_Ptr &operator=(const Shard_Ptr &rhs) {

        // 检查自我赋值
        if (this == &rhs)
            return *this;

        if (this->ptr == rhs.ptr)
            return *this;

        // 进行赋值
        this->ptr = rhs.ptr;
        this->cnt = rhs.cnt;

        // 计数器加一
        ++*cnt;

        return *this;
    }

    ~Shard_Ptr() {

        // 当计数器为零，即没有对象使用该指针，则释放资源
        if (--*cnt <= 0) {
            delete ptr;
            delete cnt;
        }
    }

    // 返回引用计数
    size_t count() const {
        return *cnt;
    }

    // 重载指针相关运算符

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
    // 普通指针
    Type *ptr;
    // 引用计数
    size_t *cnt;
};

// 用作测试的类
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