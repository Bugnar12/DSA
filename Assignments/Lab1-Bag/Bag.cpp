#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <stdio.h>
using namespace std;

///!!! IMPORTANT !!! Regarding the complexity : n -> nr. of unique elements from the dynamic array Unique[]
///                                             m -> nr. of positions from the dynamic array Positions[]



///Theta(1) / Theta(capacityUnique + capacityPositions)
Bag::Bag() {
    this->nrUnique = 0;
    this->nrPositions = 0;
    this->capacityUnique = 100;
    this->capacityPositions = 200;
    this->Unique = new TElem[capacityUnique];
    this->Positions = new TElem[capacityPositions];
}


///Complexity :
///Best case : Theta(1) - if the element is on the first pos.
///Average case : Theta(n) = Theta(n) - assuming there are a lot of repetitions of the element in the bag
///Worst case : Theta(n) - if the element is not in the bag
///Total complexity : O(n)
void Bag::add(TElem elem) {
    ///if the nrUnique has reached its capacity, we resize by doubling the size and copying the elements into a new vector
    if (this->nrUnique == this->capacityUnique) {
        if (this->capacityUnique != 0)
            this->capacityUnique = this->capacityUnique * 2;
        else
            this->capacityUnique = this->capacityUnique + 1;


        TElem *newUnique = new TElem[capacityUnique];
        for (int i = 0; i < this->nrUnique; ++i)
            newUnique[i] = this->Unique[i];

        delete [] this->Unique;
        this->Unique = newUnique;

    }
    ///if the nrPositions has reached its capacity, we resize by doubling the size and copying the elements into a new vector
    if (this->nrPositions == this->capacityPositions)
    {
        if(this->capacityPositions != 0)
            this->capacityPositions = this->capacityPositions * 2;
        else
            this->capacityPositions = this->capacityPositions + 1;


        TElem* newPositions = new TElem[capacityPositions];
        for(int i = 0; i < nrPositions; ++i)
            newPositions[i] = this->Positions[i];

        delete [] this->Positions;
        this->Positions = newPositions;

    }
    ///if the element is not found among the unique ones, it must be added in the Uniques and in the Positions dynamic arrays
    if(search(elem) == false)
    {
        this->Unique[nrUnique] = elem;
        this->Positions[nrPositions] = nrUnique++;
        this->nrPositions++;
    }
    ///if the element is however found in the unique, it must be added on the last position of the Positions DA
    else{
        for(int i = 0; i < this->nrUnique; ++i) {
            if (this->Unique[i] == elem) {
                Positions[nrPositions] = i;
                nrPositions++;
            }
        }
    }

}

///Complexities: ( Theta because best case != worst case)
///Best case : Theta(n) if the element is not found and the UNIQUE array is parsed once by the search function
///Average case : Theta(n + m) (T(n) = 2*n + 2*m)
///Worst case : T(n) = 2*n + 2 * m => Theta(n + m)
///Overall complexity : O(n + m)
bool Bag::remove(TElem elem) {

    if(search(elem)) ///O(n)
    {
        int nrFound = -1;
        for(int i = 0; i < nrUnique; i++) ///O(n)
            if(this->Unique[i] == elem) {
                nrFound = i;
                break;
            }
        if(nrFound != -1)
        {
            int nrApp = 0;
            int last = -1;
            for(int i = 0; i < this->nrPositions; i++) ///O(m)
                if(this->Positions[i] == nrFound)
                    nrApp++, last = i; ///counts how many times the element appears in the Positions[] array to see if it gets removed from the Unique[] array

            if(nrApp == 1) ///if the element appears only once in the Positions array, it must be removed from the Unique array
            {
                for(int i = nrFound; i < this->nrUnique - 1; i++) ///O(n) amortized
                    this->Unique[i] = this->Unique[i + 1];
                this->nrUnique--;

                if(nrFound == nrUnique) ///if the element is last in the UNIQUE, it means all the positions have been already attribuited and so they won't be modified
                    for(int i = last; i < this->nrPositions - 1; i++) ///O(m) amortized
                        this->Positions[i] = this->Positions[i + 1];
                else
                {
                    for(int i = last; i < this->nrPositions - 1; i++) { ///O(m) amortized
                        this->Positions[i] = this->Positions[i + 1];
                    }
                    for(int i = last; i < this->nrPositions - 1; i++) ///O(m) amortized
                        if(this->Positions[i] > nrFound)
                            this->Positions[i]--;
                }
                this->nrPositions--;
                return true;
            }
            else ///if the element appears multiple times, its last appearence will be deleted from Positions[], but not from Unique[]
            {
                for(int i = last ; i < this->nrPositions - 1; i++) ///O(m) amortized
                    this->Positions[i] = this->Positions[i + 1];
                this->nrPositions--;
                return true;
            }
        }
        else
            return false;
        }
	return false; 
}

///Complexity :
///Best case : Theta(1) if the element is found in the first position of the Unique array
///Average case : Theta(n) (T(n) = n)
///Worst case : Theta(n) (T(n) = n)
///Total complexity : O(n)
bool Bag::search(TElem elem) const {
    for(int i = 0; i < this->nrUnique; i++)
        if(this->Unique[i] == elem)
            return true;
    return false;
}

///Complexity :
/// BC : Theta(n) , if we do not find the element in the Unique[] DA
/// AC : Theta(n + m), assuming the element has a high chance of not being unique
/// WC : Theta(n + m), if the element is the last in the Unique[] and its position in the bag is the same
/// Total complexity O(n + m)
int Bag::nrOccurrences(TElem elem) const {
    int result = 0;
    if (search(elem)) ///if the element exits in the Unique DA (O(n))
    {
        for(int i = 0; i < this->nrPositions; i++) ///O(m)
            if(Unique[Positions[i]] == elem)
                result = result + 1;
    }
    if(result != 0)
        return result;
    return 0;
}

///Complexity:
///BC : Theta (1)
///AC : Theta(1)
///WC : Theta(1)
int Bag::size() const {
	if(this->nrPositions > 0)
        return this->nrPositions;
    return 0;
}

///Complexity :
///BC : Theta(1)
///WC : Theta(1)
///AC : Theta(1)
bool Bag::isEmpty() const {
	if(this->nrPositions == 0)
        return true;
	return false;
}

///Complexity
///Best case : if nr < 0 => Theta(1)
///Worst case : if we have multiple occurences of the element in the Positions[], and it also must be removed from the Unique[] => Theta(m + n)
///Total complexity : O(m + n)
int Bag::removeOccurences(int nr, TElem elem) {
    if(nr < 0)
        throw exception();
    else
    {
        int nrRemoved = 0;
        for(int i = 0; i < this->nrPositions && nr != 0; i++) ///O(m) amortized
        {
//            if(Unique[Positions[i]] == elem)
//            {
//                swap(this->Positions[i], this->Positions[nrPositions - 1]);
//                nrPositions--;
//                nr--;
//                nrRemoved++;
//            }
            if(this->Positions[i] != -1 && Unique[Positions[i]] == elem)
            {
                nrRemoved++;
                nr--;
                Positions[i] = -1; ///mark the deleted positions
            }
        }
        if(nrRemoved > 0)
        {
            int j = 0;
            for(int i = 0; i < this->nrPositions; i++) ///O(m)
            {
                if(this->Positions[i] != -1)
                    this->Positions[j++] = this->Positions[i];
            }
            this->nrPositions = j;
            if(nrRemoved == 1)
            {
//                for(int i = 0; i < this->nrUnique; i++)
//                    if(Unique[i] == elem){
//                        swap(Unique[i], Unique[nrUnique - 1]);
//                        nrUnique--;
//                        break;
//                    }
                nrUnique--; /// if we
            }
        }
        return nrRemoved;
    }
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

///Complexity :
///BC : Theta(1)
///WC : Theta(1)
///AC : Theta(1)
Bag::~Bag() {
	delete [] Unique;
    delete [] Positions;
}
