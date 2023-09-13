#include "SetIterator.h"
#include <iostream>

///Theta(1)
SetIterator::SetIterator(Set& m) : set(m)
{
    first();
}

///Theta(1)
void SetIterator::first() {
    currentElement = set.head; ///first node of the linked list
}

///Theta(1)
void SetIterator::next() {
	if(!valid())
        throw std::exception();
    currentElement = currentElement->next;

}

///Theta(1)
TElem SetIterator::getCurrent()
{
	if(!valid())
        throw std::exception();
    return currentElement->info;
}

///Theta(1)
bool SetIterator::valid() const {
	if(currentElement != nullptr) ///check if the current Node is not nullptr
        return true;
	return false;
}
/// Complexity :
/// Best case : Theta(1) - if the current element is the head
/// Worst case : Theta(n) - if the current element is the last element
/// Total complexity : O(n)
/// \return
TElem SetIterator::remove()
//removes and returns the current element from the iterator
// after the operation the current element from the Iterator is the next element from the Set, or, if the removed element was the last one, the iterator is invalid
// throws exception if the iterator is invalid
{
    if(!valid())
        throw std::exception();
    TElem removedElement = currentElement->info; ///save the current element
    Set::Node* previousElement = nullptr; ///the previous element of the current element
    Set::Node* current = set.head;
    while(current != currentElement) ///find the previous element of the current element
    {
        previousElement = current;
        current = current->next;
    }
    if(previousElement == nullptr) ///if the previous element is nullptr, it means that the current element is the head
    {
        set.head = currentElement->next; ///change the head with the next element
        delete currentElement;
        currentElement = set.head; ///set the current element with the new head
        set.length--;
        return removedElement;
    }
    previousElement->next = currentElement->next; ///change the next field of the previous element with the next field of the current element
    delete currentElement;
    currentElement = previousElement->next; ///set the current element with the next element of the previous element
    set.length--;
    return removedElement;
}




