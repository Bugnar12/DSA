#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"
#include <stdio.h>



void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5); //[5] [0]
	b.add(1); // [5,1] [0,1]
	b.add(10); //
	b.add(7);
	b.add(1);// [5,1,10,7] [0, 1, 2, 3, 1]
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
    assert(b.removeOccurences(2,1) == 1);
    assert(b.removeOccurences(2, 14) == 0);
    assert(b.nrOccurrences(1) == 0);
    b.add(1);
    b.add(2);
    b.add(1);
    b.add(3);
    b.add(1);
    assert(b.nrOccurrences(1) == 3);
    assert(b.removeOccurences(3, 1) == 3);
    assert(b.nrOccurrences(1) == 0);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next();
	}
}
