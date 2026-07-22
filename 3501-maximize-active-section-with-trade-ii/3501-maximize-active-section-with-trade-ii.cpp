#pragma GCC optimize("O3", "unroll-loops")
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Replaced slow std::vector with highly optimized fixed-size arrays
    struct NodeZ {
        pair<long long, int> top[3];
        int sz = 0;
        void add(long long v, int id) {
            if (sz < 3) top[sz++] = {v, id};
        }
    };
    
    struct NodeO {
        pair<long long, int> top[3];
        int sz = 0;
        void add(long long v, int id) {
            if (sz < 3) top[sz++] = {v, id};
        }
    };

    // Fast stack-allocated merge for top 3 maximums
    NodeZ mergeZ(const NodeZ& a, const NodeZ& b) {
        pair<long long, int> temp[6];
        int t_sz = 0;
        for(int i = 0; i < a.sz; ++i) temp[t_sz++] = a.top[i];
        for(int i = 0; i < b.sz; ++i) temp[t_sz++] = b.top[i];
        
        // Simple insertion sort (descending) is extremely fast for <= 6 elements
        for(int i = 0; i < t_sz; ++i) {
            for(int j = i + 1; j < t_sz; ++j) {
                if(temp[i].first < temp[j].first) {
                    swap(temp[i], temp[j]);
                }
            }
        }
        
        NodeZ res;
        for(int i = 0; i < t_sz; ++i) {
            bool dup = false;
            for(int j = 0; j < res.sz; ++j) {
                if(res.top[j].second == temp[i].second) { dup = true; break; }
            }
            if(!dup) {
                res.top[res.sz++] = temp[i];
                if(res.sz == 3) break;
            }
        }
        return res;
    }

    // Fast stack-allocated merge for top 3 minimums
    NodeO mergeO(const NodeO& a, const NodeO& b) {
        pair<long long, int> temp[6];
        int t_sz = 0;
        for(int i = 0; i < a.sz; ++i) temp[t_sz++] = a.top[i];
        for(int i = 0; i < b.sz; ++i) temp[t_sz++] = b.top[i];
        
        // Simple insertion sort (ascending) is extremely fast for <= 6 elements
        for(int i = 0; i < t_sz; ++i) {
            for(int j = i + 1; j < t_sz; ++j) {
                if(temp[i].first > temp[j].first) {
                    swap(temp[i], temp[j]);
                }
            }
        }
        
        NodeO res;
        for(int i = 0; i < t_sz; ++i) {
            bool dup = false;
            for(int j = 0; j < res.sz; ++j) {
                if(res.top[j].second == temp[i].second) { dup = true; break; }
            }
            if(!dup) {
                res.top[res.sz++] = temp[i];
                if(res.sz == 3) break;
            }
        }
        return res;
    }

    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + (s[i] == '1' ? 1 : 0);
        }

        struct Block {
            int start, end;
            long long len;
        };
        
        vector<Block> B_arr;
        int i = 0;
        while (i < n) {
            if (s[i] == '0') {
                int j = i;
                while (j < n && s[j] == '0') j++;
                B_arr.push_back({i, j - 1, (long long)(j - i)});
                i = j;
            } else {
                i++;
            }
        }

        int K = B_arr.size();
        vector<long long> B(K);
        vector<long long> O(max(0, K - 1));
        vector<int> starts(K), ends(K);

        for (int idx = 0; idx < K; idx++) {
            B[idx] = B_arr[idx].len;
            starts[idx] = B_arr[idx].start;
            ends[idx] = B_arr[idx].end;
            if (idx < K - 1) {
                O[idx] = B_arr[idx+1].start - B_arr[idx].end - 1;
            }
        }

        int max_log = 18; // Reduced max_log to 18 (plenty for N=100,000)
        
        vector<vector<long long>> st_adj(K, vector<long long>(max_log, 0));
        if (K > 0) {
            for (int idx = 0; idx < K - 1; idx++) {
                st_adj[idx][0] = B[idx] + B[idx+1];
            }
            for (int j = 1; (1 << j) < K; j++) {
                for (int idx = 0; idx + (1 << j) - 1 < K - 1; idx++) {
                    st_adj[idx][j] = max(st_adj[idx][j-1], st_adj[idx + (1 << (j-1))][j-1]);
                }
            }
        }
        auto query_adj = [&](int L, int R) -> long long {
            if (L > R) return 0;
            int j = 31 - __builtin_clz(R - L + 1);
            return max(st_adj[L][j], st_adj[R - (1 << j) + 1][j]);
        };

        vector<vector<NodeZ>> st_B(max(1, K), vector<NodeZ>(max_log));
        for (int idx = 0; idx < K; idx++) {
            st_B[idx][0].add(B[idx], idx);
        }
        if (K > 0) {
            for (int j = 1; (1 << j) <= K; j++) {
                for (int idx = 0; idx + (1 << j) - 1 < K; idx++) {
                    st_B[idx][j] = mergeZ(st_B[idx][j-1], st_B[idx + (1 << (j-1))][j-1]);
                }
            }
        }
        auto query_B = [&](int L, int R) -> NodeZ {
            if (L > R) return NodeZ();
            int j = 31 - __builtin_clz(R - L + 1);
            return mergeZ(st_B[L][j], st_B[R - (1 << j) + 1][j]);
        };

        vector<vector<NodeO>> st_O(max(1, K), vector<NodeO>(max_log));
        for (int idx = 0; idx < K - 1; idx++) {
            st_O[idx][0].add(O[idx], idx);
        }
        if (K > 1) {
            for (int j = 1; (1 << j) <= K - 1; j++) {
                for (int idx = 0; idx + (1 << j) - 1 < K - 1; idx++) {
                    st_O[idx][j] = mergeO(st_O[idx][j-1], st_O[idx + (1 << (j-1))][j-1]);
                }
            }
        }
        auto query_O = [&](int L, int R) -> NodeO {
            if (L > R) return NodeO();
            int j = 31 - __builtin_clz(R - L + 1);
            return mergeO(st_O[L][j], st_O[R - (1 << j) + 1][j]);
        };

        vector<int> ans;
        ans.reserve(queries.size()); // Pre-allocate to prevent reallocation delays

        for (auto& q : queries) {
            int l = q[0], r = q[1];
            long long orig = pref[n]; 
            
            if (K == 0) {
                ans.push_back((int)orig);
                continue;
            }

            auto it = lower_bound(ends.begin(), ends.end(), l);
            if (it == ends.end()) {
                ans.push_back((int)orig);
                continue;
            }
            int a = distance(ends.begin(), it);
            if (starts[a] > r) {
                ans.push_back((int)orig);
                continue;
            }
            
            int b = upper_bound(starts.begin(), starts.end(), r) - starts.begin() - 1;
            
            if (a == b) {
                ans.push_back((int)orig);
                continue;
            }

            long long z_1 = min(ends[a], r) - max(starts[a], l) + 1;
            long long z_m = min(ends[b], r) - max(starts[b], l) + 1;

            long long v1 = 0;
            if (b == a + 1) {
                v1 = z_1 + z_m;
            } else {
                v1 = max(z_1 + B[a+1], B[b-1] + z_m);
                if (b - 2 >= a + 1) {
                    v1 = max(v1, query_adj(a + 1, b - 2));
                }
            }

            long long v2 = 0;
            NodeZ z_nodes = query_B(a + 1, b - 1);
            NodeZ ends_z;
            ends_z.add(z_1, a);
            ends_z.add(z_m, b);
            z_nodes = mergeZ(z_nodes, ends_z);

            NodeO o_nodes = query_O(a, b - 1);

            for (int iz = 0; iz < z_nodes.sz; iz++) {
                for (int io = 0; io < o_nodes.sz; io++) {
                    auto& z_cand = z_nodes.top[iz];
                    auto& o_cand = o_nodes.top[io];
                    if (z_cand.second != o_cand.second && z_cand.second != o_cand.second + 1) {
                        v2 = max(v2, z_cand.first - o_cand.first);
                    }
                }
            }

            long long max_add = max({0LL, v1, v2});
            ans.push_back((int)(orig + max_add));
        }

        return ans;
    }
};