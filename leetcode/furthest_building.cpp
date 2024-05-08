#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution1 {
public:
    int furthestBuildingHelper(vector<int>& heights, int idx, int bricks, int ladders) {
       if (idx == heights.size() - 1) return idx;
       auto diff = heights[idx+1] - heights[idx];
       while (diff <= 0) {
           idx ++;
           if (idx == heights.size()-1) return idx;
           diff = heights[idx+1] - heights[idx];
       }
       int next = idx;
       if (diff <= bricks) {
          next = furthestBuildingHelper(heights, idx+1, bricks-diff, ladders);
       }
       if (ladders > 0) {
          auto tmp = furthestBuildingHelper(heights, idx+1, bricks, ladders-1);
          if (tmp > next) next = tmp;
       }
       return next;
    }   
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
       return furthestBuildingHelper(heights, 0, bricks, ladders);
    }   
};

class Solution2 {
    priority_queue <int, vector<int>, greater<int> > diffs;
public:
    int furthestBuilding(const vector<int>& heights, int bricks, int ladders) {
		int c = heights.size()-1;
        int bsum = 0;
		for (int i = 0; i < c; i++) {
           int diff = heights[i+1] - heights[i];
           if (diff <= 0) continue;
           diffs.push(diff);
           if (diffs.size() > ladders) {
              bsum += diffs.top();
              diffs.pop();
              if (bsum > bricks) return i;
              if (bsum == bricks) return i+1;
           }
        }
        return c;
    }   
};

int main()
{
  Solution2 s;
  std::cout << s.furthestBuilding({4,2,7,6,9,14,12}, 5, 1) << std::endl;
  Solution2 s2;
  std::cout << s2.furthestBuilding({2,7,9,12}, 5, 1) << std::endl;
  return 0;
}
