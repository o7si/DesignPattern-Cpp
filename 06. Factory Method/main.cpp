#include <iostream>

using namespace std;

/**
 * 工厂方法模式（Factory Method）
 * 定义一个用于创建对象的接口，让子类决定实例化哪一个类。
 * 使得一个类的实例化延迟到子类。
 */

// 水果
class Fruit {
public:
    // 获取果汁
    virtual string getJuice() const = 0;

    // 为多态基类声明虚析构函数
    virtual ~Fruit() = default;
};

// 水果工厂，用于生产水果
class FruitFactory {
public:
    // 生产水果
    // 最好不要直接返回指针，使用者可能会忘记释放资源，造成内存泄漏，此处使用智能指针进行管理
    virtual shared_ptr<Fruit> createFruit() = 0;

    // 为多态基类声明虚析构函数
    virtual ~FruitFactory() = default;
};

// 苹果
class Apple : public Fruit {
public:
    // 拿到苹果汁
    string getJuice() const override {
        return "Apple Juice";
    }
};

// 生产苹果的工厂
class AppleFactory : public FruitFactory {
public:
    // 生产苹果
    shared_ptr<Fruit> createFruit() override {
        return shared_ptr<Fruit>(new Apple());
    }
};

// 西瓜
class Watermelon : public Fruit {
public:
    // 拿到西瓜汁
    string getJuice() const override {
        return "Watermelon Juice";
    }
};

// 生产西瓜的工厂
class WatermelonFactory : public FruitFactory {
public:
    // 生产一个西瓜
    shared_ptr<Fruit> createFruit() override {
        return shared_ptr<Fruit>(new Watermelon());
    }
};

// 果汁类
class Juice {
public:
    explicit Juice(shared_ptr<FruitFactory> factory)
            : fruitFactory(factory) {
    }

    // 获取果汁
    string getJuice() const {
        // 通过水果工厂生产一个水果，再通过水果获得其果汁
        return fruitFactory->createFruit()->getJuice();
    }

private:
    shared_ptr<FruitFactory> fruitFactory;
};

int main() {

    // 使用苹果工厂
    shared_ptr<FruitFactory> appleFactory(new AppleFactory());
    Juice appleJuice(appleFactory);
    cout << appleJuice.getJuice() << endl;

    // 使用西瓜工厂
    shared_ptr<FruitFactory> watermelonFactory(new WatermelonFactory());
    Juice watermelonJuice(watermelonFactory);
    cout << watermelonJuice.getJuice() << endl;

    return 0;
}