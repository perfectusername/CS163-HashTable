#include "item.h"


using std::cout;
using std::endl;

Item::Item()
{
	_itemName = nullptr;
	_itemHint = nullptr;
	_itemLocation = nullptr;
}



Item::Item(char itemName[], char itemHint[], char itemLocation[])
{
	_itemName = nullptr;
	_itemLocation = nullptr;
	_itemHint = nullptr;

	if ((itemName != nullptr) && (itemLocation != nullptr) && (itemHint != nullptr))
	{
		createItem(itemName, itemLocation, itemHint);
	}
}



Item::Item(Item& sourceItem)
{
	_itemName = nullptr;
	_itemLocation = nullptr;
	_itemHint = nullptr;

	createItem(sourceItem._itemName, sourceItem._itemLocation, sourceItem._itemHint);
}



Item::~Item()
{
	deleteItem();
}




int Item::createItem(const char itemName[], const char itemHint[], const char itemLocation[])
{
	int successValue = 0;

	deleteItem();

	if ((_itemName == nullptr) && (_itemHint == nullptr) && (_itemLocation == nullptr))
	{
		_itemName = new char[strlen(itemName) + 1];
		strcpy(_itemName, itemName);

		_itemHint = new char[strlen(itemHint) + 1];
		strcpy(_itemHint, itemHint);

		_itemLocation = new char[strlen(itemLocation) + 1];
		strcpy(_itemLocation, itemLocation);

		successValue = 1;
	}

	return successValue;

}



int Item::createItem(const Item& sourceItem)
{
	int successValue = 0;

	successValue = createItem(sourceItem._itemName, sourceItem._itemHint, sourceItem._itemLocation);

	return successValue;

}



int Item::deleteItem()
{
	int successValue = 0;

	if (_itemName != nullptr)
	{
		delete[] _itemName;
		_itemName = nullptr;
	}

	if (_itemHint != nullptr)
	{
		delete[] _itemHint;
		_itemHint = nullptr;
	}

	if (_itemLocation != nullptr)
	{
		delete[] _itemLocation;
		_itemLocation = nullptr;
	}

	if ((_itemName == nullptr) && (_itemHint == nullptr) && (_itemLocation == nullptr))
	{
		successValue = 1;
	}

	return successValue;

}



int Item::copyItem(const Item& sourceItem)
{
	return createItem(sourceItem._itemName, sourceItem._itemHint, sourceItem._itemLocation);
}



int Item::copyItem(const char sourceName[])
{
	int successValue = 0;

	

	return successValue;
}



int Item::copyName(char copiedName[]) const
{
	int successValue = 0;

	if ((copiedName != nullptr) && (_itemName != nullptr))
	{
		strcpy(copiedName, _itemName);
		successValue = 1;
	}

	return successValue;
}



int Item::nameSize() const
{
	return strlen(_itemName);
}



// Returns a negative number if the calling itemName is lower
// Returns a positive number if the calling itemName is higher
// Returns a 0 if the names match.
int Item::compareNames(const Item& itemToCheck) const
{
	return strcmp(_itemName, itemToCheck._itemName);
}



int Item::compareNames(const char nameToCheck[]) const
{
	return strcmp(_itemName, nameToCheck);
}



int Item::displayItem()
{
	int successValue = 0;

	if ((_itemName != nullptr) && (_itemHint != nullptr) && (_itemLocation != nullptr))
	{
		cout << endl;
		cout << "Item Name: " << _itemName << endl;
		cout << "Item Hint: " << _itemHint << endl;
		cout << "Item Location: " << _itemLocation << endl;
		cout << endl;
		successValue = 1;
	}

	return successValue;
}



int Item::displayHint()
{
        int successValue = 0;

        if ((_itemName != nullptr) && (_itemHint != nullptr) && (_itemLocation != nullptr))
        {
                cout << endl;
                cout << "Item Name: " << _itemName << endl;
                cout << "Item Hint: " << _itemHint << endl;
                cout << endl;
                successValue = 1;
        }

        return successValue;
}
