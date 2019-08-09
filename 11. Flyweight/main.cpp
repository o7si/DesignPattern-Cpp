#include <iostream>
#include <sstream>

#include <random>
#include <ctime>

#include <vector>
#include <map>

using namespace std;

/**
 * ��Ԫģʽ��Flyweight)
 * ���ù�����Ч��֧�ִ���ϸ���ȵĶ���
 * ������ʵ�ֶ���صȡ�
 */

// ����
class Word {
public:
    explicit Word(const string &t)
            : type(t) {
    }

    void setContent(const string &c) {
        this->content = c;
    }

    void print() {
        cout << "type : " << type << ", content : " << content << endl;
    }

private:
    // �ڲ����ԣ�������ʽ��
    string type;
    // �ⲿ���ԣ��������ݣ�
    string content;
};

// ������ʽ����
class WordTypeFactory {
public:

    // ����ʽ���л�ȡ������ʽ
    Word *getWordType(const string &type) {

        // ��ѯ�����Ƿ��Ѿ��и���ʽ
        auto iter = typePool.find(type);
        // ���޸���ʽ���������Ӹ���ʽ
        if (iter == typePool.end())
            typePool.insert(make_pair(type, new Word(type)));
        // ������ʽ
        return typePool[type];
    }

    void clear() {
        // �ͷ���Դ
        for (const auto &item : typePool) {
            delete item.second;
        }
    }

private:
    // ��ʽ��
    map<string, Word *> typePool;
};

// ���һ����ʽ
string randomType() {

    // �������������
    static std::default_random_engine engine(time(nullptr));

    // ���塢б�塢�»���
    vector<string> types = {
            "Bold",
            "Italic",
            "Underline"
    };

    // ����������ֲ�Ϊ[0, type.size() - 1]
    std::uniform_int_distribution<int> distribution(0, types.size() - 1);

    return types[distribution(engine)];
}

int main() {

    string article = "All or nothing , now or never .";
    istringstream iss(article);

    // ��ʼ��һ����
    auto *wtf = new WordTypeFactory;

    string content;
    while (iss >> content) {
        // ���һ����ʽ
        string type = randomType();
        // �ӳ��л�ȡ��ʽ
        Word *word = wtf->getWordType(type);
        // ���õ�������
        word->setContent(content);
        // �������
        word->print();
    }

    // ��ճ�
    wtf->clear();
    // �ͷ�ָ����ָ��Դ
    delete wtf;

    return 0;
}