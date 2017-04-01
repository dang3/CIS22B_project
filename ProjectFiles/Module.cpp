#include <iostream>
#include <fstream>
#include "Module.h"
#include "Book.h"
using namespace std; 

void Module::updateInvFile(Book *bookInv, int bookAmount) {
	fstream output("dataBase.txt", ios::out);

	for (int i = 0; i < bookAmount; i++) {
		output << bookInv[i].getISBN() << endl;

		output << bookInv[i].getTitle() << endl;
		output << bookInv[i].getAuthor() << endl;
		output << bookInv[i].getPublisher() << endl;
		output << bookInv[i].getMonth() << endl;
		output << bookInv[i].getDay() << endl;
		output << bookInv[i].getYear() << endl;
		output << bookInv[i].getQuantity() << endl;
		output << bookInv[i].getWholeSale() << endl;
		output << bookInv[i].getRetail() << endl << "\t" << endl;
	}
	output.close();
}

// Sorts based on the searchParameter (see Module.h)
void Module::sort(int searchParameter, Book *bookInv, int bookAmount) {
	int minIndex;
	Book temp;

	for (int i = 0; i < bookAmount; i++) {
		minIndex = i;
		for (int j = i + 1; j < bookAmount; j++) {
			if (searchParameter == BY_ISBN) {			// Sorting by ISBN (Used by the InventoryModule)
				if (bookInv[minIndex].getISBN() < bookInv[j].getISBN()) {
					minIndex = j;
				}
			}
			else if (searchParameter == BY_QUANTITY) {	// Sorting by quatity (used by ReportModule)
				if (bookInv[minIndex].getQuantity() < bookInv[j].getQuantity()) {
					minIndex = j;
				}
			}
			else if (searchParameter == BY_WHOLESALE) {	// Sorting by WholeSale (used by ReportModule)
				if (bookInv[minIndex].getWholeSale() < bookInv[j].getWholeSale()) {
					minIndex = j;
				}
			}
			else if (searchParameter == BY_TITLE) {	// Sorting by Title (used by Cashier Module)
				if (bookInv[minIndex].getTitle() > bookInv[j].getTitle()) {		// Capital letters first
					minIndex = j;
				}
			}
		}
		temp = bookInv[minIndex];
		bookInv[minIndex] = bookInv[i];
		bookInv[i] = temp;
	}
}

// Sorts by date, with oldest book first. First sort by year, then by month, then by day. When sorting,
// only swap if the day, month and year of one book is older than another book
void Module::sortDate(Book *bookInv, int bookAmount) {
	int minIndex = 0;
	Book temp;

	// Sort Year
	for (int i = 0; i < bookAmount; i++) {
		minIndex = i;
		for (int j = i + 1; j < bookAmount; j++) {
			if (bookInv[minIndex].getYear() > bookInv[j].getYear()) {
				minIndex = j;
			}
		}
		temp = bookInv[minIndex];
		bookInv[minIndex] = bookInv[i];
		bookInv[i] = temp;
	}
	// Month
	for (int i = 0; i < bookAmount; i++) {
		minIndex = i;
		for (int j = i + 1; j < bookAmount; j++) {
			if (bookInv[minIndex].getMonth() > bookInv[j].getMonth() && bookInv[minIndex].getYear() >= bookInv[j].getYear()) {
				minIndex = j;
			}
		}
		temp = bookInv[minIndex];
		bookInv[minIndex] = bookInv[i];
		bookInv[i] = temp;
	}
	// Day
	for (int i = 0; i < bookAmount; i++) {
		minIndex = i;
		for (int j = i + 1; j < bookAmount; j++) {
			if (bookInv[minIndex].getDay() > bookInv[j].getDay() && bookInv[minIndex].getMonth() >= bookInv[j].getMonth() && bookInv[minIndex].getYear() >= bookInv[j].getYear()) {
				minIndex = j;
			}
		}
		temp = bookInv[minIndex];
		bookInv[minIndex] = bookInv[i];
		bookInv[i] = temp;
	}
}

int Module::searchISBN(long isbnSearch, Book *bookInv, int bookAmount) {
	int left = 0, right = bookAmount - 1, mid, index = -1;
	bool found = false;

	sort(BY_ISBN, bookInv, bookAmount);		// Sort the inventory by ISBN before searching
	while (!found && left <= right) {
		mid = (left + right) / 2;

		if (isbnSearch == bookInv[mid].getISBN()) {
			index = mid;
			found = true;
		}
		else if (isbnSearch > bookInv[mid].getISBN()) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return index;
}

// This function allows the user to search for book by typing in all or part of a book's title
int Module::searchTitle(string inTitle, Book *bookInv, int bookAmount) {
	long isbn;
	int inTitleLength = inTitle.length(), counter = 0, index = -1, j = 0;
	string getTitle, formattedTitle;

	// Because we are searching for more than 1 title, we use linear search. Therefore, no sorting is necessary
	for (int i = 0; i < bookAmount; i++) {
		getTitle = bookInv[i].getTitle();		// Obtain the full title of each book
		formattedTitle = getTitle.substr(0, inTitleLength);	// For each title obtained, extract the number of characters  equal to the number of characters of the input title
		if (inTitle == formattedTitle) {
			// if a match is found, increment counter, counter will be used to dynamically allocate an area containing the books whose title match the input title
			counter++;
			index = i;
		}
	}
	// If only 1 match is found after searching, return the index of the book whose title matches the input title. 	if no match is found, -1 is returned
	if (counter <= 1) {
		return index;
	}
	else {
		// The program enters this block when more than 1 match is found
		Book *matchedBooks = new Book[counter];	// Dynamically allocate an area to hold the books that whose title match with the input title
		index = -1;		// Index is reset to -1, to be used later on if the user enters an ISBN that does not match with any of the books listed

		// Perform the same operation as before, except now each time there is a match, store the index of that book in the allocated array
		for (int i = 0; i < bookAmount; i++) {
			getTitle = bookInv[i].getTitle();
			formattedTitle = getTitle.substr(0, inTitleLength);
			if (inTitle == formattedTitle)
				matchedBooks[j++] = bookInv[i];	// i is the indexing variable for bookInv, a seperate indexing variable j is used for the matchBooks array
		}

		cout << "\nUsing the information that you've entered, multiple matches have been found\n";
		cout << "Press <Enter> to continue";
		cin.get();
		cout << "\n\n******** Books that match your input ********\n\n";
		cout << "Your input: " << inTitle << endl << endl;
		for (int i = 0; i < counter; i++) {
			cout << "ISBN: " << matchedBooks[i].getISBN() << endl;	// Print out the books that match
			cout << "Title: " << matchedBooks[i].getTitle() << endl;
			cout << "Retail price: $" << matchedBooks[i].getRetail() << endl << endl;
		}
		cout << "To make a selection, enter the ISBN of the desired book\n";
		while (index < 0) {
			cout << "ISBN: ";
			isbn = getCheck_int();
			// returns the index from the new array, needs to return index from old array
			index = searchISBN(isbn, matchedBooks, counter);	// Using the isbn entered, search through the new book array to see if the user entered a valid isbn
			if (index < 0) {
				cout << "The ISBN you have entered does not match any of the ones listed. Please try again\n";
			}
			index = searchISBN(isbn, bookInv, bookAmount);		// If the isbn is valid, then search through the original bookInv array for the book index
		}
		delete[] matchedBooks;
	}
	return index;
}
// Counts the number of lines in the database file, then divides that number by the bookLine (the number of lines of information corresponding to each book) to get the total number of books
void Module::updateNumBooks(int &bookAmount) {		
	fstream input("dataBase.txt", ios::in);		
	int numLines = 0;							
	char test;									

	if (input) {
		while (input.get(test)) {
			if (test == '\n') {
				numLines++;
			}
		}
	}
	input.close();
	bookAmount = numLines / bookLine;
}

// Whenever the user is prompted to enter an integer/long (except for date information), use this this functon to check for valid input
long Module::getCheck_int() {
	bool tryAgain = true;						
	string input;

	while (tryAgain) {
		cin >> input;
		cin.ignore();
		try {
			checkForDigits(input);	// Only digits are allowed to be entered
			tryAgain = false;
		}
		catch (string inputException) {
			cerr << inputException;
			cout << "\nNew Input: ";	
		}
	}
	return stol(input);
}

// When the user is prompted to enter information for the date, call this function
int Module::getCheck_date(int parameter) {
	bool tryAgain = true;
	int temp;
	string input;

	while (tryAgain) {
		cin >> input;
		cin.ignore();
		try {
			checkForDigits(input);	// check to make sure input is only digits
			temp = stoi(input);		// convert string to int
			if (parameter == MONTH && (temp < 1 || temp > 12)) {	// if checking months, input is between 1 and 12 (for January and December)
				cout << "Please enter an integer between 1 and 12 corresponding to the months\n";
				cout << "Month: ";
				continue;
			}
			else if (parameter == DAY && (temp < 1 || temp > 31)) {	// if checking days, make sure input is between 1 and 31 (for the days of the month)
				cout << "Please enter an integer between 1 and 31 corresponding to the days of the month\n";
				cout << "Day: ";
				continue;
			}
			tryAgain = false;	// only end the loop when all requirements for month/days input are met
		}
		catch (string inputException) {
			cerr << inputException;
			cout << "\nNew Input: ";
		}
	}
	return temp;
}

// Call this function when the user is prompted to enter floating point numbers, a valid input contains only digits and a maximum of 1 decimal point
double Module::getCheck_double() {
	bool tryAgain = true;
	double temp;
	string input;
	
	while (tryAgain) {
		bool decimalFound = false;
		cin >> input;
		cin.ignore();
		try {
			checkForLetters(input);	// Check to make sure input doesn't contain letters
			for (int i = 0; i < input.length(); i++) {
				if (input[i] == '.' && decimalFound == true) {	// Checks if there are more than 1 decimal point
					string message = "Please enter a valid floating point number. A valid floating point number consists of only 1 decimal point.\n";
					throw message;
				}
				if (input[i] == '.')
					decimalFound = true;
			}
			tryAgain = false;
		}
		catch (string inputException) {
			cerr << inputException;
			cout << "\nNew Input: ";
		}
	}
	temp = stod(input);
	return temp;
}

string Module::getCheck_YN() {
	string choice = "";

	while (choice != "y" && choice != "n") {
		cin >> choice;
		cin.ignore();

		if (choice != "y" && choice != "n") {
			cout << "Invalid input, please enter only y or n\n";
			cout << "Input (y/n): ";
		}
	}
	return choice;
}
// Check the entire input string for only digits, if letters or special characters are found, throw an exception
void Module::checkForDigits(string input) {
	for (int i = 0; i < input.length(); i++) {
		if (!isdigit(input[i])) {
			string inputException_digits = "\nInput error. Please enter only digits!";
			throw inputException_digits;
		}
	}
}

// Checks if the input string contains letters and special characers
void Module::checkForLetters(string input) {
	for (int i = 0; i < input.length(); i++) {
		if (isalpha(input[i])) {	// Checks for letters
			string inputException_letters = "\nInput error. Please enter only digits!";
			throw inputException_letters;
		}
		if (!isdigit(input[i]) && input[i] != '.') {	// Checks for special characters that are not decimal points
			string inputException = "\nInvalid input. Please do not enter any special characters other than a decimal point";
			throw inputException;
		}
	}
}