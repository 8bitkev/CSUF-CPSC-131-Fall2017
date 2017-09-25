#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "PriceList.h"
#include "PriceListItem.h"

using namespace std;

PriceList::PriceList(const PriceList &list) {
    // Initialize the new list data to reflect an empty list
    _numItems = 0;
    _headPtr  = NULL;
    _tailPtr  = NULL;
    
    // Get a pointer to the head of the list that is to be copied
    const node *currentNode = list._headPtr;
    
    // Copy the specified list into the new list
    PriceListItem *item;
    for (int i = 0; i < list._numItems; ++i) {
        item = currentNode->getData();
        addEntry(item->getItemName(), item->getCode(),
                 item->getPrice(), item->isTaxable());
        currentNode = currentNode->getLink();
    }
}

PriceList::~PriceList() {
    // Release memory utilized by the list. For each node in the list:
    // - first delete the price list item object
    // - second, delete the node object
    node *currentNode = _headPtr;
    node *nextNode;
    for (int i = 0; i < _numItems; ++i) {
        nextNode = currentNode->getLink();
        delete currentNode->getData();
        delete currentNode;
        currentNode = nextNode;
    }
}

// Load information from a text file with the given filename.
void PriceList::createPriceListFromDatafile(string filename) {
	ifstream myfile(filename);

	if (myfile.is_open()) {
		cout << "Successfully opened file " << filename << endl;
		string name;
		string code;
		double price;
		bool taxable;
		while (myfile >> name >> code >> price >> taxable) {
			// cout << code << " " << taxable << endl;
			addEntry(name, code, price, taxable);
		}
		myfile.close();
	}
	else {
		throw invalid_argument("Could not open file " + filename);
    }
}

// return true only if the code is valid
bool PriceList::isValid(string code) const {
    // Get a pointer to the head of the list
    node *currentNode = _headPtr;
    
    // Search the price list for a scan code match
    PriceListItem *item;
    for (int i = 0; i < _numItems; ++i) {
        item = currentNode->getData();
        if (code == item->getCode()) return true;
        currentNode = currentNode->getLink();
    }
    return false;
}

// return price, item name, taxable? as an ItemPrice object; throw exception if code is not found
PriceListItem PriceList::getItem(string code) const {
    // Throw an exception if the scan code is not valid
    if (!isValid(code)) {
        throw invalid_argument("Item scan code is not valid");
    }
    
    // Get a pointer to the head of the list
    node *currentNode = _headPtr;
    
    // Retrieve the price list item and return it
    PriceListItem *item;
    for (int i = 0; i < _numItems; ++i) {
        item = currentNode->getData();
        if (code == item->getCode()) break;
        currentNode = currentNode->getLink();
    }
    return *item;
}

// add to the price list information about a new item
void PriceList::addEntry(string itemName, string code, double price, bool taxable) {
    // Establish the maximum number of items allowed in the price list
    const int _maxItems = 1000000;
	
	// Throw an exception if the price list is full
    if (_numItems >= _maxItems) {
        throw out_of_range ("Price list is full, could not add new item");
    }
    
    // Create a new price list item 
    PriceListItem *newItem = new PriceListItem(itemName, code, price, taxable);
    
    // Create a new price list node 
    node* newNode = new node(newItem);
    
    // Add new node to the list
    if (_headPtr == NULL) {     // special case for inserting first node
        _headPtr = newNode;
        _tailPtr = newNode;
    }
    else {
        _tailPtr->setLink(newNode);
        _tailPtr = newNode;
    }
    ++_numItems;
}

PriceList& PriceList::operator = (const PriceList &list) {
    // Initialize the destination list data to reflect an empty list
    this->_numItems = 0;
    this->_headPtr  = NULL;
    this->_tailPtr  = NULL;
    
    // Get a pointer to the head of the list that is to be copied
    const node *currentNode = list._headPtr;
    
    // Copy the specified list into the new list
    PriceListItem *item;
    for (int i = 0; i < list._numItems; ++i) {
        item = currentNode->getData();
        addEntry(item->getItemName(), item->getCode(),
                 item->getPrice(), item->isTaxable());
        currentNode = currentNode->getLink();
    }
    return *this;
}

