#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct UserStruct {
    string username;
    string password;
};

class AccountManager {
public:
    AccountManager(const string& dataFile) : dataFile(dataFile) {
        loadDataFromFile();
    }

    bool createUser(const string& username, const string& password) {
        if (findUser(username) != nullptr) {
            cout << "Username already exists. Please choose a different username.\n";
            return false;  // Username already exists
        }

        users.push_back({ username, password });
        saveDataToFile();
        cout << "Registration successful!\n";
        return true;  // Registration successful
    }

    bool authenticateUser(const string& username, const string& password) {
        UserStruct* user = findUser(username);
        if (user != nullptr && user->password == password) {
            cout << "Login successful!\n";
            return true;  // Login successful
        }

        cout << "Invalid username or password. Please try again.\n";
        return false;  // Invalid username or password
    }

private:
    vector<UserStruct> users;
    const string dataFile;

    UserStruct* findUser(const string& username) {
        for (UserStruct& user : users) {
            if (user.username == username) {
                return &user;
            }
        }
        return nullptr;
    }

    void loadDataFromFile() {
        ifstream inputFile(dataFile);

        if (inputFile.is_open()) {
            while (!inputFile.eof()) {
                UserStruct user;
                inputFile >> user.username >> user.password;
                if (!user.username.empty() && !user.password.empty()) {
                    users.push_back(user);
                }
            }

            inputFile.close();
        }
    }

    void saveDataToFile() {
        ofstream outputFile(dataFile);

        if (outputFile.is_open()) {
            for (const UserStruct& user : users) {
                outputFile << user.username << " " << user.password << endl;
            }

            outputFile.close();
        }
    }
};

int main() {
    AccountManager accountManager("data.txt");
    int choice;
    bool flag = false;

    do {
        cout << "\nOptions:\n";
        cout << "1. Create Account\n";
        cout << "2. Log In\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string username, password;
            cout << "Enter a username: ";
            cin >> username;
            cout << "Enter a password: ";
            cin >> password;

            accountManager.createUser(username, password);
            break;
        }
        case 2: {
            string username, password;
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            accountManager.authenticateUser(username, password);
            break;
        }
        case 3:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            flag = true;
        }
        if (flag)
        {
            break;
        }
    } while (choice != 3);

    return 0;
}
