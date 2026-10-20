#include <vector>
#include <algorithm>

class Solution {
public:
    int sortableIntegers(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> sorted_nums = nums;
        std::sort(sorted_nums.begin(), sorted_nums.end());
        
        // Lambda to check if subarray A can be cyclically rotated to equal sorted subarray B
        auto canRotateToMatch = [](const std::vector<int>& A, const std::vector<int>& B, int k) {
            if (A == B) return true;
            
            int drops = 0;
            int drop_idx = -1;
            for (int j = 0; j < k; ++j) {
                if (A[j] > A[(j + 1) % k]) {
                    drops++;
                    drop_idx = j;
                }
            }
            
            if (drops == 0) {
                return A == B;
            } else if (drops == 1) {
                int shift = drop_idx + 1;
                for (int j = 0; j < k; ++j) {
                    if (A[(j + shift) % k] != B[j]) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        };

        // Find all divisors of n
        std::vector<int> divisors;
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                divisors.push_back(i);
                if (i * i != n) {
                    divisors.push_back(n / i);
                }
            }
        }
        
        int total_sum = 0;
        
        for (int k : divisors) {
            bool is_sortable = true;
            int m = n / k;
            
            for (int i = 0; i < m; ++i) {
                std::vector<int> A(nums.begin() + i * k, nums.begin() + (i + 1) * k);
                std::vector<int> B(sorted_nums.begin() + i * k, sorted_nums.begin() + (i + 1) * k);
                
                if (!canRotateToMatch(A, B, k)) {
                    is_sortable = false;
                    break;
                }
            }
            
            if (is_sortable) {
                total_sum += k;
            }
        }
        
        return total_sum;
    }
};