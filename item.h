#include <iostream>
#include <cstring>
#include "utilities.h"

class Item
{
public:
	Item();
	Item(char itemName[], char itemHint[], char itemLocaiton[]);
	Item(Item& sourceItem);
	~Item();

	int createItem(const char itemName[], const char itemHint[], const char itemLocation[]);
	int createItem(const Item& sourceItem);
	int copyItem(const Item& sourceItem);
	int copyItem(const char sourceName[]);
	int copyName(char copiedName[]) const;
	int nameSize() const;
	int compareNames(const Item& itemToCheck) const;
	int compareNames(const char nameToCheck[]) const;
	int displayItem();
	int displayHint();

private:
	char* _itemName;     // Name of the item
	char* _itemHint;     // Hint about the item location
	char* _itemLocation; // Location of the item

	int deleteItem();
};
