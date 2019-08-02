#include <iostream>

using namespace std;

/**
 * װ����ģʽ
 * ��̬�ظ�һ����������һЩ�����ְ��
 * ��ģʽ�ȼ̳и�Ϊ��
 */

// ��Ʒ����
class Drink {
public:
    // ��ȡ����Ʒ����
    virtual string getName() = 0;

    // ��ȡ����Ʒ�ۼ�
    virtual double getPrice() = 0;

    // Ϊ��̬����������������������֤����ָ���ܹ���ȷ�ͷ���Դ
    virtual ~Drink() = default;

protected:
    // ��Ʒ����
    string name;
    // ��Ʒ�ۼ�
    double price;
};

// ��֭�ࣺ�̳���Ʒ��
class Juice : public Drink {
public:
    explicit Juice(const string &name, double initPrice) {
        this->name = name;
        this->price = initPrice;
    }

    // ��ȡ��֭����
    string getName() override {
        return name;
    }

    // ��ȡ��֭�ۼ�
    double getPrice() override {
        return price;
    }
};

// ����
class Coffee : public Drink {
public:
    explicit Coffee(const string &name, double initPrice) {
        this->name = name;
        this->price = initPrice;
    }

    // ��ȡ��������
    string getName() override {
        return name;
    }

    // ��ȡ�����ۼ�
    double getPrice() override {
        return price;
    }
};

// ��Ʒװ����Ļ��ࣨװ����ģʽ���ģ�
// ���м̳�DrinkΪ�˹淶�ӿ�
// ��Ա����drinkΪ��ָ̬�룬ָ������������ʱ��
class DrinkDecorator : public Drink {
protected:
    Drink *drink;

public:
    ~DrinkDecorator() override {
        delete drink;
    }
};

// װ���ࣺΪ��Ʒ��ӱ���
class IceDrink : public DrinkDecorator {
public:
    explicit IceDrink(Drink *d) {
        this->drink = d;
    }

    // ��ȡ��ӱ������Ʒ������
    string getName() override {

        // ��Ʒ��Ӻ�׺����ʾ����һ�ݱ���
        return drink->getName() + "+ice";
    }

    // ��ȡ��ӱ������Ʒ���ۼ�
    double getPrice() override {

        // ��Ϊ�����һ�ݱ��飬������Ʒ�ۼ�Ҫ����һ�ݱ���ļ۸�
        return drink->getPrice() + IceDrink::ice;
    }

private:
    // ÿ�ݱ����ۼ�
    static double ice;
};

// ��ʼ��ÿ�ݱ����ۼ�Ϊ0.5Ԫ
double IceDrink::ice = 0.5;

// װ���ࣺΪ��Ʒ���ţ��
class MilkDrink : public DrinkDecorator {
public:
    explicit MilkDrink(Drink *d) {
        this->drink = d;
    }

    // ��ȡ���ţ�̺���Ʒ������
    string getName() override {

        // Ϊ��Ʒ��Ӻ�׺����ʾ����һ��ţ��
        return drink->getName() + "+milk";
    }

    // ��ȡ���ţ�̺���Ʒ���ۼ�
    double getPrice() override {

        // ��Ϊ�����һ��ţ�̣�������Ʒ�ۼ�Ҫ����һ��ţ�̵ļ۸�
        return drink->getPrice() + MilkDrink::milk;
    }

private:
    // ÿ��ţ���ۼ�
    static double milk;
};

// ��ʼ��ÿ��ţ���ۼ�Ϊ1.2Ԫ
double MilkDrink::milk = 1.2;

int main() {

    // һ����ͨ�Ĺ�֭����֭��8.0Ԫ��
    Drink *juice = new Juice("OrangeJuice", 8.0);
    cout << juice->getName() << " : $" << juice->getPrice() << endl;
    delete juice;

    // һ����һ�ݱ��Ĺ�֭����֭��8.0Ԫ + 0.5Ԫ = 8.5Ԫ��
    Drink *iceJuice = new IceDrink(new Juice("OrangeJuice", 8.0));
    cout << iceJuice->getName() << " : $" << iceJuice->getPrice() << endl;
    delete iceJuice;

    // һ�������ݱ��Ĺ�֭����֭��8.0Ԫ + 0.5Ԫ + 0.5Ԫ = 9.0Ԫ��
    Drink *doubleIceJuice = new IceDrink(new IceDrink(new Juice("OrangeJuice", 8.0)));
    cout << doubleIceJuice->getName() << " : $" << doubleIceJuice->getPrice() << endl;
    delete doubleIceJuice;

    // һ����ͨ�Ŀ��ȣ��׿��ȣ�20.0Ԫ��
    Drink *coffee = new Coffee("FlatWhite", 20.0);
    cout << coffee->getName() << " : $" << coffee->getPrice() << endl;
    delete coffee;

    // һ����һ�ݱ�����ţ�̵Ŀ��ȣ��׿��ȣ�20.0Ԫ + 0.5Ԫ + 1.2Ԫ + 1.2Ԫ = 22.9Ԫ��
    Drink *iceDoubleMilkCoffee = new IceDrink(new MilkDrink(new MilkDrink(new Coffee("FlatWhite", 20.0))));
    cout << iceDoubleMilkCoffee->getName() << " : $" << iceDoubleMilkCoffee->getPrice() << endl;
    delete iceDoubleMilkCoffee;

    return 0;
}