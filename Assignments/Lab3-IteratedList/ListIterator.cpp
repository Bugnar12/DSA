#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

///Comlexity :
///Total complexity : Theta(n) since it uses the constructor for the IteratedList which parses the list
ListIterator::ListIterator(const IteratedList& list) : list(list) {
    current = list.head;
}

///Comlexity :
///Total complexity : Theta(1)
void ListIterator::first() {
    current = list.head;
}

///Comlexity :
///Total complexity : Theta(1)
void ListIterator::next() {
    if(current == -1)
        throw std::exception();
    current = list.next[current];
}

///Comlexity :
///Total complexity : Theta(1)
bool ListIterator::valid() const {
    return current != -1;
}

///Comlexity :
///Total complexity : Theta(1)
TElem ListIterator::getCurrent() const {
	if(!valid())
        throw std::exception();
    return list.elems[current];
}



