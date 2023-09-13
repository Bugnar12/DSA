#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator; 
class Bag {

private:

    TElem* Unique; ///represents the DA of unique elements
    int* Positions; ///represents the DA of the positions of the elements in the bag
    int nrUnique; ///represents the number of unique elements found in the bag
    int nrPositions; ///represents the number of positions in the bag
    int capacityUnique; ///relative to how many positions aka. how many elements are there in the bag
    int capacityPositions; ///relative to how many positions aka. how many elements are there in the bag


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

    int removeOccurences(int nr, TElem elem);

	//destructor
	~Bag();
};