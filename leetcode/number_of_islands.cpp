#include <iostream>
#include <vector>
using namespace std;

class Solution {
  int M, N;
  public:
        void markLand(vector<vector<char>>& grid, int i, int j) {
          grid[i][j] = '/';
          if (i < M - 1 && grid[i+1][j] == '1') markLand(grid, i+1, j);
          if (j < N - 1 && grid[i][j+1] == '1') markLand(grid, i, j+1);
        }

        int numIslands(vector<vector<char>>& grid) {
          M = grid.size();
          N = grid[0].size();
          int cnt = 0;
          for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
              if (grid[i][j] <= '0') continue;
              markLand(grid, i, j);
              cnt++;
            }
          }
          return cnt;
        }
};

int main()
{
  Solution s;
  std::vector<std::vector<char>> grid {
      {'1','1','0','0','0'},
      {'1','1','0','0','0'},
      {'0','0','1','0','0'},
      {'0','0','0','1','1'}
  };
  std::cout << "num-islands = " << s.numIslands(grid) << endl;
  return 0;
}
