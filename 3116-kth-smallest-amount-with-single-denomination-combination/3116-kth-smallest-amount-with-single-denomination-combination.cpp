class Solution {
public:
    long long countValid(long long x, vector<int>& coins) {
        int n = coins.size();
        long long count = 0;

        for (int mask = 1; mask < (1 << n); mask++) {
            long long l = 1;
            int bits = 0;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    l = l / gcd(l, (long long)coins[i]) * coins[i];

                    if (l > x)
                        break;
                }
            }

            if (l > x)
                continue;

            long long ways = x / l;

            if (bits % 2 == 1)
                count += ways;
            else
                count -= ways;
        }

        return count;
    }

    long long findKthSmallest(vector<int>& coins, long long k) {
        long long low = 1;
        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (countValid(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};