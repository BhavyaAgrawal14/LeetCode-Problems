
class Solution {
public:
    long long maximumSaleItems(vector<vector<int>>& items, int budget) {

        int n = items.size();

        // Step 1: Frequency of each factor
        vector<long long> freq(n + 1, 0);

        long long minPrice = LLONG_MAX;

        for (auto &it : items) {
            freq[it[0]]++;
            minPrice = min(minPrice, (long long)it[1]);
        }

        // Step 2: Count multiples for every factor
        vector<long long> multiples(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                multiples[i] += freq[j];
            }
        }

        // Step 3: Collect eligible double-benefit purchases
        vector<pair<long long, long long>> eligible;

        for (auto &it : items) {

            long long factor = it[0];
            long long price = it[1];

            long long capacity = multiples[factor] - 1;

            if (price < 2 * minPrice && capacity > 0) {
                eligible.push_back({price, capacity});
            }
        }

        // Step 4: Sort by purchase price
        sort(eligible.begin(), eligible.end());

        // Step 5: Build prefix count and prefix cost
        vector<long long> prefCount(eligible.size() + 1, 0);

        vector<__int128> prefCost(eligible.size() + 1, 0);

        for (int i = 0; i < (int)eligible.size(); i++) {

            long long price = eligible[i].first;
            long long capacity = eligible[i].second;

            prefCount[i + 1] = prefCount[i] + capacity;

            prefCost[i + 1] = prefCost[i] +
                              (__int128)price * capacity;
        }

        // Step 6: Calculate minimum cost for K copies
        auto minCost = [&](long long K) -> __int128 {

            long long t = min(K / 2, prefCount.back());

            // Find how many complete item groups to take
            int idx = upper_bound(
                prefCount.begin(),
                prefCount.end(),
                t
            ) - prefCount.begin() - 1;

            __int128 cost = prefCost[idx];

            // Remaining double-benefit purchases
            long long remaining = t - prefCount[idx];

            if (remaining > 0) {
                cost += (__int128)remaining *
                        eligible[idx].first;
            }

            // Remaining copies are ordinary purchases
            cost += (__int128)(K - 2 * t) * minPrice;

            return cost;
        };

        // Step 7: Binary search maximum possible copies
        long long low = 0;
        long long high = 2LL * (budget / minPrice);

        long long ans = 0;

        while (low <= high) {

            long long mid = low + (high - low) / 2;

            if (minCost(mid) <= budget) {
                ans = mid;
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        return ans;
    }
};
