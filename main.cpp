#include "queue.h"

using namespace std;

// Function prototypes
void userInterface(); // User interface
void menuChoice(char& input); // Menu options
void menuDequeue(Item& dequeuedItem, const HashTable& sourceTable);
int menuCreateQueue(const int& numberOfItems);
int menuHashTableTests();
int displayKeyItemsUI(HashTable& aHashTable);
int removeItemUI(HashTable& aHashTable);
int retrieveItemUI(HashTable& aHashTable);
int addItemUI(HashTable& aHashTable);
int loadHashTableUI(HashTable& aHashTable);

//  Queue UI functions
int createQueue(const int& numberOfItems); // UI function to build queue
int dequeueUI(Item& dequeuedItem, const HashTable& sourceTable);

// Hash Table UI functions
int addItemUI(const Item& sourceItem);
int removeItemUI(const char itemName[]);
int removeAllItems();
int retrieveItemUI(Item& retrievedItem, const char nameToRetrieve[]);
int displayKeyItemsUI(const char itemName[]);
int displayAll();



int main()
{
	userInterface();

	return 0;
}

// Menu and input
void menuChoice(char& input)
{
      char prompt[MAX_CHAR];

	cout << "=========================================================" << endl << endl;
	cout << "Enter a number or 'q' to quit" << endl;
	cout << endl;
	/*strcpy(prompt, "Normal user menu options\n=========================================================\nChoose a difficulty for your scavenger hunt:\n\n1. Normal difficulty (10 items)\n2. Advanced difficulty (15 items)\n\n\nTest suite options\n\nQueue:\n3. Create a queue\n4. Dequeue\n\nHash Table:\n5. Add item to hash table\n6. Display all items for a specific key\n7. Display all items\n8. Retrieve item details\n9. Remove item by name\nq. Quit\n\nPlease enter your menu choice: ");*/
	strcpy(prompt, "\nMain Menu\n=========================================================\n\n1. Normal difficulty scavenger hunt(10 items)\n2. Advanced difficulty scavenger hunt(15 items)\n3. Hash table tests (special test suite option)\nq. Quit\n\nPlease enter your menu choice: ");

        takeInput(input, prompt);
	cout << endl << endl;
	cout << "=========================================================" << endl << endl;
}


// User interface
void userInterface()
{
        Queue*	aQueue = new Queue;
        char	input;
	int	numberOfItems = 0;

        input = '\0';

        while (quitCheck(input) != true)
        {
                menuChoice(input);
                if (quitCheck(input) != true)
                {
                        switch (input)
                        {
                        case '1':
				numberOfItems = 10;
				menuCreateQueue(numberOfItems);
                                break;
                        case '2':
				numberOfItems = 15;
				menuCreateQueue(numberOfItems);
                                break;
                        case '3':
				menuHashTableTests();
                                break;
			case 'q':
				cout << "Quitting program... " << endl << endl;
				break;
                        default:
                                cout << "Invalid input. Please try again." << endl;
                        }
                }
        }
	delete aQueue;
}




void queueMenu(char& input)
{
	char 	prompt[2 * MAX_CHAR];

	strcpy(prompt, "Scavenger Hunt - Application Menu\n=========================================================\n\nChoose an option: \n1. Dequeue an item to see its hint and search for it\n2. Display all current item details (including location!)\nq. Quit to main menu\n\nPlease enter your menu choice: ");

        takeInput(input, prompt);
	cout << endl << endl;
	cout << "=========================================================" << endl << endl;
}

int menuCreateQueue(const int& numberOfItems)
{
	int		successValue;
	Item* 		dequeuedItem = nullptr;
	HashTable 	aHashTable;
	Queue 		aQueue;
	const char 	fileName[] = "items.txt";
        char 		input = '\n';

	aHashTable.loadHashTable(fileName);
	aQueue.fillQueue(numberOfItems, aHashTable);

        while (quitCheck(input) != true)
        {
                queueMenu(input);
                if (quitCheck(input) != true)
                {
			switch(input)
			{
			case '1':
				if (dequeuedItem != nullptr)
				{
					delete dequeuedItem;
					dequeuedItem = nullptr;
				}
				dequeuedItem = new Item;
				successValue = aQueue.dequeue(*dequeuedItem, aHashTable);
				if (successValue != 1)
				{
					cout << "Dequeue failed. Queue is empty.";
					cout << endl << endl;
					delete dequeuedItem;
					dequeuedItem = nullptr;
				}
				else
				{
					cout << "Your item is: ";
					cout << endl << endl;
					dequeuedItem->displayHint();
				}
				successValue = 0;
                                break;
                        case '2':
				if (dequeuedItem == nullptr)
				{
					cout << "Please dequeue an item first.";
					cout << endl << endl;
				}
				else
				{
					cout << "Your item is: ";
					cout << endl << endl;
					dequeuedItem->displayItem();
				}
                                break;
                        default:
                                cout << "Invalid input. Please try again." << endl;
                        }
                }
	successValue = 1;
        }
	
	if (dequeuedItem != nullptr)
	{
		delete dequeuedItem;
		dequeuedItem = nullptr;
	}
	return successValue;
}



void hashTableMenu(char& input)
{
	char	prompt[2 * MAX_CHAR];

	strcpy(prompt, "\nHash Table Tests\n=========================================================\n\nChoose an option: \n1. Display all items in hash table\n2. Display all items for a matching key\n3. Add an item to the hash table\n4. Load items from file\n5. Retrieve item details by item name\n6. Remove an object by item name\n7. Remove all objects from the hash table\nq. Quit to main menu\n\nPlease enter your menu choice: ");

        takeInput(input, prompt);
	cout << endl << endl;
	cout << "=========================================================" << endl << endl;
}


int menuHashTableTests()
{
        char 		input = '\n';
        Item            dequeuedItem;
        HashTable       aHashTable;
	int		successValue = 0;
        const char      fileName[] = "items.txt";

        aHashTable.loadHashTable(fileName);

        while (quitCheck(input) != true)
        {
                hashTableMenu(input);
                if (quitCheck(input) != true)
                {
                        switch(input)
			{
                        case '1':
				successValue = aHashTable.displayAll();
				if (successValue != 1)
				{
					cout << "Display failed." << endl;
					cout << "Hash table is empty." << endl;
				}
				successValue = 0;
                                break;
                        case '2':
				successValue = displayKeyItemsUI(aHashTable);
				if (successValue != 1)
				{
					cout << "Display failed." << endl;
					cout << "No matching items for that key." << endl;
				}
				successValue = 0;
                                break;
                        case '3':
                                successValue = addItemUI(aHashTable);
				if (successValue == 1)
				{
					cout << "Item successfully added!" << endl;
				}
				else
				{
					cout << "Failed to add item." << endl;
				}
				successValue = 0;
                                break;
			case '4':
				loadHashTableUI(aHashTable);
				break;
			case '5':
				successValue = retrieveItemUI(aHashTable);
                                if (successValue != 1)
                                {
                                        cout << "Retrieve Failed" << endl;
                                }
                                successValue = 0;
                                break;
			case '6':
				successValue = removeItemUI(aHashTable);
				if (successValue != 1)
				{
					cout << "Remove item failed." << endl;
					cout << "No matching item." << endl;
				}
				successValue = 0;
				break;
			case '7':
				successValue = aHashTable.removeAllItems();
				if (successValue != 1)
				{
					cout << "Remove failed." << endl;
				}
				else
				{
					cout << "Remove successful!" << endl;
				}
				successValue = 0;
				break;
                        default:
                                cout << "Invalid input. Please try again." << endl;
                        }
                }
	successValue = 1;
        }
	return successValue;
}

int displayKeyItemsUI(HashTable& aHashTable)
{
	char	input[MAX_CHAR];
	char	prompt[2 * MAX_CHAR];

	strcpy(prompt, "Display all items of a certain key\n=========================================================\n\nPlease enter a phrase that matches the desired display key: ");

	takeInput(input, prompt);

	return aHashTable.displayKeyItems(input);
}


int addItemUI(HashTable& aHashTable)
{
	char	prompt[2 * MAX_CHAR];
	char	itemName[MAX_CHAR];
	char	itemHint[MAX_CHAR];
	char	itemLocation[MAX_CHAR];
	Item	itemBuffer;

	cout << "Add item" << endl << "=========================================================" << endl << endl;
	
	strcpy(prompt, "Please enter the item's name: ");
	takeInput(itemName, prompt);

	strcpy(prompt, "Please enter the item's hint: ");
	takeInput(itemHint, prompt);

	strcpy(prompt, "Please enter the item's location: ");
	takeInput(itemLocation, prompt);

	itemBuffer.createItem(itemName, itemHint, itemLocation);

	return aHashTable.addItem(itemBuffer);
}


int retrieveItemUI(HashTable& aHashTable)
{
	char	itemName[MAX_CHAR];
	Item	retrievedItem;
	char	prompt[2 * MAX_CHAR];
	int	successValue = 0;
	
	strcpy(prompt, "Retrieve item\n=========================================================\n\nPlease enter the name of the item to retrieve: ");
        takeInput(itemName, prompt);
	
	successValue = aHashTable.retrieveItem(retrievedItem, itemName);
	if (successValue == 1)
	{
		cout << "Retrieved item details: " << endl;
		retrievedItem.displayItem();
	}

	return successValue;
}


int removeItemUI(HashTable& aHashTable)
{
        char    itemName[MAX_CHAR];
        char    prompt[2 * MAX_CHAR];
        int     successValue = 0;

        strcpy(prompt, "Remove item\n=========================================================\n\nPlease enter the name of the item to remove: ");
        takeInput(itemName, prompt);

        return aHashTable.removeItem(itemName);
}

int loadHashTableUI(HashTable& aHashTable)
{
	int 		successValue = 0;
        const char      fileName[] = "items.txt";

	successValue = aHashTable.loadHashTable(fileName);

	
	if ((successValue == 0) || (successValue == -1) || (successValue == -2))
	{
		cout << "Load failed." << endl;
		if (successValue == 0)
		{
			cout << "Hash Table uninitialized" << endl;
		}
		else if (successValue == -1)
		{
			cout << "Unable to read from file " << fileName << endl;
		}
		else if (successValue == -2)
		{
			cout << "Load error. File contents formatted improperly." << endl;
		}
	}
	else if (successValue == 1)
	{
		cout << "Load successful." << endl;
		successValue = 1;
	}

	return successValue;
}
