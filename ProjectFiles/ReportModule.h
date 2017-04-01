#ifndef REPORTMODULE_H
#define REPORTMODULE_H
#include <string>
#include "Module.h"
#include "Book.h"

class ReportModule :public Module{
protected:
	void displayMenu();

public: 
	void activateModule(Book*&, int&);
	void displayInv(Book*, int);
	void invWholeSale(Book*, int);
	void invRetail(Book*, int);
	void listQuantity(Book*, int);
	void listWholeSale(Book*, int);
	void listAge(Book*, int);
};
#endif