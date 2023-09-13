#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <math.h>
#include <unordered_set>

using namespace std;

/*Complexity :
 * Total complexity : Theta(1)
 * */
int Bag::hash_function1(int k) const {
    if(k < 0)
        k *= -1; ///if key is negative => we make it pozitive
    return k % this->hash_table.m;
}

/*Complexity :
 * Total complexity : Theta(1)
 * */
int Bag::hash_function2(int k) const {
    if(k < 0)
        k *= -1; ///if key is negative => we make it pozitive
    return 1 + (k % (this->hash_table.m - 1));
}

/*Complexity :
 * Total complexity : Theta(n) (since we have to parse the initial capacity to fill it with NULL)
 * */
Bag::Bag() {
	this->hash_table.m = 7919;
    this->hash_table.elems = new TElem[this->hash_table.m];
    this->size_hash = 0;
    for(int index = 0; index < this->hash_table.m; index++)
        hash_table.elems[index] = NULL_TELEM; ///initialize the elements of the hash table with NULL
}
/*Complexity :
 * Best case : Theta(1) -> loop executes only once
 * Worst case : Theta(n) -> loop executes n times, no available position found in the hash table
 * Total complexity : O(n)
 * */
void Bag::add(TElem elem) {
    if(this->size_hash >= this->hash_table.m) ///the size graph is bigger than the capacity => we resize the hash table
        this->resize();

    int hash1 = this->hash_function1(elem);
    int hash2 = this->hash_function2(elem);

    int position = 0;
    int index2 = 0;
    while(true)
    {
        position = (hash1 + index2 * hash2) % this->hash_table.m; ///the double hashing fucntion
        if(this->hash_table.elems[position] != NULL_TELEM && this->hash_table.elems[position] != REMOVED)
            index2++;

        else {
            this->hash_table.elems[position] = elem;
            this->size_hash++;
            break;
        }
    }

}
/*Complexity :
 * Best case : Theta(1) -> the element is found from the first "search"
 * Worst case : Theta(n) -> element is not found in the hash table
 * Total complexity : O(n)
 * */
bool Bag::remove(TElem elem) {
    int hash1 = this->hash_function1(elem);
    int hash2 = this->hash_function2(elem);

    int index2 = 0;
    int position = (hash1 + index2 * hash2) % this->hash_table.m; ///the double hashing function

    while(this->hash_table.elems[position] != NULL_TELEM && index2 < this->hash_table.m)  ///while we don't find an empty position or we don't parse the entire hash table
    {
        if (this->hash_table.elems[position] == elem) {
            this->hash_table.elems[position] = REMOVED;
            this->size_hash--;
            return true;
        }
        else {
            index2++;
            position = (hash1 + index2 * hash2) % this->hash_table.m;
        }
    }
    return false;
}

/*Complexity :
 * Best Case : Theta(1) when the element is on the first position in the hash table
 * IMPORTANT : Average case can be Theta(1) if the hash function is good and few collisions appear
 * Worst Case : Theta(n) when the element is on the last position in the hash table(or all the elements hash to the same position)
 * Total complexity : O(n)
 * */
bool Bag::search(TElem elem) const {
	int hash1 = this->hash_function1(elem);
    int hash2 = this->hash_function2(elem);

    int index2 = 0;
    int position = (hash1 + index2 * hash2) % this->hash_table.m;

    while(this->hash_table.elems[position] != NULL_TELEM && index2 < this->hash_table.m) {
        if (this->hash_table.elems[position] == elem)
            return true;
        else {

            index2++;
            position = (hash1 + index2 * hash2) % this->hash_table.m;
        }
    }
    return false;
}

/*Complexity:
 * Best Case = Worst case = Total complexity = Theta(n)
 * ->Since the hash table has to be traversed completely to see how many elements of we have
 * */
int Bag::nrOccurrences(TElem elem) const {
    int nr_occurrences = 0;

    int hash1 = this->hash_function1(elem);
    int hash2 = this->hash_function2(elem);

    int index2 = 0;
    int pos = (hash1 + index2 * hash2) % this->hash_table.m;

    while(this->hash_table.elems[pos] != NULL_TELEM && index2 < this->hash_table.m) {
        if (this->hash_table.elems[pos] == elem)
            nr_occurrences++;
        index2++;
        pos = (hash1 + index2 * hash2) % this->hash_table.m;
        }
    return nr_occurrences;
}


/* Complexity :
 * Best case = Worst case = Total compelxity = Theta(n)
 * The hash table has to be parsed and then each element's appearences must be parsed not to screw up the double hashing
 * */
int Bag::distinctCount() const {
    int distinct = 0;
    bool* distinctElements = new bool[this->hash_table.m]();  // Initialize all elements to false

    for (int i = 0; i < this->hash_table.m; i++) {
        if (this->hash_table.elems[i] != NULL_TELEM && this->hash_table.elems[i] != REMOVED) {
            int hash1 = this->hash_function1(this->hash_table.elems[i]);
            int hash2 = this->hash_function2(this->hash_table.elems[i]);
            int index2 = 0;
            int pos = (hash1 + index2 * hash2) % this->hash_table.m;

            ///check if the element has already been marked as true and change the hashing function accordingly
            while (distinctElements[pos] && this->hash_table.elems[pos] != this->hash_table.elems[i]) {
                index2++;
                pos = (hash1 + index2 * hash2) % this->hash_table.m;
            }

            if (!distinctElements[pos]) {
                distinctElements[pos] = true;
                distinct++;
            }
        }
    }

    delete[] distinctElements;
    return distinct;
}





/*Complexity :
 * Total complexity : Theta(1)
 * */
int Bag::size() const {
    return this->size_hash;
}

/*Complexity :
 * Total complexity : Theta(1)
 * */
bool Bag::isEmpty() const {
	return this->size_hash == 0;
}

/*Complexity:
 * Total complexity : Theta(1)
 * */
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

/*Complexity:
 * Total complexity : Theta(1)
 * */
Bag::~Bag() {
	delete [] this->hash_table.elems;
}

/*Complexity:
 *
 * */
void Bag::resize() {
    int previous_m = this->hash_table.m; ///the previous capacity of the hash table
    this->hash_table.m = this->biggerPrime(this->hash_table.m * 2); ///the smallest prime number bigger than double the size of the before capacity
    TElem *new_elems = new TElem[this->hash_table.m];

    for(int i = 0; i < this->hash_table.m; i++)
        new_elems[i] = NULL_TELEM; ///we initialize the new hash table with NULL_TELEM

    for(int i = 0; i < previous_m; i++)
        if( this->hash_table.elems[i] != NULL_TELEM && this->hash_table.elems[i] != REMOVED)
        {
            int ok = 0;
            int j = 0;
            int hash1 = this->hash_function1(this->hash_table.elems[i]);
            int hash2 = this->hash_function2(this->hash_table.elems[i]);
            while(ok == 0)
            {
                int position = (hash1 + j * hash2) % this->hash_table.m;
                if(new_elems[position] == NULL_TELEM)  ///if the position is empty
                {
                    new_elems[position] = this->hash_table.elems[i]; ///we add the element from the old hash table to the new one
                    ok = 1;
                }
                else
                    j++;
            }
        }
    delete [] this->hash_table.elems;
    this->hash_table.elems = new_elems;
}


/*Complexity:
 * Total complexity : O(sqrt(n))
 * */
bool Bag::isPrime(int n) {
    for(int i = 2; i <= sqrt(n); i++)
        if(n % i == 0)
            return false;
    return true;
}

/*Complexity:
 * Total complexity : Theta(1)
 * */
int Bag::biggerPrime(int n) {
    n++;
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

/*Complexity :
 * Best case : Theta(n)
 * Worst case : Theta(n)
 * Total complexity : Theta(n)
 * */






