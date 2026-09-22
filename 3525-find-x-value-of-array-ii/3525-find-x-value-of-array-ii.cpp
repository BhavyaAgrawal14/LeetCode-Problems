class Solution {
public:
    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int n, k;
    vector<Node> seg;

    Node mergeNodes(const Node& A, const Node& B) {
        Node C;

        C.prod = (A.prod * B.prod) % k;

        // Prefixes completely inside A
        for (int r = 0; r < k; r++) {
            C.cnt[r] += A.cnt[r];
        }

        // Prefixes = A + prefix of B
        for (int r = 0; r < k; r++) {
            int rem = (A.prod * r) % k;
            C.cnt[rem] += B.cnt[r];
        }

        return C;
    }

    void build(int node, int l, int r, const vector<int>& nums) {
        if (l == r) {
            int rem = nums[l] % k;

            seg[node].prod = rem;
            seg[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) >> 1;

        build(node << 1, l, mid, nums);
        build(node << 1 | 1, mid + 1, r, nums);

        seg[node] = mergeNodes(
            seg[node << 1],
            seg[node << 1 | 1]
        );
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            int rem = val % k;

            seg[node] = Node();
            seg[node].prod = rem;
            seg[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) >> 1;

        if (idx <= mid)
            update(node << 1, l, mid, idx, val);
        else
            update(node << 1 | 1, mid + 1, r, idx, val);

        seg[node] = mergeNodes(
            seg[node << 1],
            seg[node << 1 | 1]
        );
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[node];

        int mid = (l + r) >> 1;

        if (qr <= mid)
            return query(node << 1, l, mid, ql, qr);

        if (ql > mid)
            return query(node << 1 | 1, mid + 1, r, ql, qr);

        Node left = query(node << 1, l, mid, ql, qr);
        Node right = query(node << 1 | 1, mid + 1, r, ql, qr);

        return mergeNodes(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        n = nums.size();
        this->k = k;

        vector<int> ans;
        ans.reserve(queries.size());

        // IMPORTANT OPTIMIZATION
        if (k == 1) {
            for (auto &q : queries) {
                int start = q[2];

                // Every possible prefix has product 0 mod 1.
                // Number of non-empty prefixes = n - start.
                ans.push_back(n - start);
            }

            return ans;
        }

        seg.resize(4 * n);

        build(1, 0, n - 1, nums);

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};