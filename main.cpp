#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again =  true;

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

    list<Goat> trip;

    while (again) {
        int user = main_menu();
        switch (user){
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2: 
                delete_goat(trip);
                break;
            case 3: 
                display_trip(trip);
                cout << endl;
                break;
            case 4:
                cout << "Exiting program.\n";
                again = false;
                break;
            default:
                cout << "Error. Not a valid entry.\n";
                break;
        }
    }

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice > 4 or choice < 1){
        cout << "Please enter 1-4: ";
        cin >> choice;
    }
    return choice;
}

void add_goat(list<Goat> &trip, string names[], string colors[]) {
    string randname = names[rand() % SZ_NAMES];
    string randcolor = colors[rand() % SZ_COLORS];
    int randage = rand()% MAX_AGE;

    Goat newgoat(randname, randage, randcolor);
    trip.push_back(newgoat);

    cout << "Adding goat: " << randname << "(" << randage << ", " << randcolor << ")\n";
    display_trip(trip);
    cout << endl << endl;;
}

void display_trip(list<Goat> trip){
    if (trip.empty()) {
        cout << "Trip is empty.\n";
        return;
    }

    int i = 1;
    for (auto it = trip.begin(); it != trip.end(); it++) {
        cout << "[" << i++ << "] " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n";
    } 
}


int select_goat(list<Goat> trip){
    display_trip(trip);
    cout << endl;
    cout << "Select a goat (enter a #): ";
    int entry;
    cin >> entry;
    while (entry < 1 or entry > trip.size()) {
        cout << "Please enter a valid number: ";
        cin >> entry;
    }
    return entry;
}

void delete_goat(list<Goat> &trip){
    if (trip.empty()) {
        cout << "Trip is empty, no goats to delete.\n";
        return;
    }
    int i = select_goat(trip) - 1;
    auto it = trip.begin();
    advance(it, i);
    cout << "Deleting goat: " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n";
    trip.erase(it);
    display_trip(trip);
    cout << endl << endl;
}
