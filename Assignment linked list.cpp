#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<vector>
#include "martyr.h"
#include "vector.h"
#include"singly_list_minDate.h"
#include "circular_doubly_linked_list.h"
using namespace std;

void locationMenu() {
	cout << " ----------------------------------------------" << endl;
	cout << "|                Location Menu                 |" << endl;
	cout << "| 1. An option to insert new location record.  |" << endl;
	cout << "| 2. An option to update an existing location  |" << endl;
	cout << "| 3. An option to delete an existing location  |" << endl;
	cout << "| 4. An option to search for a location record |" << endl;
	cout << "| 5. Exit                                      |" << endl;
	cout << " ----------------------------------------------" << endl;
}

int main() {
	//ifstream inputFile("C:\\Users\\hp Lap\\Desktop\\sub.txt");
	ifstream inputFile("C:\\Users\\hp Lap\\Desktop\\btselem.csv");
	if (!inputFile.is_open()) {
		cerr << "Failed to open file!" << endl;
		return 1;
	}

	// Skip the first line
	/*string headerLine;
	getline(inputFile, headerLine);*/

	Martyr obj;
	CDList<Martyr> cd;
	string line;
	while (getline(inputFile, line)) {
		stringstream ss(line);
		string token;
		vector<string> tokens;

		while (getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		if (tokens.size() >= 5) {
			obj.name = tokens[0];
			obj.age = tokens[1];
			obj.eventLocationDistrict = tokens[2];
			obj.dateOfDeath = tokens[3];
			obj.gender = tokens[4];
			cd.addInOrder(obj);
		}
	}
	inputFile.close();
	//cd.printList();
	int choice;
	do {
		locationMenu();
		cout << "Enter your choice number here -> "; cin >> choice;
		if (choice == 1) {
			string loc;
			Martyr v;
			cout << "What is the new location ? "; cin >> loc;
			if (!cd.findLocation(loc)) {
				cout << "Enter information about the first martyr of this location" << endl;
				cout << "Martyr name is : "; cin >> v.name;
				cout << "Martyr age is : "; cin >> v.age;  
				v.eventLocationDistrict = loc;
				cout << "Date of his martyrdom : "; cin >> v.dateOfDeath;
				cout << "Martyr gender is : "; cin >> v.gender;
				cd.addInOrder(v);
				cd.printLocation(loc);
				obj.modified = true;
				cout << "inserted successfully" << endl;
			}// end if (!cd.findLocation(loc))
			else {
				cout << "This location already exists" << endl;
			}


		}//end if (choice == 1)

		else if (choice == 2) {
			string locationToUpdate;
			cout << "Enter the location you want to update: ";
			cin >> locationToUpdate;
			CDNode<Martyr>* locationNodeToUpdate = cd.findLocation(locationToUpdate);
			if (locationNodeToUpdate) {
				string newLocation;
				cout << "Enter the new location: ";
				cin >> newLocation;
				locationNodeToUpdate->location = newLocation;
				locationNodeToUpdate->vec.updateAllLocation(newLocation);
				locationNodeToUpdate->sta.updateLocation(newLocation);
				cout << "District updated successfully!" << endl;
				cd.printLocation(newLocation);
				obj.modified = true;
			}
			else {
				cout << "Location not found." << endl;
			}
		}//end else if (choice == 2)

		else if (choice == 3) {
			string locationToDelete;
			cout << "Enter the location you want to delete: ";
			cin >> locationToDelete;

			if (cd.deleteLocation(locationToDelete)) {
				cout << "Location deleted successfully!" << endl;
				obj.modified = true;
			}
			else {
				cout << "Location not found." << endl;
			}
		}//end else if (choice == 3)

		else if (choice == 4) {
			char option;
			cout << "You want to search in:" << endl;
			cout << "a.Martyrs' Menu" << endl;
			cout << "b.Statistics Report" << endl;
			cout << "choice a or b => "; cin >> option;

			if (option == 'a') {
				string loca;
				cout << "Enter the name of the location you want => "; cin >> loca;
				CDNode<Martyr>* ptr = cd.findLocation(loca);
				if (ptr) {
					int number;
					cout << "You can do one of these options.Choose the number you want" << endl;
					cout << "1. Insert a new martyr record" << endl;
					cout << "2. Update a martyr record" << endl;
					cout << "3. Delete a martyr record" << endl;
					cout << "4. Search for a martyr by name and display his/her information." << endl;
					cout << "You want to do number : "; cin >> number;
					if (number == 1) {
						cout << "Martyrs of this location :" << endl;
						cout << "Martyr name is : "; cin >> obj.name;
						cout << "Martyr age is : "; cin >> obj.age;
						obj.eventLocationDistrict = loca;
						cout << "Date of his martyrdom : "; cin >> obj.dateOfDeath;
						cout << "Martyr gender is : "; cin >> obj.gender;
						cd.addInOrder(obj);
						obj.modified = true;
					}//end if (number == 1)
					else if (number == 2) {
						cd.printLocation(loca);
						cout << "Martyrs of this location :" << endl;
						int updateNum, choiseNum;
						string upd;
						cout << "The number of the martyr you want to update : "; cin >> updateNum;
						cout << "Choose what you want to update (choose the number) :\n1 - The name of the martyr\n2 - The age of the martyr\n3 - Date of martyrdom\n4 - Gender of the martyr \n5- location" << endl;
						cout << "number : "; cin >> choiseNum;
						if (choiseNum == 1) {
							cout << "the new name is : "; cin >> upd;
							ptr->vec[updateNum - 1].name = upd;
							cd.printLocation(loca);
							obj.modified = true;
						}
						else if (choiseNum == 2) {
							cout << "the new age is : "; cin >> upd;
							ptr->vec[updateNum - 1].age = upd;
							cd.printLocation(loca);
							obj.modified = true;
						}
						else if (choiseNum == 3) {
							cout << "the new date is : "; cin >> upd;
							ptr->vec[updateNum - 1].dateOfDeath = upd;
							cd.printLocation(loca);
							obj.modified = true;
						}
						else if (choiseNum == 4) {
							cout << "the new Gender is : "; cin >> upd;
							ptr->vec[updateNum - 1].gender = upd;
							cd.printLocation(loca);
							obj.modified = true;
						}
						else if (choiseNum == 5) {
							cout << "the new Location is : "; cin >> upd;
							ptr->vec[updateNum - 1].eventLocationDistrict = upd;
							cd.printLocation(loca);
							obj.modified = true;
						}
						else cout << "This option is not available" << endl;

					}//end else if (number == 2)
					else if (number == 3) {
						cd.printLocation(loca);
						cout << "Martyrs of this location :" << endl;
						int deleteNum;
						cout << "The number of the martyr you want to delete : "; cin >> deleteNum;
						if (ptr->vec.deleteRecord(deleteNum)) {
							cout << "The deletion was completed successfully" << endl;
							cd.printLocation(loca);
							obj.modified = true;
						}
						else cout << "An error occurred during the deletion operation" << endl;

					}//end else if (number == 3)
					else if (number == 4) {
						string searchName;
						cout << "Enter the name of the martyr whose data you want to display : "; cin >> searchName;
						ptr->vec.printSearchByName(searchName);
					}//end else if (number == 4)


				}//end if (2) (ptr)


				else cout << "not foind this location"; //else for (if 2)


			}//end if (1) (option == 'a')

			else if (option == 'b') {
				string selectedLocation;
				cout << "Enter the name of the location you want => "; cin >> selectedLocation;
				CDNode<Martyr>* selectedNode = cd.findLocation(selectedLocation);
				if (selectedNode) {
					// a. Count the number of martyrs in the selected location
					int numMartyrs = selectedNode->vec.size();
					cout << "Number of martyrs in " << selectedLocation << ": " << numMartyrs << endl;

					// b. Print the full information of martyrs in that location
					cout << "Martyrs' information in " << selectedLocation << ":" << endl<<endl;
					selectedNode->vec.print();

					// c. Traverse the stack and print the martyrs' information
					cout << "Information about martyrs in order of Date of Martyrdom:" << endl<<endl;
					selectedNode->sta.printStack();

					//d. the date that had the minimum number of martyrs.
					cout << "the date that had the minimum number of martyrs is : ";
					SMList o;
					for (int i = 0; i < selectedNode->vec.size(); i++) {
						o.addFront(selectedNode->vec[i].dateOfDeath);
					}
					cout << o.minDate() << endl;

				}//end if (selectedNode)
				else {
					cout << "Location not found." << endl;
				}

			}//end else if (option == 'b')

		}//end else if (choice == 4)
		 
		else if (choice == 5) {
			cout << "Done" << endl;
		}

		else {
			cout << " Enter only a number from 1-5 " << endl;
		}

	} while (choice < 1 || choice > 5 || choice!=5 );

	///////////////////////////////////////////////////// save change ////////////////////////////////////////////////////////

	if (obj.modified) {
		char saveChoice;
		cout << "Do you want to save the changes to the file?" << endl;
		cout << "a. Yes" << endl;
		cout << "b. No" << endl;
		cout << "Your choice: ";
		cin >> saveChoice;

		if (saveChoice == 'a' || saveChoice == 'A') {
			string filePath = "C:\\Users\\hp Lap\\Desktop\\new.txt";

			ofstream outputFile(filePath);
			if (!outputFile.is_open()) {
				cerr << "Failed to open file for writing!" << endl;
				return 1;
			}

			// Check if the list is empty
			if (cd.empty()) {
				cout << "The list is empty. No data to save." << endl;
				outputFile.close();
				return 0;
			}

			CDNode<Martyr>* currentNode = cd.header->next;
			do {
				for (int i = 0; i < currentNode->vec.size(); i++) {
					outputFile << currentNode->vec[i].name << "," << currentNode->vec[i].age << ","
						<< currentNode->vec[i].eventLocationDistrict << "," << currentNode->vec[i].dateOfDeath
						<< "," << currentNode->vec[i].gender << endl;
				}
				currentNode = currentNode->next;
			} while (currentNode != cd.header->next);

			outputFile.close();
			cout << "Changes saved successfully to: " << filePath << endl;
		}
	}

return 0;
}

