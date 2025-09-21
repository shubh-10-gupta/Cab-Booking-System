#include <bits/stdc++.h>
using namespace std;

// ------------------------- CAB CLASS -------------------------
class Cab {
public:
    int cabId;
    string type;       // Mini, Sedan, SUV
    float ratePerKm;
    bool available;

    Cab(int id, string t, float rate) {
        cabId = id;
        type = t;
        ratePerKm = rate;
        available = true;
    }

    void displayCab() {
        cout << "Cab ID: " << cabId
             << " | Type: " << type
             << " | Rate/km: Rs." << ratePerKm
             << " | Status: " << (available ? "Available" : "Booked") << endl;
    }
};

// ------------------------- USER CLASS -------------------------
class User {
public:
    int userId;
    string name;
    string phone;

    User(int id, string n, string p) {
        userId = id;
        name = n;
        phone = p;
    }
};

// ------------------------- BOOKING CLASS -------------------------
class Booking {
public:
    int bookingId;
    int userId;
    int cabId;
    string pickup, drop;
    float distance;
    float fare;

    Booking(int bId, int uId, int cId, string p, string d, float dist, float rate) {
        bookingId = bId;
        userId = uId;
        cabId = cId;
        pickup = p;
        drop = d;
        distance = dist;
        fare = dist * rate;
    }

    void displayBooking() {
        cout << "\nBooking ID: " << bookingId
             << "\nUser ID: " << userId
             << "\nCab ID: " << cabId
             << "\nPickup: " << pickup
             << "\nDrop: " << drop
             << "\nDistance: " << distance << " km"
             << "\nFare: Rs." << fare << endl;
    }
};

// ------------------------- SYSTEM CLASS -------------------------
class CabBookingSystem {
private:
    vector<Cab> cabs;
    vector<User> users;
    vector<Booking> bookings;
    int nextBookingId = 1;

public:
    CabBookingSystem() {
        // Preload some cabs
        cabs.push_back(Cab(1, "Mini", 10));
        cabs.push_back(Cab(2, "Sedan", 15));
        cabs.push_back(Cab(3, "SUV", 20));
        cabs.push_back(Cab(4, "Luxury", 30));
    }

    void addUser() {
        int id = users.size() + 1;
        string name, phone;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Phone: ";
        cin >> phone;
        users.push_back(User(id, name, phone));
        cout << "User Registered. Your ID is " << id << endl;
    }

    void viewCabs() {
        cout << "\nAvailable Cabs:\n";
        for (auto &cab : cabs) cab.displayCab();
    }

    void bookCab() {
        int userId;
        cout << "Enter your User ID: ";
        cin >> userId;

        if (userId < 1 || userId > users.size()) {
            cout << "Invalid User ID.\n";
            return;
        }

        viewCabs();
        int cabId;
        cout << "Enter Cab ID to book: ";
        cin >> cabId;

        bool found = false;
        for (auto &cab : cabs) {
            if (cab.cabId == cabId && cab.available) {
                string pickup, drop;
                float dist;
                cout << "Enter Pickup Location: ";
                cin >> pickup;
                cout << "Enter Drop Location: ";
                cin >> drop;
                cout << "Enter Distance (km): ";
                cin >> dist;

                Booking b(nextBookingId++, userId, cabId, pickup, drop, dist, cab.ratePerKm);
                bookings.push_back(b);
                cab.available = false;

                cout << "\nBooking Successful!\n";
                b.displayBooking();
                found = true;
                break;
            }
        }
        if (!found) cout << "Cab not available!\n";
    }

    void cancelBooking() {
        int bId;
        cout << "Enter Booking ID to cancel: ";
        cin >> bId;

        for (auto it = bookings.begin(); it != bookings.end(); ++it) {
            if (it->bookingId == bId) {
                for (auto &cab : cabs) {
                    if (cab.cabId == it->cabId) cab.available = true;
                }
                bookings.erase(it);
                cout << "Booking Cancelled.\n";
                return;
            }
        }
        cout << "Booking ID not found.\n";
    }

    void viewBookings() {
        cout << "\nAll Bookings:\n";
        for (auto &b : bookings) b.displayBooking();
    }
};

// ------------------------- MAIN PROGRAM -------------------------
int main() {
    CabBookingSystem system;
    int choice;

    do {
        cout << "\n===== CAB BOOKING SYSTEM =====";
        cout << "\n1. Register User";
        cout << "\n2. View Cabs";
        cout << "\n3. Book Cab";
        cout << "\n4. Cancel Booking";
        cout << "\n5. View All Bookings";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.addUser(); break;
            case 2: system.viewCabs(); break;
            case 3: system.bookCab(); break;
            case 4: system.cancelBooking(); break;
            case 5: system.viewBookings(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }
    } while (choice != 6);

    return 0;
}
