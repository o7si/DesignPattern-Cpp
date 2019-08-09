#include <iostream>
#include <sstream>

#include <random>
#include <ctime>

#include <vector>
#include <map>

using namespace std;

/**
 * 享元模式（Flyweight)
 * 运用共享有效地支持大量细粒度的对象。
 * 可用来实现对象池等。
 */

// 单词
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
    // 内部属性（单词样式）
    string type;
    // 外部属性（单词内容）
    string content;
};

// 单词样式工厂
class WordTypeFactory {
public:

    // 从样式池中获取单词样式
    Word *getWordType(const string &type) {

        // 查询池中是否已经有该样式
        auto iter = typePool.find(type);
        // 若无改样式则向池中添加该样式
        if (iter == typePool.end())
            typePool.insert(make_pair(type, new Word(type)));
        // 返回样式
        return typePool[type];
    }

    void clear() {
        // 释放资源
        for (const auto &item : typePool) {
            delete item.second;
        }
    }

private:
    // 样式池
    map<string, Word *> typePool;
};

// 随机一个样式
string randomType() {

    // 设置随机数引擎
    static std::default_random_engine engine(time(nullptr));

    // 粗体、斜体、下划线
    vector<string> types = {
            "Bold",
            "Italic",
            "Underline"
    };

    // 设置随机数分布为[0, type.size() - 1]
    std::uniform_int_distribution<int> distribution(0, types.size() - 1);

    return types[distribution(engine)];
}

int main() {

    string article = "All or nothing , now or never .";
    istringstream iss(article);

    // 初始化一个池
    auto *wtf = new WordTypeFactory;

    string content;
    while (iss >> content) {
        // 随机一个样式
        string type = randomType();
        // 从池中获取样式
        Word *word = wtf->getWordType(type);
        // 设置单词内容
        word->setContent(content);
        // 输出单词
        word->print();
    }

    // 清空池
    wtf->clear();
    // 释放指针所指资源
    delete wtf;

    return 0;
}