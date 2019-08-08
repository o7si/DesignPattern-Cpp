#include <iostream>
#include <vector>
#include <string>

/**
 * Strategy
 * 定义一系列的算法,把每一个算法封装起来, 并且使它们可相互替换。
 * 使得算法可独立于使用它的客户而变化。
 */

/**
 * 示例涉及的英语词汇：
 * 平时成绩：Regular Grade
 * 期中考试成绩：Midterm Grade
 * 期末考试成绩：Final Exam Grade
 * 总成绩：Total Mark
 * 绩点：Grade Point
 * 平均绩点：Grade Point Average
 */

// 学科策略
class SubjectStrategy {
public:
    // 计算总成绩
    virtual double calcTotalMark() = 0;

    // 获取该科目学分
    virtual double getCredit() const = 0;

    // 为多态基类声明虚析构函数，保证基类指针能够正确释放资源
    // 虽然该示例程序中该类的派生类并未涉及到资源管理，但不建议省略该函数
    virtual ~SubjectStrategy() = default;
};

// 数学科目：计算总成绩只需要期末考试成绩
class Math : public SubjectStrategy {
public:
    explicit Math(double feg)
            : finalExamGrade(feg) {
    }

    // 计算公式：总成绩 = 期末考试成绩
    double calcTotalMark() override {
        return finalExamGrade * 1.0;
    }

    // 获取该科目学分
    double getCredit() const override {
        return credit;
    }

private:
    // 期末考试成绩
    double finalExamGrade;
    // 所占学分，静态修饰保证多个对象只能有一份该数据
    static const double credit;
};

// 初始化：数学科目所占学分为4.0分
const double Math::credit = 4.0;

// 物理科目：计算总成绩需要平时成绩和期末考试成绩
class Physics : public SubjectStrategy {
public:
    explicit Physics(double rg, double feg)
            : regularGrade(rg), finalExamGrade(feg) {
    }

    // 计算公式：总成绩 = 平时成绩 * 30% + 期末考试成绩 * 70%
    double calcTotalMark() override {
        return regularGrade * 0.3 + finalExamGrade * 0.7;
    }

    // 获取该科目学分
    double getCredit() const override {
        return credit;
    }

private:
    // 平时成绩
    double regularGrade;
    // 期末考试成绩
    double finalExamGrade;
    // 所占学分，静态修饰保证多个对象只能有一份该数据
    static const double credit;
};

// 初始化：物理科目所占学分为5.0分
const double Physics::credit = 5.0;

// 化学科目：计算总成绩需要平时成绩、期中考试成绩以及期末考试成绩
class Chemistry : public SubjectStrategy {
public:
    explicit Chemistry(double rg, double mg, double feg)
            : regularGrade(rg), midtermGrade(mg), finalExamGrade(feg) {
    }

    // 计算公式：总成绩 = 平时成绩 * 30% + 期中考试成绩 * 20% + 期末考试成绩 * 50%
    double calcTotalMark() override {
        return regularGrade * 0.3 + midtermGrade * 0.2 + finalExamGrade * 0.5;
    }

    // 获取该科目学分
    double getCredit() const override {
        return credit;
    }

private:
    // 平时成绩
    double regularGrade;
    // 期中考试成绩
    double midtermGrade;
    // 期末考试成绩
    double finalExamGrade;
    // 所占学分，静态修饰保证多个对象只能有一份该数据
    static const double credit;
};

// 初始化：化学科目所占学分为6.0分
const double Chemistry::credit = 6.0;

// GPA：标准4.0平均绩点算法
namespace GPA4_0 {

    // 分数段：100-90   绩点：4.0  等级：A
    const double A = 4.0;
    // 分数段： 89-80   绩点：3.0  等级：B
    const double B = 3.0;
    // 分数段： 79-70   绩点：2.0  等级：C
    const double C = 2.0;
    // 分数段： 69-60   绩点：1.0  等级：D
    const double D = 1.0;
    // 分数段： 59-0    绩点：0.0  等级：E
    const double E = 0.0;

    // 获取分数对应绩点
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
    // 定义类型别名，方便后续使用
    using Subject = SubjectStrategy;
public:

    explicit Student(const std::string &name)
            : name(name) {
    }

    // 释放vector中指针所指资源
    ~Student() {
        for (auto &subject : subjects) {
            delete subject;
        }
    }

    // 获取学生姓名
    std::string getName() const {
        return name;
    }

    // 添加新科目到学生课程列表中
    void addSubject(Subject *subject) {
        subjects.push_back(subject);
    }

    // 计算学生平均绩点（GPA）
    double caluGradePointAverage() {

        // 绩点和
        double gp = 0.0;
        // 学分和
        double c = 0.0;

        // 平均绩点计算公式
        // （科目学分1 * 科目绩点1 + 科目学分2 * 科目绩点2 + ... + 科目学分n * 科目绩点n）/（科目学分1 + 科目学分2 + ... + 科目学分n）
        for (const auto &subject : subjects) {

            // 获取科目学分
            double credit = subject->getCredit();
            // 获取科目成绩
            double totalMark = subject->calcTotalMark();

            gp += credit * GPA4_0::getGradePoint(totalMark);
            c += credit;
        }

        // 返回平均绩点
        return gp / c;
    }

private:
    // 学生姓名
    std::string name;
    // 学生所选课程列表
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