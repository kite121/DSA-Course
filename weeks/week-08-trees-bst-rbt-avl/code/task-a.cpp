//Danil Elgin DSAI 04
#include <iostream>
#include <vector>
#include <string>
using namespace std;
template <typename T, typename K>
class Node {
    public:
    K value;
    T key;
    int height;
    Node<T, K>* left = nullptr;
    Node<T, K>* right = nullptr;
    Node(T key, K value) {
        this->key = key;
        this->value = value;
        this->height = 0;
    }
};
template <typename T, typename K>
class AVL_tree {
    int number_of_rotations = 0;
    public:
    int height(Node<T, K>*& node) {
        if (node == nullptr) {
            return -1;
        }
        return node->height;
    }
    void add(Node<T,K>*& current, T key, K value) {
        if (current == nullptr) {
            current = new Node<T, K>(key, value);
            return;
        }
        if (current->key == key) {
            cout << "KEY ALREADY EXISTS" << endl;
            return;
        }
        if (current->key > key) {
            add(current->left, key, value);
        }
        if (current->key < key) {
            add(current->right, key, value);
        }
        current->height = 1 + max(height(current->left), height(current->right));
        int balance = height(current->left) - height(current->right);
        if (balance > 1 && height(current->left->right) <= height(current->left->left)) {
            rightRotation(current);
            return;
        }
        if (balance > 1 && height(current->left->right) > height(current->left->left)) {
            leftRotation(current->left);
            rightRotation(current);
            return;
        }
        if (balance < -1 && height(current->right->left) <= height(current->right->right)) {
            leftRotation(current);
            return;
        }
        if (balance < -1 && height(current->right->left) > height(current->right->right)) {
            rightRotation(current->right);
            leftRotation(current);
            return;
        }
    }
    void rightRotation(Node<T, K>*& current) {
        number_of_rotations++;
        Node<T, K>* temp_2 = current->left;
        current->left = temp_2->right;
        temp_2->right = current;
        current->height = 1 + max(height(current->left), height(current->right));
        temp_2->height = 1 + max(height(temp_2->left), height(temp_2->right));
        current = temp_2;
    }

    void leftRotation(Node<T, K>*& current) {
        number_of_rotations++;
        Node<T, K>* temp_2 = current->right;
        current->right = temp_2->left;
        temp_2->left = current;
        current->height = 1 + max(height(current->left), height(current->right));
        temp_2->height = 1 + max(height(temp_2->left), height(temp_2->right));
        current = temp_2;
    }

    void deletion(Node<T, K>*& current, T key) {
        if (current == nullptr) {
            cout << "KEY NOT FOUND" << endl;
            return;
        }
        if (current->key > key) {
            deletion(current->left, key);
        }
        if (current->key < key) {
            deletion(current->right, key);
        }
        if (current->key == key) {
            if (current->left == nullptr && current->right == nullptr) {
                delete current;
                current = nullptr;
            }
            else if (current->left != nullptr && current->right == nullptr) {
                Node<T, K>* temp = current;
                current = current->left;
                delete temp;
            }
            else if (current->right != nullptr && current->left == nullptr) {
                Node<T, K>* temp = current;
                current = current->right;
                delete temp;
            }
            else if (current->left != nullptr && current->right != nullptr) {
                Node<T, K>* successor = search_successor(current);
                current->key = successor->key;
                current->value = successor->value;
                deletion(current->right, successor->key);
            }
        }
        if (current == nullptr) return;
        current->height = 1 + max(height(current->left), height(current->right));
        int balance = height(current->left) - height(current->right);
        if (balance > 1 && height(current->left->right) <= height(current->left->left)) {
            rightRotation(current);
            return;
        }
        if (balance > 1 && height(current->left->right) > height(current->left->left)) {
            leftRotation(current->left);
            rightRotation(current);
            return;
        }
        if (balance < -1 && height(current->right->left) <= height(current->right->right)) {
            leftRotation(current);
            return;
        }
        if (balance < -1 && height(current->right->left) > height(current->right->right)) {
            rightRotation(current->right);
            leftRotation(current);
            return;
        }
    }
    Node<T, K>* search_successor(Node<T, K>*& current) {
        Node<T, K>* temp = current->right;
        if (current->right == nullptr) return nullptr;
        while (temp ->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    };
    void LookUp(Node<T, K>*& current, T key) {
        if (current == nullptr) {
            cout << "KEY NOT FOUND" << endl;
            return;
        }
        if (current->key == key) {
            cout << current->value << endl;
            return;
        }
        if (current->key > key) {
            LookUp(current->left, key);
            return;
        }
        if (current->key < key) {
            LookUp(current->right, key);
        }
    }
    void Print_rotations() {
        cout << number_of_rotations << endl;
    }
};
int main() {
    int n;
    cin >> n;
    string operation;
    AVL_tree<int, int> tree;
    int key;
    int value;
    Node<int, int>* root = nullptr;
    for (int i = 0; i < n; i++) {
        cin >> operation;
        if (operation == "ADD") { cin >> key >> value; tree.add(root, key, value);}
        if (operation == "DELETE") {cin >> key; tree.deletion(root, key);}
        if (operation == "LOOKUP"){ cin >> key; tree.LookUp(root, key);}
        if (operation == "PRINT_ROTATIONS"){ tree.Print_rotations();}
        }
    }
