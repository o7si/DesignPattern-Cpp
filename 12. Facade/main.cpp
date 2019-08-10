#include <iostream>

using namespace std;

/**
 * Facadeģʽ
 * Ϊ��ϵͳ��һ��ӿ��ṩһ��һ�µĽ��档
 * ��ģʽ������һ���߲�ӿڣ�����ӿ�ʹ����һ��ϵͳ��������ʹ�á�
 * �û�����ҪЭ������ģ��ķ���������ȫ������Facade���п��ƣ�Facadeֻ��Ҫ�ṩһ���߲�ӿڹ��û����á�
 */

// �ڲ�ģ��A
class ModuleA {
public:
    void process() {
        cout << "ModuleA->Processing" << endl;
    }
};

// �ڲ�ģ��B
class ModuleB {
public:
    void process() {
        cout << "ModuleB->Processing" << endl;
    }
};

// �ڲ�ģ��C
class ModuleC {
public:
    void process() {
        cout << "ModuleC->Processing" << endl;
    }
};

// ����Э���ڲ�����ģ�飬�û�ֱ�ӵ��ø���ķ�����ʵ�ֹ���
class Facade {
public:
    void process() {
        // �û�����Ҫ��Ƹ���ģ��֮���Э������
        moduleA.process();
        moduleB.process();
        moduleC.process();
    }

private:
    ModuleA moduleA;
    ModuleB moduleB;
    ModuleC moduleC;
};

int main() {

    Facade facade;
    facade.process();

    return 0;
}