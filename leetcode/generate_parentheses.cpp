#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
  vector<string> vec;
  int N;
  public:
        void genParen(string& s, int cur_opened, int tot_opened) {
          if (cur_opened == 0 && tot_opened == N) { vec.push_back(s); return; }
          if (cur_opened == 0 && tot_opened < N) {
            s += '(';
            genParen(s, cur_opened+1, tot_opened+1);
          } else if (cur_opened > 0) {
            string tmp1 = s;
            if (tot_opened < N) {
              tmp1 += '(';
              genParen(tmp1, cur_opened+1, tot_opened+1);
            }
            string tmp2 = s;
            tmp2 += ')';
            genParen(tmp2, cur_opened-1, tot_opened); 
          }
        } 
        vector<string> generateParenthesis(int n) {
            N = n;
            string s = "";
            genParen(s, 0, 0);
            return vec;
        }
};

int main()
{
  Solution s;
  std::vector<string> x = s.generateParenthesis(10);
  for (auto& s : x) {
    cout << s << std::endl;
  }
  cout << "total: " << x.size() << endl;
}
