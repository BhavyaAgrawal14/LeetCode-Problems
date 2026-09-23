class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();

        long long total = 0;
        for (int num : nums)
            total += num;

        long long target = total - x;

        // If we need to keep nothing
        if (target == 0)
            return n;

        // Impossible to keep a subarray with negative sum
        if (target < 0)
            return -1;

        int left = 0;
        long long currSum = 0;
        int maxLen = -1;

        for (int right = 0; right < n; right++) {
            currSum += nums[right];

            // Shrink window if sum becomes too large
            while (left <= right && currSum > target) {
                currSum -= nums[left];
                left++;
            }

            // Found a subarray with required sum
            if (currSum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }

        if (maxLen == -1)
            return -1;

        return n - maxLen;
    }
};