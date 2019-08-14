#include <iostream>
#include <vector>

using namespace std;

/**
 * 组合模式
 * 将对象组合成树形结构以表示“部分-整体”的层次结构。
 * Composite使得用户对单个对象和组合对象的使用具有一致性。
 */

class XMLComponent {
public:
    virtual ~XMLComponent() = default;

    virtual void print() = 0;
};

// XML的根节点
class Composite : public XMLComponent {
public:
    // 构造函数：将标签初始化
    explicit Composite(const string &t)
            : tag(t) {
    }
    // 给该节点添加一个字节点
    void add(XMLComponent *component) {
        elements.push_back(component);
    }
    // 输出XML文件
    void print() override {
        cout << "<" << tag << ">" << endl;

        for (const auto &elem : elements)
            elem->print();

        cout << "</" << tag << ">" << endl;
    }

    // 释放资源
    ~Composite() override {

        for (const auto& elem : elements)
            delete elem;
    }

private:
    // 管理该节点的子节点
    vector<XMLComponent *> elements;
    // 该节点的标签
    string tag;
};

// XML的叶子结点
class Leaf : public XMLComponent {
public:
    // 将标签以及内容进行初始化
    explicit Leaf(const string &tag, const string &content)
            : tag(tag), content(content) {
    }
    // 输出XML文件
    void print() override {
        cout << "<" << tag << ">";
        cout << content;
        cout << "</" << tag << ">" << endl;
    }

private:
    // 标签
    string tag;
    // 标签内容
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

    // 资源管理交给Composite，此处无需自己delete
    return 0;
}