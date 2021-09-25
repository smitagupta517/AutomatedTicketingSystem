#include <bits/stdc++.h>

using namespace std;

/*
Implementation of an automated ticketing system

A parking lot can hold up to 'n'cars. Whenever a vehicle enters a parking lot, it is alloted the slot that is available and nearest to the entry. And,when the car leaves, the slot gets available for other cars to use.
*/
class ParkingLot {
    int capacity; // Capacity of the parking lot
    set < int > available_slots; // Stores the slots that are available for parking a car
    vector < string > registration_num; // Stores registration number of car at a allotted slot
    vector < int > age; // Stores age of the driver who has parked the car at allotted slot
    map < string, int > slot_num; // Maps registration number with slot number.
    vector < set < int >> age_group; // Stores slots given to a driver of particular age.

    public:

    /*
    Create a parking lot of a given capacity.
    @param n is the capacity of the parking lot
    */
    ParkingLot(int n) {
        if (n <= 0 || n > 1000) // Checks whether the capacity is feasible or not.
            throw invalid_argument("Please pass a Valid Parking Lot Size between 1 - 1000");

        capacity = n;
        registration_num.resize(capacity + 1);
        age.resize(capacity + 1);
        age_group.resize(200);
        for (int i = 1; i <= capacity; i++) {
            available_slots.insert(i);
        }
        cout << "Created parking of " << n << " slots" << endl;
    }

    /*
    Allotting nearest available parking slot to the vehicle.
    @param new_registration_num is the vehicle's registration number that has entered into parking lot.
    @param new_age is the age of the driver who wants to park his vehicle.
    */
    void Park(string new_registration_num, int new_age) {

        if (new_age <= 0 || new_age >= 200) { // Checks whether driver is eligible to drive or not.
            cout << new_age << " is not a valid Age. \nPlease pass a valid age between 1 - 200" << endl;
            return;
        }

        if (new_registration_num.size() != 13) { // Checks whether the registration number is valid or not.
            cout << "Invalid registration number" << endl;
            return;
        }

        if (slot_num.find(new_registration_num) != slot_num.end()) { // Checks whether the registration number is unique or not.
            cout << "Vehicle with this registeration number  is already parked" << endl;
            return;
        }

        if (available_slots.empty()) { // Tell whether slots are available for parking or not.
            cout << "Parking Lot is full" << endl;
            return;
        }

        int slot = *available_slots.begin();
        available_slots.erase(slot);
        age_group[new_age].insert(slot);
        age[slot] = new_age;
        registration_num[slot] = new_registration_num;
        slot_num[new_registration_num] = slot;

        cout << "Car with vehicle registration number \"" << new_registration_num << "\" has been parked at slot number " << slot << endl;
    }

    /*
    Vacant the parking slot whenever car from a slot leaves the parking lot.
    @param slot is slot which was occupied by the car
    */
    void Leave(int slot) {
        if (slot <= 0 || slot > capacity) { // Checks whether the entered slot is valid or not.
            cout << "Given slot number is invalid" << endl;
            return;
        }

        if (available_slots.find(slot) != available_slots.end()) { // Checks whether the slot is already empty or not.
            cout << "The slot is already empty" << endl;
            return;
        }
        string reg_number = registration_num[slot];
        int driver_age = age[slot];

        slot_num.erase(registration_num[slot]);
        registration_num[slot].clear();
        age_group[age[slot]].erase(slot);
        age[slot] = 0;
        available_slots.insert(slot);

        cout << "Slot number " << slot << " vacated, the car with vehicle registration number \"" << reg_number << "\" left the space, the driver of the car was of age " << driver_age << endl;
    }

    /*
    This function will tell us the slot numbers where the driver's of the given age has parked their cars.
    @param age is age of the driver
    */
    void Slot_numbers_for_driver_of_age(int age) {
        if (age <= 0 || age >= 200) { // Checks whether the driver's age is valid or not.
            cout << "Enter valid age." << endl;
            return;
        }
        int i = age_group[age].size();
        for (auto slot_num: age_group[age]) {
            cout << slot_num;
            if (i > 1) {
                cout << ",";
            }
            i--;
        }
        cout << endl;
    }

    /*
    This function will tell us the registration number of the vehicles whose driver's age is given.
    @param age is age of the driver
    */
    void Vehicle_registration_number_for_driver_of_age(int age) {
        if (age <= 0 || age >= 200) { // Checks whether the age of the driver is valid or not.
            cout << "Enter valid age." << endl;
            return;
        }
        int i = age_group[age].size();
        for (auto slot_num: age_group[age]) {
            cout << registration_num[slot_num];
            if (i > 1) {
                cout << ",";
            }
            i--;
        }
        cout << endl;
    }

    /*
    This function will give us the slot number which was allotted to the car of given registration number.
    @param registration_num is registration number of the car
    */
    void Slot_number_for_car_with_number(string registration_num) {
        if (slot_num.find(registration_num) == slot_num.end()) { // Checks whether a car with given registration number is parked in parking lot or not.
            cout << "The vehicle with registration number \"" << registration_num << "\" is not in the parking lot" << endl;
			return;
        }
        cout << slot_num[registration_num] << endl;
    }
};

signed main() {
    ios::sync_with_stdio(0), cout.tie(0), cin.tie(0);
    string input, func, reg_num, temp;
    int size_of_parking_lot, age, slot;

    fstream newfile;
    newfile.open("input.txt", ios:: in );

    // Read the input file
    if (newfile.is_open()) {
        getline(newfile, input);
        stringstream ss(input);
        ss >> input >> size_of_parking_lot;

        // Create the object of class ParkingLot
        ParkingLot obj = ParkingLot(size_of_parking_lot);

        while (getline(newfile, input)) {
            stringstream ss(input);
            ss >> func;
            if (func == "Park") { // If the first word is Park, then call the Park method of ParkingLot class.
                ss >> reg_num;
                ss >> temp;
                ss >> age;
                obj.Park(reg_num, age);
            } else if (func == "Slot_numbers_for_driver_of_age") { // If the first word is Slot_numbers_for_driver_of_age, then call the Slot_numbers_for_driver_of_age method of ParkingLot class.
                ss >> age;
                obj.Slot_numbers_for_driver_of_age(age);
            } else if (func == "Slot_number_for_car_with_number") { // If the first word is Slot_number_for_car_with_number, then call the Slot_number_for_car_with_number method of ParkingLot class.
                ss >> reg_num;
                obj.Slot_number_for_car_with_number(reg_num);
            } else if (func == "Vehicle_registration_number_for_driver_of_age") { // If the first word is Vehicle_registration_number_for_driver_of_age, then call the Vehicle_registration_number_for_driver_of_age method of ParkingLot class.
                ss >> age;
                obj.Vehicle_registration_number_for_driver_of_age(age);
            } else if (func == "Leave") { // If the first word is Leave, then call the Leave method of ParkingLot class.
                ss >> slot;
                obj.Leave(slot);
            } else { // If the input is not from the above methods, then user is trying to get invalid information.
                cout << "Can't get this information." << endl;
            }
        }
    }
    return 0;
}