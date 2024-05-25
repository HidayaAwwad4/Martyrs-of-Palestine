#pragma once
#include"singly linked list.h"
template<typename T>
class LinkedStack {
private:
	SList<T> obj;
public:
	LinkedStack() :obj() {}

	~LinkedStack() {
		obj.~SList();
	}

	bool empty()const {
		return obj.empty();
	}

	void push(const T& node) {
		obj.addFront(node);
		//obj.addSorted(node);
	}

	void pop() {
		if (empty())return;
		obj.removeFront();
	}

	T top()const {
		if (empty())exit(1);
		return obj.getFront();
	}

	void printStack() {
		obj.displayList();
	}

	void updateLocation(const string& newLocation) {
		obj.updateALocation(newLocation);
	}
};
