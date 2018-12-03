#include "list.h"
#include <iostream>

template <class ItemType>
class Hash
{
public:
	Hash();     // Class constructor	
	~Hash();    // Class destructor

	void HashRetrieveItem(int key, bool& found, bool& Busy, bool& Delayed, bool& Writing);

	void HashInsertItem(int key);

	void HAshDeleteItem(int key);

	void markBusy(int key);

	void markDelayed(int key);

	void markWrite(int key);

	int counterUp(int key);

private:
	int maxHashes;
	UnsortedType<int>* HashQueue;
};


template <class ItemType>
Hash<ItemType>::Hash()  // Class constructor
{
	maxHashes = 5;
	HashQueue = new UnsortedType<int>[maxHashes];
		
}

template <class ItemType>
Hash<ItemType>::~Hash()
// Class destructor
{
	for (int i = 0; i < maxHashes; i++)
		HashQueue[i].MakeEmpty();
}

template<class ItemType>
void Hash<ItemType>::HashInsertItem(int key)
{
	int location = key % maxHashes;
	HashQueue[location].InsertItem(key);
}

template<class ItemType>
void Hash<ItemType>::HAshDeleteItem(int key)
{
	int location = key % maxHashes;
	HashQueue[location].DeleteItem(key);
}

template<class ItemType>
void Hash<ItemType>::HashRetrieveItem(int key, bool& found, bool& Busy, bool& Delayed, bool& Writing)
{
	int location = key % maxHashes;
	HashQueue[location].RetrieveItem(key, found, Busy, Delayed,Writing);
}

template<class ItemType>
void Hash<ItemType>::markBusy(int key)
{
	int location = key % maxHashes;
	HashQueue[location].Changebusy(key);
}

template<class ItemType>
void Hash<ItemType>::markDelayed(int key)
{
	int location = key % maxHashes;
	HashQueue[location].Changedelayed(key);
}

template<class ItemType>
void Hash<ItemType>::markWrite(int key)
{
	int location = key % maxHashes;
	HashQueue[location].ChangeWrite(key);
}

template<class ItemType>
int Hash<ItemType>::counterUp(int key)
{
	int location = key % maxHashes;
	return HashQueue[location].cntUp(key);
}
#pragma once
