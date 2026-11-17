
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        // cost[i][j] = minimum changes to make s[i...j]
        // a semi-palindrome
        vector<vector<int>> cost(n, vector<int>(n, INF));

        // Precompute costs
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int len = j - i + 1;

                // Try every proper divisor
                for (int d = 1; d < len; d++) {

                    if (len % d != 0)
                        continue;

                    int changes = 0;

                    // Check each group
                    for (int r = 0; r < d; r++) {

                        int l = r;
                        int right = len - d + r;

                        // Compare mirrored positions
                        while (l < right) {
                            if (s[i + l] != s[i + right])
                                changes++;

                            l += d;
                            right -= d;
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // DP
        vector<vector<int>> dp(
            n + 1, vector<int>(k + 1, INF)
        );

        dp[0][0] = 0;

        for (int parts = 1; parts <= k; parts++) {

            for (int i = 2 * parts; i <= n; i++) {

                // Start index of last substring
                for (int p = 2 * (parts - 1);
                     p <= i - 2; p++) {

                    if (dp[p][parts - 1] == INF)
                        continue;

                    dp[i][parts] = min(
                        dp[i][parts],
                        dp[p][parts - 1] + cost[p][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
