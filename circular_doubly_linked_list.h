#pragma once
#include<iostream>
#include<string>
#include"vector.h"
#include"linked stack.h"
#include"martyr.h"
using namespace std;

template<typename T>
class CDNode {
public:
	string location;
	MyVector<T> vec;
	LinkedStack<T> sta;
	CDNode<T>* next;
	CDNode<T>* prev;
	CDNode(): vec(),sta() {
		location = " ";
		next = prev = NULL;
	}
	~CDNode() {
		vec.~MyVector();
		sta.~LinkedStack();
	}
	template <typename T> friend class DList;
};
template<typename T>
class CDList {
public:
	CDNode<T>* header;
	int n;
	//constructure
	CDList() : n(0) {
		header = new CDNode<T>;
		header->next = NULL;
	}
	//destructure
	~CDList() {
		header->~CDNode();
		while (!empty()) {
			removeBack();
		}
		header = NULL;
		n = 0;
	}
	CDNode<T>* getHeader()const {
		return header;
	}
	//empty
	bool empty() const {
		return header->next == NULL;
	}

	// create node
	CDNode<T>* createNode(const T& m) {
		CDNode<T>* p = new CDNode<T>;
		p->location = m.eventLocationDistrict;
		p->vec.addInOrder(m);
		p->sta.push(m);
		p->prev = p->next = NULL;
		return p;
	}

	// add back
	void addBack(const T& m) {
		CDNode<T>* p = createNode(m);
		if (empty()) {
			header->next = p;
			p->next = p;
			p->prev = p;

		}
		else {
			p->prev = header->next->prev;
			p->next = header->next;
			p->prev->next = p;
			header->next->prev = p;
		}

	}

	// add node in order
	void addInOrder(const T& m) {
		CDNode<T>* p = findLocation(m.eventLocationDistrict);
		if (p) {
			p->vec.addInOrder(m);
			p->sta.push(m);
		}
		else {
			CDNode<T>* newNode = createNode(m);
			if (empty()) {
				header->next = newNode;
				newNode->next = newNode->prev = newNode;
				n++;
				return;
			}
			CDNode<T>* ptr = header->next;
			while (ptr->next != header->next && ptr->location < newNode->location) {
				ptr = ptr->next;
			}

			newNode->next = ptr;
			newNode->prev = ptr->prev;
			ptr->prev->next = newNode;
			ptr->prev = newNode;
			if (ptr == header->next && newNode->location < ptr->location) {
				header->next = newNode;
			}
			n++; 
		}
	}

	void printList() {
		if (empty()) {
			cout << "The list is empty." << endl;
			return;
		}
		CDNode<T>* ptr = header->next;
		do {
			cout <<"< " << ptr->location <<" >" << endl;
			cout << "Martyrs List Sorted by Names :"<<endl;
			ptr->vec.print();
			/*cout << "Martyrs List Sorted by Date of Martyrdom :" << endl;
			ptr->sta.printStack();*/
			cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;
			ptr = ptr->next;
		} while (ptr != header->next);
	}

	// print location
	void printLocation(const string& loc) {
		CDNode<T>* p =findLocation(loc);
		if (p) {
			cout << "[ " << loc << " ] " << endl;
			p->vec.print();
		}
		else cout << " the location not found" << endl;

	}

	//find location
	CDNode<T>* findLocation(const string& loc) {
		if (empty()) {
			return NULL;
		}
		CDNode<T>* p = header->next;
		do {
			if (p->location == loc) {
				return p;
			}
			p = p->next;
		} while (p != header->next);
		return NULL;
	}


	//remove back
	bool removeBack() {
		if (empty()) return false;

		CDNode<T>* p = header->next->prev;
		if (n == 1) {
			delete p; 
		    header->next = NULL;
			n--;
			return true;
		}

		p->prev->next = header->next;
		header->next->prev = p->prev;
		delete p;
		n--;
		return true;
	}

	// delete location 
	bool deleteLocation(const string& locationToDelete) {
		CDNode<Martyr>* locationNodeToDelete = findLocation(locationToDelete);
		if (locationNodeToDelete) {
			if (locationNodeToDelete->next == locationNodeToDelete) {
				// Only one node in the list
				delete locationNodeToDelete;
				header->next = NULL;
			}
			else {
				// Multiple nodes in the list
				locationNodeToDelete->prev->next = locationNodeToDelete->next;
				locationNodeToDelete->next->prev = locationNodeToDelete->prev;

				if (header->next == locationNodeToDelete) {
					header->next = locationNodeToDelete->next;
				}
				delete locationNodeToDelete;
				n--;
				return true;
			}
		}
		else return false;
	}



	//git size
	int size()const {
		return n;
	}

};

