#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>


using namespace std;

int getID()     //read user interface
{
    while (true)
    {
        int a;
        cout << "Enter 1 if you wish to encrypt a message. Enter 2 if you wish to decrypt a message." << endl;
        cin >> a;
        cin.clear();    //clear output stream to avoid skipping future inputs
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (a != 1 && a != 2)   //check for valid input
        {
            cout << "Not a valid numerical. Try again." << endl;
            continue;
        }
        return a;
    }
}

int getKey()    //read encryption key
{
    while (true)
    {
        int a;
        cout << "Enter the encryption key you want to use:" << endl;
        cin >> a;
        if (cin.fail())     //check for valid input
        {
            cin.clear();    //clear output stream to avoid skipping future inputs
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Not a valid numerical. Try again." << endl;
            continue;
        }
         return a;
    }
}

string getBaseLine(int ID)      //read text
{
    string baseLine;
    if (ID == 1)
    {
        cout << "Enter the Text you wish to encrypt:" << endl;
    }
    if (ID == 2)
    {
        cout << "Enter the Text you wish to decrypt:" << endl;
    }
    cin.clear();    //clear output stream to avoid skipping future inputs
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, baseLine);
    return baseLine;
}

char genRngChar()   //generate random character
{
    char c;
    c = 65 + rand() % 26;
    return c;
}

char genEncryptChar(char baseChar, int encryptKey)  //generate encrypted character
{
    for (int i = 0; i < (encryptKey % 26); i++)
    {
        --baseChar;
        if (baseChar < 65)
        {
            baseChar += 26;
        }
    }
    return baseChar;
}

char genDecryptChar(char baseChar, int encryptKey)  //generate decrypted character
{
    for (int i = 0; i < (encryptKey % 26); i++)
    {
        ++baseChar;
        if (baseChar > 90)
        {
            baseChar -= 26;
        }
    }
    return baseChar;
}

vector<char> splitString(string baseLine)   //pull characters from string into a vector
{
    vector<char> v;
    for (int i = 0; i < baseLine.length(); i++)
    {
        if (!isalpha(baseLine[i]))
        {
            v.push_back(baseLine[i]);
            continue;
        }
        v.push_back(toupper(baseLine[i]));
    }
    return v;
}

vector<char> genRngStr(string baseLine)     //generate random character sequence for fancy visuals
{
    vector<char> v;
    for (int i = 0; i < baseLine.length(); i++)
    {
        if (!isalpha(baseLine[i]))
        {
            v.push_back(baseLine[i]);
            continue;
        }
        v.push_back(genRngChar());
    }
    return v;
}

vector<char> genEncryptStr(vector<char> v, int encryptKey)      //assemble the encrypted message
{
    vector<char> e;
    for (int i = 0; i < v.size(); i++)
    {
        if (!isalpha(v[i]))
        {
            e.push_back(v[i]);
            continue;
        }
        e.push_back(genEncryptChar(v[i], encryptKey));
    }
    return e;
}

vector<char> genDecryptStr(vector<char> v, int encryptKey)      //assemble the decrypted message
{
    vector<char> e;
    for (int i = 0; i < v.size(); i++)
    {
        if (!isalpha(v[i]))
        {
            e.push_back(v[i]);
            continue;
        }
        e.push_back(genDecryptChar(v[i], encryptKey));
    }
    return e;
}

int main()
{   
    while (true)
    {
        srand(time(NULL));      //set random seed
        int userInterface = getID();
        int encryptKey = getKey();
        string baseLine = getBaseLine(userInterface);
        int lineLength = baseLine.length();
        vector<vector<char>> genStr(0, vector<char>(0));
        genStr.push_back(splitString(baseLine));
        for (int i = 0; i < 8; i++)     //push random sequences to vector container
        {
            genStr.push_back(genRngStr(baseLine));
        }
        if(userInterface == 1)      //push encrypted message to vector container
        {
            genStr.push_back(genEncryptStr(genStr[0], encryptKey));
        }
        if (userInterface == 2)     //push decrypted message to vector container
        {
            genStr.push_back(genDecryptStr(genStr[0], encryptKey));
        }
        for (int j = 0; j < genStr.size(); j++)     //print vector array
        {
            for (int i = 0; i < lineLength; i++)
            {
                cout << genStr[j][i];
            }
            if (j > genStr.size() - 2) 
            { 
                continue; 
            }
            cout << '\r' << flush;      //fancy visual effect
            using namespace std::chrono_literals;
            this_thread::sleep_for(250ms);      //delay for 0.25s
        }
        cout << endl;
        char a;
        cout << "Do you want to continue? (Y/N)" << endl;
        cin >> a;
        if (a == 'N' || a == 'n')
        {
            return 0;
        }
    }
}