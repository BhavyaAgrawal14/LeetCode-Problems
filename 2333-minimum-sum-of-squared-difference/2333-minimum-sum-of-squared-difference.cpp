class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1,
                               vector<int>& nums2,
                               int k1, int k2) {
        int n = nums1.size();
        long long k = 1LL * k1 + k2;

        vector<int> diff(n);
        long long total = 0;
        int mx = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total += diff[i];
            mx = max(mx, diff[i]);
        }

        if (k >= total) return 0;

        int low = 0, high = mx;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long operations = 0;

            for (int d : diff) {
                if (d > mid)
                    operations += d - mid;
            }

            if (operations <= k)
                high = mid;
            else
                low = mid + 1;
        }

        int limit = low;
        long long remaining = k;
        long long ans = 0;

        for (int d : diff) {
            if (d > limit) {
                remaining -= d - limit;
                d = limit;
            }
            ans += 1LL * d * d;
        }

        // Apply leftover operations to differences equal to limit.
        for (int d : diff) {
            if (remaining == 0) break;

            if (d >= limit && d > 0) {
                ans -= 1LL * limit * limit;
                ans += 1LL * (limit - 1) * (limit - 1);
                remaining--;
            }
        }

        return ans;
    }
};