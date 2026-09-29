class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Valid parentheses string must have even length
        if ((m + n - 1) % 2 == 1)
            return false;

        // First character must be '('
        if (grid[0][0] == ')')
            return false;

        // Last character must be ')'
        if (grid[m - 1][n - 1] == '(')
            return false;

        // dp[i][j][balance]
        vector<vector<vector<bool>>> dp(
            m, vector<vector<bool>>(
                n, vector<bool>(m + n, false)
            )
        );

        // Starting cell
        dp[0][0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Skip starting cell
                if (i == 0 && j == 0)
                    continue;

                int change = (grid[i][j] == '(') ? 1 : -1;

                for (int balance = 0; balance <= m + n; balance++) {

                    int prevBalance = balance - change;

                    if (prevBalance < 0)
                        continue;

                    // Coming from above
                    if (i > 0 && dp[i - 1][j][prevBalance])
                        dp[i][j][balance] = true;

                    // Coming from left
                    if (j > 0 && dp[i][j - 1][prevBalance])
                        dp[i][j][balance] = true;
                }
            }
        }

        // Valid string must finish with balance 0
        return dp[m - 1][n - 1][0];
    }
};