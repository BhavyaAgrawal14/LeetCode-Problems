class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long ans = 0;
        long long cost = 0;          // current cost of window [i, r]
        int r = n - 1;
        // deque of (value, count): blocks from left (front) to right (back)
        // each block: all elements in it are raised to 'value'
        // front = leftmost block
        deque<pair<long long, long long>> dq;

        for (int i = n - 1; i >= 0; --i) {
            // add nums[i] on the left
            long long cnt = 1;
            while (!dq.empty() && dq.front().first <= nums[i]) {
                // those blocks get raised to nums[i]
                cost += (long long)(nums[i] - dq.front().first) * dq.front().second;
                cnt += dq.front().second;
                dq.pop_front();
            }
            dq.push_front({nums[i], cnt});
            // note: the new element itself adds no cost (it equals its own max)

            // shrink right end while cost > k
            while (cost > k) {
                // remove nums[r] from the right
                auto &b = dq.back();
                cost -= (b.first - nums[r]);
                b.second--;
                if (b.second == 0) dq.pop_back();
                --r;
            }
            ans += r - i + 1;
        }
        return ans;
    }
};