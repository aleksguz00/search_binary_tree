#include <iostream>
#include <memory>
#include <initializer_list>

template<class Value>
class BinaryTree;

template <class Value>
class Node {
public:
    Node() = delete;

    explicit Node(Value data) : 
        data_{ data }, left_{ nullptr }, right_{ nullptr } {}

    Node(const Node& other) : 
        data_{ other.data_ }, left_{ nullptr }, right_{ nullptr } {
            if (other.left_) { 
                left_ = other.left_;
            }

            if (other.right_) {
                right_ = other.right_;
            }
        }

    Node(Node&& other) : 
        data_{ std::move(other.data_) },
        left_{ std::move(other.left_) },
        right_{ std::move(other.right_) } {}

private:
    Value data_;
    std::shared_ptr<Node<Value>> left_;
    std::shared_ptr<Node<Value>> right_;

    friend BinaryTree<Value>;
};

template <class Value>
class BinaryTree {
public:
    BinaryTree() = default;

    explicit BinaryTree(Node<Value> node) :
        root_{ std::make_unique<Node<Value>>(node) } {}

    explicit BinaryTree(Value data) :
        root_{ std::make_unique<Node<Value>>(data) } {}

    void Insert(Value data) {
        InsertNode_(root_, data);
    }

    void Delete(Value data) {
        DeleteNode_(root_, data);
    }

    void Print() const {
        PrintTree_(root_);
        std::cout << '\n';
    }

    bool Search(Value data) const {
        return Search_(root_, data);
    }

    Value Min() const {
        return GetMin_(root_)->data_;
    }

    Value Max() const {
        return GetMax_(root_)->data_;
    }

private:
    std::shared_ptr<Node<Value>> root_;

    void InsertNode_(
        std::shared_ptr<Node<Value>>& node,
        Value data
    ) {
        if (!node) {
            node = std::make_shared<Node<Value>>(data);
            return;
        }

        if (data < node->data_) {
            InsertNode_(node->left_, data);
        }
        else {
            InsertNode_(node->right_, data);
        }
    }

    std::shared_ptr<Node<Value>> DeleteNode_(
        std::shared_ptr<Node<Value>>& node,
        Value data
    ) {
        if (!node) return nullptr;
        else if (data < node->data_) node->left_ = DeleteNode_(node->left_, data);
        else if (data > node->data_) node->right_ = DeleteNode_(node->right_, data);
        else {
            if (!node->left_ || !node->right_) {
                node = (!node->left_) ? node->right_ : node->left_;
            }
            else {
                auto left_max = GetMax_(node->left_);
                node->data_ = left_max->data_;
                node->right_ = DeleteNode_(node->right_, left_max->data_);
            }
        }

        return node;
    }

    void PrintTree_(const std::shared_ptr<Node<Value>>& node) const {
        if (node) {
            PrintTree_(node->left_);
            std::cout << node->data_ << " ";
            PrintTree_(node->right_);
        }
    }

    bool Search_(const std::shared_ptr<Node<Value>>& node, Value data) const {
        if (!node) return false;
        if (node->data_ == data) return true;

        return (data < node->data_) ? Search_(node->left_, data) : Search_(node->right_, data);
    }

    std::shared_ptr<Node<Value>> GetMin_(const std::shared_ptr<Node<Value>>& node) const {
        if (!node) throw std::out_of_range("Tree is empty");

        if (!node->left_) return node;

        return GetMin_(node->left_);
    }

    std::shared_ptr<Node<Value>> GetMax_(const std::shared_ptr<Node<Value>>& node) const {
        if (!node) throw std::out_of_range("Tree is empty");

        if (!node->right_) return node;

        return GetMax_(node->right_);
    }
};

int main() {
    BinaryTree<int> tree;
    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(7);
    tree.Insert(1);
    tree.Insert(777);
    tree.Insert(9912);
    tree.Insert(-50);

    tree.Print();

    tree.Delete(777);

    tree.Print();

    std::cout << tree.Min() << '\n';
}