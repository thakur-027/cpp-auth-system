#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "securehash.h"
using namespace std;

const string FILE_NAME = "file.csv";

// Check if username exists
bool userExists(const string& username) {
    ifstream file(FILE_NAME);
    string line, user, pass, age;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, user, ',');
        if (user == username) {
            return true;
        }
    }
    return false;
}

// Register a new user
void registerUser() {
    string username, password, age;

    cout << "\n----------- REGISTER -----------\n";
    cout << "Enter username: ";
    cin >> username;

    if (userExists(username)) {
        cout << "User already exists. Try another username.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;
    cout << "Enter age: ";
    cin >> age;

    string hashedPassword = sha256(password);

    ofstream file(FILE_NAME, ios::app);
    file << username << "," << hashedPassword << "," << age << "\n";
    file.close();

    cout << "Registration successful!\n";
}

// Login existing user
void loginUser() {
    string username, password;
    string line, user, pass, age;
    bool found = false;

    cout << "\n----------- LOGIN -----------\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string hashedInput = sha256(password);

    ifstream file(FILE_NAME);

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, user, ',');
        getline(ss, pass, ',');
        getline(ss, age, ',');

        if (user == username && pass == hashedInput) {
            found = true;
            cout << "Login successful!\n";
            cout << "Username: " << user << "\n";
            cout << "Age: " << age << "\n";
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Incorrect credentials.\n";
    }
}

// Change password
void changePassword() {
    string username, oldPass, newPass1, newPass2;
    bool updated = false;
    string line, user, pass, age;

    cout << "\n------ CHANGE PASSWORD ------\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter old password: ";
    cin >> oldPass;

    string oldHashed = sha256(oldPass);

    ifstream file(FILE_NAME);
    ofstream temp("temp.csv");

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, user, ',');
        getline(ss, pass, ',');
        getline(ss, age, ',');

        if (user == username && pass == oldHashed) {
            cout << "Enter new password: ";
            cin >> newPass1;
            cout << "Re-enter new password: ";
            cin >> newPass2;

            if (newPass1 == newPass2) {
                string newHashed = sha256(newPass1);
                temp << user << "," << newHashed << "," << age << "\n";
                updated = true;
                cout << "Password changed successfully!\n";
            } else {
                cout << "Passwords do not match. Try again.\n";
                temp << user << "," << pass << "," << age << "\n"; // Keep old password
            }
        } else {
            temp << user << "," << pass << "," << age << "\n"; // Keep other users
        }
    }

    file.close();
    temp.close();
    remove(FILE_NAME.c_str());
    rename("temp.csv", FILE_NAME.c_str());

    if (!updated) {
        cout << "Username or old password is incorrect.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n==============================\n";
        cout << "        SECURITY SYSTEM        \n";
        cout << "==============================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Change Password\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: changePassword(); break;
            case 4: cout << "Exiting... Thank you!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
