
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        // Step 1: Calculate free copies for each item
        vector<int> bonus(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j &&
                    items[j][0] % items[i][0] == 0) {
                    bonus[i]++;
                }
            }
        }

        // Step 2: DP
        vector<int> dp(budget + 1, 0);

        for (int i = 0; i < n; i++) {
            int p = items[i][1];
            int w = bonus[i];

            vector<int> ndp = dp;

            for (int b = p; b <= budget; b++) {

                // Buy first copy of this item
                ndp[b] = max(ndp[b],
                             dp[b - p] + 1 + w);

                // Buy additional copies
                ndp[b] = max(ndp[b],
                             ndp[b - p] + 1);
            }

            dp = ndp;
        }

        return dp[budget];
    }
};
