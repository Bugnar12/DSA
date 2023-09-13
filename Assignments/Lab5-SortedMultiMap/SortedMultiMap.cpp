#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

/*Complexity :
 * Best case = Worst case = Theta(1)
 * */
SortedMultiMap::SortedMultiMap(Relation r) {
	this->root = nullptr;
    this->relation = r;
}

//void SortedMultiMap::add(TKey c, TValue v) {
//    Node* newNode = new Node;
//    newNode->key = c;
//    newNode->values.push_back(v);
//    newNode->left = nullptr;
//    newNode->right = nullptr;
//
//    ///check if the key exists in the BST
//    ///TRUE => CHEIE1<=CHEIE2
//    ///FALSE => CHEIE1>CHEIE2
//
//    if (root == nullptr) {
//        root = newNode;
//        return;
//    }
//
//    Node* currentNode = root;
//    Node* parentNode = nullptr;
//
//    while (currentNode != nullptr) {
//        if(currentNode->key == c) {
//            currentNode->values.push_back(v);
//            return;
//        }
//        else if (relation(currentNode->key, c)) {
//            parentNode = currentNode;
//            currentNode = currentNode->right;
//        }
//        else if(relation(c, currentNode->key)) {
//            parentNode = currentNode;
//            currentNode = currentNode->left;
//        }
//    }
//
//    if (relation(parentNode->key, c))
//        parentNode->right = newNode;
//    else if(relation(c, parentNode->key))
//        parentNode->left = newNode;
//
//}

/*Complexity :
 * Best case : Theta(log n)
 * Worst case : Theta(log n) -> if the tree is well-balanced, Theta(n) -> if the tree is not well balanced
 * Total complexity : Theta(log n) or O(n)
 * */
void SortedMultiMap::add(TKey c, TValue v) {
    Node* currentNode = root;
    Node* parentNode = nullptr;

    while (currentNode != nullptr) {
        if (currentNode->key == c) {
            currentNode->values.push_back(v);
            return;
        } else if (relation(currentNode->key, c)) {
            parentNode = currentNode;
            currentNode = currentNode->right;
        } else if (relation(c, currentNode->key)) {
            parentNode = currentNode;
            currentNode = currentNode->left;
        }
    }

    Node* newNode = new Node;
    newNode->key = c;
    newNode->values.push_back(v);
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (parentNode == nullptr) {
        root = newNode; ///means the tree is empty, so the root becomes the new node
    } else if (relation(parentNode->key, c)) {
        parentNode->right = newNode;
    } else if (relation(c, parentNode->key)) {
        parentNode->left = newNode;
    }
}

/*Complexity :
 * Best case : Theta(log n)
 * Worst case : Theta(log n) -> if the tree is well-balanced, Theta(n) -> if the tree is not well balanced
 * Total complexity : Theta(log n) or O(n)
 * */
vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> values;
    Node* currentNode = root;

    while (currentNode != nullptr) {
        if(currentNode->key == c) {
            values = currentNode->values;
            break;
        }
        else if (relation(currentNode->key, c))
            currentNode = currentNode->right;
        else if(relation(c, currentNode->key))
            currentNode = currentNode->left;
    }

    return values;
}

/*Complexity :
 * Best case : Theta(log n)
 * Worst case : Theta(log n) -> if the tree is well-balanced, Theta(n) -> if the tree is not well balanced
 * Total complexity : Theta(log n) or O(n)
 * */
bool SortedMultiMap::remove(TKey c, TValue v) {
    Node* currentNode = root;
    Node* parentNode = nullptr;

    while (currentNode != nullptr) {
        if(currentNode->key == c) {
            for (int i = 0; i < currentNode->values.size(); ++i) {
                if(currentNode->values[i] == v) {
                    currentNode->values.erase(currentNode->values.begin() + i);
                    if(currentNode->values.empty()) {
                        if(parentNode == nullptr) { ///it means the node to be removed is actually the root
                            root = nullptr;
                            delete currentNode;
                        }
                        else if(parentNode->left == currentNode) { ///left side key removed
                            parentNode->left = nullptr;
                            delete currentNode;
                        }
                        else if(parentNode->right == currentNode) { ///right side key removed
                            parentNode->right = nullptr;
                            delete currentNode;
                        }
                    }
                    return true;
                }
            }
            return false;
        }
        else if (relation(currentNode->key, c)) {
            parentNode = currentNode;
            currentNode = currentNode->right;
        }
        else if(relation(c, currentNode->key)) {
            parentNode = currentNode;
            currentNode = currentNode->left;
        }
    }

    return false;
}

/*Complexity :
 * Best case = Worst Case = Theta(n) -> considering a well-balanced tree
 * */
int SortedMultiMap::size() const {
    int count = 0;
    countPairs(this->root, count);
    return count;
}

/*Complexity : Best case = Worst case = Theta(1)
 * */
bool SortedMultiMap::isEmpty() const {
	return this->root == nullptr;
}

/*Complexity : Best case = Worst case = Theta(1)
 * */
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

/*Complexity : Best case = Worst case = Theta(1)
 * */
SortedMultiMap::~SortedMultiMap() {
	delete root;
}

void SortedMultiMap::countPairs(Node *node, int &count) const {
    if(node != nullptr)
    {
        count += node->values.size();
        countPairs(node->left, count);
        countPairs(node->right, count);
    }
}

/*Complexity:
 * Best case : Theta(n)
 * Worst case : Theta(n) -> if the tree is well-balanced
 * Total complexity : O(n)
 * */
vector<TKey> SortedMultiMap::keySet() const {
    vector<TKey> keys;
    countKeys(this->root, keys);
    return keys;
}

///helper function for counting the keys recursively
void SortedMultiMap::countKeys(Node *node, vector<TKey> &keys) const {
    if(node == nullptr)
        return;
    countKeys(node->left, keys);
    keys.push_back(node->key);
    countKeys(node->right, keys);
}
