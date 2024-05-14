#include <iostream>
#include <memory>
#include <initializer_list>

template<class Value>
class BinaryTree;

template<class Value>
class TreeNode {
public:
    TreeNode() = delete;
    explicit TreeNode(Value value) : value_{ value }, left_{ nullptr }, right_{ nullptr } {}

    TreeNode(const TreeNode<Value>& node) : 
            value_{ node.value_ }, left_{ nullptr }, right_{ nullptr } {
                if (node.left_) {
                    left_ = std::make_unique<TreeNode<Value>>(*node.left_);
                }

                if (node.right_) {
                    right_ = std::make_unique<TreeNode<Value>>(*node.right_);
                }
            }

    TreeNode(TreeNode<Value>&& node) noexcept :
            value_{ std::move(node.value_ ) }, 
            left_{ std::move(node.left_) },
            right_{ std::move(node.right_) } {}

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
    explicit BinaryTree(TreeNode<Value> node) : root_{ node } {}
    explicit BinaryTree(std::initializer_list<Value> values) {}
    explicit BinaryTree(std::initializer_list<TreeNode<Value>> nodes) {}
    
    void Insert(TreeNode<Value> node) {
        if (root_ == nullptr) {
            root_ = std::make_unique<TreeNode<Value>>(node);
            ++size_;
            return;
        }


    }

private:
    std::unique_ptr<TreeNode<Value>> root_;
    size_t size_ = 0;


};

int main() {
    TreeNode<int> node{ 5 };
    BinaryTree<int> tree;
    tree.Insert(node);
}