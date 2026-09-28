class Solution {
public:
    int maxDepth(string s) {
        int depth = 0, count = 0;

        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] == '(')
            {
                count++;
            }
            else if(s[i] == ')')
            {
                depth = max(depth, count);
                count--;
            }
            else
            {
                continue;
            }
        }

        return depth;
    }
};