#include <iostream>
#include <termios.h>
#include <unistd.h>

using namespace std;

string getPassword() {
  string password;
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  newt.c_lflag &= ~ECHO;

  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  cout << "password: ";
  cin >> password;
  cout << endl;

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return password;
}

bool RegisterUser() {
  string username, password1, password2;
  cout << "Register\n";
  cout << "Enter username: ";
  cin >> username;
  do {
    cout << "Enter ";
    password1 = getPassword();
    cout << "Verify ";
    password2 = getPassword();
    if (password1 != password2) {
      cout << "Passwords do not match. Please try again.\n";
    }
  } while (password1 != password2);
  return true;
}

bool LoginUser() {
  string username, password;
  cout << "Register\n";
  do {
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter ";
    password = getPassword();
  } while (0); // Condition will be Authentication of username and password in
               // database;
  return true;
}
int main() {
  int choice;
  cout << "1. Register\n2. Login\n" << endl;
  cin>>choice;
  if (choice == 1) {
    RegisterUser();
  } else if (choice == 2) {
    LoginUser();
  } else {
    cout << "Invalid choice. Exiting program." << endl;
  }
  return 0;
}