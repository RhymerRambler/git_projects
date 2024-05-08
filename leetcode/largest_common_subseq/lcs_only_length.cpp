#include <iostream>
#ifdef USE_HASH_MAP
#include <unordered_map>
#else
#include <cstring>
#endif

#ifdef USE_HASH_MAP
std::unordered_map<std::string, int> seqmap;

std::string getkey(int i, int j) {
  return "i" + std::to_string(i) + "j" + std::to_string(j);
}
#else
int seqmap[1000][1000] = {0};
#endif

int lcs(int i, int j, const std::string& str1, const std::string& str2)
{

#ifdef USE_HASH_MAP
  auto it = seqmap.find(getkey(i, j));
  if (it != seqmap.end()) {
    return it->second;
  }
#else
  if (seqmap[i][j] > 0) return seqmap[i][j];
#endif
  if (i == str1.size() || j == str2.size()) return 0;
  if (str1[i] == str2[j]) {
    int len = lcs(i+1, j+1, str1, str2);
#ifdef USE_HASH_MAP
    seqmap[getkey(i,j)] = len+1;
#else
    seqmap[i][j] = len+1;
#endif
    return len+1;
  } else {
    auto len1 = lcs(i+1, j, str1, str2);
    auto len2 = lcs(i, j+1, str1, str2);
    if (len1 > len2) {
#ifdef USE_HASH_MAP
      seqmap[getkey(i,j)] = len1;
#else
      seqmap[i][j] = len1;
#endif
      return len1;
    } else {
#ifdef USE_HASH_MAP
      seqmap[getkey(i,j)] = len2;
#else
      seqmap[i][j] = len2;
#endif
      return len2;
    }
  }
}

int main()
{
  std::cout << lcs(0, 0, "abcabcdef", "xbcxxdef") << std::endl;
#ifdef USE_HASH_MAP
  seqmap.clear();
#else
  memset(seqmap, 0, 1000*1000*4);
#endif
  std::cout << lcs(0, 0, "abcdgh", "aedfhr") << std::endl;
#ifdef USE_HASH_MAP
  seqmap.clear();
#else
  memset(seqmap, 0, 1000*1000*4);
#endif
  std::cout << lcs(0, 0, "abcdgh", "xbaccd2acdgh") << std::endl;
  return 0;
}
