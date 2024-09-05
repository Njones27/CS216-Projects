/*
 * Course: CS216-003
 * Project: Lab 2
 * Purpose: practice how to run unix command from C++ program
 *          system() is used to invoke an operating command from a C++ program
 *          demo cowsay command using three different cow files
 * Author: Nathan Jones
 */

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream inFile("cowFiles.txt");
    string line;
    int cowCount = 0;


    if (inFile.fail()) {
    cout << "Unable to open file" << endl;
    return 0;
    }
        
    while (getline(inFile, line)) {
        // each time use a different cow file for cowsay command to use
        string command_str = "cowsay -f /usr/share/cowsay/cows/";
        command_str = command_str + line;
        command_str = command_str + " Hello, CS216 Students!";
        const char* command = command_str.c_str();
        system(command);
        cowCount++;
    
    }

    inFile.close();
    
    cout << "There are "<< cowCount << " cow Files stored in my VM" << endl;
    return 0;
}

