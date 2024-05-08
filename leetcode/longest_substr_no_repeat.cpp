class Solution {
    int flag[255] = {0};
public:
    int lengthOfLongestSubstring(string s) {
        unsigned int len = s.length();
        int last = 0;
        int maxlen = 0;
        for (int i = 0; i < len; i++) {
            if (i != 0) flag[s[i-1]] = 0;
            int j = last;
            for (; j < len; j++) {
                if (flag[s[j]] == 1) break;
                flag[s[j]] = 1;
            }
            if ((j - i) > maxlen) maxlen = j - i;
            last = j;
        }
        return maxlen;
    }
};
