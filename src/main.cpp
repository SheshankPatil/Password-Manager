#include "../include/mysql_test.h"
#include "../include/user_management.h"
#include <iostream>

using namespace std;

int main() {
  MYSQL con = Connection_establish();

  int choice;
  cout << "1. Register\n2. Login\n" << endl;
  cin >> choice;
  if (choice == 1) {
    int UserId = RegisterUser(&con);
  } else if (choice == 2) {
    LoginUser();
  } else {
    cout << "Invalid choice. Exiting program." << endl;
  }
  return 0;
}
