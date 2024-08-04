#ifndef PASSWORD_ID_H
#define PASSWORD_ID_H

#include <string>
using namespace std;

string executeCommand(const string &command);
string hashpass(const string &password);
string encryption(const string &text, const string &master_pass);
string decryption(const string &enc, const string &master_pass);

#endif
