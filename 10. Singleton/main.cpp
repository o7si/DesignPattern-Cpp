#include <iostream>
#include <mutex>
#include <atomic>
#include <memory>

using namespace std;

// ��һ��ʵ�֣�����ʽ���ӳټ��أ�
// �Ƿ��̰߳�ȫ����
namespace impl_1 {

    // ʹ������ָ����й�����ֹ�û���õ����������delete
    class Singleton {
    public:
        // ��ȡ��������
        static shared_ptr<Singleton> getInstance();

        // ɾ���������캯������ֹ�û����Ƶ�������
        Singleton(const Singleton &other) = delete;

    private:
        // �����캯������Ϊprivate����ֹ�û�����ʵ��������
        Singleton() = default;

        // ��������
        static shared_ptr<Singleton> instance;
    };

    // ��ʼ��Ϊ��
    shared_ptr<Singleton> Singleton::instance = nullptr;

    // ��ȡ��������
    shared_ptr<Singleton> Singleton::getInstance() {

        if (instance == nullptr)
            // �˴������̰߳�ȫ����
            // �ڶ��̻߳����£����ܻ���һ�����ϵĽ���ͬʱ�����ж����
            // ��ᵼ�¶��ʵ����
            instance = shared_ptr<Singleton>(new Singleton());
        return instance;
    }
}

// �ڶ���ʵ�֣���̬�������ӳټ��أ�
// �Ƿ��̰߳�ȫ����
namespace impl_2 {

    // ʹ������ָ����й�����ֹ�û���õ����������delete
    class Singleton {
    public:
        // ��ȡ��������
        static shared_ptr<Singleton> getInstance();

        // ɾ���������캯������ֹ�û����Ƶ�������
        Singleton(const Singleton &other) = delete;

    private:
        // �����캯������Ϊprivate����ֹ�û�����ʵ��������
        Singleton() = default;
    };

    // ��ȡ��������
    shared_ptr<Singleton> Singleton::getInstance() {
        // static�������ܱ�֤�̰߳�ȫ
        static shared_ptr<Singleton> instance(new Singleton());
        return instance;
    }
}

// ������ʵ�֣�����ʽ���������أ�
// �Ƿ��̰߳�ȫ����
namespace impl_3 {

    // ʹ������ָ����й�����ֹ�û���õ����������delete
    class Singleton {
    public:
        // ��ȡ��������
        static shared_ptr<Singleton> getInstance();

        // ɾ���������캯������ֹ�û����Ƶ�������
        Singleton(const Singleton &other) = delete;

    private:
        // �����캯������Ϊprivate����ֹ�û�����ʵ��������
        Singleton() = default;

        // ��������
        static shared_ptr<Singleton> instance;
    };

    // ����ʵ����
    shared_ptr<Singleton> Singleton::instance(new Singleton());

    // ��ȡ��������
    shared_ptr<Singleton> Singleton::getInstance() {
        return instance;
    }
}

// ������ʵ�֣��������
// �Ƿ��̰߳�ȫ����
namespace impl_4 {

    // ʹ������ָ����й�����ֹ�û���õ����������delete
    class Singleton {
    public:
        // ��ȡ��������
        static shared_ptr<Singleton> getInstance();

        // ɾ���������캯������ֹ�û����Ƶ�������
        Singleton(const Singleton &other) = delete;

    private:
        // �����캯������Ϊprivate����ֹ�û�����ʵ��������
        Singleton() = default;

        // ��������
        static shared_ptr<Singleton> instance;
        // ������
        static mutex mMutex;
    };

    // ��ʼ��Ϊ��
    shared_ptr<Singleton> Singleton::instance = nullptr;

    // ��ʼ��������
    mutex Singleton::mMutex;

    // ��ȡ��������
    shared_ptr<Singleton> Singleton::getInstance() {

        // ���Ĵ��۹��ߣ���instance��Ϊ���Ի�����
        // ����
        mMutex.lock();

        if (instance == nullptr)
            instance = shared_ptr<Singleton>(new Singleton());

        // �ͷ���
        mMutex.unlock();

        return instance;
    }
}

// ������ʵ�֣�˫�����
// �Ƿ��̰߳�ȫ����
namespace impl_5 {

    // ʹ������ָ����й�����ֹ�û���õ����������delete
    class Singleton {
    public:
        // ��ȡ��������
        static shared_ptr<Singleton> getInstance();

        // ɾ���������캯������ֹ�û����Ƶ�������
        Singleton(const Singleton &other) = delete;

    private:
        // �����캯������Ϊprivate����ֹ�û�����ʵ��������
        Singleton() = default;

        // ��������
        static shared_ptr<Singleton> instance;
        // ������
        static mutex mMutex;
    };

    // ��ʼ��Ϊ��
    shared_ptr<Singleton> Singleton::instance = nullptr;

    // ��ʼ��������
    mutex Singleton::mMutex;

    // ��ȡ��������
    shared_ptr<Singleton> Singleton::getInstance() {

        if (instance == nullptr) {

            // �����ڴ��дreorder���ܻᵼ�»᲻��ȫ

            // ����
            mMutex.lock();
            if (instance == nullptr)
                instance = shared_ptr<Singleton>(new Singleton());
            // �ͷ���
            mMutex.unlock();
        }

        return instance;
    }
}

// ������ʵ�֣��ڴ�դ���������䣩
// �Ƿ��̰߳�ȫ����
namespace impl_6 {

}

int main() {

    cout << boolalpha;
    {
        // ��һ��ʵ��
        using namespace impl_1;
        cout << (Singleton::getInstance() == Singleton::getInstance()) << endl;
    }
    {
        // �ڶ���ʵ��
        using namespace impl_2;
        cout << (Singleton::getInstance() == Singleton::getInstance()) << endl;
    }
    {
        // ������ʵ��
        using namespace impl_3;
        cout << (Singleton::getInstance() == Singleton::getInstance()) << endl;
    }
    {
        // ������ʵ��
        using namespace impl_4;
        cout << (Singleton::getInstance() == Singleton::getInstance()) << endl;
    }
    {
        // ������ʵ��
        using namespace impl_5;
        cout << (Singleton::getInstance() == Singleton::getInstance()) << endl;
    }
    {
        // ������ʵ��
        using namespace impl_6;
    }
    cout << noboolalpha;

    return 0;
}