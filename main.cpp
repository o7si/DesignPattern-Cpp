#include <iostream>
#include <ctime>
#include <random>

/**
 * Template Method
 * ����һ�������е��㷨�ĹǼܣ�����һЩ�����ӳٵ������С�
 * ʹ��������Բ��ı�һ���㷨�Ľṹ�����ض�����㷨��ĳЩ�ض����衣
 */

// �����ࣺ������ʵ����Container����
class Container {
public:
    /**
     * Template Method
     * ����sort�����Լ�size�������ӳٵ�������
     */
    void testSort() {

        using std::cout;
        using std::endl;

        // ��¼��ʼʱ��
        clock_t startTime = clock();
        // �������
        sort();
        // ��¼����ʱ��
        clock_t endTime = clock();

        // ����n��Ԫ����ʱm��
        cout << "size = " << size() << endl;
        cout << "time = " << static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    }

    // ��sort�����ӳٵ�������ʵ��
    virtual void sort() = 0;
    // ��size�����ӳٵ�������ʵ��
    virtual size_t size() = 0;
    // Ϊ��̬����������������������֤����ָ���ܹ���ȷ�ͷ���Դ
    virtual ~Container() = default;
};

// ģ���࣬final�ؼ���ʹ�ø��಻�����̳�
template<typename Type>
class MyContainer final : public Container {
public:
    explicit MyContainer(const Type* arr, int n) : sz(n) {

        data = new Type[sz];
        // ���������arr�е����ݵ�data
        for (int i = 0; i < sz; ++i) {
            data[i] = arr[i];
        }
    }

    /**
     * ���һ�������ָ���Ա������������Ҫ��д�������캯����������ֵ������Լ�����������
     * ���У�������ֵ�����Ӧ���ܹ��������Ҹ�ֵ�������
     */

    // �������캯��
    MyContainer(const MyContainer& rhs) {

        sz = rhs.sz;
        data = new Type[sz];
        // ���������arr�е����ݵ�data
        for (int i = 0; i < sz; ++i) {
            data[i] = arr[i];
        }
    }

    // ������ֵ�����
    MyContainer &operator=(const MyContainer& rhs) {

        // �������Ҹ�ֵ
        if (this == &rhs)
            return *this;

        delete[] data;

        sz = rhs.sz;
        data = new Type[sz];
        // ���������arr�е����ݵ�data
        for (int i = 0; i < sz; ++i) {
            data[i] = arr[i];
        }
    }

    // �����������ͷ���Դ
    ~MyContainer() override {
        delete[] data;
    }

    // �ض���sort����������testSort��������
    void sort() override {

        // ��������
        for (int i = 1; i < sz; ++i) {

            Type elem = data[i];

            int j;
            for (j = i; j > 0 && data[j - 1] > elem; --j)
                data[j] = data[j - 1];

            data[j] = elem;
        }
    }

    // �ض���size����������testSort��������
    size_t size() override {
        return sz;
    }
private:
    Type* data;
    size_t sz;
};

namespace helper {

    // ���ɾ���n��Ԫ�ص�������飬ÿ��Ԫ�صķ�Χ��[rangeL, rangeR]
    int* generateRandomIntArray(const int sz, const int rangeL, const int rangeR) {

        // ������������棨��̬���α�֤��ʱ�����ظ����ò���������ͬ�����У�
        static std::default_random_engine engine(time(nullptr));
        // ����������ֲ�Ϊ[rangeL, rangeR]
        std::uniform_int_distribution<int> distribution(rangeL, rangeR);

        int* arr = new int[sz];
        for (int i = 0; i < sz; ++i)
            arr[i] = distribution(engine);
        return arr;
    }
}

int main() {

    const int n = 50000;
    int* arr = helper::generateRandomIntArray(n, 0, n);

    // ����ָ��ָ����������󣨶�̬��
    Container* container = new MyContainer<int>(arr, n);
    // testSortΪTemplate Method
    container->testSort();

    // �ͷ���Դ
    delete arr;
    delete container;

    return 0;
}