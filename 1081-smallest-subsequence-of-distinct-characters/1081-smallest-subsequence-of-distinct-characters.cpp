class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        unordered_set<char> inStack;
        string st;

        for (char c : s) {
            freq[c - 'a']--;

            if (inStack.count(c))
                continue;

            while (!st.empty() &&
                   st.back() > c &&
                   freq[st.back() - 'a'] > 0) {
                inStack.erase(st.back());
                st.pop_back();
            }

            st.push_back(c);
            inStack.insert(c);
        }

        return st;
    }
};