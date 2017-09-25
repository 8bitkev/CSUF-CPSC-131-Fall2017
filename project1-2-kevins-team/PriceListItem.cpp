#include "PriceListItem.h"

PriceListItem::PriceListItem(const string &itemName, const string &code, double price, bool taxable) {
    _itemName = itemName;
    _code     = code;
    _price    = price;
    _taxable  = taxable;
}

PriceListItem::PriceListItem() {
    _itemName = "";
    _code     = "";
    _price    = 0.0;
    _taxable  = false;
}

string PriceListItem::getItemName() {
    return _itemName;
}

string PriceListItem::getCode() {
    return _code;
}

double PriceListItem::getPrice() {
    return _price;
}

bool PriceListItem::isTaxable() {
    return _taxable;
}
