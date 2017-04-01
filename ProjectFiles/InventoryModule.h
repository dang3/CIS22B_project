#ifndef INVENTORYMODULE_H
#define INVENTORYMODULE_H
#include <string>
#include "Module.h"
#include "Book.h"

class InventoryModule:public Module {
protected:		
	void displayMenu();


public:
	void activateModule(Book*&, int&);
	Book* makeInv(int);
	void lookUpBook(Book*, int);
	void addBook(Book*&, int&);
	void editBook(Book*, int);
	void removeBook(Book*, int&);
};
#endif