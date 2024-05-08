#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, std::string> seqmap;

std::string getkey(int i, int j) {
  return "i" + std::to_string(i) + "j" + std::to_string(j);
}

std::string lcs(const std::string& str1, const std::string& str2, int i, int j)
{
  auto it = seqmap.find(getkey(i, j));
  if (it != seqmap.end()) {
    return it->second;
  }
  if (i == str1.size() || j == str2.size()) return "";
  if (str1[i] ==  str2[j]) {
    std::string seq = lcs(str1, str2, i+1, j+1);
    seq.insert(seq.begin(), str1[i]);
    seqmap[getkey(i,j)] = seq;
    return seq;
  } else {
    auto seq1 = lcs(str1, str2, i+1, j);
    auto seq2 = lcs(str1, str2, i, j+1);
    if (seq1.size() > seq2.size()) {
      seqmap[getkey(i,j)] = seq1;
      return seq1;
    } else {
      seqmap[getkey(i,j)] = seq2;
      return seq2;
    }
  }
}

int main()
{
  std::cout << lcs("abcabcdef", "xbcxxdef", 0, 0) << std::endl;
  seqmap.clear();
  std::cout << lcs("abcdgh", "aedfhr", 0, 0) << std::endl;
  seqmap.clear();
  std::cout << lcs("abcdgh", "xbaccd2acdgh", 0, 0) << std::endl;
  return 0;
}
