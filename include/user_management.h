#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include "mysql_test.h"
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;
string getPassword();
int RegisterUser(MYSQL *con);
int LoginUser(MYSQL *con);
void Store_Password(MYSQL *con, int UserID);
void Retrieve_Password(MYSQL *con, int UserID);

#endif // USER_MANAGEMENT_H
