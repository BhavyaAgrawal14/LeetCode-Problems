class Solution {
public:
    int countCommas(int n) {
        int ans = 0;
        int commas = 1;
        
        for(int i = 1000; i <= n; i *= 1000) {
            int last = min(n, i * 1000 - 1);
            ans += (last - i + 1) * commas;
            commas++;
        }
        
        return ans;
    }
};