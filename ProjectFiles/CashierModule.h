#ifndef CASHIERMODULE_H
#define CASHIERMODULE_H
#include "Module.h"
#include <fstream>
#include <string>

class CashierModule : public Module {
protected: 
	const double salesTax = 8.75;
	double totalPrice;

	void clearReceiptFile();
	void displayMenu();
	int continueISBN(Book*, int);
	int continueTitle(Book*, int);
	void addToCart(Book*, int, int, std::fstream&);
	void viewCart(std::fstream&, int);
	void completeTransaction(std::fstream&, int);
	void makeReceipt(Book*, int);
	void readReceipt();
	
public:
	void activateModule(Book*&, int&);
};
#endif
