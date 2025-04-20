#include <iostream>
#include <string>
using namespace std;
class Student {
public:
    string id;
    string name;
    string address;
    string phone;
    Student(string id, string name, string address, string phone) {
        this->id = id;
        this->name = name;
        this->address = address;
        this->phone = phone;
    }
};
class TelephoneDirectory {
private:
    Student** directory;
    int capacity;
    int size;
    void resizeDirectory() {
        int newCapacity = capacity * 2;
        Student** newDirectory = new Student*[newCapacity];
        for (int i = 0; i < size; i++) {
            newDirectory[i] = directory[i];
        }
        delete[] directory;
        directory = newDirectory;
        capacity = newCapacity;
    }
public:
    TelephoneDirectory(int initialCapacity = 2) {
        directory = new Student*[initialCapacity];
        capacity = initialCapacity;
        size = 0;
    }
    ~TelephoneDirectory() {
        for (int i = 0; i < size; i++) {
            delete directory[i];  
        }
        delete[] directory;  
    }
    bool idExists(const string& id) {
        for (int i = 0; i < size; i++) {
            if (directory[i]->id == id) {
                return true;
            }
        }
        return false;
    }
    void insertStudent() {
        string id, name, address, phone;
        cout << "Enter ID: ";
        cin >> id;
        if (idExists(id)) {
            cout << "ID already exists. Cannot insert.\n";
            return;
        }
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Phone Number: ";
        getline(cin, phone);
        int confirm;
        cout << "Press 1 to save, 0 to not save: ";
        cin >> confirm;
        if (confirm == 0) return;
        if (size == capacity) {
            resizeDirectory();
        }
        directory[size] = new Student(id, name, address, phone);
        size++;
        cout << "Record saved successfully.\n";
    }
    void updateStudent() {
        string input;
        cout << "Enter ID or Name: ";
        cin.ignore();
        getline(cin, input);
        for (int i = 0; i < size; i++) {
            if (directory[i]->id == input || directory[i]->name == input) {
                cout << "Current Information is:\n";
                displayStudent(directory[i]);
                char confirm;
                cout << "Do you want to update [y/n]?: ";
                cin >> confirm;
                if (confirm == 'n') return;
                cin.ignore();
                cout << "Enter New ID: ";
                getline(cin, directory[i]->id);
                cout << "Enter New Name: ";
                getline(cin, directory[i]->name);
                cout << "Enter New Address: ";
                getline(cin, directory[i]->address);
                cout << "Enter New Phone: ";
                getline(cin, directory[i]->phone);
                cout << "Record updated successfully.\n";
                return;
            }
        }
        cout << "Record not found.\n";
    }
    void deleteStudent() {
        string id;
        cout << "Enter ID: ";
        cin >> id;
        for (int i = 0; i < size; i++) {
            if (directory[i]->id == id) {
                cout << "Current Information is:\n";
                displayStudent(directory[i]);
                char confirm;
                cout << "Do you want to delete this record [y/n]?: ";
                cin >> confirm;
                if (confirm == 'n') return;
                delete directory[i];
                for (int j = i; j < size - 1; j++) {
                    directory[j] = directory[j + 1];
                }
                size--;
                cout << "Record deleted successfully.\n";
                return;
            }
        }
        cout << "Record not found.\n";
    }
    void searchStudent() {
        string input;
        cout << "Enter ID or Name: ";
        cin.ignore();
        getline(cin, input);

        for (int i = 0; i < size; i++) {
            if (directory[i]->id == input || directory[i]->name == input) {
                cout << "Record Found:\n";
                displayStudent(directory[i]);
                return;
            }
        }
        cout << "Record not found.\n";
    }
    void listDirectory() {
        if (size == 0) {
            cout << "Directory is empty.\n";
            return;
        }
        for (int i = 0; i < size; i++) {
            displayStudent(directory[i]);
            cout << "--------------------------\n";
        }
    }
    void displayStudent(Student* s) {
        cout << "ID: " << s->id << "\n";
        cout << "Name: " << s->name << "\n";
        cout << "Address: " << s->address << "\n";
        cout << "Phone: " << s->phone << "\n";
    }
};
int main() {
    TelephoneDirectory dir;
    int choice;
    char again;
    do {
        cout << "Telephone Directory: Main Menu\n";
        cout << "1. Insert a new student\n";
        cout << "2. Update an existing student\n";
        cout << "3. Delete a record\n";
        cout << "4. Search for a student (using name or ID)\n";
        cout << "5. List directory\n";
        cout << "Select Option [1, 2, 3, 4 or 5]: ";
        cin >> choice;
        switch (choice) {
        case 1:
            do {
                dir.insertStudent();
                cout << "Want to insert another record? [y/n]: ";
                cin >> again;
            } while (again == 'y');
            break;
        case 2:
            do {
                dir.updateStudent();
                cout << "Do you want to update another record? [y/n]: ";
                cin >> again;
            } while (again == 'y');
            break;
        case 3:
            do {
                dir.deleteStudent();
                cout << "Do you want to delete another record? [y/n]: ";
                cin >> again;
            } while (again == 'y');
            break;
        case 4:
            do {
                dir.searchStudent();
                cout << "Do you want to search another record? [y/n]: ";
                cin >> again;
            } while (again == 'y');
            break;
        case 5:
            dir.listDirectory();
            break;
        default:
            cout << "Invalid Option!\n";
        }
    } while (true);
    return 0;
}