class Solution {
public:
    int ans = 0;

    pair<int, int> dfs(TreeNode* root) {
        if (root == nullptr)
            return {0, 0};

        // Get sum and count of left subtree
        auto left = dfs(root->left);

        // Get sum and count of right subtree
        auto right = dfs(root->right);

        // Calculate sum and count of current subtree
        int sum = root->val + left.first + right.first;
        int count = 1 + left.second + right.second;

        // Check if current node equals floor(subtree average)
        if (root->val == sum / count)
            ans++;

        return {sum, count};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};