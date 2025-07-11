#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Leetcode problem: https://leetcode.com/problems/3sum/ */

// Demonstrates use of std algorithms: binary_search, lower_bound, sort and
// unique

class Solution {
    void get_zero_cases(vector<int>& nums, vector<int>::iterator itz, vector<vector<int>>& result)
    {
        int cnt = 0;
        while (itz != nums.end() && (*itz == 0 )) {
            ++itz;
            ++cnt;
        }
        if (cnt >= 3) result.push_back({0,0,0});
        for (auto it = itz; it != nums.end(); it++) {
            if (std::binary_search(nums.begin(), itz-1, -(*it))) {
                result.push_back({-(*it), 0, *it});
            }
        }
    }

    void get_two_pos_cases(vector<int>& nums, vector<int>::iterator itz, vector<vector<int>>& result)
    {
        while (itz != nums.end() && (*itz == 0 )) {
            ++itz;
        }
        for (auto it = itz; it != nums.end(); it++) {
            for (auto it2 = it+1; it2 != nums.end(); it2++) {
                auto sum = *it + *it2;
                if (std::binary_search(nums.begin(), itz, -sum)) {
                    result.push_back({-sum, *it, *it2});
                }
            }
        }
    }

    void get_two_neg_cases(vector<int>& nums, vector<int>::iterator itz, vector<vector<int>>& result)
    {
        for (auto it = nums.begin(); it != itz; it++) {
            for (auto it2 = it+1; it2 != itz; it2++) {
                auto sum = *it + *it2;
                if (std::binary_search(itz, nums.end(), -sum)) {
                    result.push_back({*it, *it2, -sum});
                }
            }
        }
    }

public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        std::sort(nums.begin(), nums.end());
        // lower_bound: gets the iterator of the first number in the range that is greater or
        // equal to the given value. Returns end() if not found
        auto it = std::lower_bound(nums.begin(), nums.end(), 0);
        bool zero_present = false;
        if (it != nums.end() && *it == 0) zero_present = true;
        // all negatives or positives
        if (it == nums.end() || (it == nums.begin() && *it != 0))
            return std::vector<std::vector<int>>();
        // one-pos, zero, one-neg
        if (zero_present) get_zero_cases(nums, it, result);
        // two-pos, one-neg
        get_two_pos_cases(nums, it, result);
        // two neg, one-pos
        get_two_neg_cases(nums, it, result);
        // sort with custom comparator - comparing triplets
        std::sort(result.begin(), result.end(), [](vector<int> x, vector<int> y) {
            if (x[0] < y[0]) return true;
            if ((x[0] == y[0]) && (x[1] < y[1])) return true;
            if ((x[0] == y[0]) && (x[1] == y[1]) && (x[2] < y[2])) return true;
            return false;
        });
        // unique: requires sorted range, and then it moves all the duplicates
        // towards the end, and returns the pointer to the start of the
        // duplicates, that can be later erased
        auto last_uniq = std::unique(result.begin(), result.end());
        result.erase(last_uniq, result.end());
        return result;
    }
};

void print(vector<vector<int>> v) {
  for (auto vec : v) {
    cout << "{" << vec[0] << ", " << vec[1] << ", " << vec[2] << "}, ";
  }
  cout << "\n";
}

int main()
{
  Solution s1;
  vector<int> v = {0, 0, 0};
  print(s1.threeSum(v));
  v = {-1,0,1,2,-1,-4};
  print(s1.threeSum(v));
  v = {-1,2,1,2,-1,-4};
  print(s1.threeSum(v));
}
