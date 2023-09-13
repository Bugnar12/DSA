#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

/*Complexity:
 * Total complexity : Theta(1)
 * */
BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = 0;
    while(this->bag.hash_table.elems[this->current] == NULL_TELEM || this->bag.hash_table.elems[this->current] == REMOVED)
        this->current++;
}

/*Complexity:
 * Total complexity : Theta(1)
 * */
void BagIterator::first() {
    this->current = 0;
    while(this->bag.hash_table.elems[this->current] == NULL_TELEM || this->bag.hash_table.elems[this->current] == REMOVED)
        this->current++;
}

/*Complexity:
 * Total complexity : Theta(1)
 * */
void BagIterator::next() {
	    if(!this->valid())
        throw std::exception();
    this->current++;
    while(this->bag.hash_table.elems[this->current] == NULL_TELEM || this->bag.hash_table.elems[this->current] == REMOVED)
        this->current++;
}

/*Complexity:
 * Total complexity : Theta(1)
 * */
bool BagIterator::valid() const {
	    return this->current < this->bag.hash_table.m;
}

/*Complexity:
 * Total complexity : Theta(1)
 * */
TElem BagIterator::getCurrent() const
{
    if(!this->valid())
        throw std::exception();
    return this->bag.hash_table.elems[this->current];
}


