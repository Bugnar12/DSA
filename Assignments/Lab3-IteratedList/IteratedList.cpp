#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

///Complexity:
///Total complexity : Theta(n) since the array has to be parsed to initialize the elements
IteratedList::IteratedList() {
    ///initializes the capacity and the head
    this->cap = 20;
    this->head = -1;
    this->firstFree = 0;

    this->elems = new TElem[this->cap];
    this->next = new int[this->cap];

    ///set default positions for the next elements
    for(int i = 0; i < this->cap; i++)
        this->next[i] = i + 1;
    this->next[this->cap - 1] = -1;
}

/*Total complexity : Theta(n)
 * */
int IteratedList::size() const {
    if(isEmpty())
        return 0;
    int size = 1;
    int currentIndex = this->head;
    int nextIndex = this->next[currentIndex];

    ///parse the array until there are no elements left
    while(nextIndex != -1)
    {
        size++;
        currentIndex = nextIndex;
        nextIndex = this->next[currentIndex];
    }
    return size;

}
/*Complexity:
 * Total complexity : Theta(1)
 * */
bool IteratedList::isEmpty() const {
    if(head == -1)
        return true;
    return false;
}

/*Complexity:
 * Theta(1)
 * */
ListIterator IteratedList::first() const {
    return ListIterator(*this);
}

///Complexity:
///Total complexity : Theta(1)
TElem IteratedList::getElement(ListIterator pos) const {
    ///check if the position is valid
    if(!pos.valid())
        throw std::exception();
    return pos.getCurrent();
}

/*Complexity:
 *Best case : Theta(1) - when the element is the first one
 * Worst case : Theta(n) - when the element is the last one
 * Total complexity : O(n)
 * */
TElem IteratedList::remove(ListIterator& pos) {
    if(!pos.valid())
        throw std::exception();
    ///get the element to be removed
    TElem removedElement = pos.getCurrent();
    int removedPosition = pos.current;
    int nextPosition = this->next[removedPosition];
    ///set the next position of the removed element to the first free position
    this->next[removedPosition] = this->firstFree;
    this->firstFree = removedPosition;
    ///set the next position of the previous element to the next position of the removed element
    if(removedPosition == this->head)
        this->head = nextPosition;
    else
    {
        ListIterator it(*this);
        while(it.valid())
        {
            if(this->next[it.current] == removedPosition)
            {
                this->next[it.current] = nextPosition;
                break;
            }
            else
                it.next();
        }
    }
    return removedElement;
}

/*Complexity:
 *Best Case : the iterator is not valid => Theta(1)
 * Worst Case : the iterator is valid => Theta(n)
 * Total complexity : O(n)
 * */
ListIterator IteratedList::search(TElem e) const{
    ListIterator it(*this);
    while(it.valid())
    {
        if(this->elems[it.current] == e)
            return it;
        else
            it.next();
    }
    return it;
}

/*Complexity:
 * Total complexity : Theta(1)
 * */
TElem IteratedList::setElement(ListIterator pos, TElem e) {
    if(!pos.valid())
        throw std::exception();
    TElem oldElement = pos.getCurrent();
    this->elems[pos.current] = e;
    return oldElement;
}

/*Complexity:
 * Best case : Theta(1) - when the element is added to the first position
 * Worst case : Theta(1) - when the element is added to the last position
 * Total complexity : Theta(1)
 * */
void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    if (!pos.valid())
        throw std::exception();

    if (this->firstFree == -1)
        resize();

    int newPosition = this->firstFree;
    this->firstFree = this->next[this->firstFree];
    this->elems[newPosition] = e;
    this->next[newPosition] = -1;

    if (pos.current == -1) {
        if (this->head == -1) {
            this->head = newPosition;
        } else {
            this->next[newPosition] = this->head;
            this->head = newPosition;
        }
        pos.current = this->head;
    } else {
        this->next[newPosition] = this->next[pos.current];
        this->next[pos.current] = newPosition;
        // Update the position iterator to point to the newly inserted element
        pos.current = newPosition;
    }
}

/*Complexity:
 * Best case : Theta(1)
 * Worst case : Theta(n)
 * Total complexity : O(n)
 * */
void IteratedList::addToEnd(TElem e) {
    if(isEmpty()) ///if the list is empty, we have to add to the first position and modify the head
    {
        int newPosition = this->firstFree;
        this->elems[newPosition] = e;
        this->firstFree = this->next[newPosition];
        this->next[newPosition] = -1;
        this->head = newPosition;
    }
    else
    {
        if (this->firstFree == -1) ///if the list is full, we have to resize it
            resize();
        int lastElement = this->head;
        while(this->next[lastElement] != -1)
            lastElement = this->next[lastElement];

        ///inserting at the end
        int newPosition = this->firstFree;
        this->elems[newPosition] = e;
        this->firstFree = this->next[newPosition];
        this->next[newPosition] = -1;

        this->next[lastElement] = newPosition;
    }
}
/*Complexity :
 * Total complexity : Theta(1)
 * */
IteratedList::~IteratedList() {
    delete [] this->next;
    delete [] this->elems;
}

/*Complexity:
 * Total complexity : Theta(n) ; since we have to parse the whole array to resize
 * */
void IteratedList::resize() {
    int new_cap = this->cap * resize_factor;
    auto newElems = new TElem[new_cap];
    auto newNext = new int[new_cap];

    for(int index = 0 ; index < this->cap; index++) {
        newElems[index] = this->elems[index];
        newNext[index] = this->next[index];
    }

    for(int index = this->cap; index < new_cap; index++)
        newNext[index] = index + 1;
    newNext[new_cap - 1] = -1;
    this->firstFree = this->cap;

    delete [] this->elems;
    delete [] this->next;

    this->elems = newElems;
    this->next = newNext;
    this->cap = new_cap;
}

/*Complexity:
 * Best case = Worst case = Total complexity = Theta(1) Since we add to the beginning of the array, no parsing needs to be done to update elements
 * */
void IteratedList::addToBeginning(TElem e) {
    if(isEmpty()) ///if the list is empty, we have to add to the first position and modify the head
    {
        int newPosition = this->firstFree;
        this->elems[newPosition] = e;
        this->firstFree = this->next[newPosition]; ///it will be 1 in our case
        this->next[newPosition] = -1;
        this->head = newPosition;
    }
    else
    {
        if (this->firstFree == -1) ///if the list is full, we have to resize it
            resize();
        ///inserting at the beginning
        int newPosition = this->firstFree;
        this->elems[newPosition] = e;
        this->firstFree = this->next[newPosition];
        this->next[newPosition] = this->head;
        this->head = newPosition;
    }
}
