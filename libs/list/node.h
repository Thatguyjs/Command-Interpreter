#pragma once


template <class type>
class ListNode {
public:
	ListNode() {};

	ListNode(type data) {
		this->data = data;
	}

	type data;
	ListNode<type> *next;
};