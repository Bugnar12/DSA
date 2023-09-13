#include "ExtendedTest.h"
#include "ShortTest.h"
#include "FixedCapBiMapIterator.h"

#include "FixedCapBiMap.h"


#include <iostream>
using namespace std;


int main() {
    //create a map
    FixedCapBiMap map(5);
    //add elements

    map.add(1, 2);
    map.add(2, 3);
    map.add(3, 4);
    map.add(4, 5);
    map.add(5, 6);

    //create an iterator
    FixedCapBiMapIterator it = map.iterator();
    cout<<"iterator valid"<<endl;
    while (it.valid()) {
        TElem e = it.getCurrent();
        cout << e.first << " " << e.second << endl;
        it.next();
    }

    //update the value of the first element
    it.first();
    it.update(10);
    cout<<"iterator valid"<<endl;
    while (it.valid()) {
        TElem e = it.getCurrent();
        cout << e.first << " " << e.second << endl;
        it.next();
    }


///    testAll();
///	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}