class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();

        // land[d][i][j]: the non-mirror cell (encoded as i*n+j) where the robot ends up
        // when it tries to enter (i,j) moving in direction d (0 = right, 1 = down).
        // -1 means it leaves the grid, so the path is invalid.
        vector<vector<int>> land0(m + 1, vector<int>(n + 1, -1));
        vector<vector<int>> land1(m + 1, vector<int>(n + 1, -1));

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (grid[i][j] == 0) {
                    land0[i][j] = land1[i][j] = i * n + j;
                } else {
                    // entered moving right -> turned down, goes to (i+1, j), now moving down
                    land0[i][j] = land1[i + 1][j];
                    // entered moving down -> turned right, goes to (i, j+1), now moving right
                    land1[i][j] = land0[i][j + 1];
                }
            }
        }

        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 || dp[i][j] == 0) continue;

                // try moving right
                if (j + 1 < n) {
                    int t = land0[i][j + 1];
                    if (t != -1) {
                        int ti = t / n, tj = t % n;
                        dp[ti][tj] = (dp[ti][tj] + dp[i][j]) % MOD;
                    }
                }
                // try moving down
                if (i + 1 < m) {
                    int t = land1[i + 1][j];
                    if (t != -1) {
                        int ti = t / n, tj = t % n;
                        dp[ti][tj] = (dp[ti][tj] + dp[i][j]) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};