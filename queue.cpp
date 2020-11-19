#include "queue.h"

using std::endl;
using std::cout;

// QueueNode struct
QueueNode::QueueNode()
{
	itemName = nullptr;
	next = nullptr;
}



QueueNode::~QueueNode()
{
	if (itemName != nullptr)
	{
		delete[] itemName;
		itemName = nullptr;
	}
	if (next != nullptr)
	{
		next = nullptr;
	}
}



Queue::Queue()
{
	front = nullptr;
	rear = nullptr;	
}


Queue::~Queue()
{
	QueueNode* currentNode = front;

	if (front != nullptr)
	{	
		rear->next = nullptr;
		while (front != nullptr)
		{
			currentNode = front;
			front = front->next;
			delete currentNode;
		}
		front = nullptr;
	}
	rear = nullptr;
}




int Queue::enqueue(const char incomingName[])
{
	int successValue = 0;
	QueueNode* newNode;
	
	if (incomingName != nullptr)
	{
		// Allocate the node
		newNode = new QueueNode;
		// Allocate and set name data
		newNode->itemName = new char[strlen(incomingName) + 1];
		strcpy(newNode->itemName, incomingName);

		// If the queue is empty
		if (front == nullptr)
		{
			// front and rear and rear->next must be set to the new node
			front = newNode;
			rear = newNode;
			rear->next = newNode;
		}
		// Otherwise there is at least 1 node in the queue.
		else
		{
			// front will stay the same. 
			// but, the current rear's rear->next must be set to newNode
			rear->next = newNode;
			// Then rear must be set to the newNode
			rear = newNode;
			// newNode->next must be set to front.
			newNode->next = front;
		}
	}

	return successValue;
}




// Fills the queue with a random set of items from the hash table.
int Queue::fillQueue(const int& numberOfItems, const HashTable& sourceTable)
{
	int successValue = 0;
	int i;
	Item* itemArray[numberOfItems];
	int nameSize;
	char* nameBuffer;

	if (numberOfItems > 0)
	{
		// Create an array of item pointers
		for (i = 0; i < numberOfItems; ++i)
		{
			itemArray[i] = new Item;
		}

		// Get a list of items from the hash table to pull names from
		sourceTable.giveItems(numberOfItems, itemArray);

		for (i = 0; i < numberOfItems; ++i)
		{
			nameSize = itemArray[i]->nameSize();
			nameBuffer = new char[nameSize + 1];
			itemArray[i]->copyName(nameBuffer);
			enqueue(nameBuffer);
			delete[] nameBuffer;
		}
		
		// Delete the item pointers;
		for (i = 0; i < numberOfItems; ++i)
		{
			if (itemArray[i] != nullptr)
			{
				delete itemArray[i];
				itemArray[i] = nullptr;
			}
		}
		successValue = 1;
	}

	return successValue;
}



int Queue::dequeue(Item& dequeuedItem, const HashTable& sourceTable)
{
	int successValue = 0;
	QueueNode* nodeToDequeue;

	if (front != nullptr)
	{
		nodeToDequeue = front;

		// If there is only one node in the list
		if (front == rear)
		{
			front = nullptr;
			rear = nullptr;
			successValue = 1;
		}
		// Otherwise there are at least 2 nodes in the list
		else
		{
			front = front->next;
			rear->next = front;
			successValue = 1;
		}
		
		sourceTable.retrieveItem(dequeuedItem, nodeToDequeue->itemName);
			
		delete nodeToDequeue;
		nodeToDequeue = nullptr;
	}

	
	return successValue;
}
