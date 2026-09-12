class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> ids;
    };

    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return lexicographical_compare(
            a.ids.begin(), a.ids.end(),
            b.ids.begin(), b.ids.end()
        );
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {right, left, weight, original index}
        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][1],
                intervals[i][0],
                intervals[i][2],
                i
            };
        }

        // Sort by right endpoint
        sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
            if (x[0] != y[0])
                return x[0] < y[0];

            if (x[1] != y[1])
                return x[1] < y[1];

            return x[3] < y[3];
        });

        // For every interval, find the LAST interval
        // whose right endpoint is strictly before its left endpoint.
        vector<int> prev(n);

        vector<long long> rights(n);
        for (int i = 0; i < n; i++)
            rights[i] = a[i][0];

        for (int i = 0; i < n; i++) {
            // Need right < current left
            prev[i] =
                lower_bound(
                    rights.begin(),
                    rights.end(),
                    a[i][1]
                ) - rights.begin() - 1;
        }

        /*
         * dp[i][k] = best result using first i intervals
         * and choosing at most k.
         */
        vector<vector<State>> dp(n + 1, vector<State>(5));

        for (int i = 1; i <= n; i++) {
            int cur = i - 1;

            for (int k = 1; k <= 4; k++) {

                // Don't take current interval
                State skip = dp[i - 1][k];

                // Take current interval
                State take;
                take.score = a[cur][2];

                if (prev[cur] >= 0) {
                    take.score += dp[prev[cur] + 1][k - 1].score;
                    take.ids = dp[prev[cur] + 1][k - 1].ids;
                }

                take.ids.push_back((int)a[cur][3]);
                sort(take.ids.begin(), take.ids.end());

                dp[i][k] = better(take, skip) ? take : skip;
            }
        }

        return dp[n][4].ids;
    }
};