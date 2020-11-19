#include "item.h"
#include <fstream>
#include <time.h>

struct Node
{
	Node();
	~Node();

	Item* itemData;
	Node* next;
};



class HashTable
{
public:
	HashTable();
	~HashTable();
	
	int removeAllItems();
	int addItem(const Item& sourceItem);
	int loadHashTable(const char fileName[]);
	int removeItem(const char itemName[]);
	int retrieveItem(Item& retrievedItem, const char nameToRetrieve[]) const;
	int displayKeyItems(const char itemName[]) const;
	int displayAll() const;
	int giveItems(const int& numberOfItems, Item* returnedItems[]) const;

private:
	int _tableSize;
	Node** _hashTable;

	int _numberOfNodes;

	int generateRandom(const int& numberOfItems, int intArray[]) const;
	int generateKey(const char sourceCstring[]) const;
	Node* retrieveItemByPosition(const int& position) const;
	int getPrime(const char& aChar);
	int checkForDuplicate(Node*& head, const Item& itemToAdd) const;
};
