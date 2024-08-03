#include <cstdlib>
#include <iostream>
#include <string>
#include "../include/password_id.h"

using namespace std;
string encryption(const string &password, const string &text, const string &master_pass)
{
    string command =
        "echo -n \"" + text +
        "\" | openssl enc -aes-256-cbc -e -base64 -pbkdf2 -pass pass:" + password;
    string encText = executeCommand(command);
    if (!encText.empty())
    {
        cout << encText << endl;
    }
    else
    {
        cerr << "Encryption failed!" << endl;
    }
    return encText;
}

string decryption(const string &password, const string &enc, const string &master_pass)

{
    string command =
        "echo \"" + enc +
        "\" | openssl enc -aes-256-cbc -d -base64 -pbkdf2 -pass pass:" + password;
    string decText = executeCommand(command);
    if (!decText.empty())
    {
        cout << "Decrypted text: " << decText << endl;
        return decText;
    }
    else
    {
        cerr << "Decryption failed!" << endl;
        return -1; 
    }
}
