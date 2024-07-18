#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

string executeCommand(const string &command)
{
    char buffer[128];
    string result;
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        cerr << "popen() failed!" << endl;
        return "";
    }
    try
    {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            result += buffer;
        }
    }
    catch (...)
    {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

string hashpass(const string &password)
{
    string command =
        "echo -n" + password + "| shasum -a 256";
    string text = executeCommand(command);
    return text;
}
