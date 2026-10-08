class Solution {
public:
    string removeOuterParentheses(string s) {
        int count = 0;
        string s1 = "";

        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] == '(')
            {
                if(count > 0)
                {
                    s1 += s[i];
                }
                count++;
            }
            else
            {
                count--;

                if(count > 0)
                {
                    s1 += s[i];
                }
            }
        }

        return s1;
    }
};