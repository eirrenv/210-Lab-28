#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <random>
#include <ctime>
#include "Goat.h"
#include <string> // for getline
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

void check_old_goat(list<Goat> trip); // check if there are any elderly goats over 15
void find_goat(list<Goat> trip); // find specific goat in list
void youngest_goat(list<Goat> trip); // find youngest goat in list
void oldest_goat(list<Goat> trip); // find oldest goat in list
void shuffle_goats(list<Goat>& trip); // shuffle the list

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
    while (sel != 12) {
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
            case 4:
                // first milestone, clear list
                cout << "Clearing list.\n";
                trip.clear();
                break;
            case 5:
                // second milestone, check for any elderly goats
                cout << "Checking for elderly goats.\n";
                check_old_goat(trip);
                break;
            case 6:
                // milestone 3, find specific goat in list
                cout << "Finding goat.\n";
                find_goat(trip);
                break;
            case 7:
                // milestone 4, find youngest goat in list
                cout << "Finding youngest goat.\n";
                youngest_goat(trip);
                break;
            case 8:
                // milestone 5, find oldest goat in list
                cout << "Finding oldest goat.\n";
                oldest_goat(trip);
                break;
            case 9:
                // milestone 6, shuffle list of goats
                cout << "Shuffling goats.\n";
                shuffle_goats(trip);
                break;
            case 10:
                // milestone 7
                break;
            case 11:
                // milestone 8
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
    cout << "[4] Clear goats from list\n";
    cout << "[5] Check for elderly goats\n";
    cout << "[6] Find specific goat in list\n";
    cout << "[7] Find youngest goat in list\n";
    cout << "[8] Find oldest goat in list\n";
    cout << "[9] Shuffle goats\n";
    cout << "[10] Milestone 7\n";
    cout << "[11] Milestone 8\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
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
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void check_old_goat(list<Goat> trp) {
    bool isOlder = any_of(trp.begin(), trp.end(), []( const Goat& g ) { return g.get_age() > 15; } );
    if (isOlder) {
        cout << "There are elderly goats older than 15." << endl;
    }
    else {
        cout << "There are no elderly goats." << endl;
    }
}

void find_goat(list<Goat> trp) {
    string searchGoat;
    cout << "Please enter name of goat you want to search for: ";
    cin.ignore();
    getline(cin, searchGoat);

    auto it = find_if(trp.begin(), trp.end(), [searchGoat](const Goat& g) {
        return g.get_name() == searchGoat;
    });

    if (it != trp.end()) {
        cout << searchGoat << " is in the list." << endl;
    }
    else {
        cout << searchGoat << " is not in the list." << endl;
    }

}

void youngest_goat(list<Goat> trp) {
    auto it = min_element(trp.begin(), trp.end(), [](const Goat& first, const Goat& second) { return first.get_age() < second.get_age(); } );

    cout << "The youngest goat in the list is " << it->get_name() << " at "
         << it->get_age() << " year(s) old." 
         << endl;
}

void oldest_goat(list<Goat> trp) {
    auto it = max_element(trp.begin(), trp.end(), [](const Goat& first, const Goat& second) { return first.get_age() < second.get_age(); } );

    cout << "The oldest goat in the list is " << it->get_name() << " at "
         << it->get_age() << " year(s) old." 
         << endl;
}

void shuffle_goats(list<Goat>& trp) {
    vector<Goat> tmp(trp.begin(), trp.end());

    shuffle(tmp.begin(), tmp.end(), default_random_engine(time(0)));

    trp.assign(tmp.begin(), tmp.end());
}