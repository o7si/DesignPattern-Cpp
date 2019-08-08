#include <iostream>
#include <string>
#include <map>

using namespace std;

// �۲��ߣ����ڵĽ��������
class IFocusListener {
public:
    // �����ڻ�ý���
    virtual void focusGained() = 0;

    // ������ʧȥ����
    virtual void focusLost() = 0;

    // Ϊ��̬����������������������֤����ָ���ܹ���ȷ�ͷ���Դ
    virtual ~IFocusListener() = default;
};

// ���ڻ��ࣺ���ڹ�����������۲��ߣ�
class FrameBase {
public:
    // ��Ӵ��ڵĽ����¼���������ʹ��identity��ʶ������
    void addFocusListener(const string &identity, IFocusListener *focusListener) {
        focusListeners.insert(make_pair(identity, focusListener));
    }

    // �Ƴ����ڵĽ����¼���������ͨ��identity�Ƴ�������
    void removeFocusListener(const string &identity) {

        // �ͷ�identity����Ӧ����������Դ
        auto begin = focusListeners.lower_bound(identity);
        auto end = focusListeners.upper_bound(identity);
        for (auto iter = begin; iter != end; ++iter)
            delete iter->second;
        // �Ƴ�identity����Ӧ�ļ�����
        focusListeners.erase(identity);
    }

    // �����ڻ�ý���ʱ���ô˷���֪ͨ���������۲��ߣ�
    void doFocusGainedNotify() {

        for (const auto &elem : focusListeners) {
            // �����ڻ���˽������Ϣ֪ͨ��ÿһ���۲���
            elem.second->focusGained();
        }
    }

    // ������ʧȥ����ʱ���ô˷���֪ͨ���������۲��ߣ�
    void doFocusLostNotify() {

        for (const auto &elem : focusListeners) {
            // ������ʧȥ�˽������Ϣ֪ͨ��ÿһ���۲���
            elem.second->focusLost();
        }
    }

    // Ϊ��̬����������������������֤����ָ���ܹ���ȷ�ͷ���Դ
    virtual ~FrameBase() {

        // �ͷ����������������Դ
        for (auto &elem : focusListeners) {

            delete elem.second;
        }
    }

private:
    // �Թ۲��ߣ����ڽ����¼������������й���
    // ʹ��multimap��ʾһ����ʶ����ͬʱ��Ӧ���������
    // ���磺��ʶ��"test"����ͬʱ��Ӧ������"focusListener1"��"focusListener2"
    multimap<const string, IFocusListener *> focusListeners;
};

// �����ࣺʡ�������ģʽ����صķ���
class Frame : public FrameBase {
public:
    //...

    // ���ڻ�ý���
    void onFocusGained() {

        // ֪ͨ�۲��߸ô��ڻ���˽���
        doFocusGainedNotify();
    }

    // ����ʧȥ����
    void onFocusLost() {

        // ֪ͨ�۲��߸ô���ʧȥ�˽���
        doFocusLostNotify();
    }

    // ...
};

// �����ã��̳м������ӿڣ���ʵ���䷽��
class MyFocusListener1 : public IFocusListener {
public:
    // �յ�֪ͨ�����ڻ���˽���
    void focusGained() override {
        cout << "FocusGained1" << endl;
    }

    // �յ�֪ͨ������ʧȥ�˽���
    void focusLost() override {
        cout << "FocusLost1" << endl;
    }
};

// �����ã��̳м������ӿڣ���ʵ���䷽��
class MyFocusListener2 : public IFocusListener {
public:
    // �յ�֪ͨ�����ڻ���˽���
    void focusGained() override {
        cout << "FocusGained2" << endl;
    }

    // �յ�֪ͨ������ʧȥ�˽���
    void focusLost() override {
        cout << "FocusLost2" << endl;
    }
};

int main() {

    // ʵ����һ�����ڶ���
    Frame *frame = new Frame;

    // Ϊ���ڰ�������ʶΪ"test"������
    frame->addFocusListener("test", new MyFocusListener1);
    frame->addFocusListener("test", new MyFocusListener2);

    // ��ʱ���ڰ�������������
    // �����ڻ�ý���
    frame->onFocusGained();
    // ������ʧȥ����
    frame->onFocusLost();

    // �Ƴ������б�ʶΪ"test"�ļ�����
    frame->removeFocusListener("test");

    // ��ʱ����δ���κμ�����
    // �����ڻ�ý���
    frame->onFocusGained();
    // ������ʧȥ����
    frame->onFocusLost();

    delete frame;
    return 0;
}