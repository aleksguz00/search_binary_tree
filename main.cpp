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
                left_ = other.left_.release();
            }

            if (other.right_) {
                right_ = other.left_.release();
            }
        }

    Node(Node&& other) : 
        data_{ std::move(other.data_) },
        left_{ std::move(other.left_) },
        right_{ std::move(other.right_) } {}

private:
    Value data_;
    std::unique_ptr<Node<Value>> left_;
    std::unique_ptr<Node<Value>> right_;

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

    void Print() const {
        PrintTree_(root_);
        std::cout << '\n';
    }

private:
    std::unique_ptr<Node<Value>> root_;

    void InsertNode_(
        std::unique_ptr<Node<Value>>& node,
        Value data
    ) {
        if (!node) {
            node = std::make_unique<Node<Value>>(data);
            return;
        }

        if (data < node->data_) {
            InsertNode_(node->left_, data);
        }
        else {
            InsertNode_(node->right_, data);
        }
    }

    void PrintTree_(const std::unique_ptr<Node<Value>>& node) const {
        if (node) {
            PrintTree_(node->left_);
            std::cout << node->data_ << " ";
            PrintTree_(node->right_);
        }
    }
};

int main() {
    BinaryTree<int> tree;
    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(7);
    tree.Insert(1);
    tree.Insert(777);

    tree.Print();
}





















// struct Node {
//     int data;
//     Node *left;
//     Node *right;
// };

// class BinarySearchTree {
// private:
//     Node *root;

//     Node* insertNode(Node *node, int data) {
//         if (node == nullptr) {
//             return new Node{data, nullptr, nullptr};
//         } else {
//             if (data <= node->data) {
//                 node->left = insertNode(node->left, data);
//             } else {
//                 node->right = insertNode(node->right, data);
//             }
//         }

//         return node;
//     }

//     void printTree(Node *node) {
//         if (node != nullptr) {
//             printTree(node->left);
//             cout << node->data << " ";
//             printTree(node->right);
//         }
//     }

// public:
//     BinarySearchTree() : root(nullptr) {}

//     void insert(int data) {
//         root = insertNode(root, data);
//     }

//     void printInOrder() {
//         printTree(root);
//         cout << endl;
//     }
// };

// int main() {
//     BinarySearchTree bst;

//     bst.insert(10);
//     bst.insert(5);
//     bst.insert(15);
//     bst.insert(3);
//     bst.insert(7);

//     cout << "In-order traversal: ";
//     bst.printInOrder();

//     return 0;
// }