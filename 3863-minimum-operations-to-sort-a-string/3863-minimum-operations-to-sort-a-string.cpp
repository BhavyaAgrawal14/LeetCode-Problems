class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        if (is_sorted(s.begin(), s.end())) return 0;
        if (n == 2) return -1;

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        if (s[0] == mn || s[n - 1] == mx) return 1;

        // mn somewhere in s[0..n-2], or mx somewhere in s[1..n-1]
        if (s.find(mn) < (size_t)(n - 1)) return 2;
        if (s.rfind(mx) > 0) return 2;

        return 3;
    }
};