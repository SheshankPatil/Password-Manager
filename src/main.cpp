#include "../include/user_management.h"
#include <iostream>

using namespace std;

int main() {
  int choice;
  cout << "1. Register\n2. Login\n" << endl;
  cin >> choice;
  if (choice == 1) {
    RegisterUser();
  } else if (choice == 2) {
    LoginUser();
  } else {
    cout << "Invalid choice. Exiting program." << endl;
  }
  return 0;
}
