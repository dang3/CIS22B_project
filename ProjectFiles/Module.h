#ifndef MODULE_H
#define MODULE_H
#include <string>
#include <iostream>
#include "Book.h"

class Module {
protected:
	// Search parameters, for inventory sorting
	const int BY_ISBN = 0,
		BY_QUANTITY = 1,
		BY_WHOLESALE = 2,
		BY_TITLE = 3;

	// For checking date input
	const int MONTH = 4,
		DAY = 5;
	void updateInvFile(Book*, int);
	void sort(int, Book*, int);
	void sortDate(Book*, int);
	int searchISBN(long, Book*, int);
	int searchTitle(std::string, Book*, int);
	int getCheck_date(int);
	long getCheck_int();
	double getCheck_double();
	std::string getCheck_YN();
	void checkForDigits(std::string);
	void checkForLetters(std::string);

public:
	virtual void activateModule(Book*&, int&) { std::cout << "not mean to be seen\n"; }
	static void updateNumBooks(int&);
};
#endif