class Solution {
public:
    static const int LIM = 1000001;
    vector<int> primes;

    void sieve(int n) {
        vector<bool> isPrime(n + 1, true);
        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                if (1LL * i * i <= n) {
                    for (int j = i * i; j <= n; j += i)
                        isPrime[j] = false;
                }
            }
        }
    }

    int factExp(int n, int p) {
        int e = 0;
        while (n) {
            n /= p;
            e += n;
        }
        return e;
    }

    long long countWays(const vector<int>& cnt) {
        int total = 0;
        for (int x : cnt) total += x;

        long long ans = 1;

        for (int p : primes) {
            int e = factExp(total, p);
            for (int x : cnt)
                e -= factExp(x, p);

            while (e--) {
                if (ans > LIM / p) return LIM;
                ans *= p;
            }
        }

        return min(ans, 1LL * LIM);
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        vector<int> half(26, 0);
        string mid = "";
        int m = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            m += half[i];
            if (freq[i] & 1)
                mid.push_back(char('a' + i));
        }

        sieve(m);

        if (countWays(half) < k) return "";

        string left;

        for (int pos = 0; pos < m; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;
                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};