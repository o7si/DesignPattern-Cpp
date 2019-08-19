#include <iostream>
#include <map>
#include <stack>

using namespace std;

/**
 * Interpreter
 * 给定一个语言，定义它的文法的一种表示，并定义一种解释器，这个解释器使用该表达来解释语言中的句子。
 */

// 表达式
class Expression {
public:
    virtual int interpreter(map<char, int> &var) = 0;

    virtual ~Expression() = default;
};

// 值表达式
class VarExpression : public Expression {
public:
    explicit VarExpression(char key) {
        this->key = key;
    }

    int interpreter(map<char, int> &var) override {
        return var[key];
    }

private:
    char key;
};

// 运算符表达式
class SymbolExpression : public Expression {
protected:
    // 将构造函数声明为受保护的，不希望客户实例化该对象
    SymbolExpression(Expression *left, Expression *right) {
        this->left = left;
        this->right = right;
    }

    // 表达式的左值
    Expression *left;
    // 表达式的右值
    Expression *right;

    ~SymbolExpression() override {
        delete left;
        delete right;
    }
};


// 加法运算
class AddExpression : public SymbolExpression {
public:
    AddExpression(Expression *left, Expression *right)
            : SymbolExpression(left, right) {
    }

    int interpreter(map<char, int> &var) override {
        // 多态调用，先计算左值，再计算右值，然后返回相加的结果
        return left->interpreter(var) + right->interpreter(var);
    }
};

// 减法运算
class SubExpression : public SymbolExpression {
public:
    SubExpression(Expression *left, Expression *right)
            : SymbolExpression(left, right) {
    }

    int interpreter(map<char, int> &var) override {
        // 多态调用，先计算左值，再计算右值，然后返回相减的结果
        return left->interpreter(var) - right->interpreter(var);
    }
};

class Analyse {
public:
    Expression *operator()(const string &expStr) {

        Expression *left = nullptr;
        Expression *right = nullptr;

        // 栈顶元素为解析的结果
        stack<Expression *> c;

        for (size_t i = 0; i < expStr.size(); ++i) {
            switch (expStr[i]) {
                case '+':
                    // 如果当前是加号
                    // 栈顶元素作为左值，加号之后的下一个元素作为右值，重新压入栈中
                    left = c.top();
                    right = new VarExpression(expStr[++i]);

                    c.push(new AddExpression(left, right));
                    break;
                case '-':
                    // 如果当前是减号
                    // 栈顶元素作为左值，减号之后的下一个元素作为右值，重新压入栈中
                    left = c.top();
                    right = new VarExpression(expStr[++i]);

                    c.push(new SubExpression(left, right));
                    break;
                default:
                    // 如果不是加号或减号，代表当前为一个值表达式
                    c.push(new VarExpression(expStr[i]));
                    break;
            }
        }
        // 返回栈顶元素
        return c.top();
    }
};

int main() {

    // 将要进行解析的表达式
    string expStr = "a+b-c+d";

    // 表达式中各元素所代表的数值
    map<char, int> var;
    var.insert(make_pair('a', 1));
    var.insert(make_pair('b', 2));
    var.insert(make_pair('c', 3));
    var.insert(make_pair('d', 4));

    // 进行表达式的解析
    Expression *expression = Analyse()(expStr);
    // 输出结果
    cout << expression->interpreter(var) << endl;

    // 释放资源
    delete expression;
    return 0;
}