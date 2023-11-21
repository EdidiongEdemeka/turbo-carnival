#include <iostream>
#include <list>

using namespace std;

// Structure for student record
struct StudentRecord {
  int key;
  string name;
  float gpa;
  string academicLevel;
  StudentRecord *next; // to resolve collisions using chaining

  StudentRecord(int key, string name, float gpa, string academicLevel)
      : key(key), name(name), gpa(gpa),
  academicLevel(academicLevel), next(nullptr) {}
};

// Hash table class
class HashTable {
private:
  static const int tableSize = 1000;
  StudentRecord** table = (StudentRecord**)malloc(tableSize * sizeof(StudentRecord*));
int count = 0;

public:
  // constructor
  HashTable() {
    // initialize table elements to nullptrs
    for (int i = 0; i < tableSize; i++) {
      table[i] = nullptr;
    }
  }

  // Hash function (helper)
  int hashFunction(int key) { return key % tableSize; }

  // INSERT function
  void insertRecord(StudentRecord *record) {
    if (count < 10000) {
      int key = record->key;
      int index = hashFunction(key);
      StudentRecord *temp = table[index];
      // first we check if the table slot is empty
      if (temp == nullptr) {
        table[index] = record;  //insert the new record as the first element in the list
        count++;
        return;
      } else {
        while (temp->next != nullptr) {
          temp = temp->next;
        }
        temp->next = record; // insert the record into the linked list
        count++;
        return;
      }
    } else {
      cout << "Table is full.\n" << endl;
    }
  }

  // SEARCH helper function
  StudentRecord *searchRecordHelper(int key) {
    int index = hashFunction(key);
    StudentRecord *temp = table[index];
    if (temp == nullptr) {
      return temp;
    } else {
      while (temp != nullptr) {
        if (temp->key == key) {
          return temp;
        } else {
          temp = temp->next;
        }
      }
      return temp;
    }
  }

  // DELETE function
  void deleteRecord(int key) {
    int index = hashFunction(key);
    StudentRecord *temp = table[index];
    StudentRecord *prev = temp;
    if (temp == nullptr) {
      cout << "Record with key " << key << " not found.\n";
      return;
    } else {
      while (temp != nullptr) {
        if (temp->key == key) {
          // delete the record
          prev->next = temp->next;
          delete temp;
          cout << "Record with key " << key << " has been deleted.\n";
          return;
        } else {
          prev = temp;
          temp = temp->next;
        }
      }
      cout << "Record with key " << key << " not found.\n";
    }
  }

  // SEARCH function
  void searchRecord(int key) {
    StudentRecord *record = searchRecordHelper(key);
    if (record == nullptr) {
      cout << "Record with key " << key << " not found.\n";
      return;
    } else {
      cout << "Record found:\n";
      cout << "Key: " << record->key << "\n";
      cout << "Name: " << record->name << "\n";
      cout << "GPA: " << record->gpa << "\n";
      cout << "Academic Level: " << record->academicLevel << "\n";
    }
  }
};

int main() {
  HashTable studentTable;
  int choice;
  int key;
  string name;
  float gpa;
  string academicLevel;

  do {
    // Display menu
    std::cout << "\nHash Table Implementation" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "1. Insert a Record" << std::endl;
    std::cout << "2. Search the table" << std::endl;
    std::cout << "3. Delete a record" << std::endl;
    std::cout << "4. Exit" << std::endl;

    // Get user choice
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Process user choice
    switch (choice) {
    case 1:{
      std::cout << "You selected Option 1. Inserting a Record." << std::endl;

      std::cout << "Enter name: ";
      std::cin >> name;
      std::cout << "Enter GPA: ";
      std::cin >> gpa;
      std::cout << "Enter Academic Level: ";
      std::cin >> academicLevel;
      std::cout << "Enter key: ";
      std::cin >> key;

      if(key < 0 || key > 65536) {
          std::cout << "Key is out of range" << std::endl;
      }
      else {
      if(studentTable.searchRecordHelper(key) == nullptr) {
      StudentRecord *newRecord =
          new StudentRecord(key, name, gpa, academicLevel);
      studentTable.insertRecord(newRecord);
      }
      else
        std::cout << "Record with key " << key << " already exists." << std::endl;
      }
      break;
    }
    case 2:
      std::cout << "You selected Option 2. Searching the table." << std::endl;

      // search
      std::cout << "Enter key to search: ";
      std::cin >> key;

      if(key < 0 || key > 65536) {
          std::cout << "Key is out of range" << std::endl;
          break;
      }
      else
        studentTable.searchRecord(key);
      break;

    case 3:
      std::cout << "You selected Option 3. Deleting a record." << std::endl;

      // deletion
      std::cout << "Enter key to delete: ";
      std::cin >> key;

      if(key < 0 || key > 65536) {
          std::cout << "Key is out of range" << std::endl;
          break;
      }
      else
        studentTable.deleteRecord(key);
      break;

    case 4:
      std::cout << "Exiting the program." << std::endl;
      break;

    default:
      std::cout << "Invalid choice. Please enter a valid option." << std::endl;
    }

  } while (choice != 4);

  return 0;
}
