#include <iostream>

using namespace std;

/**
 * Command
 * ��һ�������װΪһ������ʹ������������κ�ִ����������ηָ��
 * ��������֮��ͨ�����������й�ͨ���������㽫���������д��桢���ݡ����á����������
 */

/************************************************************/
// �����ߣ��������׵�����
class CoatReceiver {
public:
    void product() {
        cout << "Coat" << endl;
    }
};

// �����ߣ�����ñ�ӵ�����
class HatReceiver {
public:
    void product() {
        cout << "Hat" << endl;
    }
};
/************************************************************/


/************************************************************/
// ��������
class Command {
public:
    // ִ������
    virtual void execute() = 0;

    // Ϊ��̬�����д����������
    virtual ~Command() = default;
};

// ������������
class CoatCommand : public Command {
public:
    explicit CoatCommand(const CoatReceiver &cr)
            : receiver(cr) {
    }

    // ִ������
    void execute() override {
        receiver.product();
    }

private:
    // �����ߣ�������������
    CoatReceiver receiver;
};

// ����ñ������
class HatCommand : public Command {
public:
    explicit HatCommand(const HatReceiver &hr)
            : receiver(hr) {
    }

    // ִ������
    void execute() override {
        receiver.product();
    }

private:
    // �����ߣ���������ñ��
    HatReceiver receiver;
};
/************************************************************/


/************************************************************/
// �˿ͣ�������
class Customer {
public:

    Customer(const CoatCommand &cc, const HatCommand &hc)
            : coatCommand(cc), hatCommand(hc) {
    }

    // ��������
    void buyCoat() {
        // ִ����������ָ��
        coatCommand.execute();
    }

    // ����ñ��
    void buyHat() {
        // ִ������ñ��ָ��
        hatCommand.execute();
    }

private:
    // ������������
    CoatCommand coatCommand;
    // ����ñ������
    HatCommand hatCommand;
};
/************************************************************/

int main() {

    // �����ߣ��������׵�����
    CoatReceiver coatReceiver;
    // �����ߣ�����ñ�ӵ�����
    HatReceiver hatReceiver;

    // �����������
    CoatCommand coatCommand(coatReceiver);
    // �������ñ��
    HatCommand hatCommand(hatReceiver);

    // �˿ͣ����𷢳�����
    Customer customer(coatCommand, hatCommand);

    // �˿ͷ��������Ҫ����һ������
    customer.buyCoat();

    // �˿ͷ��������Ҫ����һ��ñ��
    customer.buyHat();

    return 0;
}