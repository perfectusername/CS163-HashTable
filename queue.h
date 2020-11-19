#include "hashtable.h"

struct QueueNode
{
	QueueNode();
	~QueueNode();

	char* itemName;
	QueueNode* next;
};



class Queue
{
public:
	Queue();
	~Queue();

	int enqueue(const char incomingName[]);
	int fillQueue(const int& numberOfItems, const HashTable& sourceTable);
	int dequeue(Item& dequeuedItem, const HashTable& sourceTable);

private:
	QueueNode* front;
	QueueNode* rear;
};
