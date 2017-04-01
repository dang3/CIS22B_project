#include <fstream>
#include "Book.h"

using namespace std;

// *******************************************************************************************
// Setters
// *******************************************************************************************

void Book::setISBN(long isbn) {
	this->isbn = isbn;
}

void Book::setTitle(std::string title) {
	this->title = title;
}

void Book::setAuthor(std::string author) {
	this->author = author;
}

void Book::setPublisher(std::string publisher) {
	this->publisher = publisher;
}

void Book::setMonth(int month) {
	this->month = month;
}

void Book::setDay(int day) {
	this->day = day;
}

void Book::setYear(int year) {
	this->year = year;
}

void Book::setQuantity(int quantity) {
	this->quantity = quantity;
}

void Book::setWholeSale(double wholeSale) {
	this->wholeSale = wholeSale;
}

void Book::setRetail(double retail) {
	this->retail = retail;
}

// *******************************************************************************************
// Getters
// *******************************************************************************************

long Book::getISBN() {
	return isbn;
}

std::string Book::getTitle() {
	return title;
}

std::string Book::getAuthor() {
	return author;
}

std::string Book::getPublisher() {
	return publisher;
}

int Book::getMonth() {
	return month;
}

int Book::getDay() {
	return day;
}

int Book::getYear() {
	return year;
}

int Book::getQuantity() {
	return quantity;
}

double Book::getWholeSale() {
	return wholeSale;
}

double Book::getRetail() {
	return retail;
}

ostream &operator << (ostream &strm, Book &book) {
	strm << "ISBN: " << book.isbn << endl;
	strm << "Title: " << book.title << endl;
	strm << "Author: " << book.author << endl;
	strm << "Publisher: " << book.publisher << endl;
	strm << "Date Added: " << book.month << "/" << book.day << "/" << book.year << endl;
	strm << "Quantity on hand: " << book.quantity << endl;
	strm << "Wholesale cost: $" << book.wholeSale << endl;
	strm << "Retail price: $" << book.retail << endl << endl;
	return strm;
}