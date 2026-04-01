#include <iostream>
using namespace std;

class Node {
public:
    int data[2];      // max 2 keys
    Node* child[3];   // max 3 children
    int n;            // number of keys

    Node() {
        n = 0;
        for (int i = 0; i < 3; i++)
            child[i] = NULL;
    }
};

class TwoThreeTree {
    Node* root;

    // Insert helper
    Node* insert(Node* node, int key, int &upKey) {
        if (node == NULL) {
            Node* newNode = new Node();
            newNode->data[0] = key;
            newNode->n = 1;
            return newNode;
        }

        // Leaf node
        if (node->child[0] == NULL) {
            if (node->n == 1) {
                // Insert in 2-node
                if (key < node->data[0]) {
                    node->data[1] = node->data[0];
                    node->data[0] = key;
                } else {
                    node->data[1] = key;
                }
                node->n = 2;
                return NULL;
            } else {
                // Split required
                int temp[3] = {node->data[0], node->data[1], key};

                // sort
                for (int i = 0; i < 3; i++)
                    for (int j = i + 1; j < 3; j++)
                        if (temp[i] > temp[j])
                            swap(temp[i], temp[j]);

                Node* newNode = new Node();
                node->data[0] = temp[0];
                node->n = 1;

                newNode->data[0] = temp[2];
                newNode->n = 1;

                upKey = temp[1];
                return newNode;
            }
        }

        // Internal node
        int pos;
        if (key < node->data[0]) pos = 0;
        else if (node->n == 1 || key < node->data[1]) pos = 1;
        else pos = 2;

        int newKey;
        Node* newChild = insert(node->child[pos], key, newKey);

        if (newChild == NULL) return NULL;

        // Insert newKey into node
        if (node->n == 1) {
            if (pos == 0) {
                node->data[1] = node->data[0];
                node->data[0] = newKey;

                node->child[2] = node->child[1];
                node->child[1] = newChild;
            } else {
                node->data[1] = newKey;
                node->child[2] = newChild;
            }
            node->n = 2;
            return NULL;
        } else {
            // Split internal node
            int temp[3] = {node->data[0], node->data[1], newKey};
            Node* tempChild[4] = {
                node->child[0], node->child[1], node->child[2], newChild
            };

            // sort keys
            for (int i = 0; i < 3; i++)
                for (int j = i + 1; j < 3; j++)
                    if (temp[i] > temp[j]) swap(temp[i], temp[j]);

            Node* newNode = new Node();

            node->data[0] = temp[0];
            node->n = 1;

            newNode->data[0] = temp[2];
            newNode->n = 1;

            upKey = temp[1];
            return newNode;
        }
    }

    void inorder(Node* node) {
        if (node == NULL) return;

        if (node->n == 1) {
            inorder(node->child[0]);
            cout << node->data[0] << " ";
            inorder(node->child[1]);
        } else {
            inorder(node->child[0]);
            cout << node->data[0] << " ";
            inorder(node->child[1]);
            cout << node->data[1] << " ";
            inorder(node->child[2]);
        }
    }

public:
    TwoThreeTree() { root = NULL; }

    void insert(int key) {
        int upKey;
        Node* newChild = insert(root, key, upKey);

        if (newChild != NULL) {
            Node* newRoot = new Node();
            newRoot->data[0] = upKey;
            newRoot->n = 1;
            newRoot->child[0] = root;
            newRoot->child[1] = newChild;
            root = newRoot;
        }
    }

    void display() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    TwoThreeTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);

    cout << "Inorder traversal:\n";
    tree.display();

    return 0;
}