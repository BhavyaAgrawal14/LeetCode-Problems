class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {

        // Closest x-coordinate on rectangle
        int x = max(x1, min(xCenter, x2));

        // Closest y-coordinate on rectangle
        int y = max(y1, min(yCenter, y2));

        // Squared distance from circle center to closest point
        int dx = x - xCenter;
        int dy = y - yCenter;

        return dx * dx + dy * dy <= radius * radius;
    }
};