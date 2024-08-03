#include "../include/user_management.h"
#include "../include/mysql_test.h"
#include "../include/password_id.h"
#include <iostream>

using namespace std;

string getPassword()
{
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

int RegisterUser(MYSQL *con)
{
  string username, password1, password2;
  cout << "Register\n";
  cout << "Enter username: ";
  cin >> username;
  do
  {

    cout << "Enter ";
    password1 = getPassword();

    cout << "Verify ";
    password2 = getPassword();
    if (password1 != password2)
    {

      cout << "Passwords do not match. Please try again.\n";
    }
  } while (password1 != password2);
  password1 = hashpass(password1);

  int userid = insert_user(con, const_cast<char *>(username.c_str()),
                           const_cast<char *>(password1.c_str()));
  return userid;
}

int LoginUser(MYSQL *con)
{
  string username, password;
  cout << "Login\n";
  cout << "Enter username: ";
  cin >> username;
  cout << "Enter ";
  password = getPassword();
  password = hashpass(password);
  int userid = login_user(con, const_cast<char *>(username.c_str()),
                          const_cast<char *>(password.c_str()));
  return userid;
}

void Store_Password(MYSQL *con, int UserID)
{
  string Site_name, Site_username, password;
  cout << "Enter Site Name\n";
  cin >> Site_name;
  cout << "Enter username\n";
  cin >> Site_username;
  cout << "Enter ";
  password = getPassword();
  password = hashpass(password);
  insert_password(con, UserID, const_cast<char *>(Site_name.c_str()), const_cast<char *>(Site_username.c_str()), const_cast<char *>(password.c_str()));
}

void Retrieve_Password(MYSQL *con, int UserID)
{
  string Site_name, Site_username;
  cout << "Enter Site Name\n";
  cin >> Site_name;
  cout << "Enter username\n";
  cin >> Site_username;
  retrieve_user_password(con, UserID, const_cast<char *>(Site_name.c_str()), const_cast<char *>(Site_username.c_str()));
}