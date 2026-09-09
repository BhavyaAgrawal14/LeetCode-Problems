class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;
        long long commas = 1;
        
        for(long long i = 1000; i <= n; i *= 1000) {
            long long last = min(n, i * 1000 - 1);
            ans += (last - i + 1) * commas;
            commas++;
        }
        
        return ans;
    }
};