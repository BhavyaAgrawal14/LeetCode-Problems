
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class Solution {
    multiset<ll> low, high;
    ll sumLow = 0, sumHigh = 0;

    void add(ll x) {
        if (low.empty() || x <= *low.rbegin()) {
            low.insert(x);
            sumLow += x;
        } else {
            high.insert(x);
            sumHigh += x;
        }

        balance();
    }

    void remove(ll x) {
        auto it = low.find(x);

        if (it != low.end()) {
            sumLow -= x;
            low.erase(it);
        } else {
            it = high.find(x);
            sumHigh -= x;
            high.erase(it);
        }

        balance();
    }

    void balance() {
        while (low.size() > high.size() + 1) {
            auto it = prev(low.end());
            ll x = *it;

            low.erase(it);
            sumLow -= x;

            high.insert(x);
            sumHigh += x;
        }

        while (low.size() < high.size()) {
            auto it = high.begin();
            ll x = *it;

            high.erase(it);
            sumHigh -= x;

            low.insert(x);
            sumLow += x;
        }
    }

    ll getCost() {
        ll med = *low.rbegin();

        return med * (ll)low.size() - sumLow
             + sumHigh - med * (ll)high.size();
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<ll> cost(n - x + 1);

        // Calculate cost of every window.
        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }

        // DP: dp[j] = minimum cost to select j windows.
        const ll INF = LLONG_MAX / 4;

        vector<ll> dp(k + 1, INF);
        dp[0] = 0;

        for (int i = 0; i <= n - x; i++) {
            for (int j = k; j >= 1; j--) {
                if (i == 0) {
                    if (j == 1)
                        dp[j] = min(dp[j], cost[i]);
                    continue;
                }

                // Previous window must end before this one starts.
                // dp is indexed by number of windows, so we need
                // a position-aware DP for non-overlapping windows.
            }
        }

        // Position-aware DP with rolling rows.
        vector<vector<ll>> dummy; 
        vector<ll> prev(n + 1, 0), curr(n + 1, INF);

        // dp[j][i] = minimum cost for j windows in first i elements.
        vector<vector<ll>> D(k + 1, vector<ll>(n + 1, INF));

        for (int i = 0; i <= n; i++)
            D[0][i] = 0;

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i <= n; i++) {
                D[j][i] = D[j][i - 1];

                if (i >= x && D[j - 1][i - x] != INF) {
                    D[j][i] = min(
                        D[j][i],
                        D[j - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return D[k][n];
    }
};
