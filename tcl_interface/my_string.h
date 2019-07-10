#include <string>
#include <vector>

class MyString
{
   std::string buf;
   int len;
   public:
        MyString();
        MyString(const char* s);
        int length();
        char at(int pos);
        void set(int pos, char c);
        const char* get();
};

extern std::vector<MyString> my_strings_vec;

void addString(const char* s);
std::vector<MyString> getMyStrings();

