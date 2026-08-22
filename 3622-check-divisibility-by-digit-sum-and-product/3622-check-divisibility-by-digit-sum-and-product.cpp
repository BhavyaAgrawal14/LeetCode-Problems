class Solution {
public:
    bool checkDivisibility(int n) {
        long long sum = 0, mul = 1;
        int num = n;

        while(n > 0)
        {
            int a = n %10;
            sum += a;
            mul *= a;
            n /= 10;
        }

        sum += mul;

        if (num%sum == 0)
        {
            return true;
        }

        return false;
    }
};