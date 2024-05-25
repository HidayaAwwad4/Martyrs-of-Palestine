#pragma once
#include<iostream>
using namespace std;
template<typename T>
class SNode {
private:
	T node;
	SNode<T>* next;
	template <typename T> friend class SList;
};
template<typename T>
class SList {
private:
	SNode<T>* head;
	int n;
public:
	//constructure
	SList() :head(NULL) { n = 0; }

	//destructure
	~SList() {
		removeAll();
	}

	// empty 
	bool empty() const { return head == NULL; }

	// get Front 
	T getFront()const {
		if (empty())exit(1);
		return head->data;
	}

	// addFront function 
	void addFront(const T& m) {
		SNode<T>* newNode = new SNode<T>;
		newNode->node = m;
		newNode->next = NULL;
		newNode->next = head;
		head = newNode;
		n++;
	}

	//remove Front 
	bool removeFront() {
		if (empty())return false;
		SNode<T>* ptr = head;
		head = head->next;
		ptr->next = NULL;
		delete ptr;
		n--;
		return true;
	}

	//remove all
	void removeAll() {
		while (!empty()) {
			removeFront();
		}
		head = NULL;
	}

	// add sorted data
    void addSorted(const T& m) {
        SNode<T>* newNode = new SNode<T>;
        newNode->node = m;
		newNode->next = NULL;

        if (empty() || m.dateOfDeath < head->node.dateOfDeath) {
            newNode->next = head;
            head = newNode;
        } else {
            SNode<T>* temp = head;
            while (temp->next != NULL && temp->next->node.dateOfDeath < m.dateOfDeath) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        n++;
    }
	// dispaly List 
	void displayList() {
		SNode<T>* ptr = head;
		int i = 1;
		while (ptr) {
			cout << i << "-" << " name: [ " << ptr->node.name << " ]";
			cout << " age: [ " << ptr->node.age << " ]";
			cout << " location: [ " << ptr->node.eventLocationDistrict << " ]";
			cout << " date of death: [ " << ptr->node.dateOfDeath << " ]";
			cout<< " gender: [ " << ptr->node.gender << " ]" << endl;
			cout << endl;
			i++;
			ptr = ptr->next;
		}
	}

	// size
	int size() const { return n; }

	// update location
	void updateALocation(const string& newLocation) {
		SNode<T>* p = head;
		while (!p) {
			p->node.eventLocationDistrict = newLocation;
			p = p->next;
		}
	}

};

