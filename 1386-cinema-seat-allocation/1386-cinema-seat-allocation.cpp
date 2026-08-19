class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, unordered_set<int>> reserved;

        // Store reserved seats row-wise
        for (auto &v : reservedSeats) {
            reserved[v[0]].insert(v[1]);
        }

        // Every completely empty row can accommodate 2 groups
        int ans = 2 * n;

        for (auto &[row, seats] : reserved) {

            bool left = true;    // seats 2,3,4,5
            bool middle = true;  // seats 4,5,6,7
            bool right = true;   // seats 6,7,8,9

            // Check left block
            for (int s = 2; s <= 5; s++) {
                if (seats.count(s)) {
                    left = false;
                    break;
                }
            }

            // Check middle block
            for (int s = 4; s <= 7; s++) {
                if (seats.count(s)) {
                    middle = false;
                    break;
                }
            }

            // Check right block
            for (int s = 6; s <= 9; s++) {
                if (seats.count(s)) {
                    right = false;
                    break;
                }
            }

            int groups = 0;

            if (left && right) {
                // Both non-overlapping blocks can be used
                groups = 2;
            }
            else if (left || middle || right) {
                // At least one block is possible
                groups = 1;
            }

            // We had initially counted this row as 2
            ans -= (2 - groups);
        }

        return ans;
    }
};