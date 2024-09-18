/* 
 * File:   MagicString.cpp
 * Purpose: provide the definition of the MagicString class
 *
 * Author: Nathan Jones
 *
 */
#include <iostream>
#include <stack>
#include "MagicString.h"

// initialize str with ini_str passing as a parameter
MagicString::MagicString(string ini_str)
{
    this->str = ini_str;
}

// return the current value of the private data member: str
string MagicString::getString() const
{
    return str;
}

// set the value of str to be the passed in parameter input_str
void MagicString::setString(string input_str)
{
    str = input_str;
}

// return a reverse string
// using a loop to implement
// Note that the private data member named str, has not been changed
string MagicString::rev_loop() const
{
    string rev_str = "";
    for (int i = str.length() - 1; i >= 0; i--) {
        rev_str += str[i];
    }
    return rev_str;
}

// return a reverse string
// using recursion to implement
// Note that the private data member named str, has not been changed
string MagicString::rev_recursion() const
{
    string revReverse;

    if (str.length() == 0) {
        return "";
    }
    else {
        MagicString magic(str.substr(1, str.length()));
        return magic.rev_recursion() + str[0];
    }
}

// return a reverse string
// using a stack to implement
// Note that the private data member named str, has not been changed
string MagicString::rev_stack() const
{
    stack<char> stack;
    string rev_str = "";
    for (int i = 0; i < str.length(); i++) {
        stack.push(str[i]);
    }
    while (!stack.empty()) {
        rev_str += stack.top();
        stack.pop();
    }
    return rev_str;
}

// return true if str is a palindrome
// otherwise return false
// A palindrome is defined as a sequence of characters which reads the same backward as forward
// calling member function to  implement
// Note that the private data member named str, has not been changed
bool MagicString::isPalindrome() const
{
    string rev_str = rev_stack();
    return (str == rev_str);

}
        
// return true if str is a palindrome
// otherwise return false
// A palindrome is defined as a sequence of characters which reads the same backward as forward
// using recursion to implement
// Note that the private data member named str, has not been changed
bool MagicString::isPalindrome_recursion() const
{
    // base case
    if (str.length() <= 1)
        return true;
    else // recursive case
    {
        MagicString shorter(str.substr(1, str.length()-2));
        bool firstPair = str[0] == str[str.length()-1];
        return (firstPair && shorter.isPalindrome_recursion());
    }    
}
        
// displays str followed by a new line marker
// to the standard output
void MagicString::print() const
{
    cout << str << endl;
}
