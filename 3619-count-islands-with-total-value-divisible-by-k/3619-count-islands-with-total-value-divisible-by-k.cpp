
class Solution {
public:
    int m, n;

    long long dfs(int i, int j, vector<vector<int>>& grid) {
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 0)
            return 0;

        // Mark this cell as visited
        int val = grid[i][j];
        grid[i][j] = 0;

        return val
            + dfs(i + 1, j, grid)
            + dfs(i - 1, j, grid)
            + dfs(i, j + 1, grid)
            + dfs(i, j - 1, grid);
    }

    int countIslands(vector<vector<int>>& grid, int k) {
        m = grid.size();
        n = grid[0].size();

        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    long long sum = dfs(i, j, grid);

                    if (sum % k == 0)
                        count++;
                }
            }
        }

        return count;
    }
};
