#include <iostream>

using namespace std;

/**
 * ������ģʽ
 * ��һ�����Ӷ���Ĺ��������ʾ����룬ʹ��ͬ���Ĺ������̿��Դ�����ͬ�ı�ʾ��
 */

// ���ӣ�ӵ�еذ塢ǽ�ڡ��������š��ݶ�
class House {
public:
    // ���õذ���ʽ
    void setFloor(const string &floorPart) {
        this->floor = floorPart;
    }

    // ����ǽ����ʽ
    void setWall(const string &wallPart) {
        this->wall = wallPart;
    }

    // ���ô�����ʽ
    void setWindow(const string &windowPart) {
        this->window = windowPart;
    }

    // ��������ʽ
    void setDoor(const string &doorPart) {
        this->door = doorPart;
    }

    // �����ݶ���ʽ
    void setRoof(const string &roofPart) {
        this->roof = roofPart;
    }

    // չʾ���ӵĸ����ɷ�
    void show() {

        cout << "FloorPart  : " << floor << endl;
        cout << "WallPart   : " << wall << endl;
        cout << "WindowPart : " << window << endl;
        cout << "DoorPart   : " << door << endl;
        cout << "RoofPart   : " << roof << endl;
    }

private:
    // �ذ�
    string floor;
    // ǽ��
    string wall;
    // ����
    string window;
    // ��
    string door;
    // �ݶ�
    string roof;
};

// �����彨�췿������ĸ�������
class HouseBuilder {
public:
    // ����ذ�
    virtual void buildFloorPart() = 0;

    // ����ǽ��
    virtual void buildWallPart() = 0;

    // ���촰��
    virtual void buildWindowPart() = 0;

    // ������
    virtual void buildDoorPart() = 0;

    // �����ݶ�
    virtual void buildRoofPart() = 0;

    // ��ȡ������ϵķ���
    virtual shared_ptr<House> getHouse() = 0;

    // Ϊ��̬������������������
    virtual ~HouseBuilder() = default;
};

// ����ľ�Ʒ���
class WoodHouseBuilder : public HouseBuilder {
public:
    // ����ľ�Ʒ��ӵĵذ�ɷ�
    void buildFloorPart() override {
        house->setFloor("Wood Floor");
    }

    // ����ľ�Ʒ��ӵ�ǽ�ڳɷ�
    void buildWallPart() override {
        house->setWall("Wood Wall");
    }

    // ����ľ�Ʒ��ӵĴ����ɷ�
    void buildWindowPart() override {
        house->setWindow("Wood Window");
    }

    // ����ľ�Ʒ��ӵ��ųɷ�
    void buildDoorPart() override {
        house->setDoor("Wood Door");
    }

    // ����ľ�ƴ��ڵ��ݶ��ɷ�
    void buildRoofPart() override {
        house->setRoof("Wood Roof");
    }

    shared_ptr<House> getHouse() override {
        return house;
    }

private:
    shared_ptr<House> house = make_shared<House>(House());
};

// ����ʯ�Ʒ���
class StoneHouseBuilder : public HouseBuilder {
public:
    // ����ʯ�Ʒ��ӵĵذ�ɷ�
    void buildFloorPart() override {
        house->setFloor("Stone Floor");
    }

    // ����ʯ�Ʒ��ӵ�ǽ�ڳɷ�
    void buildWallPart() override {
        house->setWall("Stone Wall");
    }

    // ����ʯ�Ʒ��ӵĴ����ɷ�
    void buildWindowPart() override {
        house->setWindow("Stone Window");
    }

    // ����ʯ�Ʒ��ӵ��ųɷ�
    void buildDoorPart() override {
        house->setDoor("Stone Door");
    }

    // ����ʯ�ƴ��ڵ��ݶ��ɷ�
    void buildRoofPart() override {
        house->setRoof("Stone Roof");
    }

    shared_ptr<House> getHouse() override {
        return house;
    }

private:
    shared_ptr<House> house = make_shared<House>(House());
};

// ��������ӵĹ�������
class HouseDirector {
public:
    explicit HouseDirector(shared_ptr<HouseBuilder> builder)
            : houseBuilder(move(builder)) {
    }

    // ���й���
    shared_ptr<House> build() {

        // ���췿�ӵĵذ�
        houseBuilder->buildFloorPart();
        // ���췿�ӵ�ǽ��
        houseBuilder->buildWallPart();
        // ���췿�ӵĴ���
        houseBuilder->buildWindowPart();
        // ���췿�ӵ���
        houseBuilder->buildDoorPart();
        // ���췿�ӵ��ݶ�
        houseBuilder->buildRoofPart();

        // ���ؽ��õķ���
        return houseBuilder->getHouse();
    }

private:
    shared_ptr<HouseBuilder> houseBuilder;
};


int main() {

    // ����һ��ľ�Ʒ���
    shared_ptr<House> woodHouse = HouseDirector(make_shared<WoodHouseBuilder>(WoodHouseBuilder())).build();
    cout << "WoodHouse" << endl;
    woodHouse->show();
    cout << endl;

    // ����һ��ʯ�Ʒ���
    shared_ptr<House> stoneHouse = HouseDirector(make_shared<StoneHouseBuilder>(StoneHouseBuilder())).build();
    cout << "StoneHouse" << endl;
    stoneHouse->show();
    cout << endl;

    return 0;
}