#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	this->current = 0;
}


void FixedCapBiMapIterator::first() {
	this->current = 0;
}


void FixedCapBiMapIterator::next() {
	if(this->current >= this->map.nrPairs) {
        throw exception();
    }
    else
        this->current++;
}


TElem FixedCapBiMapIterator::getCurrent(){
	if(this->current >= this->map.nrPairs)
        throw exception();
    return this->map.elements[this->current];
}


bool FixedCapBiMapIterator::valid() const {
	if(this->current < this->map.nrPairs) {
        return true;
    }
    else {
        return false;
    }
}

void FixedCapBiMapIterator::update(TValue v) {
    if(this->current >= this->map.nrPairs)
        throw exception();
    this->map.elements[this->current].second = v;
}



