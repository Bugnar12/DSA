#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

///Complexity : Theta(1) (BC = WC = AC = Total complexity)
BagIterator::BagIterator(const Bag& c): bag(c)
{
	index = 0;
}

///Complexity : Theta(1) (BC = WC = AC = Total complexity)
void BagIterator::first() {
	index = 0;
}

///Comlexity : Theta(1) (BC = WC = AC = Total complexity)
void BagIterator::next() {
	if(index < bag.nrPositions)
        index += 1;
    else
        throw exception();
}

///Comlexity : Theta(1) (BC = WC = AC = Total complexity)
bool BagIterator::valid() const {
	if(index < bag.nrPositions)
        return true;
	return false;
}


///Comlexity : Theta(1) (BC = WC = AC = Total complexity)
TElem BagIterator::getCurrent() const
{
	if(valid())
        return bag.Unique[bag.Positions[index]];
    else
        throw exception();

    return NULL_TELEM
}
