
class Solution {
public:
    int digitSum(int x) {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        vector<pair<int, int>> arr;

        for (int x : nums) {
            arr.push_back({x, digitSum(x)});
        }

        // Sort by digit sum, then by number
        sort(arr.begin(), arr.end(), [](const auto& a, const auto& b) {
            if (a.second != b.second)
                return a.second < b.second;
            return a.first < b.first;
        });

        // Map each number to its original index
        unordered_map<int, int> index;
        for (int i = 0; i < n; i++) {
            index[nums[i]] = i;
        }

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || index[arr[i].first] == i)
                continue;

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = index[arr[j].first];
                cycleSize++;
            }

            swaps += cycleSize - 1;
        }

        return swaps;
    }
};
