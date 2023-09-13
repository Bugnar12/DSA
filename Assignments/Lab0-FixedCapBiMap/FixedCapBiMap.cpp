#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

using namespace std;

///this is the __init__(in Python)
FixedCapBiMap::FixedCapBiMap(int capacity) {
	if(capacity <= 0)
        throw exception();
    this->capacity = capacity;
    this->nrPairs = 0;
    this->elements = new TElem[capacity]; ///alocates for capacity number of TElems(new)

}

///this is the destroyer
FixedCapBiMap::~FixedCapBiMap() {
	delete [] this->elements;  ///delete all the array (with [])
}

bool FixedCapBiMap::add(TKey c, TValue v){
	if(this->capacity == this->nrPairs)
        throw exception();
    int index = 0;
    int count = 0;
    while(count < 2 && index < this->nrPairs)
    {
        if(this->elements[index].first == c)
            count++;
        index++;
    }
    if(count == 2)
        return false;
    else
    {
        this->elements[this->nrPairs].first = c;
        this->elements[this->nrPairs].second = v;
        this->nrPairs++;
        return true;
    }

}

ValuePair FixedCapBiMap::search(TKey c) const{
	//TODO - Implementation
	return std::pair<TValue, TValue>(NULL_TVALUE, NULL_TVALUE);
}

bool FixedCapBiMap::remove(TKey c, TValue v){
	//TODO - Implementation
	return false;
}


int FixedCapBiMap::size() const {
	return this->nrPairs;
}

bool FixedCapBiMap::isEmpty() const{
	//TODO - Implementation
	return false;
}

bool FixedCapBiMap::isFull() const {
	//TODO - Implementation
	return false;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {

	return FixedCapBiMapIterator(*this);
}



