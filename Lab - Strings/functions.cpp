#include "functions.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <tuple>
#include <sstream>

// add any includes

using namespace std;

string replaceAll(string str, char a, char b) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == a) {
            str[i] = b;
        }
    }
    return str;
}

string reverseString(const string& str) {
    string reversed;
    for (int i = str.length() - 1; i >= 0; --i) {
        reversed += str[i];
    }
    return reversed;
}

bool isPalindrome(const string &str)
{
    int i = 0;
    int j = str.length() - 1;

    while (i < j)
    {
        if (str[i] != str[j])
        {
            return false;
        }
        i++;
        j--;
    }

    return true;
}

void deobfuscate()
{
    // TODO
}

void wordFilter()
{
    // TODO
}

void passwordConverter()
{
    // TODO
    cout << "Please enter your text input: ";
    string password;
    getline(cin, password);

    cout << "input: " << password << endl;

    password = replaceAll(password, 'a', '@');
    password = replaceAll(password, 'e', '3');
    password = replaceAll(password, 'i', '!');
    password = replaceAll(password, 'o', '0');
    password = replaceAll(password, 'u', '^');

    string newPassword = password + reverseString(password);
    cout << "output: " << newPassword << endl;
}

void wordCalculator()
{
    // TODO
}

void palindromeCounter()
{
    // TODO
    string input = "";
    cout << "Please enter a sentence (end with 'quit'): ";
    getline(cin, input);
    int numWords = 0;

    stringstream ssin(input);
    string word;
    while (ssin >> word && word != "quit")
    {
        numWords++;
    }

    ssin.clear();
    ssin.seekg(0);

    string *arr = new string[numWords];
    int i = 0;
    while (i < numWords)
    {
        ssin >> arr[i];
        i++;
    }

    int numPalindromes = 0;
    for (i = 0; i < numWords; i++)
    {
        if(isPalindrome(arr[i]))
        {
            numPalindromes++;
        }
    }

    cout << "You have typed " << numPalindromes << " palindromes." << endl;

    delete[] arr;
}