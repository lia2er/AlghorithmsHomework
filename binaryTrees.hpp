#pragma once
#include <iostream>

using namespace std;

struct TreeNode {
  int data;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

TreeNode *Insert(TreeNode *root, int value) {
  if (root == nullptr) return new TreeNode(value);
  if (value < root->data) root->left = Insert(root->left, value);
  else if (value > root->data) root->right = Insert(root->right, value);
  return root;
}

bool Search(TreeNode *root, int value) {
  if (root == nullptr) return false;
  if (value == root->data) return true;
  else if (value < root->data) return Search(root->left, value);
  else return Search(root->right, value);
}

void InOrderTraversal(TreeNode *root) {
  if (root != nullptr) {
    InOrderTraversal(root->left);
    cout << root->data << " ";
    InOrderTraversal(root->right);
  }
}

TreeNode *Delete(TreeNode *root, int value) {
  if (root == nullptr) return root;
  if (value < root->data) root->left = Delete(root->left, value);
  else if (value > root->data) root->right = Delete(root->right, value);
  else {
    if (root->left == nullptr) {
      TreeNode *temp = root->right;
      delete root;
      return temp;
    }
    else if (root->right == nullptr) {
      TreeNode *temp = root->left;
      delete root;
      return temp;
    }
    TreeNode *temp = root->right;
    while (temp->left != nullptr) temp = temp->left;
    root->data = temp->data;
    root->right = Delete(root->right, temp->data);
  }
  return root;
}

void DeleteTree(TreeNode *root) {
  if (root != nullptr) {
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
  }
}
