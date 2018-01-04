/*
 * SortedBag.h
 *
 *  Created on: Oct 20, 2017
 *      Author: mener
 */

#ifndef SORTEDBAG_H_
#define SORTEDBAG_H_
#include "Node.h"
namespace dsanagu_5 {

// Invariant
// Items are stored in Node objects which are located in the heap
// The bag is always sorted
// The node objects are connected in a doubly linked ring list
template <class T>
class SortedBag { // class I must implement
public:
	SortedBag() : m_data(0), m_size(0), m_asc(true), m_curr(0), iter_position(0) {}
	SortedBag(const SortedBag&);

	void operator=(const SortedBag&);
	~SortedBag();

	// modifying member functions
	bool erase_one(const T&);
	long erase(const T&);
	void insert(const T&);
	void operator +=(const SortedBag&);

	// const member functions
	long size() const { return m_size; }
	long count(const T&) const;
	bool operator==(const SortedBag& lhs);
	long iter() const { return iter_position; }

	// SIMPLE ITERATOR
	void begin(const bool ascending = true);
	bool end() const;
	void operator++();
	void operator--();
	T& get();

	//template<class T1>
	//friend std::ostream& operator<<(std::ostream& o, const SortedBag<T1>& sb);
private:
	Node<T>* m_data; // pointer to ring structure.
	long m_size; // number of elements in the Bag.

	// fields for the simple iterator
	bool m_asc; // flag to indicate iteration in ascending order or not.
	Node<T>* m_curr; // iterator's current position.
	long iter_position; // int to keep track of iterator's position. Used for end()

	void copy_over(const SortedBag& sb); // copies over sb's nodes to our bag
	void delete_all(); // returns all dynamic members to the heap
};

template<class T>
SortedBag<T> operator+(const SortedBag<T>&, const SortedBag<T>&);

};

#include "SortedBag.template"
#endif /* SORTEDBAG_H_ */
