#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            __int128 prod = 1;
            long long g = 0;
            long long l = 1;

            for (int j = i; j < n; ++j) {
                long long x = nums[j];

                if (prod > (__int128)1e36 / x) {
                    break;
                }
                prod *= x;

                g = (j == i) ? x : std::gcd(g, x);
                l = std::lcm(l, x);

                if (prod == (__int128)l * (__int128)g) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};