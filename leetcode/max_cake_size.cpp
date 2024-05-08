class Solution {
  public:
        int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
          std::sort(horizontalCuts.begin(), horizontalCuts.end());          
          std::sort(verticalCuts.begin(), verticalCuts.end());
          int maxh = 0;
          for (int i = 0; i < h-1; i++) {
            int diff = horizontalCuts[i+1] - horizontalCuts[i];
            if (diff > maxh) maxh = diff;
          }
          int maxw = 0;
          for (int i = 0; i < w-1; i++) {
            int diff = verticalCuts[i+1] - verticalCuts[i];
            if (diff > maxw) maxw = diff;
          }
          int mod = 10000 * 10000 * 10 + 7;
          maxh = maxh % mod;
          maxw = maxw % mod;
          return (maxh * maxw) % mod;
        }
};
