class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);  // Base index
        int ans = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } 
            else {
                st.pop();

                if (st.empty()) {
                    // Current ')' cannot be matched
                    st.push(i);
                } 
                else {
                    // Length of valid substring
                    ans = max(ans, i - st.top());
                }
            }
        }

        return ans;
    }
};