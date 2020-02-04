#pragma once

#include "node.h"


template <class type>
class LinkedList {
public:

	// Add an element to the list
	unsigned int append(type element) {
		ListNode<type> *node = new ListNode<type>(element);

		if (this->first == nullptr) {
			this->first = node;
			this->last = node;
		}
		else {
			this->last->next = node;
			this->last = node;
		}

		return ++this->_length;
	}

	// Remove an element from the list
	unsigned int remove(unsigned int index) {
		if (index == 0) {
			ListNode<type> *first = this->first->next;
			delete this->first;
			this->first = first;

			return --this->_length;
		}

		ListNode<type> *element = this->first;

		for (unsigned int i = 0; i < index-1; i++) {
			element = element->next;
		}

		ListNode<type> *future = nullptr;

		if (index < this->_length - 1)
			future = element->next->next;
		else
			this->last = element;

		delete element->next;
		element->next = future;

		return --this->_length;
	}

	// Get an element from the list
	type get(unsigned int index) {
		if (index >= this->_length) {
			return this->last->data;
		}

		ListNode<type> *element = this->first;

		for (unsigned int i = 0; i < index; i++) {
			element = element->next;
		}

		return element->data;
	}

	// Get the list length
	unsigned int length() {
		return this->_length;
	}

private:
	friend class ListIterator;

	ListNode<type> *first = nullptr;
	ListNode<type> *last = nullptr;
	unsigned int _length = 0;
};