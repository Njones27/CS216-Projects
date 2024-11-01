/* 
 * File:   powerString.cpp
 * Course: CS216-003
 * Project: Lab 8
 * Purpose: provide the implementation of member functions of powerString class
 */
#include <iostream> 
#include <algorithm>
#include "powerString.h"

using namespace std;

//constructor
powerString::powerString(string ini_string)
{
    this->str = ini_string;
}

// set the current value of str
void powerString::setPowerString(string value)
{
    this->str = value;
}

// return the value of str
string powerString::getPowerString() const
{
    return this->str;
}

//returns a string which transforms each character of str into lower case
//note that str has not been changed
//(algorithm header file is needed for the definition of transform function)
string powerString::toLower() const
{
    string result = this->str;
    transform(this->str.begin(), this->str.end(), result.begin(), ::tolower);
    return result;
}

//returns a string which transforms each character of str into upper case
// use recursive function to implement
//note that str has not been changed
string powerString::toUpper() const
{
    static int fcount = 0; // use a static variable to count the function calling
    fcount++;   // increase count by one while calling the function
    cout << "Calling the recursive function named " << __func__ << " : " << fcount  << " times." << endl;   // note that __func__ is macro for the funciton name, it may be different for different compiler
    // Base case:
    if (this->str.length() == 0)
        return this->str;
    // Recursive case:
    string first = this->str.substr(0,1);
    const char* front = first.c_str();
    char upperFront[LEN];
    string result;
    upperFront[0] = toupper(front[0]);
    upperFront[1] = '\0';
    result = upperFront;
    powerString part(this->str.substr(1, this->str.length()-1));
    return result + part.toUpper();
}

//it remove the extra blank spaces(including tab) from str
//It defines as:
//   1. it remains only one space if str contains more than
//      one continuous blank spaces between two non-space characters
//      For example, if str is "hello,     world",
//      it should change into "hello, world"
//   2. it removes all spaces before the first non-space character
//   3. it also removes all spaces after the last non-space character
void powerString::removeExtraSpace()
{
    // your code should start here...
    if (str.empty()) {
        return;
    }

    // Find first non-space character
    int start = 0;
    while (start < str.length() && isspace(str[start])) {
        start++;
    }

    // If string is all spaces, clear it and return
    if (start == str.length()) {
        str.clear();
        return;
    }

    // Find last non-space character
    int end = str.length() - 1;
    while (end > start && isspace(str[end])) {
        end--;
    }

    // Process the string between start and end
    string result;
    bool prevSpace = false;
    
    for (int i = start; i <= end; i++) {
        if (isspace(str[i])) {
            if (!prevSpace) {
                result += ' ';  // Add only one space
                prevSpace = true;
            }
        } else {
            result += str[i];
            prevSpace = false;
        }
    }

    str = result;
}

// return a string which transforms only the first letter of each word in str into upper case letter
// the word in str is defined as a sequence of characters starting with non-space character and ending right before the next space
// note that str has not been changed
string powerString::wordFormat() const
{
    string result = this->str;
    // before the wordFormat transformation
    // make sure (1)the extra space(s) has been removed from str; 
    //           (2)apply to all lower case letters of str
    // your code should start here...
    
    // Temporary powerString object to use removeExtraSpace
    powerString temp(result);
    temp.removeExtraSpace();
    result = temp.str;  // Get the processed string back
    
    // Convert the entire string to lowercase
    for (int i = 0; i < result.length(); i++) {
        result[i] = tolower(result[i]);
    }
    
    // Capitalize first letter of each word
    if (!result.empty()) {
        result[0] = toupper(result[0]);  // Capitalize first letter of the string
    }
    
    // Capitalize first letter after each space
    for (int i = 1; i < result.length(); i++) {
        if (result[i-1] == ' ') {
            result[i] = toupper(result[i]);
        }
    }
    return result;
}
