class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int>lastseen;

        int left = 0, len = 0;

        for(int i = 0; i < s.size(); i++)
        {
            if(lastseen.find(s[i]) != lastseen.end())
            {
                left = max(left, lastseen[s[i]]+1);
            }

            lastseen[s[i]] = i;
            len = max(len, i-left+1);
        }
        
        return len;
       
    }
};