498. Parking Lot
中文English
Design a parking lot.

see CC150 OO Design for details.

n levels, each level has m rows of spots and each row has k spots.So each level has m x k spots.
The parking lot can park motorcycles, cars and buses
The parking lot has motorcycle spots, compact spots, and large spots
Each row, motorcycle spots id is in range [0,k/4)(0 is included, k/4 is not included), compact spots id is in range [k/4,k/4*3)(k/4*3 is not included) and large spots id is in range [k/4*3,k)(k is not included).
A motorcycle can park in any spot
A car park in single compact spot or large spot
A bus can park in five large spots that are consecutive and within same row. it can not park in small spots
Example
Example 1

Input:
level=1
num_rows=1
spots_per_row=11
parkVehicle("Motorcycle_1")
parkVehicle("Car_1")
parkVehicle("Car_2")
parkVehicle("Car_3")
parkVehicle("Car_4")
parkVehicle("Car_5")
parkVehicle("Bus_1")
unParkVehicle("Car_5")
parkVehicle("Bus_1")

Output:
true
true
true
true
true
true
false
true

Explanation: When there is a "Car_5", there is no "Bus_1".
Example 2

Input:
level=1
num_rows=1
spots_per_row=14
parkVehicle("Motorcycle_1")
parkVehicle("Motorcycle_2")
parkVehicle("Motorcycle_3")
parkVehicle("Car_1")
parkVehicle("Car_2")
parkVehicle("Car_3")
parkVehicle("Motorcycle_4")
parkVehicle("Car_4")
parkVehicle("Car_5")
parkVehicle("Car_6")
parkVehicle("Car_7")
parkVehicle("Bus_1")
unParkVehicle("Car_1")
unParkVehicle("Motorcycle_4")
unParkVehicle("Car_3")
unParkVehicle("Car_6")
parkVehicle("Bus_1")
unParkVehicle("Car_7")
parkVehicle("Bus_1")

Output:
true
true
true
true
true
true
true
true
true
true
true
false
false
true

在线评测地址: http://www.lintcode.com/problem/parking-lot/

设计一个停车场

一共有n层，每层m列，每列k个位置
停车场可以停摩托车，公交车，汽车
停车位分别有摩托车位，汽车位，大型停车位
每一列，摩托车位编号范围为[0,k/4)(注：包括0，不包括k/4),汽车停车位编号范围为[k/4,k/4*3)(注：不包括k/4*3),大型停车位编号范围为[k/4*3,k)(注：不包括k)
一辆摩托车可以停在任何停车位
一辆汽车可以停在一个汽车位或者大型停车位
一辆公交车可以停在一列里的连续5个大型停车位。


enum class VehicleSize {
    Motorcycle,
    Compact,
    Large
};

class Vehicle {
public:
    virtual VehicleSize size() {}
    virtual int spot_num() {}
};

class Bus: public Vehicle {
public:
    VehicleSize size() {
        return VehicleSize::Large;
    }
    int spot_num() {
        return 5;
    }
};

class Car: public Vehicle {
public:
    VehicleSize size() {
        return VehicleSize::Compact;
    }
    int spot_num() {
        return 1;
    }
};

class Motorcycle: public Vehicle {
public:
    VehicleSize size() {
        return VehicleSize::Motorcycle;
    }
    int spot_num() {
        return 1;
    }
};

class Level {
public:
    Level(int num_rows, int spots_per_row) {
        for (int i = 0 ; i < num_rows; ++i) {
            spots.push_back(vector<Vehicle*>(spots_per_row, NULL));
        }
        this->num_rows = num_rows;
        this->spots_per_row = spots_per_row;
    }
    
    bool park_vehicle(Vehicle* vehicle) {
        for (int row = 0; row < num_rows; ++row) {
            int start = 0;
            if (vehicle->size() == VehicleSize::Compact) {
                start = spots_per_row / 4;
            } else if (vehicle->size() == VehicleSize::Large) {
                start = spots_per_row / 4 * 3;
            }
            for (int i = start; i < spots_per_row - vehicle->spot_num() + 1; ++i) {
                bool can_park = true;
                for (int j = i; j < i +  vehicle->spot_num(); ++j) {
                    if (spots[row][j] != NULL) {
                        can_park = false;
                        break;
                    }
                }
                if (can_park) {
                    for (int j = i; j < i + vehicle->spot_num(); ++j) {
                        spots[row][j] = vehicle;
                    } 
                    return true;
                }
            }
        }
        return false;
    }
    
    void unpark_vehicle(Vehicle *vehicle) {
        for (int row = 0; row < num_rows; ++row) {
            for (int i = 0; i < spots_per_row; ++i)
                if (spots[row][i] == vehicle) {
                    spots[row][i] = NULL;
                }
        }
    }
    
private:
    vector<vector<Vehicle*>> spots;
    int num_rows;
    int spots_per_row;
    
};

class ParkingLot {
public:
    // @param n number of leves
    // @param num_rows  each level has num_rows rows of spots
    // @param spots_per_row each row has spots_per_row spots
    ParkingLot(int n, int num_rows, int spots_per_row) {
        for (int i = 0; i < n; ++i) {
            Level *level = new Level(num_rows, spots_per_row);
            levels.push_back(level);
        }
    }

    // Park the vehicle in a spot (or multiple spots)
    // Return false if failed
    bool parkVehicle(Vehicle* vehicle) {
        for (int i = 0; i < levels.size(); ++i) {
            if (levels[i]->park_vehicle(vehicle)) {
                vehicle_to_level[vehicle] = levels[i];
                return true;
            }
        }
        return false;
    }

    // unPark the vehicle
    void unParkVehicle(Vehicle* vehicle) {
        Level *level = vehicle_to_level[vehicle];
        if (level) {
            level->unpark_vehicle(vehicle);
        }
    }
    
private:
    vector<Level*> levels;
    map<Vehicle*, Level*> vehicle_to_level;
};