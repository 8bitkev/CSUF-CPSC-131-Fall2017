#pragma once
#include <string>
#include <stdexcept>
#include "PriceListItem.h"

using namespace std;

class PriceList {
public:
    PriceList() { _headPtr = NULL; _tailPtr = NULL; _numItems = 0; } // Default constructor
    PriceList(const PriceList& list); // Alternate constructor
    ~PriceList(); // Destructor
	void createPriceListFromDatafile(string filename); // Load information from a text file with the given filename (Completed)
	void addEntry(string itemName, string code, double price, bool taxable); // add to the price list information about a new item. A max of 1,000,000 entries can be added
	bool isValid(string code) const; // return true only if the code is valid
	PriceListItem getItem(string code) const; // return price, item name, taxable? as a PriceListItem object; throw exception if code is not found
    PriceList& operator = (const PriceList &list); // assignment operator

private:
    // Add private member variables for your class along with any 
    // other variables required to implement the public member functions
    class node {    // Node to support a singly link list
    public:
        // Constructor
        node(PriceListItem* initData, node* initLink = NULL)
        { _dataField = initData; _linkField = initLink; }
    
        // Member functions to set data and link fields
        void setData(PriceListItem* newData) { _dataField = newData; }
        void setLink(node* newLink) { _linkField = newLink; }

        // Constant member function to retrieve node data
        PriceListItem* getData() const { return _dataField; }
    
        // Constant member function to retrieve link to next node in list
        node* getLink() const { return _linkField; }
    private:
        PriceListItem* _dataField; // Data
        node* _linkField;          // Link to next node in list
    };
    
    node* _headPtr; // Pointer to first node in price list
    node* _tailPtr; // Pointer to last node in price list
    int _numItems;  // Number of items in price list
};
