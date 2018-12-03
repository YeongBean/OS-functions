#pragma once
#include "hash.h"
using namespace std;

int getblk(int& blockNum, Hash<int>& HashQueues, UnsortedType<int>& FreeList)
{
	bool foundBlock = false;
	bool blockIsBusy = false;
	bool blockIsDelayed = false;
	bool blockISWriting = false;
	bool freeListFound = false;
	int tempBlockNum = 0;
	int temp = 0;
	
	HashQueues.HashRetrieveItem(blockNum, foundBlock, blockIsBusy, blockIsDelayed, blockISWriting);
	if (foundBlock == true)//해시큐에 찾는 블록이 있다면
	{
		if (blockIsBusy == true)
		{
			//sleep은 단순히 기다리는것과 같으므로
			//continue;
			return -1; //-1은 없다는 뜻임
		}
		else //busy 상태가 아니라면
		{
			
			FreeList.RetrieveItem(blockNum, freeListFound, blockIsBusy, blockIsDelayed, blockISWriting);
			if (freeListFound == true)
			{
				FreeList.DeleteItem(blockNum); //freelist에서 제거
				HashQueues.markBusy(blockNum); //busy상태로 바꿈
			}
			return blockNum;
		}
	}
	else //해시큐에 찾는 번호가 없다면
	{
		if (FreeList.LengthIs() == 0) //프리리스트가 비었으면
		{
			//continue;
			return -1; //-1은 없다는 뜻임
		}
		else //freelist가 비어있지 않은 경우
		{
			FreeList.ResetList();
			while (true)
			{
				FreeList.GetNextItem(tempBlockNum);
				FreeList.RetrieveItem(tempBlockNum, freeListFound, blockIsBusy, blockIsDelayed, blockISWriting);
				if (blockIsDelayed == true)
				{
					FreeList.Changedelayed(tempBlockNum); //딜레이 해제
					if (blockISWriting == false) FreeList.ChangeWrite(tempBlockNum); //write상태 바꿈
				}
				
				else if (blockIsBusy == true)
					continue;
				else if (blockISWriting == true)
					continue;
				else //프리리스트가 비어있지 않고 딜레이나 busy도 아닌경우
				{
					FreeList.DeleteItem(tempBlockNum); // 프리리스트에서 삭제
					HashQueues.HAshDeleteItem(tempBlockNum); //해시큐에서도 삭제
					HashQueues.HashInsertItem(blockNum); //새로운 번호로 해시큐에 삽입
					cout << "---프리리스트로부터 ";
					return blockNum;
				}
			}
		}
	}
}