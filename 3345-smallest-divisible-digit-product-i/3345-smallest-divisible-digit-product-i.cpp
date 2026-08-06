class Solution {
public:
    int smallestNumber(int n, int t) {
        int x = n;

        while (true) {
            int temp = x;
            int mul = 1;

            while (temp > 0) {
                mul *= (temp % 10);
                temp /= 10;
            }

            if (mul % t == 0)
                return x;

            x++;
        }
    }
};