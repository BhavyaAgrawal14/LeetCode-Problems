class Solution {
public:
    string smallestNumber(string num, long long t) {
        int n = num.size();

        // factor t into 2^a * 3^b * 5^c * 7^d * r
        long long temp = t;
        int a = 0, b = 0, c = 0, d = 0;
        while (temp % 2 == 0) { temp /= 2; a++; }
        while (temp % 3 == 0) { temp /= 3; b++; }
        while (temp % 5 == 0) { temp /= 5; c++; }
        while (temp % 7 == 0) { temp /= 7; d++; }
        if (temp != 1) return "-1";

        int exp2[10] = {0,0,1,0,2,0,1,0,3,0};
        int exp3[10] = {0,0,0,1,0,0,1,0,0,2};
        int exp5[10] = {0,0,0,0,0,1,0,0,0,0};
        int exp7[10] = {0,0,0,0,0,0,0,1,0,0};

        // digit options (digit, e2, e3) ascending
        vector<array<int,3>> opts = {{2,1,0},{3,0,1},{4,2,0},{6,1,1},{8,3,0},{9,0,2}};

        const int INF = 1e9;
        vector<vector<int>> dp(a+1, vector<int>(b+1, INF));
        dp[0][0] = 0;
        for (int i = 0; i <= a; i++) {
            for (int j = 0; j <= b; j++) {
                if (i == 0 && j == 0) continue;
                int best = INF;
                for (auto &o : opts) {
                    int pi = max(0, i - o[1]);
                    int pj = max(0, j - o[2]);
                    if (dp[pi][pj] + 1 < best) best = dp[pi][pj] + 1;
                }
                dp[i][j] = best;
            }
        }

        auto build23 = [&](int ra, int rb) -> vector<int> {
            int k = dp[ra][rb];
            vector<int> res;
            int ci = ra, cj = rb, rem = k;
            for (int step = 0; step < k; step++) {
                for (auto &o : opts) {
                    int ni = max(0, ci - o[1]);
                    int nj = max(0, cj - o[2]);
                    if (dp[ni][nj] <= rem - 1) {
                        res.push_back(o[0]);
                        ci = ni; cj = nj; rem--;
                        break;
                    }
                }
            }
            return res;
        };

        int fz = num.find('0');
        if (fz == (int)string::npos) fz = n;

        vector<int> pre2(fz+1,0), pre3(fz+1,0), pre5(fz+1,0), pre7(fz+1,0);
        for (int i = 0; i < fz; i++) {
            int dg = num[i] - '0';
            pre2[i+1] = pre2[i] + exp2[dg];
            pre3[i+1] = pre3[i] + exp3[dg];
            pre5[i+1] = pre5[i] + exp5[dg];
            pre7[i+1] = pre7[i] + exp7[dg];
        }

        if (fz == n) {
            if (pre2[n] >= a && pre3[n] >= b && pre5[n] >= c && pre7[n] >= d) {
                return num;
            }
        }

        int hi = (fz < n) ? fz : n - 1;
        for (int p = hi; p >= 0; p--) {
            int baseA = pre2[p], baseB = pre3[p], baseC = pre5[p], baseD = pre7[p];
            int low = (fz < n && p == fz) ? 1 : (num[p] - '0' + 1);
            for (int D = low; D <= 9; D++) {
                int newA = baseA + exp2[D];
                int newB = baseB + exp3[D];
                int newC = baseC + exp5[D];
                int newD_ = baseD + exp7[D];
                int ra = max(0, a - newA);
                int rb = max(0, b - newB);
                int rc = max(0, c - newC);
                int rd = max(0, d - newD_);
                int m = n - 1 - p;
                int req = dp[ra][rb] + rc + rd;
                if (req <= m) {
                    vector<int> multiset = build23(ra, rb);
                    for (int i = 0; i < rc; i++) multiset.push_back(5);
                    for (int i = 0; i < rd; i++) multiset.push_back(7);
                    sort(multiset.begin(), multiset.end());
                    string suffix(m - req, '1');
                    for (int x : multiset) suffix += char('0' + x);
                    return num.substr(0, p) + char('0' + D) + suffix;
                }
            }
        }

        // extend length
        int k0 = dp[a][b] + c + d;
        int L = max(n + 1, k0);
        vector<int> multiset = build23(a, b);
        for (int i = 0; i < c; i++) multiset.push_back(5);
        for (int i = 0; i < d; i++) multiset.push_back(7);
        sort(multiset.begin(), multiset.end());
        string result(L - k0, '1');
        for (int x : multiset) result += char('0' + x);
        return result;
    }
};