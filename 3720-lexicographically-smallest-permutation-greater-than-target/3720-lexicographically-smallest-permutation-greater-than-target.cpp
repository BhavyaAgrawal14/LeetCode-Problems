class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> freq(26, 0);
        for (char c : s)
            freq[c - 'a']++;

        string ans = "";

        for (int i = 0; i < n; i++) {
            int cur = target[i] - 'a';

            // Try to make the first difference at position i.
            // Choose the SMALLEST character > target[i].
            for (int c = cur + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    string temp = target.substr(0, i);
                    temp += char('a' + c);

                    vector<int> remaining = freq;
                    remaining[c]--;

                    // Fill the rest in sorted order.
                    for (int x = 0; x < 26; x++) {
                        temp += string(remaining[x], char('a' + x));
                    }

                    // Since we process left -> right,
                    // a valid answer here is better than any
                    // answer found at an earlier position.
                    ans = temp;

                    // Only the smallest greater character is needed.
                    break;
                }
            }

            // Continue only if target[i] can be matched.
            if (freq[cur] == 0)
                break;

            freq[cur]--;
        }

        return ans;
    }
};