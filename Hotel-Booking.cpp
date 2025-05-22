
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>
#include <algorithm>
#include <regex>
#include <chrono>
#include <ctime>

using namespace std;

const int MAX_NAME_LEN = 30;
const int MAX_ID_LEN = 15;
const int ROOM_COUNT = 10;
const int PRICE_PER_DAY = 500;

struct Customer {
    string id;
    string name;
    string phone;
    int roomNumber;
    string checkIn;
    string checkOut;
    long long stayDays;
    long long totalBill;
    Customer* next;
};

Customer* head = nullptr;
bool rooms[ROOM_COUNT + 1] = { false };


tm parseDate(const string& dateString) {
    tm t = {};
    stringstream ss(dateString);
    char slash;
    ss >> t.tm_mday >> slash >> t.tm_mon >> slash >> t.tm_year;
    t.tm_mon -= 1;
    t.tm_year -= 1900;

    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1;
    return t;
}


tm getCurrentDate() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&currentTime);

    tm current = *localTime;

    current.tm_hour = 0;
    current.tm_min = 0;
    current.tm_sec = 0;
    current.tm_isdst = -1;
    return current;
}


bool isDatePast(const tm& input, const tm& current) {
    time_t input_time = mktime(const_cast<tm*>(&input));
    time_t current_time = mktime(const_cast<tm*>(&current));
    return difftime(input_time, current_time) < 0;
}


long long calculateStayDays(const string& checkInStr, const string& checkOutStr) {
    tm checkInTm = parseDate(checkInStr);
    tm checkOutTm = parseDate(checkOutStr);

    time_t checkInTime = mktime(&checkInTm);
    time_t checkOutTime = mktime(&checkOutTm);


    double seconds = difftime(checkOutTime, checkInTime);
    return static_cast<long long>(seconds / (60 * 60 * 24));
}


bool isIDUnique(const string& id) {
    Customer* temp = head;
    while (temp) {
        if (temp->id == id) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}


bool isPhoneUnique(const string& phone) {
    Customer* temp = head;
    while (temp) {
        if (temp->phone == phone) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}


bool isValidDate(const string& date) {
    if (!regex_match(date, regex("^\\d{2}/\\d{2}/\\d{4}$"))) {
        return false;
    }


    return true;
}

string inputID() {
    string id;
    regex idPattern("^[a-zA-Z0-9]{1,15}$");
    while (true) {
        cout << "Enter Customer ID (max 15 alphanumeric chars): ";
        getline(cin, id);
        if (regex_match(id, idPattern)) {
            if (isIDUnique(id)) {
                return id;
            } else {
                cout << "This ID already exists. Please enter a unique ID.\n";
            }
        } else {
            cout << "Invalid ID! Only alphanumeric characters allowed, max 15 chars.\n";
        }
    }
}


string inputName() {
    string name;
    regex namePattern("^[a-zA-Z ]{1,30}$");
    while (true) {
        cout << "Enter Name (max 30 chars, letters and spaces allowed): ";
        getline(cin, name);
        if (regex_match(name, namePattern)) return name;
        cout << "Invalid Name! Use letters and spaces only, max 30 chars.\n";
    }
}

string inputPhone() {
    string phone;
    regex phonePattern("^\\d{10,12}$");
    while (true) {
        cout << "Enter Phone Number (10 to 12 digits): ";
        getline(cin, phone);
        if (regex_match(phone, phonePattern)) {
            if (isPhoneUnique(phone)) {
                return phone;
            } else {
                cout << "This Phone Number already exists. Please enter a unique phone number.\n";
            }
        } else {
            cout << "Invalid Phone Number! Must be 10 to 12 digits.\n";
        }
    }
}

string inputDate(const string& msg, const string& referenceDate = "") {
    string date;
    tm currentDateTm = getCurrentDate();
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &currentDateTm);
    string currentDateStr(buffer);

while (true) {
        cout << msg;
        if (referenceDate.empty()) {
            cout << " (Current date: " << currentDateStr << "): ";
        } else {
            cout << " (Must be after " << referenceDate << "): ";
        }

        getline(cin, date);
        if (!isValidDate(date)) {
            cout << "Invalid date format! Use DD/MM/YYYY.\n";
            continue;
        }

        tm inputTm = parseDate(date);

        if (referenceDate.empty()) {
            if (isDatePast(inputTm, currentDateTm)) {
                cout << "Date cannot be in the past. Please enter a date on or after " << currentDateStr << ".\n";
            } else {
                return date;
            }
        } else {
            tm referenceTm = parseDate(referenceDate);
            if (isDatePast(inputTm, referenceTm)) {
                cout << "Check-out date cannot be on or before Check-in date. Please enter a date after " << referenceDate << ".\n";
            } else {
                return date;
            }
        }
    }
}

int inputRoom() {
    int room;
    while (true) {
        cout << "Enter Room Number (1-10): ";
        cin >> room;
        if (!cin.fail() && room >= 1 && room <= ROOM_COUNT && !rooms[room]) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return room;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid or already booked room. Try again.\n";
    }
}

// File I/O
void saveCustomersToFile() {

}



void loadCustomersFromFile() {


}



// Display available rooms
void displayAvailableRooms() {
cout << "\nAvailable Rooms:\n";
    bool found = false;
    for (int i = 1; i <= ROOM_COUNT; ++i) {
        if (!rooms[i]) {
            cout << "- Room " << i << "\n";
            found = true;
        }
    }
    if (!found) cout << "No rooms available.\n";



}

// Book a room
void bookRoom() {



}
// Display all booked rooms
void displayBookedRooms() {


}

// Update check-out date
void updateBooking() {


}
// Delete customer and archive to file
void deleteBooking() {


}
// Search customer by ID
void searchCustomer() {


}
// Sort customers by ID (swaps data, not nodes)
void sortCustomers() {


}
// Main Menu
int main() {
    loadCustomersFromFile();

    while (true) {
        cout << "\nHotel Management Menu:\n";
        cout << "1. Display Available Rooms\n";
        cout << "2. Book Room\n";
        cout << "3. Display Booked Rooms\n";
        cout << "4. Update Check-out Date\n";
        cout << "5. Delete Booking (Archive)\n";
        cout << "6. Search Customer by ID\n";
        cout << "7. Sort Customers by ID\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume the rest of the line


switch (choice) {
            case 1: displayAvailableRooms(); break;
            case 2: bookRoom(); break;
            case 3: displayBookedRooms(); break;
            case 4: updateBooking(); break;
            case 5: deleteBooking(); break;
            case 6: searchCustomer(); break;
            case 7: sortCustomers(); break;
            case 0:
                cout << "Exiting...\n";
                // Add cleanup for dynamically allocated memory (Customer nodes)
                while (head) {
                    Customer* temp = head;
                    head = head->next;
                    delete temp;
                }
                return 0;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
