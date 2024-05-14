#include <iostream>
#include <memory>

template<class Value>
class BinaryTree;

template<class Value>
class TreeNode {
public:
    TreeNode() = delete;
    explicit TreeNode(Value value) : value_{ value }, left_{ nullptr }, right_{ nullptr } {}
    explicit TreeNode(TreeNode<Value> node) :
                value_{ node.value_ }, left_{ node.left_ }, right_{ node.right_ } {}

private:
    Value value_;
    std::unique_ptr<TreeNode<Value>> left_;
    std::unique_ptr<TreeNode<Value>> right_;

    friend BinaryTree<Value>;
};

template<class Value>
class BinaryTree {
public:
    BinaryTree() = default;
    explicit BinaryTree(Node<Value> node) : root{ node } {}

private:
    TreeNode<Value> root;
};

int main() {

}