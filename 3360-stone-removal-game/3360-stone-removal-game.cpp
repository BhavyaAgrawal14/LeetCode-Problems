
class Solution {
public:
    bool canAliceWin(int n) {
        int stones = 10;
        bool aliceTurn = true;

        while (n >= stones) {
            n -= stones;
            aliceTurn = !aliceTurn;
            stones--;
        }

        return !aliceTurn;
    }
};
