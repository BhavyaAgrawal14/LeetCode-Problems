
class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int maxlen = 1;
        int minlen = 1;
        int ans = 1;

        for(int i = 1; i < nums.size(); i++)
        {
            if(nums[i-1] < nums[i])
            {
                maxlen++;
                minlen = 1;
            }
            else if(nums[i-1] > nums[i])
            {
                minlen++;
                maxlen = 1;
            }
            else
            {
                maxlen = 1;
                minlen = 1;
            }

            ans = max(ans, max(maxlen, minlen));
        }

        return ans;
    }
};
