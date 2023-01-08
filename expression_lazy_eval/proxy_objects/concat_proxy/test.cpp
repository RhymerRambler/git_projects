#include "concat_proxy.h"

ConcatProxy operator+(const StringWrap& s1, const StringWrap& s2)
{
  return ConcatProxy{s1.m_str, s2.m_str};
}

// implement concat_equal without create a temporary third string (a + b == c)
bool is_concat_equal (const std::string& a, const std::string& b, const std::string& c)
{
  return (a.size() + b.size() == c.size() &&
          std::equal(a.begin(), a.end(), c.begin()) &&
          std::equal(b.begin(), b.end(), c.begin()+a.size()));
}

bool operator== (ConcatProxy&& c, const StringWrap& s)
{
  return is_concat_equal(c.s1, c.s2, s.m_str);
}

int main()
{
  StringWrap s1{"hello "};
  StringWrap s2{"world"};
  StringWrap s3{"hello world"};
  return s1 + s2 == s3;
}
