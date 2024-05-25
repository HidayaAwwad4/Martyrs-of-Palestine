#pragma once
#include<iostream>
#include<string>
using namespace std;
class Martyr {
public:
	string name;
	string age;
	string eventLocationDistrict;
	string dateOfDeath;
	string gender;
	bool modified;
	Martyr() {
		name = age = eventLocationDistrict = dateOfDeath = gender = "";
		modified = false;
	}
};

