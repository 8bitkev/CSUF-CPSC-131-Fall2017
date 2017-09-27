#include "GroceryBill.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

GroceryBill::GroceryBill(const PriceList *priceList, double taxRate) {
    // Initialize the grocery bill data
	_priceList = priceList;
	_taxRate   = taxRate;
	_numItems  = 0;
	_headPtr   = NULL;
    _tailPtr   = NULL;
}

GroceryBill::~GroceryBill() {
    // Release memory utilized by the grocery bill list
    node *currentNode = _headPtr;
    node *nextNode;
    for (int i = 0; i < _numItems; ++i) {
        nextNode = currentNode->getLink();
        delete currentNode;
        currentNode = nextNode;
    }
}

void GroceryBill::scanItem(string scanCode, double quantity) {
    // Establish the maximum number of items allowed in the grocery bill list
    const int _maxItems = 1000;

    // Throw an exception if the scan code is invalid. 
    if (!_priceList->isValid(scanCode)) {
        throw invalid_argument("Item code is not valid");
    }
        
    // Throw an exception if the grocery bill is already full
    if (_numItems >= _maxItems) {
        throw out_of_range("Grocery bill is full, could not add new item");
    }
    
    // Create a new node for the grocery bill item list
    node* newNode = new node(scanCode, quantity);
    
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

// Scan multiple codes and quantities from the given text file
// Each line contains two numbers separated by space: the first is the code (an integer), the second the quantity (a float/double)
// Example line from text file:
// 15000000 1.5
void GroceryBill::scanItemsFromFile(string filename) {
    // Open file stream
    ifstream myfile(filename);

    // If the file was opened successfully, scan in the items
    if (myfile.is_open()) {
        cout << "Successfully opened file " << filename << endl;
        string scanCode;
        double quantity;
        while (myfile >> scanCode >> quantity) {
            // cout << scanCode << " " << quantity << endl;
            scanItem(scanCode, quantity);
        }
        myfile.close();
    }
    else {
        throw invalid_argument("Could not open file " + filename);
    }
}

// return the total cost of all items scanned
double GroceryBill::getTotal() {
    // Get a pointer to the head of the grocery bill list
    node* currentNode = _headPtr;
    
    // Calculate the total cost of the grocery bill
    string scanCode;
    double quantity;
    PriceListItem item;
    double totalItemCost;
    double grandTotal = 0.0;
    for (int i = 0; i < _numItems; ++i) {
        // Get the scan code and quantity for the current grocery bill item
        scanCode = currentNode->getScanCode();
        quantity = currentNode->getQuantity();
        
        // Use the scan code to get info from the price list
        item = _priceList->getItem(scanCode);
        
        // Calculate the cost for this item and add it to the running total
        totalItemCost = item.getPrice() * quantity;
        if (item.isTaxable()) totalItemCost *= 1.0 + (_taxRate / 100.0);
        grandTotal += totalItemCost;
        
        // Point to the next node in the list
        currentNode = currentNode->getLink();
    }
	
    return grandTotal;
}

// Print the bill to cout. Each line contains the name of an item, total price, and the letter "T" if tax was addded. 
// The last line shows the total.
// An example:
//Plastic_Wrap	1.60547 T
//Sugar_white	5.475
//Waffles_frozen	5.16
//Oil_Canola_100%_pure	2.69
//Potatoes_red	13.446
//TOTAL 	28.3765
void GroceryBill::printBill() {
    // Get a pointer to the head of the grocery bill list
    node* currentNode = _headPtr;
    
    // Process each item in the grocery bill
    string itemName;
    string scanCode;
    double quantity;
    PriceListItem item;
    double totalItemCost;
    for (int i = 0; i < _numItems; ++i) {
        // Get the scan code and quantity for the current grocery bill item
        scanCode = currentNode->getScanCode();
        quantity = currentNode->getQuantity();
        
        // Use the scan code to get info from the price list
        item = _priceList->getItem(scanCode);
        
        // Calculate the cost for this item
        totalItemCost = item.getPrice() * quantity;
        
        // Print the item information (adding tax if necessary)
        if (item.isTaxable()) {
            totalItemCost *= 1.0 + (_taxRate / 100.0);
            cout << item.getItemName() << "  " << totalItemCost << " T" << endl;;
        }
        else {
            cout << item.getItemName() << "  " << totalItemCost << endl;;
        }
        
        // Point to the next node in the list
        currentNode = currentNode->getLink();
    }

    // Print out the grand total
    cout << "TOTAL  " << getTotal() << endl;
}
