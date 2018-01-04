/*
 * Node.h
 *
 *  Created on: Oct 21, 2017
 *      Author: mener
 */

#ifndef NODE_H_
#define NODE_H_

namespace dsanagu_5 {
template<class T>
struct Node {
	Node() : m_next(this), m_prev(this) {}
	Node(const T& val, Node<T>* n =0, Node<T>* p =0): m_val(val)
	{ m_next = n? n : this; m_prev = p? p : this; }

	bool is_singleton() const { return m_next == this && m_prev == this; }

	T m_val;
	Node<T>* m_next; // pointer to successor element.
	Node<T>* m_prev; // pointer to predecessor element.
};

}



#endif /* NODE_H_ */
