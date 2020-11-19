#include "hashtable.h"

using std::cout;
using std::endl;
using std::ifstream;

const int TABLE_SIZE = 37;

// NODE STRUCT
//
// Node Default constructor
Node::Node()
{
	itemData = nullptr;
	next = nullptr;
}



// Node Destructor
Node::~Node()
{
	if (itemData != nullptr)
	{
		delete itemData;
		itemData = nullptr;
	}
	
	next = nullptr;
}



// HASHTABLE CLASS
//
// Default constructor
HashTable::HashTable()
{
	int i;

	_tableSize = TABLE_SIZE;
	_numberOfNodes = 0;
	_hashTable = new Node*[_tableSize]; // Delete pair is in destructor ~HashTable
	Node** currentNode = _hashTable;
	
	for (i = 0; i < _tableSize; ++i)
	{
		*currentNode = nullptr;
		++currentNode;
	}
}



HashTable::~HashTable()
{
	int i;

	Node** currentNode = _hashTable;
	Node** previousNode;
	Node* innerCurrent;
	Node* innerPrevious;


	if (_hashTable != nullptr)
	{
		// Look at each index
		for (i = 0; i < _tableSize; ++i)
		{
			// If the Node** index is not null
			if (currentNode != nullptr)
			{
				// Look at the inner Node* and delete
				// the chain until its gone
				innerCurrent = *currentNode;
				while (innerCurrent != nullptr)
				{
					innerPrevious = innerCurrent;
					innerCurrent = innerCurrent->next;
					delete innerPrevious;
					innerPrevious = nullptr;
				}
				// Delete the Node**
			}
			// Get to the next index
			++currentNode;
		}
		// Delete the entire hash table when done.
		delete[] _hashTable;
		_hashTable = nullptr;
	}



/*
	if (_hashTable != nullptr)
	{
		for (i = 0; i < _tableSize; ++i)
		{
			if (*currentNode != nullptr)
			{
				innerCurrent = *currentNode;
				while (innerCurrent != nullptr)
				{
					innerPrevious = innerCurrent;
					innerCurrent = innerCurrent->next;
					delete innerPrevious;
					innerPrevious = nullptr;
				}
			}
			previousNode = currentNode;
			++currentNode;
			delete previousNode;
			previousNode = nullptr;
		}
	}

	if (_hashTable != nullptr)
	{
		delete[] _hashTable;
	}
*/
}



int HashTable::removeAllItems()
{
	int i;
	int successValue = 0;

	Node** currentNode = _hashTable;
	Node** previousNode;
	Node* innerCurrent;
	Node* innerPrevious;


	if (_hashTable != nullptr)
	{
		// Look at each index
		for (i = 0; i < _tableSize; ++i)
		{
			// If the Node** index is not null
			if (currentNode != nullptr)
			{
				// Look at the inner Node* and delete
				// the chain until its gone
				innerCurrent = *currentNode;
				while (innerCurrent != nullptr)
				{
					innerPrevious = innerCurrent;
					innerCurrent = innerCurrent->next;
					innerPrevious->next = nullptr;
					delete innerPrevious;
					innerPrevious = nullptr;
				}
				// Delete the Node**
			}
			previousNode = currentNode;
			// Get to the next index
			++currentNode;
			*previousNode = nullptr;
		}
		// Delete the entire hash table when done.
		successValue = 1;
	}

	return successValue;
/*
	int successValue = 0;
	int i;
	Node** currentNode = _hashTable;
	Node* tempNode = *currentNode;

	if (_hashTable != nullptr)
	{
		for (i = 0; i < _tableSize; i++)
		{
			tempNode = *currentNode;
			while (tempNode != nullptr)
			{
				tempNode = *currentNode;
				*currentNode = (*currentNode)->next;
				delete tempNode;
				tempNode = nullptr;
				--_numberOfNodes;
			}
			++currentNode;
		}
	successValue = 1;
	}

	return successValue;
*/
}



int HashTable::addItem(const Item& sourceItem)
{
	int index = 0;
	int successFlag = 0;
	int nameSize = 0;
	int duplicateExists = 0;
	char* titleBuffer;
	Node* newNode;

	nameSize = sourceItem.nameSize();
	
	if (nameSize != 0)
	{
		// Allocate space for a char and copy the item name into it
		titleBuffer = new char[nameSize + 1];
		sourceItem.copyName(titleBuffer);

		// Generate the index key for the item name
		index = generateKey(titleBuffer);

		// Check for duplicate in the linear linked list at this index
		if (_hashTable[index] != nullptr)
		{
			duplicateExists = checkForDuplicate(_hashTable[index], sourceItem);
		}

		// If there is no existing node at this index,
		// OR there is no dupliate name in an existing LLL, 
		// Then then add the item to the LLL
		if ((_hashTable[index] == nullptr) || (duplicateExists != 0))
		{
			// Allocate memory for a new node and transfer data into it
			newNode = new Node;
			newNode->itemData = new Item;
			newNode->itemData->createItem(sourceItem);
			newNode->next = _hashTable[index];
			_hashTable[index] = newNode;

			
			++_numberOfNodes;
			successFlag = 1;
		}

		delete[] titleBuffer;
	}
	return successFlag;
}



// Loads the hash table from an argument file name.
// Returns a 0 if the hashTable has not been initialized.
// Returns a -1 if the file location is invalid
// Returns a -2 if the contents of the file are formatted improperly.
/*
	Data in the file should be formatted using ; delimiter
	for the three item data: itemName, itemHint, itemLocation
	and new line between different items.

	Example:
		An item name;An item hint;An item location
		Another item name;Another item hint;Another item location

		or

		An item name;an item hint;an item location\nanother item name;another item hint; another item location\n
*/
int HashTable::loadHashTable(const char fileName[])
{
	ifstream in;
	char nameBuffer[MAX_CHAR];
	char hintBuffer[MAX_CHAR];
	char locationBuffer[MAX_CHAR];
	Item itemBuffer;
	int successFlag = 0;	

	if (_hashTable != nullptr)
	{
		// Open the file
		in.open(fileName);
		if (!in)
		{
			successFlag = -1;
		}
		else
		{
			// Get the information from the file
			// Get the item name
			in.get(nameBuffer,MAX_CHAR, ';');
			while((!in.eof()) && (successFlag != -2))
			{
				in.get(); // get rid of the ; delimiter

				// Get item hint
				in.get(hintBuffer, MAX_CHAR, ';');
				in.get(); // get rid of the ; delimiter

				// Get item location
				in.get(locationBuffer, MAX_CHAR, '\n');
				in.get(); // get rid of the \n delimiter

				// Allocate space for new item and save 

				// If the fstream is in error then return an 
				// error flag of -2
				if (!in)
				{
					successFlag = -2;
				}
				// Otherwise, copy the item in the buffer over 
				// to the hash table
				else
				{
					// Allocate space for a new item and 
					// input the values loaded from the file
					itemBuffer.createItem(nameBuffer, hintBuffer, locationBuffer);
					successFlag = addItem(itemBuffer);

					// Restart the cycle
					// Get the item name
					in.get(nameBuffer,MAX_CHAR, ';');
				}
			}
			if (successFlag != -2)
			{
				successFlag = 1;
			}
			// Close the file
			in.close();
		}
	}
	return successFlag;
}



int HashTable::removeItem(const char itemName[])
{
	int successValue = 0;
	int index = 0;
	Node* innerNode;
	Node* previousNode;

	if (itemName != nullptr)
	{
		index = generateKey(itemName);
		
		innerNode = _hashTable[index];
		previousNode = innerNode;
		
		while ((innerNode != nullptr) && (successValue != 1))
		{
			if (innerNode->itemData->compareNames(itemName) == 0)
			{
				// If there is only one entry in the slot
				if ((innerNode == _hashTable[index]) && (innerNode->next == nullptr))
				{
					delete _hashTable[index];
					_hashTable[index] = nullptr;
					--_numberOfNodes;
				}
				// Otherwise there is more than 1 entry
				else
				{
					// If removing first item
					if (innerNode == _hashTable[index])
					{
						_hashTable[index] = innerNode->next;
					}
					// Otherwise we're not the first item
					else
					{
						previousNode->next = innerNode->next;
					}
					delete innerNode;
					innerNode = nullptr;
					--_numberOfNodes;
				}
				successValue = 1;
			}
			else
			{
				previousNode = innerNode;
				innerNode = innerNode->next;
			}	
		}
	}
	return successValue;
}



int HashTable::retrieveItem(Item& retrievedItem, const char nameToRetrieve[]) const
{
	int index = 0;
	int successValue = 0;
	Node* innerCurrent;

	if (nameToRetrieve != nullptr)
	{
		// Find the index
		index = generateKey(nameToRetrieve);
		// Go to the array index and look through the chain if item name
		// exists
		if (_hashTable[index] != nullptr)
		{
			innerCurrent = _hashTable[index];
			while ((innerCurrent != nullptr) && (successValue != 1))
			{
				if (innerCurrent->itemData->compareNames(nameToRetrieve) == 0)
				{
					successValue = retrievedItem.copyItem(*innerCurrent->itemData);
				}
				innerCurrent = innerCurrent->next;
			}
		}
	}

	return successValue;
}



int HashTable::displayKeyItems(const char itemName[]) const
{
	int successValue = 0;
	int index = 0;
	Node* innerCurrent;

	if (itemName != nullptr)
	{
		index = generateKey(itemName);

		if (_hashTable[index] != nullptr)
		{
			innerCurrent = _hashTable[index];
			
			while (innerCurrent != nullptr)
			{
				innerCurrent->itemData->displayItem();
				innerCurrent = innerCurrent->next;
			}
			successValue = 1;	
		}
	}
	return successValue;
}



int HashTable::displayAll() const
{
	int successValue = 0;
	int i;
	Node** currentNode;
	Node* innerCurrent;

	if (_hashTable != nullptr)
	{
		cout << endl << endl << "===============================" << endl;
		cout << endl << "Displaying all table entries..." << endl << endl;
		currentNode = _hashTable;
		for (i = 0; i < _tableSize; i++)
		{
			cout << "Index #" << i << ":" << endl;
			innerCurrent = *currentNode;
			while (innerCurrent != nullptr)
			{
				innerCurrent->itemData->displayItem();
				innerCurrent = innerCurrent->next;
			}
			cout << "--------------------------" << endl;
			++currentNode;
		}
	successValue = 1;
	}

	return successValue;
}



int HashTable::giveItems(const int& numberOfItems, Item* returnedItems[]) const
{
	int successValue = 0;
	int i = 0;
	int n = 0;
	Node** currentNode = _hashTable;
	Node* innerCurrent;
	int intArray[numberOfItems];
	Node* randomNode;

	// Generate a unique random number between 0 and (_tableSize - 1) for each
	// item to be returned (equal to the numberOfItems)
	// Fill the intArray with those numbers
	successValue = generateRandom(numberOfItems, intArray);

	for (i = 0; i < numberOfItems; ++i)
	{
		randomNode = retrieveItemByPosition(intArray[i]);
		(*returnedItems[i]).copyItem(*randomNode->itemData);
		randomNode = nullptr;
	}

	return successValue;
}

Node* HashTable::retrieveItemByPosition(const int& position) const
{
	int i;
	int n = 0;
	Node** currentNode = _hashTable;
	Node* innerCurrent = nullptr;
	Node* returnPointer = nullptr;
	
	
	for (i = 0; ((i < _tableSize) && (n <= position)); ++i)
	{
		if (*currentNode != nullptr)
		{
			++n;
			innerCurrent = *currentNode;
			returnPointer = innerCurrent;
			while ((innerCurrent->next != nullptr) && (n <= position))
			{
				++n;
				innerCurrent = innerCurrent->next;
				returnPointer = innerCurrent;
			}
		}
		++currentNode;
	}

	return returnPointer;
}

// Returns 0 if there are not enough items in the hash table to provide a unique
// item for the requested numberOfItems
int HashTable::generateRandom(const int& numberOfItems, int intArray[]) const
{
	int i;
	int n;
	int duplicateFlag = 0;
	int randomNumber = 0;
	srand (time(NULL));

	if (_numberOfNodes >= numberOfItems)
	{
		// Initialize the randomness using time.
		// https://www.cplusplus.com/reference/cstdlib/rand/
		for (i = 0; i < numberOfItems; ++i)
		{
			do
			{
				duplicateFlag = 0;
				//get a random number
				randomNumber = rand() % (_numberOfNodes - 1);

				// check if it's in the array already
				for (n = 0; ((n < i) && (duplicateFlag != 1)); ++n)
				{
					if (randomNumber == intArray[n])
					{
						duplicateFlag = 1;
					}
				}
			} while (duplicateFlag != 0);

			intArray[i] = randomNumber;
		}
	}
	
	return 0;
}



int HashTable::generateKey(const char sourceCstring[]) const
{
	int index = 0;
	int sum = 0;
	int i;

	if (sourceCstring != nullptr)
	{
		/*
		// First try on hash function
		for (i=0; i< strlen(sourceCstring); i++)
		{
			// If the index is even
			if ((i % 2) == 0)
			{
				index += (3*i + sourceCstring[i]);
			}
			// If the index is odd
			if ((i % 2) != 0)
			{
				index += (11*i * sourceCstring[i]);
			}
		}
		*/
	
		// Second try on hash function
		for (i = 0; i < strlen(sourceCstring); i++)
		{
			// If the index is even
			if ((i % 2) == 0)
			{
				index += (i + sourceCstring[i]);
				sum += sourceCstring[i];
				index += sum;
			}
			// If the index is divisible by 3
			if ((i % 3) == 0)
			{
				index += (i + sourceCstring[i] + (i * sourceCstring[i]));
				sum += sourceCstring[i];
				index += sum;
			}
			// If the index is odd
			if (( i % 2) != 0)
			{
				index += (i * sourceCstring[i]);
				sum += sourceCstring[i];
				index += sum;
			}
			index -= sum;
		}
		
		/*
		// Third try on hash function
		for (i = 0; i < strlen(sourceCstring); i++)
		{
			// If the character isn't a vowel
			if ((tolower(sourceCstring[i]) != 'a')
			&& (tolower(sourceCstring[i]) != 'e')
			&& (tolower(sourceCstring[i]) != 'i')
			&& (tolower(sourceCstring[i]) != 'o')
			&& (tolower(sourceCstring[i]) != 'u'))
			{
				// If the index is even
				if ((i % 2) == 0)
				{
					// Add the character to the index
					index += getPrime(sourceCstring[i]) * sourceCstring[i];
				}
				// If the index is odd
				else
				{
					// Subtract the character from the index
					index -= (getPrime(sourceCstring[i]) * sourceCstring[i]);
				}
			}
			else
			{
				++sum;
			}
		}
		index *= sum;
		*/
		// Make sure index is positive
		if (index < 0)
		{
			index *= -1;
		}

		// Adjust index for the table size;
		index %= _tableSize;
	}

	return index;
}



int HashTable::getPrime(const char& aChar)
{
	// The highest ASCII decimal value for a char is 127 (the delete key)
	// So I only need the first 127 primes in my table.

	const int primeArray[127] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709};
	
	return primeArray[aChar];
}



int HashTable::checkForDuplicate(Node*& head, const Item& itemToAdd) const
{
	int duplicateFound = -1;
	Node* currentNode = head;

	while ((currentNode != nullptr) && (duplicateFound != 0))
	{
		// Compare names returns 0 if the items match
		// Returns a negative number if the calling name is lower
		// Returns a positive number if the calling name is higher
		duplicateFound = currentNode->itemData->compareNames(itemToAdd);
		currentNode = currentNode->next;
	}

	return duplicateFound;
}
