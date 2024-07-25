#include <iostream>
#include <fstream>
#include <string> 

using namespace std;

class Temp {
    string userName, email, password; 
    string searchName, searchEmail, searchPass; 
    fstream file;

public:
    void login();
    void signup();
    void forgot();
};

void Temp::signup() {
    cout << "\nEnter your name: ";
    getline(cin, userName); 
    cout << "Enter your Email address: ";
    getline(cin, email); 
    cout << "Enter your password: ";
    getline(cin, password);

    file.open("loginData.txt", ios::out | ios::app);
    file << userName << "*" << email << "*" << password << endl;
    file.close();
}

void Temp::login() {
    cout << "\n------------------LOGIN---------------------\n";
    cout << "Enter the username: ";
    getline(cin, searchName); 
    cout << "Enter your password: ";
    getline(cin, searchPass); 

    file.open("loginData.txt", ios::in);
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos1 = line.find('*');
        size_t pos2 = line.find('*', pos1 + 1);
        string userNameFromFile = line.substr(0, pos1);
        string emailFromFile = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string passwordFromFile = line.substr(pos2 + 1);

        if (userNameFromFile == searchName && passwordFromFile == searchPass) {
            cout << "\nAccount Login successful!\n";
            cout << "Username: " << userNameFromFile << endl;
            cout << "Email: " << emailFromFile << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Username or password incorrect!\n";
    }

    file.close();
}

void Temp::forgot() {
    cout << "\nEnter your username: ";
    getline(cin, searchName); /
    cout << "Enter your Email address: ";
    getline(cin, searchEmail); 

    file.open("loginData.txt", ios::in);
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos1 = line.find('*');
        size_t pos2 = line.find('*', pos1 + 1);
        string userNameFromFile = line.substr(0, pos1);
        string emailFromFile = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string passwordFromFile = line.substr(pos2 + 1);

        if (userNameFromFile == searchName && emailFromFile == searchEmail) {
            cout << "\nAccount found!\n";
            cout << "Your password: " << passwordFromFile << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not found or email doesn't match!\n";
    }

    file.close();
}

int main() {
    Temp obj;
    char choice;

    do {
        cout << "\n1- Login\n";
        cout << "2- Sign-up\n";
        cout << "3- Forgot password\n";
        cout << "4- Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case '1':
                obj.login();
                break;

            case '2':
                obj.signup();
                break;

            case '3':
                obj.forgot();
                break;

            case '4':
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid selection...\n";
                break;
        }
    } while (choice != '4');

    return 0;
}
