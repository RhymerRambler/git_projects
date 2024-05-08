#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
  int X[9][9] = {0};
  int N;
  vector<vector<string>> V;
  public:
        void pushResult()
        {
          std::vector<string> v;
          for (int i = 0; i < N; i++) {
            std::string s;
            for (int j = 0; j < N; j++) {
              s += ((X[i][j] == 1) ? 'Q' : '.');
            }
            v.push_back(s);
          }
          V.push_back(v);
        }

        bool canBePlaced(int row, int col) {
          for (int c = 0; c < N; c++) {
            if (c != col && X[row][c] == 1) return false;
          }
          for (int r = 0; r < N; r++) {
            if (r != row && X[r][col] == 1) return false;
          }
          // major diagonal direction
          int r = row-1, c = col-1;
          while(r >= 0 && c >= 0) {
            if (X[r][c]) return false;
            r--; c--;
          }
          r = row+1, c = col+1;
          while(r < N && c < N) {
            if (X[r][c]) return false;
            r++; c++;
          }
          // minor diagonal direction
          r = row-1, c = col+1;
          while(r >= 0 && c < N) {
            if (X[r][c]) return false;
            r--; c++;
          }
          r = row+1, c = col-1;
          while(r < N && c >= 0) {
            if (X[r][c]) return false;
            r++; c--;
          }
          return true;
        }

        void solveNQueensHelper(int row) {
           for (int col = 0; col < N; col++) {
             if (canBePlaced(row, col)) {
               X[row][col] = 1;
               if (row > 0) 
                 solveNQueensHelper(row-1);
               else
                 pushResult();
               X[row][col] = 0;
             }
           }
        }

        vector<vector<string>> solveNQueens(int n) {
          N = n;
          solveNQueensHelper(n-1);
          return V;
        }
};

int main()
{
  Solution s1;
  auto V = s1.solveNQueens(9);
  int i = 1;
  for (auto v : V) {
    std::cout << i << ":\n";
    for (auto ve : v) {
      std::cout << ve << std::endl;
    }
    i++;
  }
  return 0;
}
