#pragma once

#include <string>

// holds const references to the std::string's whose concat is expected to be
// used later on
struct ConcatProxy
{
  const std::string& s1;
  const std::string& s2;
};

// Wrapper to std::string, to provide a special operator +
// that just creates a ConcatProxy instead of actually adding them
class StringWrap
{
public:
  StringWrap(std::string _s) : m_str(std::move(_s)) { }
  std::string m_str;
};

