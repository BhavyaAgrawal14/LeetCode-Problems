class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        int zero = cnt[0];
        int one = cnt[1];
        int two = cnt[2];

        // Alice starts with a 1
        bool start1 = false;
        if (one > 0) {
            int a = one - 1;
            int b = two;

            int pairs = min(a, b);
            int len = 1 + 2 * pairs;

            a -= pairs;
            b -= pairs;

            if (a > 0) {
                len++;
                a--;
            }

            len += zero;

            if (len % 2 == 1 && a + b > 0)
                start1 = true;
        }

        // Alice starts with a 2
        bool start2 = false;
        if (two > 0) {
            int a = two - 1;
            int b = one;

            int pairs = min(a, b);
            int len = 1 + 2 * pairs;

            a -= pairs;
            b -= pairs;

            if (a > 0) {
                len++;
                a--;
            }

            len += zero;

            if (len % 2 == 1 && a + b > 0)
                start2 = true;
        }

        return start1 || start2;
    }
};