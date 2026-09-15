class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        // pal[i][j] = true if s[i...j] is a palindrome
        vector<vector<bool>> pal(n, vector<bool>(n, false));

        // Length 1
        for (int i = 0; i < n; i++)
            pal[i][i] = true;

        // Length >= 2
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;

                if (s[i] == s[j]) {
                    if (len == 2)
                        pal[i][j] = true;
                    else
                        pal[i][j] = pal[i + 1][j - 1];
                }
            }
        }

        // dp[i] = answer for first i characters
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            // Don't select a substring ending at i-1
            dp[i] = dp[i - 1];

            // Try every substring ending at i-1
            for (int j = 0; j <= i - k; j++) {
                if (pal[j][i - 1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        return dp[n];
    }
};