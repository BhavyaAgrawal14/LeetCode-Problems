class Solution {
public:
    long long stoneGameVIII(vector<int>& stones) {
        int n = stones.size();

        vector<long long> pref(n);
        pref[0] = stones[0];

        for (int i = 1; i < n; i++) {
            pref[i] = pref[i - 1] + stones[i];
        }

        // best = max(pref[j] - dp[j])
        long long best = pref[n - 1];

        for (int i = n - 2; i >= 1; i--) {
            long long dp = best;
            best = max(best, pref[i] - dp);
        }

        // First move must take at least 2 stones,
        // hence prefix index >= 1.
        return best;
    }
};