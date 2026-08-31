class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1;
        int prev = -1;
        
        int minDist = INT_MAX;
        int maxDist = -1;

        ListNode* curr = head->next;
        ListNode* before = head;

        int pos = 1;   // curr's position

        while (curr->next != nullptr) {
            ListNode* after = curr->next;

            // Check if curr is a critical point
            if ((curr->val > before->val && curr->val > after->val) ||
                (curr->val < before->val && curr->val < after->val)) {

                if (first == -1) {
                    // First critical point
                    first = pos;
                } 
                else {
                    // Distance from previous critical point
                    minDist = min(minDist, pos - prev);

                    // Distance from first critical point
                    maxDist = max(maxDist, pos - first);
                }

                prev = pos;
            }

            before = curr;
            curr = after;
            pos++;
        }

        // Fewer than two critical points
        if (prev == first) {
            return {-1, -1};
        }

        return {minDist, maxDist};
    }
};