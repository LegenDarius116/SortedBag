//============================================================================
// Name        : DStruct_5.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stddef.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector> // only used to handle random indices
#include <cassert>

#include "SortedBag.h"
#include "Student.h"

using namespace std;
using namespace dsanagu_5;

string show_bool(bool in) {
	if(in == 0) return "false";
	else return "true";
}

// Test III works 1/7 times
int main() {

	srand(time(NULL));

	SortedBag<Student> l1, l2, l3;

	vector<int> big_indices; big_indices.reserve(198); // used for number 3

	for(size_t i = 0; i < 200; ++i) {
		l1.insert(Student());

		if(i < 198) big_indices.push_back(i);
	}

	//SortedBag<Student> ltest(l1); // test: copy constrctor is broken

	cout << "Test I.\n";

	for(l1.begin(); !l1.end(); ++l1) {
		Student temp = l1.get();
		l2.insert(temp);
	}
	// check for equality
	l1.begin(); l2.begin();
	cout << "L1 == L2 after copy insertion: " << show_bool(l1 == l2) << endl;

	//cout << "Debug L1\n" << l1 << "\n\nDebug L2\n\n"<< l2 << endl << "L1 size: " << l1.size() << " L2 size: " << l2.size() << endl; ///wtf... double insert?

	// going backward --------------------------

	for(l1.begin(false); !l1.end(); --l1)
		l3.insert(l1.get());

	l1.begin(); l3.begin();
	cout << "L1 == L3 after backwards copy insertion: " << show_bool(l1 == l3) << endl; // works only some of the time

	cout << "\nTest II. \n";
	// erase first and last from L1 and L2
	l1.begin(); Student first = l1.get();
	l1.begin(); --l1; Student last = l1.get(); // first and last works all nice

	l1.begin(); l2.begin(); // put cursor at home

	l1.erase_one(first);
	l1.erase_one(last);

	l2.erase_one(first);
	l2.erase_one(last);

	// check for equality
	cout << "L1 == L2 after removal of first and last elements: " << show_bool(l1 == l2) << endl;
	//cout << "L1 size: " << l1.size() << ", L2 size: " << l2.size() << endl; // sizes are both 198, checks out

	for(l2.begin(); !l2.end(); ++l2) { // now works correctly!
		Student temp = l2.get();

		l1.erase_one(temp);
	}

	cout << "L1 size after L2 clear: " << l1.size() << endl; // should be 0

	cout << "\nTest III.\n";

	// Preparing random indices
	random_shuffle(big_indices.begin(), big_indices.end()); // shuffling big array of indices, then picking first 50 of those

	unsigned int rand_indices[50];
	for(unsigned int i = 0; i < 50; ++i) rand_indices[i] = big_indices[i];

	sort(rand_indices, rand_indices + 50); // random indices now in numerical, ascending order.


	unsigned int list_index = 0; 	// linked list tracker, increments per loop
	unsigned int rand_look = 0; 	// currently looking for indices[0], the first random index in array
									// after there has been a match, (tracker == indices[0]), will start
									// looking for indices[1], so on and so forth.

    int l2_original_size = l2.size();

	// delete from l2 and insert to l1
	for(l2.begin(); !l2.end(); ++l2) {
		// reached one of the selected random indices
		if(list_index == rand_indices[rand_look]) {
			Student target = l2.get();
			l2.erase_one(target);
			l1.insert(target);

			++rand_look;
		}
		++list_index;
	}

    assert(l1.size() == 50);
    assert(l2_original_size - 50 == l2.size());

	// now inserting all elements of l2 into l1
	//l1 += l2; // doesn't insert stuff...

	// alternate
    cout << "[Waypoint Flag]\n"; // waypoint flag for debug purposes

    // sometimes works; sometimes turns into an infinite loop; segmentation fault?
	//for(l2.begin(); !l2.end(); ++l2) l1.insert(l2.get());

    l1 += l2;

	// erase first and last from l3
	l3.begin(); Student first3 = l3.get();
	l3.begin(); --l3; Student last3 = l3.get();

    l3.begin();
	l3.erase_one(first3); l3.erase_one(last3);

	// l1.size = 50, l3.size = 198
	cout << "L1 == L3 after procedures of Test III: " << show_bool(l1 == l3) << endl; // will sometimes crash at the end; destructor?
#if 0
#endif

#if 0
	l1.begin();

	unsigned int ctr = 0; // prints twice & not all the way...
	while(!l1.end()){
		cout << l1.get() << endl;
		++l1;
		++ctr;
	}
	cout << ctr << " Size: " << l1.size() << endl;
#endif

	return 0;
}
