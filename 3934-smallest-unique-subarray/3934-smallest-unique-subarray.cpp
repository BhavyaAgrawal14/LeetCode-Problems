#include <vector>
#include <unordered_map>
#include <cstdint>

using namespace std;

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        
        // Double hashing parameters to avoid collisions
        const uint64_t MOD1 = 1000000007ULL;
        const uint64_t MOD2 = 1000000009ULL;
        const uint64_t BASE1 = 1315423911ULL % MOD1;
        const uint64_t BASE2 = 2654435761ULL % MOD2;
        
        vector<uint64_t> p1(n + 1, 1), p2(n + 1, 1);
        vector<uint64_t> h1(n + 1, 0), h2(n + 1, 0);
        
        // Precompute powers and prefix hashes
        for (int i = 0; i < n; ++i) {
            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
            
            h1[i + 1] = (h1[i] * BASE1 + nums[i]) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + nums[i]) % MOD2;
        }
        
        // Helper lambda to check if there is at least one unique subarray of length len
        auto hasUnique = [&](int len) -> bool {
            int countSubarrays = n - len + 1;
            unordered_map<uint64_t, int> freq;
            freq.reserve(countSubarrays);
            
            for (int i = 0; i < countSubarrays; ++i) {
                uint64_t sub1 = (h1[i + len] + MOD1 - (h1[i] * p1[len]) % MOD1) % MOD1;
                uint64_t sub2 = (h2[i + len] + MOD2 - (h2[i] * p2[len]) % MOD2) % MOD2;
                
                // Combine both 32-bit hashes into a single 64-bit key
                uint64_t combinedHash = (sub1 << 32) | sub2;
                freq[combinedHash]++;
            }
            
            for (const auto& [hashVal, count] : freq) {
                if (count == 1) return true;
            }
            return false;
        };
        
        // Binary search for the minimum valid length
        int low = 1, high = n, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hasUnique(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return ans;
    }
};