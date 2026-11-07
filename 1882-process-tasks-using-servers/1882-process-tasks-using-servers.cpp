
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > available;

        priority_queue<
            tuple<long long,int,int>,
            vector<tuple<long long,int,int>>,
            greater<tuple<long long,int,int>>
        > busy;

        int n = servers.size();
        int m = tasks.size();

        vector<int> ans(m);

        for(int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        long long time = 0;

        for(int j = 0; j < m; j++) {

            // Time cannot go backwards
            time = max(time, (long long)j);

            // Release all servers that are free
            while(!busy.empty() && get<0>(busy.top()) <= time) {

                auto [freeTime, weight, idx] = busy.top();
                busy.pop();

                available.push({weight, idx});
            }

            // If all servers are busy, jump to earliest free time
            if(available.empty()) {

                time = get<0>(busy.top());

                while(!busy.empty() && get<0>(busy.top()) <= time) {

                    auto [freeTime, weight, idx] = busy.top();
                    busy.pop();

                    available.push({weight, idx});
                }
            }

            // Assign the task to the best available server
            auto [weight, idx] = available.top();
            available.pop();

            ans[j] = idx;

            // Update server's next available time
            busy.push({time + tasks[j], weight, idx});
        }

        return ans;
    }
};
