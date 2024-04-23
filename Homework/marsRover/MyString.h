// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class MyString{
    private:
        char *str;
        size_t mySize;
        size_t myCapacity;
    public:
        MyString();
        MyString(const MyString &str);
        MyString(const char *s);

        ~MyString();

        void resize(size_t n);
        size_t capacity() const;
        size_t size() const;
        size_t length() const;
        const char* data() const;
        bool empty() const;
        const char& front() const;
        const char& at(size_t pos) const;
        void clear();
        friend std::ostream& operator<<(std::ostream& os, const MyString& str);
        MyString& operator=(const MyString& str);
        MyString& operator+=(const MyString& str);
        size_t find(const MyString& str, size_t pos = 0) const;
};

#endif