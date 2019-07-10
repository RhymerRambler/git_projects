#include "my_string.h"

std::vector<MyString> my_strings_vec;

MyString::MyString() {
    buf = "";
    len = 0;
}

MyString::MyString(const char* s) {
  buf = s;
  buf = "my." + buf;
  len = buf.length();
}

int MyString::length() { return len; }

char MyString::at(int i) { return buf[i]; }

void MyString::set(int i, char c) { buf[i] = c; }

const char* MyString::get() { return buf.c_str(); }

void addString(const char* s)
{
   my_strings_vec.emplace_back(s);
}

std::vector<MyString> getMyStrings()
{
   return my_strings_vec;
}
