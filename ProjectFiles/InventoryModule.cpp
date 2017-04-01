#include <iostream>
#include <string>
#include <fstream>
#include "Book.h"
#include "InventoryModule.h"
#include "ReportModule.h"
#include "Module.h"
using namespace std;

void InventoryModule::displayMenu() {
	cout << endl;
	cout << "***********************************" << endl;
	cout << "*     Serendipity Booksellers     *" << endl;
	cout << "*        Inventory Database       *" << endl;
	cout << "***********************************" << endl << endl;
	cout << "1. Look up a book                  " << endl;
	cout << "2. Add a book                      " << endl;
	cout << "3. Edit a book's record            " << endl;
	cout << "4. Delete a book                   " << endl;
	cout << "5. Return to the Main Menu         " << endl << endl;
	cout << "Enter your choice: ";
}

void InventoryModule::activateModule(Book *&bookInv, int &bookAmount) {
	string choice; 
	while (1) {
		displayMenu();
		cin >> choice;
		cin.ignore();

		if (choice == "1") {
			lookUpBook(bookInv, bookAmount);
		}
		else if (choice == "2") {
			addBook(bookInv, bookAmount);
		}
		else if (choice == "3") {
			editBook(bookInv, bookAmount);
		}
		else if (choice == "4") {
			removeBook(bookInv, bookAmount);
		}
		else if (choice == "5") {
			return;
		}
		else {
			cout << "Invalid choice\n";
		}
	}
}

Book *InventoryModule::makeInv(int bookAmount) {		// Reads from the database file to dynamically create
	string str;											//  an array of Book objects
	fstream input("dataBase.txt", ios::in);
	Book *bookInv = new Book[bookAmount];

	for (int i = 0; i < bookAmount; i++) {
		// Set isbn
		getline(input, str);
		bookInv[i].setISBN(stol(str));
		// Set title
		getline(input, str);
		bookInv[i].setTitle(str);
		// Set author
		getline(input, str);
		bookInv[i].setAuthor(str);
		// Set publisher
		getline(input, str);
		bookInv[i].setPublisher(str);
		// Date
		getline(input, str);				// month
		bookInv[i].setMonth(stoi(str));
		getline(input, str);				// day
		bookInv[i].setDay(stoi(str));
		getline(input, str);				// year
		bookInv[i].setYear(stoi(str));
		// Set quantity on hand
		getline(input, str);
		bookInv[i].setQuantity(stoi(str));
		// Set whole sale cost
		getline(input, str);
		bookInv[i].setWholeSale(stod(str));
		// Set retail price
		getline(input, str);
		bookInv[i].setRetail(stod(str));
		getline(input, str); // discard \n character at the end of each book
	}
	input.close();
	return bookInv;
}

// Similar to the Cashier Module, the user can look up a book by ISBN or by title
void InventoryModule::lookUpBook(Book *bookInv, int bookAmount) {
	int index = -1;
	long isbn;
	string input, title;
	bool searchAgain = true;

	cout << "\nTo find a book, you can search by ISBN or by title\n";
	while (searchAgain) {
		cout << "1. Search by ISBN\n";
		cout << "2. Search by title\n";
		cout << "3. Go back to the previous menu\n";
		cout << "Input: ";
		cin >> input;
		cin.ignore();
		// Get user input
		if (input == "1") {
			cout << "ISBN: ";
			isbn = getCheck_int();
			index = searchISBN(isbn, bookInv, bookAmount);
		}
		else if (input == "2") {
			cout << "Enter all or part of the title of the book you want to buy\n";
			cout << "Title: ";
			getline(cin, title);
			index = searchTitle(title, bookInv, bookAmount);
		}
		else if (input == "3")
			return;
		else {
			cout << "Invalid option, please enter only 1, 2 or 3\n";
			continue;
		}

		// Check if the book exists
		if (index < 0) {
			cout << "No books can be found using the information that you have entered\n. Do you want to search again? (y/n): ";
			while (input != "y" && input != "n") {
				cout << "Input: ";
				cin >> input;
				cin.ignore();
				if (input == "y")
					continue;
				else if (input == "n")
					return;
				else
					cout << "Invalid input. please enter only y or n\n";
			}
		}
		// If the book exists, then do not loop anymore
		else
			searchAgain = false;
	}
	// Print out the book's information
	cout << "\nBook Information: " << endl;
	cout << bookInv[index] << endl;
}

void InventoryModule::addBook(Book *&bookInv, int &bookAmount) {		
	int index = -1, tempInt, month, day, year;						
	long tempLong;
	double tempDouble;
	bool tryAgain = true;
	string input;
	fstream output("dataBase.txt", ios::app);
	Book *updatedInv;

	cout << "ISBN: ";
	tempLong = getCheck_int();

	index = searchISBN(tempLong, bookInv, bookAmount);

	// If the book already exists in the inventory, then update the quantity
	if (index > 0) {
		int addQuantity, oldQuantity;
		cout << "\nUsing the ISBN information that you have entered, we have that the book that you are trying to add already\n";
		cout << "exists in the inventory. How many more do you wish to add to the inventory?. Enter 0 if you do not wish to add any.\n";
		cout << "Quantity: ";
		addQuantity = getCheck_int();
		oldQuantity = bookInv[index].getQuantity();
		bookInv[index].setQuantity(oldQuantity + addQuantity);	// updating the new quantity, old quantity + add quantity = new quantity
		updateInvFile(bookInv, bookAmount);	// update the database file
		cout << "Quantity updated\n\n";
		output.close();
	}
	// If the book does not exist, have the user enter the new book's information
	else {
		output << tempLong << endl;

		cout << "Title: ";
		getline(cin, input);
		output << input << endl;

		cout << "Author: ";
		getline(cin, input);
		output << input << endl;

		cout << "Publisher: ";
		getline(cin, input);
		output << input << endl;

		cout << "Enter today's date (digits only), starting with the month\n";
		cout << "Month: ";
		month = getCheck_date(MONTH);
		output << month << endl;

		cout << "Day: ";
		day = getCheck_date(DAY);
		output << day << endl;

		cout << "Year: ";
		year = getCheck_int();
		output << year << endl;

		cout << "Quantity-on-hand: ";
		tempInt = getCheck_int();
		output << tempInt << endl;

		cout << "Wholesale cost: ";
		tempDouble = getCheck_double();
		output << tempDouble << endl;

		cout << "Retail price: ";
		tempDouble = getCheck_double();
		output << tempDouble << endl;

		output << "\t\n";
		cout << "\nBook added\n\n";
		
		// If the user enters a new book, update the total number of books quantity and remake the book array
		output.close();
		updateNumBooks(bookAmount);
		cout << "Total number of books in inventory: " << bookAmount << endl << endl;
		delete[] bookInv;
		bookInv = makeInv(bookAmount);
	}
}

void InventoryModule::editBook(Book *bookInv, int bookAmount) {			
	int index = -1, tempInt;
	long isbn;
	string input;
	double tempDouble;
	bool searchAgain = true;

	while (searchAgain) {
		cout << "Please enter the ISBN of the book you want to edit: ";
		isbn = getCheck_int();
		index = searchISBN(isbn, bookInv, bookAmount);

		if (index > 0)
			searchAgain = false;

		while (index < 0) {
			cout << "The book you entered does not exists. Do you want to search again (y/n): ";
			input = getCheck_YN();
			
			if (input == "n")
				return;
			else
				break;
		}
	}

	cout << "\n\nBook Information:" << endl;
	cout << bookInv[index] << endl << endl;
	cout << "Which attribute of this book do you want to modify?\n";
	cout << "1. ISBN" << endl;
	cout << "2. Title" << endl;
	cout << "3. Author" << endl;
	cout << "4. Publisher" << endl;
	cout << "5. Date" << endl;
	cout << "6. Quantity" << endl;
	cout << "7. Wholesale Cost" << endl;
	cout << "8. Retail Cost" << endl;
	cout << "9. Return to the previous menu" << endl;

	while (1) {
		cout << "Selection: ";
		cin >> input;
		cin.ignore();

		if (input == "1") {
			cout << "Updated ISBN: ";
			isbn = getCheck_int();
			bookInv[index].setISBN(isbn);
			cout << "ISBN information updated\n\n";
		}
		else if (input == "2") {
			cout << "Updated Title: ";
			getline(cin, input);
			bookInv[index].setTitle(input);
			cout << "Title updated\n\n";
		}
		else if (input == "3") {
			cout << "Updated Author: ";
			getline(cin, input);
			bookInv[index].setAuthor(input);
			cout << "Author updated\n\n";
		}
		else if (input == "4") {
			cout << "Updated Publisher: ";
			getline(cin, input);
			bookInv[index].setPublisher(input);
			cout << "Publisher updated\n\n";
		}
		else if (input == "5") {
			int month, day, year;
			cout << "Updated month (digits only): ";
			month = getCheck_date(MONTH);
			cout << "Updated day (digits only): ";
			day = getCheck_date(DAY);
			cout << "Updated year (digits only): ";
			year = getCheck_int();
			bookInv[index].setMonth(month);
			bookInv[index].setDay(day);
			bookInv[index].setYear(year);
			cout << "Date updated\n\n";
		}
		else if (input == "6") {
			cout << "Updated Quantity-on-hand: ";
			tempInt = getCheck_int();
			bookInv[index].setQuantity(tempInt);
			cout << "Quantity updated\n\n";
		}
		else if (input == "7") {
			cout << "Updated Wholesale cost: $";
			tempDouble = getCheck_double();
			bookInv[index].setWholeSale(tempDouble);
			cout << "Wholesale cost updated\n\n";
		}
		else if (input == "8") {
			cout << "Updated Retail price: $";
			tempDouble = getCheck_double();
			bookInv[index].setRetail(tempDouble);
			cout << "Retail price updated\n\n";
		}
		else if (input == "9") {
			return;
		}
		else {
			cout << "Invalid input\n\n";
		}

		cout << "Would you like to modify another attribute of the same book?\n";
		cout << "Input (y/n): ";
		input = getCheck_YN();

		if (input == "n") {
			cout << "\n\nReturning the previous menu...\n";
			cout << "Press <Enter> to continue\n";
			cin.get();
			break;
		}
	}
	updateInvFile(bookInv, bookAmount);	// Update the file if changes are made
}

void InventoryModule::removeBook(Book *bookInv, int &bookAmount) {
	int index = -1;
	long isbn;
	Book temp;
	bool confirm = false;
	string choice;

	cout << "Please enter the ISBN of the book you wish to remove from he inventory\n";

	while (index < 0) {
		cout << "ISBN: ";
		isbn = getCheck_int();
		index = searchISBN(isbn, bookInv, bookAmount);

		if (index < 0) {
			cout << "There is no match with the ISBN that you have entered with any of the books in the inventory.\n";
			cout << "Please enter another ISBN\n";
		}
		else {
			cout << "\n\nInformation corresponding to the book you want to remove\n\n";
			cout << bookInv[index];
			cout << "\nAre you sure you want to delete this book? (y/n): ";
			choice = getCheck_YN();

			if (choice == "y")
				confirm = true;
			else if (choice == "n") {
				cout << "\n\nReturning to the previous menu...\n";
				cout << "Press <Enter> to continue\n";
				cin.get();
				return;
			}
		}
	}

	if (confirm == true) {
		for (int i = index; i < bookAmount - 1; i++) {
			bookInv[i] = bookInv[i + 1];
		}
		bookAmount--;
		cout << "Inventory Updated\n";
		cout << "The book with the ISBN " << isbn << " has been removed\n";
		updateInvFile(bookInv, bookAmount);
	}
}
