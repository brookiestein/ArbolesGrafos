#include <algorithm>
#include <clocale>
#include <iostream>
#include <print>
#include <vector>

class PrimeTree
{
    struct Node
    {
        int value;
        Node *left;
        Node *right;

        explicit Node(int value)
            : value(value)
            , left(nullptr)
            , right(nullptr)
        {
        }
    };

    Node *root = nullptr;

    Node *insert(Node *node, int value)
    {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        }

        return node;
    }

    void inorder(Node *node) const
    {
        if (node == nullptr) {
            return;
        }

        inorder(node->left);
        std::print("{} ", node->value);
        inorder(node->right);
    }

    int countLeaves(Node *node) const
    {
        if (node == nullptr) {
            return 0;
        }

        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }

        return countLeaves(node->left) + countLeaves(node->right);
    }

    int calculateHeight(Node *node) const
    {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    void destroy(Node *node)
    {
        if (node == nullptr) {
            return;
        }

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

public:
    ~PrimeTree()
    {
        destroy(root);
    }

    void insert(int value)
    {
        root = insert(root, value);
    }

    void displayInorder() const
    {
        inorder(root);
        std::println();
    }

    int getLeafCount() const
    {
        return countLeaves(root);
    }

    int getHeight() const
    {
        return calculateHeight(root);
    }
};

int main()
{
    PrimeTree tree;

    const std::vector<int> primes = {2,  3,  5,  7,  11, 13, 17, 19,
                                     23, 29, 31, 37, 41, 43, 47};

    for (int prime : primes) {
        tree.insert(prime);
    }

    std::println("Primeros 15 números primos en inorden:");
    tree.displayInorder();

    std::println("\nCantidad de nodos hoja: {}", tree.getLeafCount());

    std::println("Altura del arbol: {}", tree.getHeight());

    return 0;
}
