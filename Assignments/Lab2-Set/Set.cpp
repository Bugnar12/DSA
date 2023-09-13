#include "Set.h"
#include "SetITerator.h"


///Total complexity : Theta(1)
Set::Set() {
	this->head = nullptr;
    this->length = 0;
}

///Complexity
///Best case : Theta(1) if head is the null pointer
///Average case : Theta(n) if the element is available for adding or if we find a duplicate on the last position ( we can't assume nothing)
///Worst case : Theta(n) if the element must be added at the last position
///Total complexity : O(n)
bool Set::add(TElem elem) {
    Node* new_node = new Node; ///create a new node that will be added
    new_node->info = elem; ///the info field gets TElem elem
    new_node->next = nullptr; ///the next field gets nullptr since we do not know where it will be added yet

    if (head == nullptr) ///means the linked list is empty
    {
        head = new_node;
        this->length++;
        return true;
    }
    if(head->info == elem) ///means that the element is already in the list
        return false;

    Node* current = head;
    while(current->next != nullptr)
    {
        current = current->next;
        if(current->info == elem) /// if an element is found with the same value return false
            return false;
    }
    current->next = new_node;
    this->length++;
    return true;
}

///Complexity :
///Best case : Theta(1) -> if head is must be deleted
///Average case : Theta(n) -> do not have any information where the desired element to be deleted might be
///Worst case : Theta(n) -> if the element we want to delete is "on the last position"
///Total complexity : O(n)
bool Set::remove(TElem elem) {
    if(head == nullptr) ///if there are no elements => nothing can be removed
        return false;
    if(head->info == elem) ///in this case we must change the head with the next element in the list
    {
        Node* oldHead = head; ///make a copy of the head that is desired to be deleted
        head = head->next;
        delete oldHead;
        this->length--;
        return true;
    }
	Node* current = head;
    while(current->next != nullptr)
    {
        if(current->next->info == elem) ///this means that the next element is the one desired to be deleted
        {
            Node* oldElement = current->next; ///make a copy of the element that will be deleted
            current->next = oldElement->next; ///the next of the current element becomes the next of the deleted element
            delete oldElement;
            this->length--;
            return true;
        }
        current = current->next;
    }
	return false;
}

///Best case : Theta(1) -> when the wanted element is in the address of node, only one iteration
///Worst case : Theta(n) -> when the wanted element is not in the list, thus the whole list will be parsed and false will be returned
///Average case : Theta(n/2) = Theta(n) -> element is in the list, but no information about its position
///Total complexity : O(n)
bool Set::search(TElem elem) const {
    Node* current_node = head;
    while(current_node != nullptr) {
        if (current_node->info == elem)
            return true;
        current_node = current_node->next;
    }
    return false;
}

///Theta(1)
int Set::size() const {
	return this->length;
}

///Theta(1)
bool Set::isEmpty() const {
	if (this->length == 0)
        return true;
    return false;
}

///Complexity :
///Best case : Theta(1) -> the "currentNode" is nullptr thus nothing needs to be deallocated
///Average/Worst case : Theta(n) -> when we have some elements to deallocate
///Total complexity : O(n)
Set::~Set() {
	///need to parse the list and delete all nodes
    Node* currentNode = this->head; ///currentNode of type pointer gets the head( for parsing the entire linkedlist )
    while(currentNode != nullptr) ///while we haven't reach the last node ( which points to nullptr)
    {
        Node *temp = currentNode; ///make a copy of the current node
        currentNode = currentNode->next; ///the current node goes to the next
        delete temp; ///delete the copy of the previous node aka. the first node
    }
}


SetIterator Set::iterator() {
	return SetIterator(*this);
}


