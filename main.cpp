
//We start with the lab 24 solution.
//Lab 24 provided basic functionality to the list of Goat objects : add, delete.
//Now we know quite a bit more about STL algorithms and how to implement them on associative containers such as the std::list
//Expand the main menu of this program by adding 8 more options that feature different STL algorithms.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std; 

const int SZ_NAMES = 200, SZ_COLORS = 25;
const int FULL_MENU = 12, EXTRA_OPTIONS = 5, MAX_AGE_LIMIT = 100;   

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

//NEW PROTOTYPES HERE
int extended_menu(); // Displays the extended operations menu and captures the user's choice.
void reverse_goats_order(list<Goat>& trip); // Reverses the order of goats in the list.
void remove_goats_older_than(list<Goat>& trip); // Removes all goats older than a specified age.
void shuffle_goats_order(list<Goat>& trip); // Shuffles the order of goats randomly within the list.
void check_if_sorted_by_age(const list<Goat>& trip); // Checks if the list of goats is sorted by age in ascending order.
void transform_names_to_uppercase(list<Goat>& trip); // Converts all goats' names in the list to uppercase.
void find_goats_by_color(const list<Goat>& trip); // Finds and displays all goats of a specified color in the list.
void calculate_average_age(const list<Goat>& trip); // Calculates and displays the average age of goats in the list.
void remove_duplicate_goats_by_name(list<Goat>& trip); // Removes goats with duplicate names, keeping only the first occurrence.

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 4) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "[5] Extended Operations " << endl;
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 5) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

int extended_menu() {
    cout << "*** EXTENDED OPERATIONS ***\n";
    cout << "[1] Reverse goats order\n";
    cout << "[2] Remove goats older than a certain age\n";
    cout << "[3] Shuffle goats order\n";
    cout << "[4] Check if trip is sorted by age\n";
    cout << "[5] Transform goats' names to uppercase\n";
    cout << "[6] Find all goats of a certain color\n";
    cout << "[7] Calculate average age of goats\n";
    cout << "[8] Remove duplicate goats by name\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 8) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}
void reverse_goats_order(list<Goat>& trip) {
    trip.reverse(); //reverses order of elements
    cout << "Goats order has been reversed!" << endl;
}
void remove_goats_older_than(list<Goat>& trip) {
    //for this function, we remove al goats older than a userChoice specified age
    int ageLimit;
    cout << "Enter goat age limit: " << endl;
    cin >> ageLimit;

    //input validation
    while (ageLimit < 0 || ageLimit > MAX_AGE_LIMIT) {
        cout << "Invalid age, must be between 0 - " << MAX_AGE_LIMIT << endl;
        cin >> ageLimit;
    }
    //remove here
    size_t remove = trip.remove([ageLimit](const Goat& g) {
        return g.get_age() > age_limit;
        });
    cout << removed << " goat(s) removed from the trip " << endl;
}
void shuffle_goats_order(list<Goat>& trip) {
    //randomly shuffles the order of the goats

    //convert list to vector first in order to shuffle, then clear original list and repopulate 
    //and repopulate with shuffled goats

    vector<Goat> tempVec(trip.begin(), trip.end());
    random_shuffle(tempVec.begin(), tempVec.end());

    //clear here
    trip.clear();
    trip.assign(tempVec.begin(), tempVec.end());
    cout << "goats have been shuffled " << endl;
}
void check_if_sorted_by_age(list<Goat>& trip) {

}
void transform_names_to_uppercase(list<Goat>& trip) {

}
void find_goats_by_color(list<Goat>& trip) {

}
void calculate_average_age(const list<Goat>& trip) {

}
void remove_duplicate_goats_by_name(list<Goat>& trip) {

}