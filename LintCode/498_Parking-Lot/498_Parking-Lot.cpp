// enum type for Vehicle
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