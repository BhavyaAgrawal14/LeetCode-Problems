class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<int>ans;

        int x = nums[0];

        for(int i = 1; i < nums.size(); i++)
        {
            int prev = nums[i-1];
            int curr = nums[i];

            for(int x = prev + 1; x < curr; x++) 
            {
                ans.push_back(x);
            }
        }

        return ans;
    }
};