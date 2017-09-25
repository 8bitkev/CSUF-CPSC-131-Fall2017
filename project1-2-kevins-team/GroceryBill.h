#pragma once

#include "PriceList.h"

class GroceryBill {
public:
	GroceryBill(const PriceList *priceList, double taxRate);
    ~GroceryBill(); // Destructor
	void scanItem(string scanCode, double quantity); // add item and quantity to bill; throw exception if item's code is not found in the pricelist
	void scanItemsFromFile(string filename); // Scan multiple codes and quantities from the given text file
	double getTotal(); // return the total cost of all items scanned
	void printBill(); // Print the bill to cout. Each line contains the name of an item, total price, and the letter "T" if tax was addded.

private:
	// any private member variables and methods go here
    class node {    // Node to support a singly link list
    public:
        // Constructor
        node(const string& scanCode, double quantity, node* initLink = NULL)
        { _scanCode = scanCode; _quantity = quantity; _linkField = initLink; }
    
        // Member functions to set the data and link fields
        void setScanCode(const string& scanCode) { _scanCode = scanCode; }
        void setQuantity(double quantity) { _quantity = quantity; }
        void setLink(node* newLink) { _linkField = newLink; }

        // Constant member functions to retrieve the node data
        string getScanCode() const { return _scanCode; }
        double getQuantity() const { return _quantity; }
    
        // Constant member function to retrieve link to next node in list
        node* getLink() const { return _linkField; }
    
    private:
        string _scanCode;   // Scan code for item
        double _quantity;   // Quantity purchased for this item
        node* _linkField;   // Link to next node in list
    };
    
    node* _headPtr; // Pointer to first node in price list
    node* _tailPtr; // Pointer to last node in price list
    int _numItems;  // Number of items in price list
    const PriceList *_priceList; // Pointer to price list
    double _taxRate; // Tax rate (in percent)
};
