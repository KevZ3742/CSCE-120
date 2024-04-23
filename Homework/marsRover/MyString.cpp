#include "MyString.h"

MyString::MyString() : str(nullptr), mySize(0), myCapacity(0) {}

MyString::MyString(const MyString &other) : mySize(other.mySize), myCapacity(other.myCapacity) {
    str = new char[myCapacity];
    for (size_t i = 0; i < mySize; ++i) {
        str[i] = other.str[i];
    }
    str[mySize] = '\0';
}

MyString::MyString(const char *s) {
    mySize = 0;
    while (s[mySize] != '\0') {
        ++mySize;
    }
    myCapacity = mySize + 1;
    str = new char[myCapacity];
    for (size_t i = 0; i < mySize; ++i) {
        str[i] = s[i];
    }
    str[mySize] = '\0';
}

MyString::~MyString() {
    delete[] str;
}

void MyString::resize(size_t n) {
    if (n <= myCapacity) {
        mySize = n;
    } else {
        char *newStr = new char[n];
        for (size_t i = 0; i < mySize; ++i) {
            newStr[i] = str[i];
        }
        delete[] str;
        str = newStr;
        mySize = n;
        myCapacity = n;
    }
}

size_t MyString::capacity() const {
    return myCapacity;
}

size_t MyString::size() const {
    return mySize;
}

size_t MyString::length() const {
    return mySize;
}

const char *MyString::data() const {
    return str;
}

bool MyString::empty() const {
    return mySize == 0;
}

const char &MyString::front() const {
    if (mySize == 0) {
        throw std::out_of_range("MyString::front(): string is empty");
    }
    return str[0];
}

const char &MyString::at(size_t pos) const {
    if (pos >= mySize) {
        throw std::out_of_range("MyString::at(): position out of range");
    }
    return str[pos];
}

void MyString::clear() {
    delete[] str;
    str = nullptr;
    mySize = 0;
    myCapacity = 0;
}

std::ostream &operator<<(std::ostream &os, const MyString &str) {
    for (size_t i = 0; i < str.mySize; ++i) {
        os << str.str[i];
    }
    return os;
}

MyString &MyString::operator=(const MyString &other) {
    if (this != &other) {
        delete[] str;
        mySize = other.mySize;
        myCapacity = other.myCapacity;
        str = new char[myCapacity];
        for (size_t i = 0; i < mySize; ++i) {
            str[i] = other.str[i];
        }
        str[mySize] = '\0';
    }
    return *this;
}

MyString &MyString::operator+=(const MyString &other) {
    size_t newSize = mySize + other.mySize;
    if (newSize >= myCapacity) {
        myCapacity = newSize + 1;
        char *newStr = new char[myCapacity];
        for (size_t i = 0; i < mySize; ++i) {
            newStr[i] = str[i];
        }
        for (size_t i = 0; i < other.mySize; ++i) {
            newStr[mySize + i] = other.str[i];
        }
        newStr[newSize] = '\0';
        delete[] str;
        str = newStr;
    } else {
        for (size_t i = 0; i < other.mySize; ++i) {
            str[mySize + i] = other.str[i];
        }
        str[newSize] = '\0';
    }
    mySize = newSize;
    return *this;
}

size_t MyString::find(const MyString &subStr, size_t pos) const {
    if (pos > mySize) {
        return std::string::npos;
    }
    for (size_t i = pos; i <= mySize - subStr.mySize; ++i) {
        size_t j = 0;
        for (; j < subStr.mySize; ++j) {
            if (str[i + j] != subStr.str[j]) {
                break;
            }
        }
        if (j == subStr.mySize) {
            return i;
        }
    }
    return std::string::npos;
}