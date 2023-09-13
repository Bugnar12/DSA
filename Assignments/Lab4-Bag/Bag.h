#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
#define REMOVED -999999
#define resize_factor 2

typedef int TElem;
class BagIterator;

struct HashTable{
    TElem* elems;
    int m; ///the capacity of the hash table
};

class Bag {

private:
    int size_hash;
    HashTable hash_table;

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();

    /*--------------Auxiliary functions for the hash table-----------------*/

    int hash_function1(int k) const;
    int hash_function2(int k) const;
    bool isPrime(int n);
    int biggerPrime(int n);

    void resize();

    int distinctCount() const;
};