class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();

        int leftSum = 0, rightSum = 0;
        int leftQ = 0, rightQ = 0;

        for (int i = 0; i < n / 2; i++) {
            if (num[i] == '?')
                leftQ++;
            else
                leftSum += num[i] - '0';
        }

        for (int i = n / 2; i < n; i++) {
            if (num[i] == '?')
                rightQ++;
            else
                rightSum += num[i] - '0';
        }

        int diffQ = leftQ - rightQ;
        int diffSum = leftSum - rightSum;

        // Odd difference in number of '?' means
        // Alice can always force a win.
        if (abs(diffQ) % 2 == 1)
            return true;

        // Bob can force equality.
        if (diffSum == -9 * (diffQ / 2))
            return false;

        // Otherwise Alice wins.
        return true;
    }
};