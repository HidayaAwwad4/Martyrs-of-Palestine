#pragma once
#include <iostream>
using namespace std;
template<typename T>
class MyVector {
private:
	T* a;
	int MaxCap;
	int n;
public:
	MyVector(int mc = 20) {
		n = 0;
		MaxCap = mc;
		a = new T[MaxCap];
	}
	~MyVector() {
		if (a != NULL)
			delete[] a;
		a = NULL;
	}
	MyVector(const MyVector<T>& obj) {
		MaxCap = obj.MaxCap;
		a = new T[MaxCap];
		n = obj.n;
		for (int i = 0; i < n; i++) {
			a[i] = obj.a[i];
		}
	}
	MyVector<T>& operator = (MyVector<T>& obj) {
		if (this == &obj)return *this;
		MaxCap = obj.MaxCap;
		if (a != NULL) delete[] a;
		a = new T[MaxCap];
		n = obj.n;
		for (int i = 0; i < n; i++) {
			a[i] = obj.a[i];
		}
		return *this;
	}
	void addInOrder(const T& obj) {
		if (n >= MaxCap)resize();
		int i;
		for (i = 0; i < n && obj.name > a[i].name; i++);
		if(i==n)a[n++] = obj;
		else {
			for (int j = n; j > i; j--) {
				a[j] = a[j - 1];
			}
			a[i] = obj;
			n++;
		}
	}

	void updateLocation(const string& newLocation, int index) {
		a[index - 1].eventLocationDistrict = newLocation;
	}
	void updateAllLocation(const string& newLocation) {
		for (int i = 0; i < n; i++) {
			a[i].eventLocationDistrict = newLocation;
		}
	}
	bool deleteRecord(int index){
		if (index > n)return false;
		for (int i = index - 1; i < n-1; i++) {
			a[i] = a[i+1];
		}
		n--;
		return true;
	}

	void printSearchByName(const string& searchName ) {
		int i;
		for (i = 0; i < n && a[i].name!=searchName; i++);
		if (i == n)cout << "not found this name" << endl;
		else {
			cout <<" name: [ " << a[i].name << " ]" << " age: [ " << a[i].age << " ]" << " location: [ " << a[i].eventLocationDistrict << " ]" << " date of death: [ " << a[i].dateOfDeath << " ]" << " gender: [ " << a[i].gender << " ]" << endl;
			cout << endl;
		}
	}

	void print() {
		for (int i = 0; i < n; i++) {
			cout << i + 1 << "-" << " name: [ " << a[i].name << " ]" << " age: [ " << a[i].age << " ]" << " location: [ " << a[i].eventLocationDistrict << " ]" << " date of death: [ " << a[i].dateOfDeath << " ]" << " gender: [ " << a[i].gender << " ]" << endl;
			cout << endl;
		}
	}

	void resize() {
		MaxCap *= 2;
		T* b = new T[MaxCap];
		for (int i = 0; i < n; i++) {
			b[i] = a[i];
		}
		delete[]a;
		a = b;
	}

	MyVector<T> operator + (const MyVector<T>& V) {
		if (this->n == V.n) {
			MyVector<T> result(V.n);
			for (int i = 0; i < V.n; i++) {
				result.a[i] = this->a[i] + V.a[i];
				result.n++;
			}
			return result;
		}
		if (this->n > V.n) {
			MyVector<T> result(this->n);
			for (int i = 0; i < V.n; i++) {
				result.a[i] = this->a[i] + V.a[i];
				result.n++;
			}
			for (int i = result.n; i < this->n; i++) {
				result.a[i] = this->a[i];
				result.n++;
			}
			return result;
		}
		if (this->n < V.n) {
			MyVector<T> result(V.n);
			for (int i = 0; i < this->n; i++) {
				result.a[i] = this->a[i] + V.a[i];
				result.n++;
			}
			for (int i = result.n; i < V.n; i++) {
				result.a[i] = V.a[i];
				//result.n++;
			}
			result.n = V.n;
			return result;
		}
	}

	friend ostream& operator <<(ostream& out, const MyVector<T>& obj) {
		for (int i = 0; i < obj.n; i++) {
			out << obj.a[i] << " ";
		}
		return out;
	}

	T get(int index) {
		if (index <= 0 || index > n)return NULL;
		return a[index];
	}

	T& operator[](int index) {
		if (index >= 0 && index < size()) {
			return a[index];
		}
	}

	int size() {
		return n;
	}

	bool empty() {
		return n <= 0;
	}
};
