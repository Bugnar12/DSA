#include "SMMIterator.h"
#include "SortedMultiMap.h"


/*Constructor : traverses to the leftmost node in the BST, and push each node in the stack
 * Complexity:
 * Best case : Theta(1) - only one iteration
 * Worst case : Theta(log n) - assuming that the tree is quite well balanced
 * Total complexity : O(log n)
 * */
SMMIterator::SMMIterator(const SortedMultiMap& map) : map(map)
{
    // Initialize the iterator by traversing to the leftmost node
    Node* currentNode = map.root;
    while (currentNode != nullptr) {
        stack.push(StackElement(currentNode, 0));
        currentNode = currentNode->left;
    }
}

/*The same as for the constructor
 * */
void SMMIterator::first() {
    // Reset the iterator by traversing to the leftmost node
    stack = std::stack<StackElement>();
    Node* currentNode = map.root;
    while (currentNode != nullptr) {
        stack.push(StackElement(currentNode, 0));
        currentNode = currentNode->left;
    }
}

/*Next() : retrives the top of the stack, and checks if we still have values that should be pushed for the corresponding key
 * Complexity :
 * Best case : Theta(1)
 * Worst case : Theta(log n)
 * Total complexity : O(log n)
 * */
void SMMIterator::next() {
    if (!valid()) {
        throw std::exception();
    }

    StackElement currentElement = stack.top();
    stack.pop();

    Node* currentNode = currentElement.node;
    int currentIndex = currentElement.index;

    if (currentIndex + 1 < currentNode->values.size()) {
        // there are more values for the current key
        stack.push(StackElement(currentNode, currentIndex + 1));
    } else {
        // Move to the right subtree
        Node* nextNode = currentNode->right;
        while (nextNode != nullptr) {
            stack.push(StackElement(nextNode, 0));
            nextNode = nextNode->left;
        }
    }
}

/*Complexity :
 * Best case = Worst case = Total compexity = Theta(1)
 * */
bool SMMIterator::valid() const {
    return !stack.empty();
}

/*Complexity:
 * Best case = Worst case = Total complexity = Theta(1)
 * */
TElem SMMIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception();
    }

    Node* currentNode = stack.top().node;
    return std::make_pair(currentNode->key, currentNode->values[stack.top().index]);
}



