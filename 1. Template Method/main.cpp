#include <iostream>
#include <ctime>
#include <random>

/**
 * Template Method
 * 定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。
 * 使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。
 */

// 抽象类：不允许实例化Container对象
class Container {
public:
    /**
     * Template Method
     * 其中sort函数以及size函数被延迟到派生类
     */
    void testSort() {

        using std::cout;
        using std::endl;

        // 记录开始时间
        clock_t startTime = clock();
        // 排序过程
        sort();
        // 记录结束时间
        clock_t endTime = clock();

        // 排序n个元素用时m秒
        cout << "size = " << size() << endl;
        cout << "time = " << static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    }

    // 将sort函数延迟到派生类实现
    virtual void sort() = 0;
    // 将size函数延迟到派生类实现
    virtual size_t size() = 0;
    // 为多态基类声明虚析构函数，保证基类指针能够正确释放资源
    virtual ~Container() = default;
};

// 模板类，final关键字使得该类不允许被继承
template<typename Type>
class MyContainer final : public Container {
public:
    explicit MyContainer(const Type* arr, int n) : sz(n) {

        data = new Type[sz];
        // 深拷贝：复制arr中的内容到data
        for (int i = 0; i < sz; ++i) {
            data[i] = arr[i];
        }
    }

    /**
     * 如果一个类具有指针成员变量，，则需要编写拷贝构造函数、拷贝赋值运算符以及析构函数。
     * 其中，拷贝赋值运算符应该能够处理自我赋值的情况。
     */

    // 拷贝构造函数
    MyContainer(const MyContainer& rhs) {

        sz = rhs.sz;
        data = new Type[sz];
        // 深拷贝：复制arr中的内容到data
        for (int i = 0; i < sz; ++i) {
            data[i] = arr[i];
        }
    }

    // 拷贝赋值运算符
    MyContainer &operator=(const MyContainer& rhs) {

        // 处理自我赋值
        if (this == &rhs)
            return *this;

        delete[] data;

        sz = rhs.sz;
        data = new Type[sz];
        // 深拷贝：复制arr中的内容到data
        for (int i = 0; i < sz; ++i) {
            data[i] = arr[i];
        }
    }

    // 析构函数：释放资源
    ~MyContainer() override {
        delete[] data;
    }

    // 重定义sort函数供基类testSort函数调用
    void sort() override {

        // 插入排序
        for (int i = 1; i < sz; ++i) {

            Type elem = data[i];

            int j;
            for (j = i; j > 0 && data[j - 1] > elem; --j)
                data[j] = data[j - 1];

            data[j] = elem;
        }
    }

    // 重定义size函数供基类testSort函数调用
    size_t size() override {
        return sz;
    }
private:
    Type* data;
    size_t sz;
};

namespace helper {

    // 生成具有n个元素的随机数组，每个元素的范围在[rangeL, rangeR]
    int* generateRandomIntArray(const int sz, const int rangeL, const int rangeR) {

        // 设置随机数引擎（静态修饰保证短时间内重复调用不会生成相同的序列）
        static std::default_random_engine engine(time(nullptr));
        // 设置随机数分布为[rangeL, rangeR]
        std::uniform_int_distribution<int> distribution(rangeL, rangeR);

        int* arr = new int[sz];
        for (int i = 0; i < sz; ++i)
            arr[i] = distribution(engine);
        return arr;
    }
}

int main() {

    const int n = 50000;
    int* arr = helper::generateRandomIntArray(n, 0, n);

    // 基类指针指向派生类对象（多态）
    Container* container = new MyContainer<int>(arr, n);
    // testSort为Template Method
    container->testSort();

    // 释放资源
    delete arr;
    delete container;

    return 0;
}