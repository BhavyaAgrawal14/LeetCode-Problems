class Solution {
public:
    vector<vector<int>> adj, newAdj;
    vector<int> last, ans;

    void dfs1(int u, string &s, vector<int> &newParent) {
        int c = s[u] - 'a';
        int prev = last[c];

        if (prev != -1) {
            newParent[u] = prev;
        }

        last[c] = u;

        for (int v : adj[u]) {
            dfs1(v, s, newParent);
        }

        last[c] = prev;
    }

    int dfs2(int u) {
        int size = 1;

        for (int v : newAdj[u]) {
            size += dfs2(v);
        }

        ans[u] = size;
        return size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        adj.assign(n, {});
        newAdj.assign(n, {});
        last.assign(26, -1);
        ans.assign(n, 0);

        // Build original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        // Find new parents
        vector<int> newParent = parent;
        dfs1(0, s, newParent);

        // Build modified tree
        for (int i = 1; i < n; i++) {
            newAdj[newParent[i]].push_back(i);
        }

        // Calculate subtree sizes
        dfs2(0);

        return ans;
    }
};