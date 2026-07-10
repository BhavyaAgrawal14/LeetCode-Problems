class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++)
            a.push_back({nums[i], i});

        sort(a.begin(), a.end());

        vector<int> pos(n), comp(n);
        for (int i = 0; i < n; i++)
            pos[a[i].second] = i;

        int id = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first - a[i - 1].first > maxDiff)
                id++;
            comp[i] = id;
        }

        vector<int> reach(n);
        int j = 0;
        for (int i = 0; i < n; i++) {
            j = max(j, i);
            while (j + 1 < n && a[j + 1].first - a[i].first <= maxDiff)
                j++;
            reach[i] = j;
        }

        const int LOG = 17;
        vector<vector<int>> up(LOG + 1, vector<int>(n));
        up[0] = reach;

        for (int k = 1; k <= LOG; k++)
            for (int i = 0; i < n; i++)
                up[k][i] = up[k - 1][up[k - 1][i]];

        vector<int> ans;

        for (auto &q : queries) {
            int u = pos[q[0]], v = pos[q[1]];

            if (u == v) {
                ans.push_back(0);
                continue;
            }

            if (u > v)
                swap(u, v);

            if (comp[u] != comp[v]) {
                ans.push_back(-1);
                continue;
            }

            int cur = u, steps = 0;

            for (int k = LOG; k >= 0; k--) {
                if (up[k][cur] < v) {
                    steps += (1 << k);
                    cur = up[k][cur];
                }
            }

            ans.push_back(steps + 1);
        }

        return ans;
    }
};