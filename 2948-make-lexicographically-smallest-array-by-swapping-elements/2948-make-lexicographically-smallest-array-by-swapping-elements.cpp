class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<pair<int, int>> arr;
        for (int i = 0; i < n; i++)
            arr.push_back({nums[i], i});

        sort(arr.begin(), arr.end());

        vector<int> ans(n);

        int i = 0;
        while (i < n) {
            int j = i;

            // Find one connected group
            while (j + 1 < n && arr[j + 1].first - arr[j].first <= limit)
                j++;

            vector<int> indices;
            vector<int> values;

            for (int k = i; k <= j; k++) {
                values.push_back(arr[k].first);
                indices.push_back(arr[k].second);
            }

            sort(indices.begin(), indices.end());

            // Assign smallest values to smallest indices
            for (int k = 0; k < values.size(); k++)
                ans[indices[k]] = values[k];

            i = j + 1;
        }

        return ans;
    }
};