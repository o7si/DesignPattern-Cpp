#include <iostream>
#include <vector>

using namespace std;

/**
 * 抽象工厂模式（Abstract Factory）
 * 提供一个接口，让该接口负责一系列“相关或相互依赖的对象”，无需指定它们具体的类。
 */

// 服装：Clothing
// 上衣：Coat
// 裤子：Pants
// 鞋子：Shoes

// 上衣
class Coat {
public:
    // 上衣的详细说明信息
    virtual void info() const = 0;

    // 为多态基类声明虚析构函数
    virtual ~Coat() = default;
};

// 裤子
class Pants {
public:
    // 裤子的详细说明信息
    virtual void info() const = 0;

    // 为多态基类声明虚析构函数
    virtual ~Pants() = default;
};

// 鞋子
class Shoes {
public:
    // 鞋子的详细说明信息
    virtual void info() const = 0;

    // 为多态基类声明虚析构函数
    virtual ~Shoes() = default;
};


// 服装工厂：用于生产成套服饰
class ClothingFactory {
public:
    // 生产一件上衣
    virtual shared_ptr<Coat> createCoat() = 0;

    // 生产一条裤子
    virtual shared_ptr<Pants> createPants() = 0;

    // 生产一双鞋
    virtual shared_ptr<Shoes> createShoes() = 0;

    // 为多态基类声明虚析构函数
    virtual ~ClothingFactory() = default;
};

// A公司生产的上衣
class ACoat : public Coat {
public:
    void info() const override {
        // 由A公司生产的一件休闲型上衣
        cout << "Producers: " << "ACompany" << endl;
        cout << "Type: " << "Casual Coat" << endl;
    }
};

// A公司生产的裤子
class APants : public Pants {
public:
    void info() const override {
        // 由A公司生产的一条休闲型裤子
        cout << "Producers: " << "ACompany" << endl;
        cout << "Type: " << "Casual Pants" << endl;
    }
};

// A公司生产的鞋子
class AShoes : public Shoes {
public:
    void info() const override {
        // 由A公司生产的一双休闲型鞋子
        cout << "Producers: " << "ACompany" << endl;
        cout << "Type: " << "Casual Shoes" << endl;
    }
};

// A公司服饰工厂（休闲型服饰）
// 抽象工厂模式：生产相关联的一整套设施
class AClothingFactory : public ClothingFactory {
public:
    // A公司的休闲型上衣
    shared_ptr<Coat> createCoat() override {
        return shared_ptr<Coat>(new ACoat());
    }

    // A公司的休闲型裤子
    shared_ptr<Pants> createPants() override {
        return shared_ptr<Pants>(new APants());
    }

    // A公司的休闲型鞋子
    shared_ptr<Shoes> createShoes() override {
        return shared_ptr<Shoes>(new AShoes());
    }
};

// B公司生产的上衣
class BCoat : public Coat {
public:
    void info() const override {
        // 由B公司生产的一件运动型上衣
        cout << "Producers: " << "BCompany" << endl;
        cout << "Type: " << "Sport Coat" << endl;
    }
};

// B公司生产的裤子
class BPants : public Pants {
public:
    void info() const override {
        // 由B公司生产的一条运动型裤子
        cout << "Producers: " << "BCompany" << endl;
        cout << "Type: " << "Sport Pants" << endl;
    }
};

// B公司生产的鞋子
class BShoes : public Shoes {
public:
    void info() const override {
        // 由B公司生产的一双运动型鞋子
        cout << "Producers: " << "Company" << endl;
        cout << "Type: " << "Sport Shoes" << endl;
    }
};

// B公司服饰工厂（运动型服饰）
// 抽象工厂模式：生产相关联的一整套设施
class BClothingFactory : public ClothingFactory {
public:
    // B公司的运动型上衣
    shared_ptr<Coat> createCoat() override {
        return shared_ptr<Coat>(new BCoat());
    }

    // B公司的运动型裤子
    shared_ptr<Pants> createPants() override {
        return shared_ptr<Pants>(new BPants());
    }

    // B公司的运动型鞋子
    shared_ptr<Shoes> createShoes() override {
        return shared_ptr<Shoes>(new BShoes());
    }
};

// 商城：用于售卖服饰
class Mall {
public:
    // 添加一个新的供应商
    void addFactory(const shared_ptr<ClothingFactory> &factory) {
        factories.push_back(factory);
    }

    // 查看生产销售的商品
    void showProduct() const {
        for (const auto &factory : factories) {
            factory->createCoat()->info();
            factory->createPants()->info();
            factory->createShoes()->info();
            cout << endl;
        }
    }

private:
    // 供应服饰的生产商
    vector<shared_ptr<ClothingFactory>> factories;
};

int main() {

    // A公司服饰工厂
    shared_ptr<AClothingFactory> aFactory(new AClothingFactory());
    // B公司服饰工厂
    shared_ptr<BClothingFactory> bFactory(new BClothingFactory());
    // 商场
    shared_ptr<Mall> mall(new Mall());

    // 向商城添加供应商：A公司
    mall->addFactory(aFactory);
    // 向商城添加供应商：B公司
    mall->addFactory(bFactory);

    // 查看商城所售商品
    mall->showProduct();

    return 0;
}