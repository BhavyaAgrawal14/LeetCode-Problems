class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;

        function<void(string, int, int)> backtrack =
            [&](string curr, int open, int close) {

                // Used all brackets
                if (curr.size() == 2 * n) {
                    ans.push_back(curr);
                    return;
                }

                // Add opening bracket
                if (open < n) {
                    backtrack(curr + "(", open + 1, close);
                }

                // Add closing bracket only if valid
                if (close < open) {
                    backtrack(curr + ")", open, close + 1);
                }
            };

        backtrack("", 0, 0);
        return ans;
    }
};