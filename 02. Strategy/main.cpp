#include <iostream>
#include <vector>
#include <string>

/**
 * Strategy
 * ����һϵ�е��㷨,��ÿһ���㷨��װ����, ����ʹ���ǿ��໥�滻��
 * ʹ���㷨�ɶ�����ʹ�����Ŀͻ����仯��
 */

/**
 * ʾ���漰��Ӣ��ʻ㣺
 * ƽʱ�ɼ���Regular Grade
 * ���п��Գɼ���Midterm Grade
 * ��ĩ���Գɼ���Final Exam Grade
 * �ܳɼ���Total Mark
 * ���㣺Grade Point
 * ƽ�����㣺Grade Point Average
 */

// ѧ�Ʋ���
class SubjectStrategy {
public:
    // �����ܳɼ�
    virtual double calcTotalMark() = 0;

    // ��ȡ�ÿ�Ŀѧ��
    virtual double getCredit() const = 0;

    // Ϊ��̬����������������������֤����ָ���ܹ���ȷ�ͷ���Դ
    // ��Ȼ��ʾ�������и���������ಢδ�漰����Դ������������ʡ�Ըú���
    virtual ~SubjectStrategy() = default;
};

// ��ѧ��Ŀ�������ܳɼ�ֻ��Ҫ��ĩ���Գɼ�
class Math : public SubjectStrategy {
public:
    explicit Math(double feg)
            : finalExamGrade(feg) {
    }

    // ���㹫ʽ���ܳɼ� = ��ĩ���Գɼ�
    double calcTotalMark() override {
        return finalExamGrade * 1.0;
    }

    // ��ȡ�ÿ�Ŀѧ��
    double getCredit() const override {
        return credit;
    }

private:
    // ��ĩ���Գɼ�
    double finalExamGrade;
    // ��ռѧ�֣���̬���α�֤�������ֻ����һ�ݸ�����
    static const double credit;
};

// ��ʼ������ѧ��Ŀ��ռѧ��Ϊ4.0��
const double Math::credit = 4.0;

// �����Ŀ�������ܳɼ���Ҫƽʱ�ɼ�����ĩ���Գɼ�
class Physics : public SubjectStrategy {
public:
    explicit Physics(double rg, double feg)
            : regularGrade(rg), finalExamGrade(feg) {
    }

    // ���㹫ʽ���ܳɼ� = ƽʱ�ɼ� * 30% + ��ĩ���Գɼ� * 70%
    double calcTotalMark() override {
        return regularGrade * 0.3 + finalExamGrade * 0.7;
    }

    // ��ȡ�ÿ�Ŀѧ��
    double getCredit() const override {
        return credit;
    }

private:
    // ƽʱ�ɼ�
    double regularGrade;
    // ��ĩ���Գɼ�
    double finalExamGrade;
    // ��ռѧ�֣���̬���α�֤�������ֻ����һ�ݸ�����
    static const double credit;
};

// ��ʼ���������Ŀ��ռѧ��Ϊ5.0��
const double Physics::credit = 5.0;

// ��ѧ��Ŀ�������ܳɼ���Ҫƽʱ�ɼ������п��Գɼ��Լ���ĩ���Գɼ�
class Chemistry : public SubjectStrategy {
public:
    explicit Chemistry(double rg, double mg, double feg)
            : regularGrade(rg), midtermGrade(mg), finalExamGrade(feg) {
    }

    // ���㹫ʽ���ܳɼ� = ƽʱ�ɼ� * 30% + ���п��Գɼ� * 20% + ��ĩ���Գɼ� * 50%
    double calcTotalMark() override {
        return regularGrade * 0.3 + midtermGrade * 0.2 + finalExamGrade * 0.5;
    }

    // ��ȡ�ÿ�Ŀѧ��
    double getCredit() const override {
        return credit;
    }

private:
    // ƽʱ�ɼ�
    double regularGrade;
    // ���п��Գɼ�
    double midtermGrade;
    // ��ĩ���Գɼ�
    double finalExamGrade;
    // ��ռѧ�֣���̬���α�֤�������ֻ����һ�ݸ�����
    static const double credit;
};

// ��ʼ������ѧ��Ŀ��ռѧ��Ϊ6.0��
const double Chemistry::credit = 6.0;

// GPA����׼4.0ƽ�������㷨
namespace GPA4_0 {

    // �����Σ�100-90   ���㣺4.0  �ȼ���A
    const double A = 4.0;
    // �����Σ� 89-80   ���㣺3.0  �ȼ���B
    const double B = 3.0;
    // �����Σ� 79-70   ���㣺2.0  �ȼ���C
    const double C = 2.0;
    // �����Σ� 69-60   ���㣺1.0  �ȼ���D
    const double D = 1.0;
    // �����Σ� 59-0    ���㣺0.0  �ȼ���E
    const double E = 0.0;

    // ��ȡ������Ӧ����
    double getGradePoint(double grade) {

        if (grade <= 100 && grade >= 90)
            return A;
        if (grade <= 89 && grade >= 80)
            return B;
        if (grade <= 79 && grade >= 70)
            return C;
        if (grade <= 69 && grade >= 60)
            return D;
        return E;
    }
}

class Student {
private:
    // �������ͱ������������ʹ��
    using Subject = SubjectStrategy;
public:

    explicit Student(const std::string &name)
            : name(name) {
    }

    // �ͷ�vector��ָ����ָ��Դ
    ~Student() {
        for (auto &subject : subjects) {
            delete subject;
        }
    }

    // ��ȡѧ������
    std::string getName() const {
        return name;
    }

    // ����¿�Ŀ��ѧ���γ��б���
    void addSubject(Subject *subject) {
        subjects.push_back(subject);
    }

    // ����ѧ��ƽ�����㣨GPA��
    double caluGradePointAverage() {

        // �����
        double gp = 0.0;
        // ѧ�ֺ�
        double c = 0.0;

        // ƽ��������㹫ʽ
        // ����Ŀѧ��1 * ��Ŀ����1 + ��Ŀѧ��2 * ��Ŀ����2 + ... + ��Ŀѧ��n * ��Ŀ����n��/����Ŀѧ��1 + ��Ŀѧ��2 + ... + ��Ŀѧ��n��
        for (const auto &subject : subjects) {

            // ��ȡ��Ŀѧ��
            double credit = subject->getCredit();
            // ��ȡ��Ŀ�ɼ�
            double totalMark = subject->calcTotalMark();

            gp += credit * GPA4_0::getGradePoint(totalMark);
            c += credit;
        }

        // ����ƽ������
        return gp / c;
    }

private:
    // ѧ������
    std::string name;
    // ѧ����ѡ�γ��б�
    std::vector<Subject *> subjects;
};

int main() {

    Student *student = new Student("o7si");

    student->addSubject(new Math(80));
    student->addSubject(new Physics(70, 80));
    student->addSubject(new Chemistry(80, 70, 90));

    std::cout << student->getName() << "'s Grade Point Average(GPA) = "
            << student->caluGradePointAverage() << std::endl;

    delete student;
    return 0;
}