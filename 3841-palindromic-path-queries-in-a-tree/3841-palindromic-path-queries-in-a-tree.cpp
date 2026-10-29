#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> adj;
    vector<int> parent, depth, subtree, heavy;
    vector<int> head, pos, nodeMask;
    int timer = 0;

    vector<int> seg;

    void dfs(int u, int p) {
        parent[u] = p;
        subtree[u] = 1;
        int maxSize = 0;

        for (int v : adj[u]) {
            if (v == p) continue;

            depth[v] = depth[u] + 1;
            dfs(v, u);

            subtree[u] += subtree[v];

            if (subtree[v] > maxSize) {
                maxSize = subtree[v];
                heavy[u] = v;
            }
        }
    }

    void decompose(int u, int h) {
        head[u] = h;
        pos[u] = timer++;

        if (heavy[u] != -1) {
            decompose(heavy[u], h);
        }

        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            decompose(v, v);
        }
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            seg[idx] = nodeMask[l];
            return;
        }

        int mid = (l + r) / 2;
        build(idx * 2, l, mid);
        build(idx * 2 + 1, mid + 1, r);

        seg[idx] = seg[idx * 2] ^ seg[idx * 2 + 1];
    }

    void update(int idx, int l, int r, int p, int val) {
        if (l == r) {
            seg[idx] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (p <= mid)
            update(idx * 2, l, mid, p, val);
        else
            update(idx * 2 + 1, mid + 1, r, p, val);

        seg[idx] = seg[idx * 2] ^ seg[idx * 2 + 1];
    }

    int query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return seg[idx];

        int mid = (l + r) / 2;
        int res = 0;

        if (ql <= mid)
            res ^= query(idx * 2, l, mid, ql, qr);

        if (qr > mid)
            res ^= query(idx * 2 + 1, mid + 1, r, ql, qr);

        return res;
    }

    int pathQuery(int u, int v, int n) {
        int mask = 0;

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);

            mask ^= query(
                1, 0, n - 1,
                pos[head[u]], pos[u]
            );

            u = parent[head[u]];
        }

        if (depth[u] > depth[v])
            swap(u, v);

        mask ^= query(1, 0, n - 1, pos[u], pos[v]);

        return mask;
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        parent.assign(n, -1);
        depth.assign(n, 0);
        subtree.assign(n, 0);
        heavy.assign(n, -1);
        head.resize(n);
        pos.resize(n);
        nodeMask.resize(n);

        dfs(0, -1);
        decompose(0, 0);

        for (int u = 0; u < n; u++) {
            nodeMask[pos[u]] = 1 << (s[u] - 'a');
        }

        seg.assign(4 * n, 0);
        build(1, 0, n - 1);

        vector<bool> ans;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                s[u] = c;
                int mask = 1 << (c - 'a');

                update(1, 0, n - 1, pos[u], mask);
            } else {
                int v;
                ss >> v;

                int mask = pathQuery(u, v, n);

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};