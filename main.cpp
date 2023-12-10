    #include <iostream>
    #include <fstream>
    #include <string>
    #include <map>

    using namespace std;

    class TelephoneDirectory {
    private:
        map<string, string> phoneBook;
        string fileName;

    public:
        TelephoneDirectory(string file) : fileName(file) {
            loadContacts();
        }

        void addContact() {
            string name, number;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter number: ";
            cin >> number;
            phoneBook[name] = number;
            saveContacts();
            cout << "Contact added successfully!" << endl;
        }

        void displayContacts() {
            if (phoneBook.empty()) {
                cout << "Phonebook is empty." << endl;
            } else {
                cout << "Contacts:" << endl;
                for (const auto &entry : phoneBook) {
                    cout << entry.first << ": " << entry.second << endl;
                }
            }
        }

        void searchContact() {
            string name;
            cout << "Enter name to search: ";
            cin >> name;
            if (phoneBook.find(name) != phoneBook.end()) {
                cout << "Contact found: " << phoneBook.at(name) << endl;
            } else {
                cout << "Contact not found." << endl;
            }
        }

        void loadContacts() {
            ifstream file(fileName);
            if (file.is_open()) {
                string name, number;
                while (file >> name >> number) {
                    phoneBook[name] = number;
                }
                file.close();
            }
        }

        void deleteContact() {
            string name;
            cout << "Enter name to delete: ";
            cin >> name;
            auto it = phoneBook.find(name);
            if (it != phoneBook.end()) {
                phoneBook.erase(it);
                saveContacts();
                cout << "Contact deleted successfully!" << endl;
            } else {
                cout << "Contact not found." << endl;
            }
        }

        void saveContacts() {
            ofstream file(fileName);
            if (file.is_open()) {
                for (const auto &entry : phoneBook) {
                    file << entry.first << " " << entry.second << "\n";
                }
                file.close();
            } else {
                cerr << "Unable to open file for writing." << endl;
            }
        }
    };

    int main() {
        TelephoneDirectory directory("contacts.txt");
        int choice;

        while (true) {
            cout << "\nMenu:\n";
            cout << "1. Add contact\n";
            cout << "2. Display contacts\n";
            cout << "3. Search contact\n";
            cout << "4. Quit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    directory.addContact();
                    break;
                case 2:
                    directory.displayContacts();
                    break;
                case 3:
                    directory.searchContact();
                    break;
                case 4:
                    cout << "Exiting program. Goodbye!" << endl;
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }

        return 0;
    }


