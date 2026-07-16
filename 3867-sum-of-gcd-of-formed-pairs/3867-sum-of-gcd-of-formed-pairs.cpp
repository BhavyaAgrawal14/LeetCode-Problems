class Solution {
public:
    long long gcdSum(vector<int>& nums) {

        vector<long long> prefixgcd(nums.size());

        long long mx = nums[0];
        for (int i = 0; i < nums.size(); i++) 
        {
            mx = max(mx, (long long)nums[i]);
            prefixgcd[i] = gcd((long long)nums[i], mx);
        }

        sort(prefixgcd.rbegin(), prefixgcd.rend());

        int n = nums.size() / 2;
        int m = nums.size() - 1;
        long long sum = 0;

        for (int i = 0; i < n; i++) 
        {
            sum += gcd(prefixgcd[i], prefixgcd[m - i]);
        }

        return sum;
    }
};