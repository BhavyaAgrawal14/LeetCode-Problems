#include <bits/stdc++.h>
using namespace std;

struct Node {
    int len;
    int pref, suff, best;
    char leftChar, rightChar;

    Node() {
        len = pref = suff = best = 0;
        leftChar = rightChar = '#';
    }

    Node(char c) {
        len = pref = suff = best = 1;
        leftChar = rightChar = c;
    }
};

class SegmentTree {
    vector<Node> tree;
    string s;
    int n;

    Node mergeNodes(const Node &a, const Node &b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        res.pref = a.pref;
        res.suff = b.suff;
        res.best = max(a.best, b.best);

        // If boundary characters are equal,
        // suffix of left + prefix of right can be joined.
        if (a.rightChar == b.leftChar) {
            res.best = max(res.best, a.suff + b.pref);

            // Entire left segment has the same character
            if (a.pref == a.len) {
                res.pref = a.len + b.pref;
            }

            // Entire right segment has the same character
            if (b.suff == b.len) {
                res.suff = b.len + a.suff;
            }
        }

        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = Node(s[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);

        tree[node] = mergeNodes(tree[2 * node],
                                tree[2 * node + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            tree[node] = Node(c);
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(2 * node, l, mid, idx, c);
        else
            update(2 * node + 1, mid + 1, r, idx, c);

        tree[node] = mergeNodes(tree[2 * node],
                                tree[2 * node + 1]);
    }

public:
    SegmentTree(string &str) {
        s = str;
        n = s.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    void update(int idx, char c) {
        update(1, 0, n - 1, idx, c);
    }

    int getBest() {
        return tree[1].best;
    }
};

class Solution {
public:
    vector<int> longestRepeating(string s,
                                 string queryCharacters,
                                 vector<int>& queryIndices) {
        
        SegmentTree st(s);

        vector<int> lengths;

        for (int i = 0; i < queryIndices.size(); i++) {
            st.update(queryIndices[i], queryCharacters[i]);
            lengths.push_back(st.getBest());
        }

        return lengths;
    }
};