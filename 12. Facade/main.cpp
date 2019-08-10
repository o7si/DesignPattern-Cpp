#include <iostream>

using namespace std;

/**
 * Facade模式
 * 为子系统的一组接口提供一个一致的界面。
 * 该模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。
 * 用户不需要协调各个模块的繁琐工作，全部交由Facade进行控制，Facade只需要提供一个高层接口供用户调用。
 */

// 内部模块A
class ModuleA {
public:
    void process() {
        cout << "ModuleA->Processing" << endl;
    }
};

// 内部模块B
class ModuleB {
public:
    void process() {
        cout << "ModuleB->Processing" << endl;
    }
};

// 内部模块C
class ModuleC {
public:
    void process() {
        cout << "ModuleC->Processing" << endl;
    }
};

// 负责协调内部各个模块，用户直接调用该类的方法来实现功能
class Facade {
public:
    void process() {
        // 用户不需要设计各个模块之间的协调工作
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