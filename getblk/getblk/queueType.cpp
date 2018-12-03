#include "queueType.h"

QueType::QueType(int max)
// Parameterized class constructor
// Post: maxQue, front, and rear have been initialized.
//       The array to hold the queue elements has been dynamically
//       allocated.
{
	maxQue = max + 1;
	front = maxQue - 1;
	rear = maxQue - 1;
	length = 0;
	items = new int[maxQue];
	counter = new int[maxQue];
}
QueType::QueType()          // Default class constructor
							// Post: maxQue, front, and rear have been initialized.
							//       The array to hold the queue elements has been dynamically
							//       allocated.
{
	maxQue = 5;
	front = maxQue - 1;
	rear = maxQue - 1;
	length = 0;
	items = new int[maxQue];
	counter = new int[maxQue];
}
QueType::~QueType()         // Class destructor
{
	delete[] items;
}

void QueType::MakeEmpty()
// Post: front and rear have been reset to the empty state.
{
	front = maxQue - 1;
	rear = maxQue - 1;
}

bool QueType::IsEmpty() const
// Returns true if the queue is empty; false otherwise.
{
	return (rear == front);
}

bool QueType::IsFull() const
// Returns true if the queue is full; false otherwise.
{
	return ((rear + 1) % maxQue == front);
}

void QueType::Enqueue(int newItem)
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown.  
{
	if (IsFull())
		throw FullQueue();
	else
	{
		rear = (rear + 1) % maxQue;
		items[rear] = newItem;
		counter[rear] = 0;
		length++;
	}
}

void QueType::Enqueue(int newItem,int cnt)
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown.  
{
	if (IsFull())
		throw FullQueue();
	else
	{
		rear = (rear + 1) % maxQue;
		items[rear] = newItem;
		counter[rear] = cnt;
		length++;
	}
}

void QueType::Dequeue(int& item, int& cnt)
// Post: If (queue is not empty) the front of the queue has been 
//       removed and a copy returned in item; 
//       othersiwe a EmptyQueue exception has been thrown.
{
	if (IsEmpty())
		throw EmptyQueue();
	else
	{
		front = (front + 1) % maxQue;
		item = items[front];
		cnt = counter[front];
		length--;
	}
}

void QueType::counterUp()
{

}

int QueType::lengthis()
{
	return length;
}
