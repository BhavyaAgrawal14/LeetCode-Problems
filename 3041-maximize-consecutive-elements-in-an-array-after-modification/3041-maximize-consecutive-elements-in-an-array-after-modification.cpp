#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        unordered_map<int, int> dp;
        int ans = 1;

        for (int x : nums) {
            // Compute both candidates from the state before this element
            int takeUp   = dp[x] + 1;      // becomes x + 1, extends run ending at x
            int takeSame = dp[x - 1] + 1;  // stays x, extends run ending at x - 1

            dp[x + 1] = max(dp[x + 1], takeUp);
            dp[x]     = max(dp[x], takeSame);

            ans = max({ans, dp[x], dp[x + 1]});
        }
        return ans;
    }
};