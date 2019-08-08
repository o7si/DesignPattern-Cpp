#include <iostream>
#include <vector>

using namespace std;

/**
 * ���󹤳�ģʽ��Abstract Factory��
 * �ṩһ���ӿڣ��øýӿڸ���һϵ�С���ػ��໥�����Ķ��󡱣�����ָ�����Ǿ�����ࡣ
 */

// ��װ��Clothing
// ���£�Coat
// ���ӣ�Pants
// Ь�ӣ�Shoes

// ����
class Coat {
public:
    // ���µ���ϸ˵����Ϣ
    virtual void info() const = 0;

    // Ϊ��̬������������������
    virtual ~Coat() = default;
};

// ����
class Pants {
public:
    // ���ӵ���ϸ˵����Ϣ
    virtual void info() const = 0;

    // Ϊ��̬������������������
    virtual ~Pants() = default;
};

// Ь��
class Shoes {
public:
    // Ь�ӵ���ϸ˵����Ϣ
    virtual void info() const = 0;

    // Ϊ��̬������������������
    virtual ~Shoes() = default;
};


// ��װ�����������������׷���
class ClothingFactory {
public:
    // ����һ������
    virtual shared_ptr<Coat> createCoat() = 0;

    // ����һ������
    virtual shared_ptr<Pants> createPants() = 0;

    // ����һ˫Ь
    virtual shared_ptr<Shoes> createShoes() = 0;

    // Ϊ��̬������������������
    virtual ~ClothingFactory() = default;
};

// A��˾����������
class ACoat : public Coat {
public:
    void info() const override {
        // ��A��˾������һ������������
        cout << "Producers: " << "ACompany" << endl;
        cout << "Type: " << "Casual Coat" << endl;
    }
};

// A��˾�����Ŀ���
class APants : public Pants {
public:
    void info() const override {
        // ��A��˾������һ�������Ϳ���
        cout << "Producers: " << "ACompany" << endl;
        cout << "Type: " << "Casual Pants" << endl;
    }
};

// A��˾������Ь��
class AShoes : public Shoes {
public:
    void info() const override {
        // ��A��˾������һ˫������Ь��
        cout << "Producers: " << "ACompany" << endl;
        cout << "Type: " << "Casual Shoes" << endl;
    }
};

// A��˾���ι����������ͷ��Σ�
// ���󹤳�ģʽ�������������һ������ʩ
class AClothingFactory : public ClothingFactory {
public:
    // A��˾������������
    shared_ptr<Coat> createCoat() override {
        return shared_ptr<Coat>(new ACoat());
    }

    // A��˾�������Ϳ���
    shared_ptr<Pants> createPants() override {
        return shared_ptr<Pants>(new APants());
    }

    // A��˾��������Ь��
    shared_ptr<Shoes> createShoes() override {
        return shared_ptr<Shoes>(new AShoes());
    }
};

// B��˾����������
class BCoat : public Coat {
public:
    void info() const override {
        // ��B��˾������һ���˶�������
        cout << "Producers: " << "BCompany" << endl;
        cout << "Type: " << "Sport Coat" << endl;
    }
};

// B��˾�����Ŀ���
class BPants : public Pants {
public:
    void info() const override {
        // ��B��˾������һ���˶��Ϳ���
        cout << "Producers: " << "BCompany" << endl;
        cout << "Type: " << "Sport Pants" << endl;
    }
};

// B��˾������Ь��
class BShoes : public Shoes {
public:
    void info() const override {
        // ��B��˾������һ˫�˶���Ь��
        cout << "Producers: " << "Company" << endl;
        cout << "Type: " << "Sport Shoes" << endl;
    }
};

// B��˾���ι������˶��ͷ��Σ�
// ���󹤳�ģʽ�������������һ������ʩ
class BClothingFactory : public ClothingFactory {
public:
    // B��˾���˶�������
    shared_ptr<Coat> createCoat() override {
        return shared_ptr<Coat>(new BCoat());
    }

    // B��˾���˶��Ϳ���
    shared_ptr<Pants> createPants() override {
        return shared_ptr<Pants>(new BPants());
    }

    // B��˾���˶���Ь��
    shared_ptr<Shoes> createShoes() override {
        return shared_ptr<Shoes>(new BShoes());
    }
};

// �̳ǣ�������������
class Mall {
public:
    // ���һ���µĹ�Ӧ��
    void addFactory(const shared_ptr<ClothingFactory> &factory) {
        factories.push_back(factory);
    }

    // �鿴�������۵���Ʒ
    void showProduct() const {
        for (const auto &factory : factories) {
            factory->createCoat()->info();
            factory->createPants()->info();
            factory->createShoes()->info();
            cout << endl;
        }
    }

private:
    // ��Ӧ���ε�������
    vector<shared_ptr<ClothingFactory>> factories;
};

int main() {

    // A��˾���ι���
    shared_ptr<AClothingFactory> aFactory(new AClothingFactory());
    // B��˾���ι���
    shared_ptr<BClothingFactory> bFactory(new BClothingFactory());
    // �̳�
    shared_ptr<Mall> mall(new Mall());

    // ���̳���ӹ�Ӧ�̣�A��˾
    mall->addFactory(aFactory);
    // ���̳���ӹ�Ӧ�̣�B��˾
    mall->addFactory(bFactory);

    // �鿴�̳�������Ʒ
    mall->showProduct();

    return 0;
}