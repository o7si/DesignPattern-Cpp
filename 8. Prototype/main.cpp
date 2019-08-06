#include <iostream>

using namespace std;

/**
 * ԭ��ģʽ��Prototype��
 * ʹ��ԭ��ʾ��ָ��������������࣬Ȼ��ͨ��������Щԭ���������µĶ���
 */

// ͨ�׽��ͣ�
// Ϊ�˻�ȡһ��ʵ��������ĸ�����������Ҫʹ��ԭ��ģʽ��
// ��ֱ��ʹ�ÿ������캯����Ϊ�˿��������й����н��а󶨡���ȡ��

// ��Ϣԭ����
class Information {
public:
    // ��¡������ԭ��ģʽ�ĺ��ģ�
    virtual shared_ptr<Information> clone() = 0;

    // �����Ϣ
    virtual void show() const = 0;

    // Ϊ��̬������������������
    virtual ~Information() = default;
};

// ʳƷ��Ϣ
class FoodInformation : public Information {
public:
    // ��¡����ʵ��Ϊ��������Ŀ������캯����
    shared_ptr<Information> clone() override {
        return shared_ptr<Information>(new FoodInformation(*this));
    }

    // Ĭ�Ϲ��캯��
    explicit FoodInformation(const string &n = "default", unsigned d = 3)
            : name(n), days(d) {
    }

    // �������캯��
    FoodInformation(const FoodInformation &rhs) {
        this->name = rhs.name;
        this->days = rhs.days;
    }

    // ���ʳƷ��Ϣ
    void show() const override {
        cout << "FoodInformation [name = " << name << ", days = " << days << "]" << endl;
    }

private:
    // ʳƷ����
    string name;
    // ������
    unsigned days;
};

// ��Ա��Ϣ
class PersonInformation : public Information {
public:
    // ��¡����ʵ��Ϊ��������Ŀ������캯����
    shared_ptr<Information> clone() override {
        return shared_ptr<Information>(new PersonInformation(*this));
    }

    // Ĭ�Ϲ��캯��
    explicit PersonInformation(const string &n = "default", unsigned a = 20)
            : name(n), age(a) {
    }

    // �������캯��
    PersonInformation(const PersonInformation &rhs) {
        this->name = rhs.name;
        this->age = rhs.age;
    }

    // �����Ա��Ϣ
    void show() const override {
        cout << "PersonInformation [name = " << name << ", age = " << age << "]" << endl;
    }

private:
    // ����
    string name;
    // ����
    unsigned age;
};

int main() {

    shared_ptr<Information> foodInfo(new FoodInformation("Hamburg", 3));
    // ��¡һ��ʳƷ��Ϣ
    shared_ptr<Information> cloneFood = foodInfo->clone();
    // �����¡���ʳƷ��Ϣ
    cloneFood->show();

    shared_ptr<Information> personInfo(new PersonInformation("o7si", 20));
    // ��¡һ����Ա��Ϣ
    shared_ptr<Information> clonePerson = personInfo->clone();
    // �����¡�����Ա��Ϣ
    clonePerson->show();

    return 0;
}