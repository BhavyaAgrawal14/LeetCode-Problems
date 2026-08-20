class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> v1, v2, ans;
        int n = nums.size();

        v1.push_back(nums[0]);
        v2.push_back(nums[1]);

        for (int i = 2; i < n; i++) {
            if (v1.back() > v2.back()) {
                v1.push_back(nums[i]);
            }
            else {
                v2.push_back(nums[i]);
            }
        }

        ans = v1;
        ans.insert(ans.end(), v2.begin(), v2.end());

        return ans;
    }
};