class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        sort(nums.rbegin(), nums.rend());

        int mul = max((nums[0]*nums[1]*nums[2]), (nums[0]*nums[nums.size()-1]*nums[nums.size()-2]));

        return mul;
    }
};