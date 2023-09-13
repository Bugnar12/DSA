#pragma once
#include "Set.h"

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
    Set& set;
	SetIterator(Set& s);
    Set::Node* currentElement;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
    TElem remove(); ///removes and returns the current element from the Set

    ///overload the "=" operator so that it compares nodes
};
