#include <iostream>
#include <mutex>
#include <atomic>
#include <memory>

using namespace std;

// 第一种实现：懒汉式（延迟加载）
// 是否线程安全：否
namespace impl_1 {

    // 使用智能指针进行管理，防止用户获得单例对象后将其delete
    class Singleton {
    public:
        // 获取单例对象
        static shared_ptr<Singleton> getInstance();

        // 删除拷贝构造函数，防止用户复制单例对象
        Singleton(const Singleton &other) = delete;

    private:
        // 将构造函数修饰为private，防止用户擅自实例化对象
        Singleton() = default;

        // 单例对象
        static shared_ptr<Singleton> instance;
    };

    // 初始化为空
    shared_ptr<Singleton> Singleton::instance = nullptr;

    // 获取单例对象
    shared_ptr<Singleton> Singleton::getInstance() {

        if (instance == nullptr)
            // 此处存在线程安全问题
            // 在多线程环境下，可能会有一个以上的进程同时进入判断语句
            // 则会导致多次实例化
            instance = shared_ptr<Singleton>(new Singleton());
        return instance;
    }
}

// 第二种实现：静态变量（延迟加载）
// 是否线程安全：否
namespace impl_2 {

    // 使用智能指针进行管理，防止用户获得单例对象后将其delete
    class Singleton {
    public:
        // 获取单例对象
        static shared_ptr<Singleton> getInstance();

        // 删除拷贝构造函数，防止用户复制单例对象
        Singleton(const Singleton &other) = delete;

    private:
        // 将构造函数修饰为private，防止用户擅自实例化对象
        Singleton() = default;
    };

    // 获取单例对象
    shared_ptr<Singleton> Singleton::getInstance() {
        // static变量不能保证线程安全
        static shared_ptr<Singleton> instance(new Singleton());
        return instance;
    }
}

// 第三种实现：饿汉式（立即加载）
// 是否线程安全：是
namespace impl_3 {

    // 使用智能指针进行管理，防止用户获得单例对象后将其delete
    class Singleton {
    public:
        // 获取单例对象
        static shared_ptr<Singleton> getInstance();

        // 删除拷贝构造函数，防止用户复制单例对象
        Singleton(const Singleton &other) = delete;

    private:
        // 将构造函数修饰为private，防止用户擅自实例化对象
        Singleton() = default;

        // 单例对象
        static shared_ptr<Singleton> instance;
    };

    // 立即实例化
    shared_ptr<Singleton> Singleton::instance(new Singleton());

    // 获取单例对象
    shared_ptr<Singleton> Singleton::getInstance() {
        return instance;
    }
}

// 第四种实现：单检查锁
// 是否线程安全：是
namespace impl_4 {

    // 使用智能指针进行管理，防止用户获得单例对象后将其delete
    class Singleton {
    public:
        // 获取单例对象
        static shared_ptr<Singleton> getInstance();

        // 删除拷贝构造函数，防止用户复制单例对象
        Singleton(const Singleton &other) = delete;

    private:
        // 将构造函数修饰为private，防止用户擅自实例化对象
        Singleton() = default;

        // 单例对象
        static shared_ptr<Singleton> instance;
        // 互斥量
        static mutex mMutex;
    };

    // 初始化为空
    shared_ptr<Singleton> Singleton::instance = nullptr;

    // 初始化互斥量
    mutex Singleton::mMutex;

    // 获取单例对象
    shared_ptr<Singleton> Singleton::getInstance() {

        // 锁的代价过高，当instance不为空仍会上锁
        // 加锁
        mMutex.lock();

        if (instance == nullptr)
            instance = shared_ptr<Singleton>(new Singleton());

        // 释放锁
        mMutex.unlock();

        return instance;
    }
}

// 第五种实现：双检查锁
// 是否线程安全：否
namespace impl_5 {

    // 使用智能指针进行管理，防止用户获得单例对象后将其delete
    class Singleton {
    public:
        // 获取单例对象
        static shared_ptr<Singleton> getInstance();

        // 删除拷贝构造函数，防止用户复制单例对象
        Singleton(const Singleton &other) = delete;

    private:
        // 将构造函数修饰为private，防止用户擅自实例化对象
        Singleton() = default;

        // 单例对象
        static shared_ptr<Singleton> instance;
        // 互斥量
        static mutex mMutex;
    };

    // 初始化为空
    shared_ptr<Singleton> Singleton::instance = nullptr;

    // 初始化互斥量
    mutex Singleton::mMutex;

    // 获取单例对象
    shared_ptr<Singleton> Singleton::getInstance() {

        if (instance == nullptr) {

            // 由于内存读写reorder可能会导致会不安全

            // 加锁
            mMutex.lock();
            if (instance == nullptr)
                instance = shared_ptr<Singleton>(new Singleton());
            // 释放锁
            mMutex.unlock();
        }

        return instance;
    }
}

// 第六种实现：内存栅栏（待补充）
// 是否线程安全：是
namespace impl_6 {

}

int main() {

    cout << boolalpha;
    {
        // 第一种实现
        using namespace impl_1;
        cout << (Singleton::getInstance() == Singleton::getInstance()) << endl;
    }
    {
        // 第二种实现
        using namespace impl_2;
        cout << (Singleton::getInstance() == Singleton::getInstance()) << endl;
    }
    {
        // 第三种实现
        using namespace impl_3;
        cout << (Singleton::getInstance() == Singleton::getInstance()) << endl;
    }
    {
        // 第四种实现
        using namespace impl_4;
        cout << (Singleton::getInstance() == Singleton::getInstance()) << endl;
    }
    {
        // 第五种实现
        using namespace impl_5;
        cout << (Singleton::getInstance() == Singleton::getInstance()) << endl;
    }
    {
        // 第六种实现
        using namespace impl_6;
    }
    cout << noboolalpha;

    return 0;
}