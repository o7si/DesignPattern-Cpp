#include <iostream>

using namespace std;

/**
 * 装饰器模式
 * 动态地给一个对象增加一些额外的职责。
 * 该模式比继承更为灵活。
 */

// 饮品基类
class Drink {
public:
    // 获取该饮品名称
    virtual string getName() = 0;

    // 获取该饮品售价
    virtual double getPrice() = 0;

    // 为多态基类声明虚析构函数，保证基类指针能够正确释放资源
    virtual ~Drink() = default;

protected:
    // 饮品名称
    string name;
    // 饮品售价
    double price;
};

// 果汁类：继承饮品类
class Juice : public Drink {
public:
    explicit Juice(const string &name, double initPrice) {
        this->name = name;
        this->price = initPrice;
    }

    // 获取果汁名称
    string getName() override {
        return name;
    }

    // 获取果汁售价
    double getPrice() override {
        return price;
    }
};

// 咖啡
class Coffee : public Drink {
public:
    explicit Coffee(const string &name, double initPrice) {
        this->name = name;
        this->price = initPrice;
    }

    // 获取咖啡名称
    string getName() override {
        return name;
    }

    // 获取咖啡售价
    double getPrice() override {
        return price;
    }
};

// 饮品装饰类的基类（装饰器模式核心）
// 公有继承Drink为了规范接口
// 成员变量drink为多态指针，指向类型在运行时绑定
class DrinkDecorator : public Drink {
protected:
    Drink *drink;

public:
    ~DrinkDecorator() override {
        delete drink;
    }
};

// 装饰类：为饮品添加冰块
class IceDrink : public DrinkDecorator {
public:
    explicit IceDrink(Drink *d) {
        this->drink = d;
    }

    // 获取添加冰块后饮品的名称
    string getName() override {

        // 饮品添加后缀，表示加了一份冰块
        return drink->getName() + "+ice";
    }

    // 获取添加冰块后饮品的售价
    double getPrice() override {

        // 因为添加了一份冰块，所以饮品售价要增加一份冰块的价格
        return drink->getPrice() + IceDrink::ice;
    }

private:
    // 每份冰块售价
    static double ice;
};

// 初始化每份冰块售价为0.5元
double IceDrink::ice = 0.5;

// 装饰类：为饮品添加牛奶
class MilkDrink : public DrinkDecorator {
public:
    explicit MilkDrink(Drink *d) {
        this->drink = d;
    }

    // 获取添加牛奶后饮品的名称
    string getName() override {

        // 为饮品添加后缀，表示加了一份牛奶
        return drink->getName() + "+milk";
    }

    // 获取添加牛奶后饮品的售价
    double getPrice() override {

        // 因为添加了一份牛奶，所以饮品售价要增加一份牛奶的价格
        return drink->getPrice() + MilkDrink::milk;
    }

private:
    // 每份牛奶售价
    static double milk;
};

// 初始化每份牛奶售价为1.2元
double MilkDrink::milk = 1.2;

int main() {

    // 一杯普通的果汁（橘汁，8.0元）
    Drink *juice = new Juice("OrangeJuice", 8.0);
    cout << juice->getName() << " : $" << juice->getPrice() << endl;
    delete juice;

    // 一杯加一份冰的果汁（橘汁，8.0元 + 0.5元 = 8.5元）
    Drink *iceJuice = new IceDrink(new Juice("OrangeJuice", 8.0));
    cout << iceJuice->getName() << " : $" << iceJuice->getPrice() << endl;
    delete iceJuice;

    // 一杯加两份冰的果汁（橘汁，8.0元 + 0.5元 + 0.5元 = 9.0元）
    Drink *doubleIceJuice = new IceDrink(new IceDrink(new Juice("OrangeJuice", 8.0)));
    cout << doubleIceJuice->getName() << " : $" << doubleIceJuice->getPrice() << endl;
    delete doubleIceJuice;

    // 一杯普通的咖啡（白咖啡，20.0元）
    Drink *coffee = new Coffee("FlatWhite", 20.0);
    cout << coffee->getName() << " : $" << coffee->getPrice() << endl;
    delete coffee;

    // 一杯加一份冰两份牛奶的咖啡（白咖啡，20.0元 + 0.5元 + 1.2元 + 1.2元 = 22.9元）
    Drink *iceDoubleMilkCoffee = new IceDrink(new MilkDrink(new MilkDrink(new Coffee("FlatWhite", 20.0))));
    cout << iceDoubleMilkCoffee->getName() << " : $" << iceDoubleMilkCoffee->getPrice() << endl;
    delete iceDoubleMilkCoffee;

    return 0;
}