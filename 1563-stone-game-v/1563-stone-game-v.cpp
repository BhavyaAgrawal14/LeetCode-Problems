class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }

        vector<vector<long long>> dp(n, vector<long long>(n, 0));

        // length = size of current interval
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;

                for (int k = l; k < r; k++) {

                    long long leftSum =
                        prefix[k + 1] - prefix[l];

                    long long rightSum =
                        prefix[r + 1] - prefix[k + 1];

                    if (leftSum < rightSum) {
                        dp[l][r] = max(
                            dp[l][r],
                            leftSum + dp[l][k]
                        );
                    }
                    else if (leftSum > rightSum) {
                        dp[l][r] = max(
                            dp[l][r],
                            rightSum + dp[k + 1][r]
                        );
                    }
                    else {
                        dp[l][r] = max(
                            dp[l][r],
                            leftSum +
                            max(dp[l][k], dp[k + 1][r])
                        );
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};