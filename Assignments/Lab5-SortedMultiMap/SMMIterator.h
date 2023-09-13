#pragma once

#include "SortedMultiMap.h"
#include <stack>


class SMMIterator{
	friend class SortedMultiMap;
private:
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

    struct StackElement {
        Node* node;
        int index;

        StackElement(Node* n, int i) : node(n), index(i) {}
    };
    std::stack<StackElement> stack;




public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

