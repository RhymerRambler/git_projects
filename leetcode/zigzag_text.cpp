#include <iostream>
#include <string>
using namespace std;


class Solution {
  public:
        string convert(string s, int row, int numRows) {
          if (numRows <= 1) return s;
          string result = string(1, s[row]);
          int offset1 = 2 * (numRows - row - 1);
          int offset2 = 2 * row;
          int i = row, len = s.length();
          int offset = offset1;
          bool is_vertical = 1;
          while (i+offset < len) {
            if (offset > 0) {
              i += offset;
              result += s[i];
            }
            if (is_vertical) {
              offset = offset2;
            } else {
              offset = offset1;
            }
            is_vertical = !is_vertical;
          }
          return result;
        }
        string convert(string s, int numRows) {
          string result;
          if (numRows > s.length()) return s;
          for (int i = 0; i < numRows; i++) {
            result += convert(s, i, numRows);
          }
          return result;
        }
};

int main() {
  string s = "PAYPALISHIRING";
  std::cout << s << std::endl;
  std::cout << (new Solution())->convert(s, 1) << std::endl;
  std::cout << (new Solution())->convert(s, 2) << std::endl;
  std::cout << (new Solution())->convert(s, 3) << std::endl;
  std::cout << (new Solution())->convert(s, 4) << std::endl;
  std::cout << (new Solution())->convert(s, 20) << std::endl;
  return 0;
}
