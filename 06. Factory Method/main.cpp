#include <iostream>

using namespace std;

/**
 * ��������ģʽ��Factory Method��
 * ����һ�����ڴ�������Ľӿڣ����������ʵ������һ���ࡣ
 * ʹ��һ�����ʵ�����ӳٵ����ࡣ
 */

// ˮ��
class Fruit {
public:
    // ��ȡ��֭
    virtual string getJuice() const = 0;

    // Ϊ��̬������������������
    virtual ~Fruit() = default;
};

// ˮ����������������ˮ��
class FruitFactory {
public:
    // ����ˮ��
    // ��ò�Ҫֱ�ӷ���ָ�룬ʹ���߿��ܻ������ͷ���Դ������ڴ�й©���˴�ʹ������ָ����й���
    virtual shared_ptr<Fruit> createFruit() = 0;

    // Ϊ��̬������������������
    virtual ~FruitFactory() = default;
};

// ƻ��
class Apple : public Fruit {
public:
    // �õ�ƻ��֭
    string getJuice() const override {
        return "Apple Juice";
    }
};

// ����ƻ���Ĺ���
class AppleFactory : public FruitFactory {
public:
    // ����ƻ��
    shared_ptr<Fruit> createFruit() override {
        return shared_ptr<Fruit>(new Apple());
    }
};

// ����
class Watermelon : public Fruit {
public:
    // �õ�����֭
    string getJuice() const override {
        return "Watermelon Juice";
    }
};

// �������ϵĹ���
class WatermelonFactory : public FruitFactory {
public:
    // ����һ������
    shared_ptr<Fruit> createFruit() override {
        return shared_ptr<Fruit>(new Watermelon());
    }
};

// ��֭��
class Juice {
public:
    explicit Juice(shared_ptr<FruitFactory> factory)
            : fruitFactory(factory) {
    }

    // ��ȡ��֭
    string getJuice() const {
        // ͨ��ˮ����������һ��ˮ������ͨ��ˮ��������֭
        return fruitFactory->createFruit()->getJuice();
    }

private:
    shared_ptr<FruitFactory> fruitFactory;
};

int main() {

    // ʹ��ƻ������
    shared_ptr<FruitFactory> appleFactory(new AppleFactory());
    Juice appleJuice(appleFactory);
    cout << appleJuice.getJuice() << endl;

    // ʹ�����Ϲ���
    shared_ptr<FruitFactory> watermelonFactory(new WatermelonFactory());
    Juice watermelonJuice(watermelonFactory);
    cout << watermelonJuice.getJuice() << endl;

    return 0;
}