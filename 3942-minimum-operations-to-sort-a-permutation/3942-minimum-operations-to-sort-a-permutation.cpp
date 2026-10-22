class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int k = nums[0];
        const int INF = INT_MAX;
        int best = INF;

        // Case 1: cyclic ascending, nums[i] == (k + i) % n
        bool asc = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] != (k + i) % n) {
                asc = false;
                break;
            }
        }
        if (asc) {
            if (k == 0) best = 0;
            else best = min(n - k, k + 2);
        }

        // Case 2: cyclic descending, nums[i] == (k - i) mod n
        bool desc = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] != ((k - i) % n + n) % n) {
                desc = false;
                break;
            }
        }
        if (desc) {
            int a = (k + 1) % n;
            best = min(best, 1 + min(a, (n - a) % n));
        }

        return best == INF ? -1 : best;
    }
};