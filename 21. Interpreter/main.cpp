#include <iostream>
#include <map>
#include <stack>

using namespace std;

/**
 * Interpreter
 * ����һ�����ԣ����������ķ���һ�ֱ�ʾ��������һ�ֽ����������������ʹ�øñ�������������еľ��ӡ�
 */

// ���ʽ
class Expression {
public:
    virtual int interpreter(map<char, int> &var) = 0;

    virtual ~Expression() = default;
};

// ֵ���ʽ
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

// ��������ʽ
class SymbolExpression : public Expression {
protected:
    // �����캯������Ϊ�ܱ����ģ���ϣ���ͻ�ʵ�����ö���
    SymbolExpression(Expression *left, Expression *right) {
        this->left = left;
        this->right = right;
    }

    // ���ʽ����ֵ
    Expression *left;
    // ���ʽ����ֵ
    Expression *right;

    ~SymbolExpression() override {
        delete left;
        delete right;
    }
};


// �ӷ�����
class AddExpression : public SymbolExpression {
public:
    AddExpression(Expression *left, Expression *right)
            : SymbolExpression(left, right) {
    }

    int interpreter(map<char, int> &var) override {
        // ��̬���ã��ȼ�����ֵ���ټ�����ֵ��Ȼ�󷵻���ӵĽ��
        return left->interpreter(var) + right->interpreter(var);
    }
};

// ��������
class SubExpression : public SymbolExpression {
public:
    SubExpression(Expression *left, Expression *right)
            : SymbolExpression(left, right) {
    }

    int interpreter(map<char, int> &var) override {
        // ��̬���ã��ȼ�����ֵ���ټ�����ֵ��Ȼ�󷵻�����Ľ��
        return left->interpreter(var) - right->interpreter(var);
    }
};

class Analyse {
public:
    Expression *operator()(const string &expStr) {

        Expression *left = nullptr;
        Expression *right = nullptr;

        // ջ��Ԫ��Ϊ�����Ľ��
        stack<Expression *> c;

        for (size_t i = 0; i < expStr.size(); ++i) {
            switch (expStr[i]) {
                case '+':
                    // �����ǰ�ǼӺ�
                    // ջ��Ԫ����Ϊ��ֵ���Ӻ�֮�����һ��Ԫ����Ϊ��ֵ������ѹ��ջ��
                    left = c.top();
                    right = new VarExpression(expStr[++i]);

                    c.push(new AddExpression(left, right));
                    break;
                case '-':
                    // �����ǰ�Ǽ���
                    // ջ��Ԫ����Ϊ��ֵ������֮�����һ��Ԫ����Ϊ��ֵ������ѹ��ջ��
                    left = c.top();
                    right = new VarExpression(expStr[++i]);

                    c.push(new SubExpression(left, right));
                    break;
                default:
                    // ������ǼӺŻ���ţ�����ǰΪһ��ֵ���ʽ
                    c.push(new VarExpression(expStr[i]));
                    break;
            }
        }
        // ����ջ��Ԫ��
        return c.top();
    }
};

int main() {

    // ��Ҫ���н����ı��ʽ
    string expStr = "a+b-c+d";

    // ���ʽ�и�Ԫ�����������ֵ
    map<char, int> var;
    var.insert(make_pair('a', 1));
    var.insert(make_pair('b', 2));
    var.insert(make_pair('c', 3));
    var.insert(make_pair('d', 4));

    // ���б��ʽ�Ľ���
    Expression *expression = Analyse()(expStr);
    // ������
    cout << expression->interpreter(var) << endl;

    // �ͷ���Դ
    delete expression;
    return 0;
}