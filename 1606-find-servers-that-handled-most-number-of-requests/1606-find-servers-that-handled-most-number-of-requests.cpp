
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        // Available servers
        set<int> available;

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        // {finish_time, server_id}
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> busy;

        vector<int> count(k, 0);

        for (int i = 0; i < arrival.size(); i++) {

            // Free all servers whose requests are completed
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                int server = busy.top().second;
                busy.pop();

                available.insert(server);
            }

            // All servers are busy
            if (available.empty()) {
                continue;
            }

            int preferred = i % k;
            int server;

            // Find first available server >= preferred
            auto it = available.lower_bound(preferred);

            if (it == available.end()) {
                // Wrap around to the smallest available server
                it = available.begin();
            }

            server = *it;

            // Assign request
            available.erase(it);
            count[server]++;

            // Mark server as busy
            busy.push({(long long)arrival[i] + load[i], server});
        }

        // Find maximum number of handled requests
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
