#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>

// The number of lines of information corresponding to each book (includes \n character of each book, but DOESN'T INCLUDE DATE INFORMATION)
const int bookLine = 11;		// Used to determine the number of books

class Book {
private:
	long isbn;
	std::string title, author, publisher;
	int month, day, year;
	int quantity;
	double wholeSale, retail;

public:
	// Setters
	void setISBN(long);
	void setTitle(std::string);
	void setAuthor(std::string);
	void setPublisher(std::string);
	void setMonth(int);
	void setDay(int);
	void setYear(int);
	void setQuantity(int);
	void setWholeSale(double);
	void setRetail(double);

	// Getters
	long getISBN();
	std::string getTitle();
	std::string getAuthor();
	std::string getPublisher();
	int getMonth();
	int getDay();
	int getYear();
	int getQuantity();
	double getWholeSale();
	double getRetail();

	// Overloaded operators
	friend std::ostream &operator << (std::ostream &strm, Book &book);
};
#endif