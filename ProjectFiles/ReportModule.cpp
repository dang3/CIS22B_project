#include <iostream>
#include <string>
#include <iomanip>
#include "Book.h"
#include "ReportModule.h"
#include "Module.h"

using namespace std;

void ReportModule::displayMenu() {
	cout << endl;
	cout << "***********************************" << endl;
	cout << "*     Serendipity Booksellers     *" << endl;
	cout << "*             Reports             *" << endl;
	cout << "***********************************" << endl << endl;
	cout << "1. Inventory Listing               " << endl;
	cout << "2. Inventory Wholesale Value       " << endl;
	cout << "3. Inventory Retail Value          " << endl;
	cout << "4. Listing by Quantity             " << endl;
	cout << "5. Listing by Cost                 " << endl;
	cout << "6. Listng by Age                   " << endl;
	cout << "7. Return to Main Menu             " << endl;
	cout << "Enter your choice: ";
}

void ReportModule::activateModule(Book *&bookInv, int &bookAmount) {
	string choice;

	while (1) {
		displayMenu();
		cin >> choice;
		cin.ignore();

		if (choice == "1")
			displayInv(bookInv, bookAmount);
		else if (choice == "2")
			invWholeSale(bookInv, bookAmount);
		else if (choice == "3")
			invRetail(bookInv, bookAmount);
		else if (choice == "4")
			listQuantity(bookInv, bookAmount);
		else if (choice == "5")
			listWholeSale(bookInv, bookAmount);
		else if (choice == "6") 
			listAge(bookInv, bookAmount);
		else if (choice == "7") 
			return;
		else
			cout << "Invalid choice, please enter a single digit from 1 through 7\n";
	}
}

// Displays the complete inventory
void ReportModule::displayInv(Book *bookInv, int bookAmount) {
	cout << endl;
	cout << "***********************************" << endl;
	cout << "*     Serendipity Booksellers     *" << endl;
	cout << "*            Inventory            *" << endl;
	cout << "***********************************" << endl << endl;
	for (int i = 0; i < bookAmount; i++) {
		std::cout << bookInv[i];
	}
}

// Displays the ISBN, title, author and wholesale value of each book, then displays the sum of the total wholesale value of each book
void ReportModule::invWholeSale(Book *bookInv, int bookAmount) {
	double total = 0;
	cout << endl;
	cout << "*************************************" << endl;
	cout << "      Listing by Wholesale Cost      " << endl;
	cout << "*************************************" << endl;
	for (int i = 0; i < bookAmount; i++) {
		cout << "ISBN: " << bookInv[i].getISBN() << endl;
		cout << "Title: " << bookInv[i].getTitle() << endl;
		cout << "Author: " << bookInv[i].getAuthor() << endl;
		cout << "Wholesale Value: $" << setprecision(2) << fixed << bookInv[i].getWholeSale() << endl << endl;
		total += ( bookInv[i].getWholeSale() * bookInv[i].getQuantity() );
	}

	cout << "The total wholesale value of the inventory is $" << setprecision(2) << fixed << total << endl << endl;
}

// Displays the ISBN, title, author and retail cost of each book, then displays the sum of the total retail value of each book
void ReportModule::invRetail(Book *bookInv, int bookAmount) {
	double total = 0;
	cout << endl;
	cout << "*************************************" << endl;
	cout << "       Listing by Retail Price       " << endl;
	cout << "*************************************" << endl;
	for (int i = 0; i < bookAmount; i++) {
		cout << "ISBN: " << bookInv[i].getISBN() << endl;
		cout << "Title: " << bookInv[i].getTitle() << endl;
		cout << "Author: " << bookInv[i].getAuthor() << endl;
		cout << "Retail Value: $" << setprecision(2) << fixed << bookInv[i].getRetail() << endl << endl;
		total += ( bookInv[i].getRetail() * bookInv[i].getQuantity() );
	}

	cout << "The total retail value of the inventory is $" << setprecision(2) << fixed << total << endl << endl;
}

// Sort the database by quantity in order from greatest to least, then displays the sorted inventory
void ReportModule::listQuantity(Book* bookInv, int bookAmount) {
	sort(BY_QUANTITY, bookInv, bookAmount);
	cout << "\nThe database has been sorted by quantity. Press <enter> to continue.";
	cin.get();
	displayInv(bookInv, bookAmount);
}

// Sort the database by wholesale value in order from greatest to least, then displays the sorted inventory
void ReportModule::listWholeSale(Book *bookInv, int bookAmount) {
	sort(BY_WHOLESALE, bookInv, bookAmount);
	cout << "\nThe database has been sorted by wholesale cost. Press <enter> to continue.";
	cin.get();
	displayInv(bookInv, bookAmount);
}

// Sort the database by age in order from old to new, then displays the sorted inventory
void ReportModule::listAge(Book* bookInv, int bookAmount) {
	sortDate(bookInv, bookAmount);
	cout << "\nThe database has been sorted by age. Press <enter> to continue.";
	cin.get();
	displayInv(bookInv, bookAmount);
}