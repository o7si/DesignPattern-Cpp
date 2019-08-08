#include <iostream>

using namespace std;

/**
 * 构建器模式
 * 将一个复杂对象的构建与其表示相分离，使得同样的构建过程可以创建不同的表示。
 */

// 房子：拥有地板、墙壁、窗户、门、屋顶
class House {
public:
    // 设置地板样式
    void setFloor(const string &floorPart) {
        this->floor = floorPart;
    }

    // 设置墙壁样式
    void setWall(const string &wallPart) {
        this->wall = wallPart;
    }

    // 设置窗户样式
    void setWindow(const string &windowPart) {
        this->window = windowPart;
    }

    // 设置门样式
    void setDoor(const string &doorPart) {
        this->door = doorPart;
    }

    // 设置屋顶样式
    void setRoof(const string &roofPart) {
        this->roof = roofPart;
    }

    // 展示房子的各个成分
    void show() {

        cout << "FloorPart  : " << floor << endl;
        cout << "WallPart   : " << wall << endl;
        cout << "WindowPart : " << window << endl;
        cout << "DoorPart   : " << door << endl;
        cout << "RoofPart   : " << roof << endl;
    }

private:
    // 地板
    string floor;
    // 墙壁
    string wall;
    // 窗户
    string window;
    // 门
    string door;
    // 屋顶
    string roof;
};

// 负责定义建造房子所需的各个过程
class HouseBuilder {
public:
    // 建造地板
    virtual void buildFloorPart() = 0;

    // 建造墙壁
    virtual void buildWallPart() = 0;

    // 建造窗户
    virtual void buildWindowPart() = 0;

    // 建造门
    virtual void buildDoorPart() = 0;

    // 建造屋顶
    virtual void buildRoofPart() = 0;

    // 获取建造完毕的房子
    virtual shared_ptr<House> getHouse() = 0;

    // 为多态基类声明虚析构函数
    virtual ~HouseBuilder() = default;
};

// 构建木制房子
class WoodHouseBuilder : public HouseBuilder {
public:
    // 设置木制房子的地板成分
    void buildFloorPart() override {
        house->setFloor("Wood Floor");
    }

    // 设置木制房子的墙壁成分
    void buildWallPart() override {
        house->setWall("Wood Wall");
    }

    // 设置木制房子的窗户成分
    void buildWindowPart() override {
        house->setWindow("Wood Window");
    }

    // 设置木制房子的门成分
    void buildDoorPart() override {
        house->setDoor("Wood Door");
    }

    // 设置木制窗口的屋顶成分
    void buildRoofPart() override {
        house->setRoof("Wood Roof");
    }

    shared_ptr<House> getHouse() override {
        return house;
    }

private:
    shared_ptr<House> house = make_shared<House>(House());
};

// 构建石制房子
class StoneHouseBuilder : public HouseBuilder {
public:
    // 设置石制房子的地板成分
    void buildFloorPart() override {
        house->setFloor("Stone Floor");
    }

    // 设置石制房子的墙壁成分
    void buildWallPart() override {
        house->setWall("Stone Wall");
    }

    // 设置石制房子的窗户成分
    void buildWindowPart() override {
        house->setWindow("Stone Window");
    }

    // 设置石制房子的门成分
    void buildDoorPart() override {
        house->setDoor("Stone Door");
    }

    // 设置石制窗口的屋顶成分
    void buildRoofPart() override {
        house->setRoof("Stone Roof");
    }

    shared_ptr<House> getHouse() override {
        return house;
    }

private:
    shared_ptr<House> house = make_shared<House>(House());
};

// 负责管理房子的构建过程
class HouseDirector {
public:
    explicit HouseDirector(shared_ptr<HouseBuilder> builder)
            : houseBuilder(move(builder)) {
    }

    // 进行构建
    shared_ptr<House> build() {

        // 建造房子的地板
        houseBuilder->buildFloorPart();
        // 建造房子的墙壁
        houseBuilder->buildWallPart();
        // 建造房子的窗户
        houseBuilder->buildWindowPart();
        // 建造房子的门
        houseBuilder->buildDoorPart();
        // 建造房子的屋顶
        houseBuilder->buildRoofPart();

        // 返回建好的房子
        return houseBuilder->getHouse();
    }

private:
    shared_ptr<HouseBuilder> houseBuilder;
};


int main() {

    // 建造一个木制房子
    shared_ptr<House> woodHouse = HouseDirector(make_shared<WoodHouseBuilder>(WoodHouseBuilder())).build();
    cout << "WoodHouse" << endl;
    woodHouse->show();
    cout << endl;

    // 建造一个石制房子
    shared_ptr<House> stoneHouse = HouseDirector(make_shared<StoneHouseBuilder>(StoneHouseBuilder())).build();
    cout << "StoneHouse" << endl;
    stoneHouse->show();
    cout << endl;

    return 0;
}