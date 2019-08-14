#include <iostream>
#include <vector>

using namespace std;

/**
 * ���ģʽ
 * ��������ϳ����νṹ�Ա�ʾ������-���塱�Ĳ�νṹ��
 * Compositeʹ���û��Ե����������϶����ʹ�þ���һ���ԡ�
 */

class XMLComponent {
public:
    virtual ~XMLComponent() = default;

    virtual void print() = 0;
};

// XML�ĸ��ڵ�
class Composite : public XMLComponent {
public:
    // ���캯��������ǩ��ʼ��
    explicit Composite(const string &t)
            : tag(t) {
    }
    // ���ýڵ����һ���ֽڵ�
    void add(XMLComponent *component) {
        elements.push_back(component);
    }
    // ���XML�ļ�
    void print() override {
        cout << "<" << tag << ">" << endl;

        for (const auto &elem : elements)
            elem->print();

        cout << "</" << tag << ">" << endl;
    }

    // �ͷ���Դ
    ~Composite() override {

        for (const auto& elem : elements)
            delete elem;
    }

private:
    // ����ýڵ���ӽڵ�
    vector<XMLComponent *> elements;
    // �ýڵ�ı�ǩ
    string tag;
};

// XML��Ҷ�ӽ��
class Leaf : public XMLComponent {
public:
    // ����ǩ�Լ����ݽ��г�ʼ��
    explicit Leaf(const string &tag, const string &content)
            : tag(tag), content(content) {
    }
    // ���XML�ļ�
    void print() override {
        cout << "<" << tag << ">";
        cout << content;
        cout << "</" << tag << ">" << endl;
    }

private:
    // ��ǩ
    string tag;
    // ��ǩ����
    string content;
};

int main() {

    /*
    <students>
        <student>
            <name>foo</name>
            <age>18</age>
        </student>
        <student>
            <name>bar</name>
            <age>17</age>
        </student>
    </students>
     */

    Composite *students = new Composite("students");

    Composite *student1 = new Composite("student");
    Leaf *name1 = new Leaf("name", "foo");
    Leaf *age1 = new Leaf("age", "18");
    student1->add(name1);
    student1->add(age1);

    Composite *student2 = new Composite("student");
    Leaf *name2 = new Leaf("name", "bar");
    Leaf *age2 = new Leaf("age", "17");
    student2->add(name2);
    student2->add(age2);

    students->add(student1);
    students->add(student2);

    students->print();

    // ��Դ������Composite���˴������Լ�delete
    return 0;
}