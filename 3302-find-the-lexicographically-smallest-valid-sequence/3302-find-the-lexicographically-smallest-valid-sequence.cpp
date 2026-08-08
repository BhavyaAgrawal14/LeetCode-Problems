#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        // Store 0-based indices for each character in word1
        vector<vector<int>> pos(26);
        for (int i = 0; i < n; ++i) {
            pos[word1[i] - 'a'].push_back(i);
        }

        // Compute suffix array: suffix[j] is the largest index in word1 
        // to match word2[j...m-1] with 0 mismatches.
        vector<int> suffix(m + 1);
        suffix[m] = n;
        for (int j = m - 1; j >= 0; --j) {
            int c = word2[j] - 'a';
            int limit = suffix[j + 1];
            auto it = lower_bound(pos[c].begin(), pos[c].end(), limit);
            if (it == pos[c].begin()) {
                suffix[j] = -1;
            } else {
                --it;
                suffix[j] = *it;
            }
        }

        // Compute pref array: pref[j] is the smallest index in word1 
        // to match word2[0...j] with 0 mismatches.
        vector<int> pref(m);
        int prev_idx = -1;
        for (int j = 0; j < m; ++j) {
            int c = word2[j] - 'a';
            auto it = upper_bound(pos[c].begin(), pos[c].end(), prev_idx);
            if (it == pos[c].end()) {
                for (int k = j; k < m; ++k) pref[k] = n + 1; // Infinity
                break;
            } else {
                pref[j] = *it;
                prev_idx = pref[j];
            }
        }

        auto get_pref = [&](int idx) -> int {
            if (idx < 0) return -1;
            return pref[idx];
        };

        int best_p = -1;
        bool any_valid = false;

        // Find the first mismatch position p that improves the sequence lexicographically
        for (int p = 0; p < m; ++p) {
            int p_prev = get_pref(p - 1);
            if (p_prev <= n && p_prev + 1 < suffix[p + 1]) {
                any_valid = true;
                if (p_prev + 1 < pref[p]) {
                    best_p = p;
                    break;
                }
            }
        }

        // If no mismatch strictly improves the sequence, check if pure exact match is valid
        if (best_p == -1) {
            if (pref[m - 1] < n) any_valid = true;
            if (!any_valid) return {};
            return pref;
        }

        // Construct result sequence using the optimal mismatch position `best_p`
        vector<int> ans(m);
        for (int j = 0; j < best_p; ++j) {
            ans[j] = pref[j];
        }
        ans[best_p] = get_pref(best_p - 1) + 1;
        
        int curr = ans[best_p];
        for (int j = best_p + 1; j < m; ++j) {
            int c = word2[j] - 'a';
            auto it = upper_bound(pos[c].begin(), pos[c].end(), curr);
            ans[j] = *it;
            curr = ans[j];
        }

        return ans;
    }
};