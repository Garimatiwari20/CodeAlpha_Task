#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

// Hashing the password (for basic security)
string hashPassword(const string& password) {
    hash<string> hasher;
    return to_string(hasher(password));
}

// Load all users from file into a map
unordered_map<string, string> loadUsers(const string& filename) {
    unordered_map<string, string> users;
    ifstream infile(filename);
    string line, username, passwordHash;

    while (getline(infile, line)) {
        stringstream ss(line);
        getline(ss, username, ':');
        getline(ss, passwordHash);
        users[username] = passwordHash;
    }

    return users;
}

// Save new user to file
void saveUser(const string& filename, const string& username, const string& passwordHash) {
    ofstream outfile(filename, ios::app); // append mode
    outfile << username << ":" << passwordHash << endl;
}

// Registration function
void registerUser(const string& filename) {
    unordered_map<string, string> users = loadUsers(filename);
    string username, password;

    cout << "\n=== User Registration ===" << endl;
    cout << "Enter username: ";
    getline(cin, username);

    if (username.empty()) {
        cout << "❌ Username cannot be empty.\n";
        return;
    }

    if (users.find(username) != users.end()) {
        cout << "❌ Username already exists. Try another.\n";
        return;
    }

    cout << "Enter password (min 6 characters): ";
    getline(cin, password);

    if (password.length() < 6) {
        cout << "❌ Password too short.\n";
        return;
    }

    string hashedPassword = hashPassword(password);
    saveUser(filename, username, hashedPassword);

    cout << "✅ Registration successful for user: " << username << endl;
}

// Login function
void loginUser(const string& filename) {
    unordered_map<string, string> users = loadUsers(filename);
    string username, password;

    cout << "\n=== User Login ===" << endl;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    auto it = users.find(username);
    if (it == users.end()) {
        cout << "❌ Username not found.\n";
        return;
    }

    string hashedInput = hashPassword(password);
    if (hashedInput == it->second) {
        cout << "✅ Login successful. Welcome, " << username << "!\n";
    } else {
        cout << "❌ Incorrect password.\n";
    }
}

int main() {
    string filename = "users.txt";
    int choice;

    while (true) {
        cout << "\n==== USER SYSTEM ====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // To clear newline after cin

        switch (choice) {
            case 1:
                registerUser(filename);
                break;
            case 2:
                loginUser(filename);
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
