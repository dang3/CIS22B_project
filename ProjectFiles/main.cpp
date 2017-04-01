#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Book.h"
#include "InventoryModule.h"
#include "ReportModule.h"
#include "Module.h"
#include "CashierModule.h"
#include <fstream>
using namespace std;

void displayMenu();

int main() {
	int bookAmount = 0;
	Book *bookInv;
	Module *M;
	InventoryModule IM;
	ReportModule RM;
	CashierModule CM;
	string choice;

	Module::updateNumBooks(bookAmount);
	bookInv = IM.makeInv(bookAmount);	

	cout << "Welcome to Serendipity Book Sellers!!!\n\n";

	while (1) {
		displayMenu();
		cin >> choice;
		cin.ignore();

		if (choice == "1") {
			M = &CM;
			M->activateModule(bookInv, bookAmount);
		}
		else if (choice == "2") {
			M = &IM;
			M->activateModule(bookInv, bookAmount);
		}
		else if (choice == "3") {
			M = &RM;
			M->activateModule(bookInv, bookAmount);
		}
		else if (choice == "4") {
			break;
		}
	}
	cout << "\nHit <enter> to quit\n";
	cin.get();
	return 0;
}

void displayMenu() {
	cout << endl;
	cout << "***********************************" << endl;
	cout << "*     Serendipity Booksellers     *" << endl;
	cout << "*            Main Menu            *" << endl;
	cout << "***********************************" << endl << endl;
	cout << "Please choose from the following   " << endl;
	cout << "1. Cashier Module                  " << endl;
	cout << "2. Inventory Database Module       " << endl;
	cout << "3. Report Module                   " << endl;
	cout << "4. Exit Program                    " << endl;
	cout << "Choice: ";
}