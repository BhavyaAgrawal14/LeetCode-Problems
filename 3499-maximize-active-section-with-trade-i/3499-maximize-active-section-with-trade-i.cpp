class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int ones = 0;
        for (char c : s)
            if (c == '1') ones++;

        string t = "1" + s + "1";

        vector<char> ch;
        vector<int> len;

        for (char c : t) {
            if (ch.empty() || ch.back() != c) {
                ch.push_back(c);
                len.push_back(1);
            } else {
                len.back()++;
            }
        }

        int bestGain = 0;

        for (int i = 1; i + 1 < (int)ch.size(); i++) {
            if (ch[i] == '1' && ch[i - 1] == '0' && ch[i + 1] == '0') {
                bestGain = max(bestGain, len[i - 1] + len[i + 1]);
            }
        }

        return ones + bestGain;
    }
};