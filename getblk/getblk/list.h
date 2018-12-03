#pragma once
// Header file for Unsorted List ADT.  
template <class ItemType>
struct NodeType;

// Assumption:  ItemType is a type for which the operators "<" 
// and "==" are defined?ither an appropriate built-in type or
// a class that overloads these operators.

template <class ItemType>
class UnsortedType
{
public:
	UnsortedType();     // Class constructor	
	~UnsortedType();    // Class destructor

	bool IsFull() const;

	int  LengthIs() const;

	void MakeEmpty();

	void RetrieveItem(ItemType& item, bool& found, bool& IsBusy, bool& IsDelayed, bool& Isriting);

	void InsertItem(ItemType item);

	void DeleteItem(ItemType item);

	void ResetList();

	void GetNextItem(ItemType& item);

	void Changebusy(ItemType key);

	void Changedelayed(ItemType key);

	void ChangeWrite(ItemType key);

	int cntUp(ItemType key);

	bool IsEmpty();

private:
	NodeType<ItemType>* listData;
	int length;
	NodeType<ItemType>* currentPos;
};

template<class ItemType>
struct NodeType
{
	ItemType info;
	bool busy = false;
	bool delayed = false;
	bool write = false;
	int counter = 0;
	NodeType* next;
};

template <class ItemType>
UnsortedType<ItemType>::UnsortedType()  // Class constructor
{
	length = 0;
	listData = NULL;
}

template <class ItemType>
UnsortedType<ItemType>::~UnsortedType()
// Class destructor
{
	MakeEmpty();
}
template<class ItemType>
bool UnsortedType<ItemType>::IsFull() const
// Returns true if there is no room for another ItemType 
//  on the free store; false otherwise.
{
	NodeType<ItemType>* location;
	try
	{
		location = new NodeType<ItemType>;
		delete location;
		return false;
	}
	catch (bad_alloc exception)
	{
		return true;
	}
}
template <class ItemType>
int UnsortedType<ItemType>::LengthIs() const
// Post: Number of items in the list is returned.
{
	return length;
}
template <class ItemType>
void UnsortedType<ItemType>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	NodeType<ItemType>* tempPtr;

	while (listData != NULL)
	{
		tempPtr = listData;
		listData = listData->next;
		delete tempPtr;
	}
	length = 0;
}
template <class ItemType>
void UnsortedType<ItemType>::RetrieveItem(ItemType& item, bool& found, bool& IsBusy, bool& IsDelayed, bool& Isriting)
{
	bool moreToSearch;
	NodeType<ItemType>* location;
	ResetList();
	location = listData;
	moreToSearch = (location != NULL);


	if (IsEmpty())
		found = false;
	else
	{
		found = false;
		

		while (moreToSearch == true && found == false)
		{
			if (location->info == item)
			{
				found = true;
				item = location->info;
				IsBusy = location->busy;
				IsDelayed = location->delayed;
				Isriting = location->write;
			}
			else
			{
				location = location->next;
				moreToSearch = (location != NULL);
			}
		}
		
	}
}
template <class ItemType>
void UnsortedType<ItemType>::InsertItem(ItemType item)
// item is in the list; length has been incremented.
{
	NodeType<ItemType>* location;

	location = new NodeType<ItemType>;
	location->info = item;
	location->next = listData;
	listData = location;
	length++;
}
template <class ItemType>
void UnsortedType<ItemType>::DeleteItem(ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
	ResetList();
	NodeType<ItemType>* location = listData;
	NodeType<ItemType>* tempLocation;
	bool found,Busy,Delayed,write;
	RetrieveItem(item, found, Busy, Delayed, write);

	// Locate node to be deleted.
	if (found == true)
	{
		if (item == listData->info)
		{
			tempLocation = location;
			listData = listData->next;		// Delete first node.
		}
		else
		{
			while (!(item == (location->next)->info))
				location = location->next;

			// Delete node at location->next
			tempLocation = location->next;
			location->next = (location->next)->next;
		}

		length--;
	}
}

template <class ItemType>
void UnsortedType<ItemType>::ResetList()
// Post: Current position has been initialized.
{
	currentPos = NULL;
}

template <class ItemType>
void UnsortedType<ItemType>::GetNextItem(ItemType& item)
// Post:  Current position has been updated; item is current item.
{
	if (currentPos == NULL)
		currentPos = listData;
	else currentPos = currentPos->next;
	item = currentPos->info;
}


template <class ItemType>
void UnsortedType<ItemType>::Changebusy(ItemType key)
{
	bool moreToSearch;
	NodeType<ItemType>* location;

	location = listData;
	bool found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found)
	{
		if (key == location->info)
		{
			if (location->busy == false)
				location->busy = true;
			else location->busy = false;

			break;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

}

template <class ItemType>
void UnsortedType<ItemType>::Changedelayed(ItemType key)
{
	bool moreToSearch;
	NodeType<ItemType>* location;

	location = listData;
	bool found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found)
	{
		if (key == location->info)
		{
			if (location->delayed == false)
				location->delayed = true;
			else location->delayed = false;

			break;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

}

template <class ItemType>
void UnsortedType<ItemType>::ChangeWrite(ItemType key)
{
	bool moreToSearch;
	NodeType<ItemType>* location;

	location = listData;
	bool found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found)
	{
		if (key == location->info)
		{
			if (location->write == false)
				location->write = true;
			else location->write = false;

			break;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

}


template <class ItemType>
int UnsortedType<ItemType>::cntUp(ItemType key)
{
	bool moreToSearch;
	NodeType<ItemType>* location;

	location = listData;
	bool found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found)
	{
		if (key == location->info)
		{
			location->counter++;
			break;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}
	return location->counter;
}

template <class ItemType>
bool UnsortedType<ItemType>::IsEmpty()
{
	if (listData == NULL)
		return true;
	else return false;
}