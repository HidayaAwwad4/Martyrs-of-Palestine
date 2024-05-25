#pragma once
#include<iostream>
using namespace std;

class SMNode {
private:
    int count;
    string date;
    SMNode* next;
    friend class SMList;
};

class SMList {
private:
    SMNode* head;
    int n;

public:
    // Constructor
    SMList() : head(NULL), n(0) {}

    // Destructor
    ~SMList() {
        removeAll();
    }

    // Check if empty
    bool empty() const { return head == NULL; }

    // Add to the front
    void addFront(string m) {
        SMNode* ptr = findDate(m);
        if (ptr) {
            ptr->count++;
        }
        else {
            SMNode* newNode = new SMNode;
            newNode->date = m;
            newNode->count = 1;
            newNode->next = head;
            head = newNode;
            n++;
        }
    }

    // Find a date
    SMNode* findDate(const string& m) {
        SMNode* p = head;
        while (p && p->date != m) {
            p = p->next;
        }
        return p;
    }

    // Find the date with the minimum count
    string minDate() {
        if (empty()) return ""; 
        SMNode* p = head;
        int minCount = p->count;
        string minDate = p->date;
        while (p) {
            if (p->count < minCount) {
                minCount = p->count;
                minDate = p->date;
            }
            p = p->next;
        }
        return minDate;
    }

    // Remove from the front
    bool removeFront() {
        if (empty()) return false;
        SMNode* ptr = head;
        head = head->next;
        ptr->next = NULL;
        delete ptr;
        n--;
        return true;
    }

    // Remove all nodes
    void removeAll() {
        while (!empty()) {
            removeFront();
        }
        head = NULL;
    }
};

