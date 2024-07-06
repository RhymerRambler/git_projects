#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

/*
 * MaxLen(Node) = max(MaxLen(Node->left), MaxLen(Node->right)) + 1;
 * Diameter(Node) = MaxLen(Node->left) + MaxLen(Node->right) 
 *
 */
class Solution {
public:
	int maxLenAndDia(TreeNode* node, int& dia) {
		if (node->left == nullptr && node->right == nullptr) {
			dia = 0;
			return 0;
		}
		int left_len = 0, left_dia = 0, right_len = 0, right_dia = 0;
		if (node->left) left_len = maxLenAndDia(node->left, left_dia) + 1; 
		if (node->right) right_len = maxLenAndDia(node->right, right_dia) + 1;
        dia = left_len + right_len;
		if (dia < left_dia)  dia = left_dia;
		if (dia < right_dia) dia = right_dia;
        // std::cout << "dia = " << dia << std::endl;
		return std::max(left_len, right_len);
	}
    int diameterOfBinaryTree(TreeNode* root) {
		int dia;
		maxLenAndDia(root, dia);
		return dia;
    }
};

int main()
{
	TreeNode* root = new TreeNode();
	root->left = new TreeNode();
	root->right = new TreeNode();
	root->left->left = new TreeNode();
	root->left->left->left = new TreeNode();
	root->left->left->left->left = new TreeNode();
	root->left->left->left->left->left = new TreeNode();
	//root->right->right = new TreeNode();
	root->left->right = new TreeNode();
	root->left->right->left = new TreeNode();
	root->left->right->left->right = new TreeNode();
	Solution s;
	std::cout  << s.diameterOfBinaryTree(root) << std::endl;
	return 0;
}
