#include <iostream>
#include <string>
using namespace std;

int main() {
  int choice;
  do {
    cout << "1. Add Password\n2. Retrieve Password\n3. Exit\n";
    cin >> choice;
    if (choice == 1) {
      string site, username, password;
      cout << "Enter site: ";
      cin >> site;
      cout << "Enter username: ";
      cin >> username;
      cout << "Enter password: ";
      cin >> password;
    } else if (choice == 2) {
      string site, username;
      cout << "Enter site: ";
      cin >> site;
      cout << "Enter username: ";
      cin >> username;
    }
  } while (choice != 3);
  return 0;
}