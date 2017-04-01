#define _CRT_SECURE_NO_WARNINGS
#include "CashierModule.h"
#include "Book.h"
#include "ReportModule.h"
#include "InventoryModule.h"
#include "Module.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/* 
A receipt file is made at the end of every transaction. It serves 2 purposes:
	1. Shopping cart - Stores the items that the user wants to purchase, the viewCart function reads and prints from this file showing
	the items in the buyer's cart
	2. A record of the transaction - When the buyer is finished with the checkout process, a contents of the receipt.txt file is replaced
	with a record of the transaction

	The receipt.txt file must be cleared everytime the user begins the process of buying a book
*/
void CashierModule::clearReceiptFile() {
	fstream receipt("receipt.txt", ios::out);
	receipt.close();
}

void CashierModule::activateModule(Book *&bookInv, int &bookAmount) {
	int buyQuantity, temp, day, month, year, numBooksBought = 0, index = -1;
	bool finished = false;
	string input = "";
	fstream receipt("receipt.txt", ios::out | ios::in);
	cout << endl;
	cout << "***********************************" << endl;
	cout << "*     Serendipity Booksellers     *" << endl;
	cout << "*          Cashier Module         *" << endl;
	cout << "***********************************" << endl << endl;
	cout << "This module is used to purchase books. To find a book you want wish to buy, you may enter\n";
	cout << "all or part of a book's ISBN or title." << endl;
	cout << "Do you wish to continue? (y/n): ";
	
	input = getCheck_YN();

	if (input == "n") {
		cout << "\n\nReturning to the main menu...\n";
		cout << "Press <Enter> to continue\n";
		cin.get();
		return;
	}

	clearReceiptFile();	// If the user wants to begin buying a book, clear the file
	cout << "\nPlease enter today's date in numerals to continue, starting with ONLY the month\n";
	cout << "Month: ";
	month = getCheck_date(MONTH);

	cout << "Day: ";
	day = getCheck_date(DAY);

	cout << "Year: ";
	year = getCheck_int();

	receipt << month << endl;
	receipt << day << endl;
	receipt << year << endl;

	while (finished == false) {
		displayMenu();
		cin >> input;
		cin.ignore();

		// Similar to the lookUpBook function in the Inventory Module, the user can search by ISBN or by title
		if (input == "1") 
			index = continueISBN(bookInv, bookAmount);
		else if (input == "2")
			index = continueTitle(bookInv, bookAmount);
		else if (input == "3")
			finished = true;
		else {
			cout << "Invalid option, please enter only 1, 2 or 3\n";
			continue;
		}
		
		// Checks if the book that the user enters exists
		if (index < 0) {
			cout << "The book that you are looking for cannot be found. Please try again\n";
			continue;
		}

		temp = bookInv[index].getQuantity();

		// If the book does exist, check to see if its in stock
		if (temp == 0) {
			cout << "The book that you have entered is currently out of stock. Please select a different book\n";
			continue;
		}

		cout << "Quantity available for purchase: " << temp << endl;
		cout << "Quantity you wish to buy: ";

		// If the book is in stock, make sure the amount that the user enters is less than or equal
		// to the available quantity
		do {
			cin >> buyQuantity;
			cin.ignore();

			if (buyQuantity > temp) {
				cout << "There are not enough books. Please enter a different quantity\n";
				cout << "Quantity: ";
			}
		} while (buyQuantity > temp);

		cout << "\n\nAre you sure you want to add this book to your cart?\n\n";
		cout << "ISBN: " << bookInv[index].getISBN() << endl;
		cout << "Title: " << bookInv[index].getTitle() << endl;
		cout << "Author: " << bookInv[index].getAuthor() << endl;
		cout << "Publisher: " << bookInv[index].getPublisher() << endl;
		cout << "Purchase quantity: " << buyQuantity << endl;
		cout << "Retail price: " << bookInv[index].getRetail() << endl << endl;

		while (input != "y" && input != "n") {
			cout << "Input (y/n): ";
			cin >> input;
			cin.ignore();
			// Only add the book to cart if the book exists, if it is in stock and the quantity that the user enters is less than or equal to the available quantity
			// and if the user wants the book
			if (input == "y") {
				addToCart(bookInv, buyQuantity, index, receipt);
				numBooksBought++;
				updateInvFile(bookInv, bookAmount);
				cout << "Book added to cart...\n";
			}
			else if (input == "n") {
				cout << "The book has been removed from selection. Going back to the search menu\n";
				cout << "Please press <Enter> to continue \n";
				cin.get();
				continue;
			}
			else {
				cout << "Invalid input. Please enter only y or n\n";
			}
		}

		while (input != "1" && input != "3") { // Exit this loop only if the user wants to look for another book or if the transaction is complete
			cout << "\nPlease select from the following\n";
			cout << "1. Search for another book" << endl;
			cout << "2. View cart" << endl;
			cout << "3. Complete transaction (and to exit the module)" << endl;
			cout << "Input: ";
			cin >> input;
			cin.ignore();

			if (input == "2") {
				viewCart(receipt, numBooksBought);
			}
			else if (input == "3") {
				cout << "\nCompleting transaction...\n\n\n";
				completeTransaction(receipt, numBooksBought);
				finished = true;
			}
			else if (input != "1") {
				cout << "Invalid input, please enter 1, 2 or 3\n";
			}
		}
	}
}

void CashierModule::displayMenu() {
	cout << "\nTo find a book, you can search by ISBN or by title\n";
	cout << "1. Search by ISBN\n";
	cout << "2. Search by title\n";
	cout << "3. Go back to the main menu\n";
	cout << "input: ";
}

int CashierModule::continueISBN(Book *bookInv, int bookAmount) {
	long isbn;
	int index;
	cout << "\nEnter the ISBN of the book: ";
	isbn = getCheck_int();
	index = searchISBN(isbn, bookInv, bookAmount);

	if (index != -1) {
		cout << "Title of Book: " << bookInv[index].getTitle() << endl;
	}
	return index;
}

int CashierModule::continueTitle(Book *bookInv, int bookAmount) {
	int index;
	string title;
	cout << "Enter all of or part of the title of the book you want to buy\n";
	cout << "Title: ";
	getline(cin, title);
	index = searchTitle(title, bookInv, bookAmount);
	return index;
}

void CashierModule::addToCart(Book *bookInv, int buyQuantity, int index, fstream &output) {
	int temp = bookInv[index].getQuantity();
	bookInv[index].setQuantity(temp - buyQuantity);	// Since the book is added to the cart, update the number of books remaining in the inventory
	// Add items to cart
	output << buyQuantity << endl;
	output << bookInv[index].getISBN() << endl;
	output << bookInv[index].getTitle() << endl;
	output << bookInv[index].getAuthor() << endl;
	output << bookInv[index].getRetail() << endl;
}

void CashierModule::viewCart(fstream &receipt, int quantity) {
	string storage;
	// In order to view the file, the get pointer (point to element to be read in the next input operation) must be moved to the beginning
	// of the file. The current position of the get pointer is moved to the beginning of the file. Before this happens, obtain the current
	// position of the get pointer so that it can be reset at the end of the function
	int startingPos = receipt.tellg();	
	receipt.seekg(0);	// Move the get pointer to the beginning of the file
	cout << "\n\n***** Items in cart *****\n\n";
	getline(receipt, storage);	// First three lines correspond to the date that the user entered 
	getline(receipt, storage);	// at the beginning of the module, discard the date 
	getline(receipt, storage);
	for (int i = 0; i < quantity; i++) {
		getline(receipt, storage);
		cout << "Quantity: " << storage << endl;
		getline(receipt, storage);
		cout << "ISBN: " << storage << endl;
		getline(receipt, storage);
		cout << "Title: " << storage << endl;
		getline(receipt, storage);
		cout << "Author: " << storage << endl;
		getline(receipt, storage);
		cout << "Retail Price: " << storage << endl << endl;
	}
	cout << "Total books in cart: " << quantity << endl;
	cout << "\n***** End of cart *****\n";
	// Move the get pointer back to the original position
	receipt.seekg(startingPos);
}

void CashierModule::completeTransaction(fstream &receipt, int quantity) {
	Book *cart = new Book[quantity]; // Makes a new book array containing every book in the cart
	string storage;
	receipt.seekg(0);	// move cursor to beginning of the file

	// First three lines are the date information, retrieve
	getline(receipt, storage);
	cart[0].setMonth(stoi(storage));	// get month
	getline(receipt, storage);
	cart[0].setDay(stoi(storage));	// get day
	getline(receipt, storage);
	cart[0].setYear(stoi(storage));	// get year

	// Read from receipt file
	for (int i = 0; i < quantity; i++) {
		getline(receipt, storage);		// get quantity
		cart[i].setQuantity(stoi(storage));
		getline(receipt, storage);		// get isbn
		cart[i].setISBN(stol(storage));
		getline(receipt, storage);		// get title
		cart[i].setTitle(storage);
		getline(receipt, storage);		// get author
		cart[i].setAuthor(storage);
		getline(receipt, storage);		// get retail price
		cart[i].setRetail(stod(storage));
	}

	// Using the newly created book array, overwrite the receipt file
	makeReceipt(cart, quantity);
	readReceipt();	// Read from the receipt file and print onto the screen to end the transaction
	delete[] cart;
}

void CashierModule::makeReceipt(Book* cart, int quantity) {
	const int SIZE = 21;
	fstream receipt("receipt.txt", ios::out);
	string title, author;
	double subTotal = 0, taxAmount;
	const int numChar = 21;

	sort(BY_TITLE, cart, quantity);
	receipt << "\t\t***********************************" << endl;
	receipt << "\t\t*     Serendipity Booksellers     *" << endl;
	receipt << "\t\t*          Sales Receipt          *" << endl;
	receipt << "\t\t***********************************" << endl << endl;

	receipt << "Date: " << cart[0].getMonth() << "/" << cart[0].getDay() << "/" << cart[0].getYear();
	receipt << endl << endl << endl;
	receipt << "   Qty \t       ISBN \t   Title \t\t\t Author \t\t\t Price" << endl;
	receipt << "--------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < quantity; i++) {
		receipt << setw(5) << cart[i].getQuantity();	// quantity info
		receipt << setw(13) << cart[i].getISBN();		// isbn infor
		// Title
		title = cart[i].getTitle();
		receipt << "\t   " << left << setw(20) << title.substr(0,20);	// For proper formatting, print a maximum of 20 characters for the book title and author
		// Author
		author = cart[i].getAuthor();
		receipt << "\t\t " << setw(30) << author.substr(0, 20);
		receipt << "\t " << right << setw(5) << "$" << cart[i].getRetail() << endl;	// price info
		subTotal += cart[i].getRetail();
	}

	taxAmount = subTotal * (salesTax / 100);

	receipt << "\n\n" << "\t\tSubtotal: " << setprecision(2) << fixed << setw(10) << "$" << subTotal << endl;
	receipt <<  "\t\tTax " << salesTax << "%: " << setw(9) << "$" << taxAmount << endl;
	receipt << "\t\tGrand Total: " << setw(7) << "$" << subTotal + taxAmount << endl;
	
	receipt << endl << "Thank you for shopping with Serendipity Booksellers!!!\n";
	receipt.close();
}

void CashierModule::readReceipt() {
	fstream receipt("receipt.txt", ios::in);
	string reader;

	if (receipt) {
		while (getline(receipt, reader))
			cout << reader << endl;
	}
	receipt.close();
}