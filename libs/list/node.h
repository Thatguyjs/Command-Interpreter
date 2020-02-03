#pragma once


template <class type>
class ListNode {
public:
	ListNode() {};

	ListNode(type data) {
		this->data = data;
	}

	void setNext(type *next) {
		this->next = next;
	};

	type data;
	ListNode<type> *next;
};