#include <iostream>

using namespace std;

/**
 * 原型模式（Prototype）
 * 使用原型示例指定创建对象的种类，然后通过拷贝这些原型来创建新的对象。
 */

// 通俗解释：
// 为了获取一个实例化对象的副本，所以需要使用原型模式。
// 不直接使用拷贝构造函数是为了可以在运行过程中进行绑定、获取。

// 信息原型类
class Information {
public:
    // 克隆方法（原型模式的核心）
    virtual shared_ptr<Information> clone() = 0;

    // 输出信息
    virtual void show() const = 0;

    // 为多态基类声明虚析构函数
    virtual ~Information() = default;
};

// 食品信息
class FoodInformation : public Information {
public:
    // 克隆自身（实则为调用自身的拷贝构造函数）
    shared_ptr<Information> clone() override {
        return shared_ptr<Information>(new FoodInformation(*this));
    }

    // 默认构造函数
    explicit FoodInformation(const string &n = "default", unsigned d = 3)
            : name(n), days(d) {
    }

    // 拷贝构造函数
    FoodInformation(const FoodInformation &rhs) {
        this->name = rhs.name;
        this->days = rhs.days;
    }

    // 输出食品信息
    void show() const override {
        cout << "FoodInformation [name = " << name << ", days = " << days << "]" << endl;
    }

private:
    // 食品名称
    string name;
    // 保质期
    unsigned days;
};

// 人员信息
class PersonInformation : public Information {
public:
    // 克隆自身（实则为调用自身的拷贝构造函数）
    shared_ptr<Information> clone() override {
        return shared_ptr<Information>(new PersonInformation(*this));
    }

    // 默认构造函数
    explicit PersonInformation(const string &n = "default", unsigned a = 20)
            : name(n), age(a) {
    }

    // 拷贝构造函数
    PersonInformation(const PersonInformation &rhs) {
        this->name = rhs.name;
        this->age = rhs.age;
    }

    // 输出人员信息
    void show() const override {
        cout << "PersonInformation [name = " << name << ", age = " << age << "]" << endl;
    }

private:
    // 姓名
    string name;
    // 年龄
    unsigned age;
};

int main() {

    shared_ptr<Information> foodInfo(new FoodInformation("Hamburg", 3));
    // 克隆一份食品信息
    shared_ptr<Information> cloneFood = foodInfo->clone();
    // 输出克隆后的食品信息
    cloneFood->show();

    shared_ptr<Information> personInfo(new PersonInformation("o7si", 20));
    // 克隆一份人员信息
    shared_ptr<Information> clonePerson = personInfo->clone();
    // 输出克隆后的人员信息
    clonePerson->show();

    return 0;
}