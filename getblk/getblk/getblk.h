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
	if (foundBlock == true)//�ؽ�ť�� ã�� ����� �ִٸ�
	{
		if (blockIsBusy == true)
		{
			//sleep�� �ܼ��� ��ٸ��°Ͱ� �����Ƿ�
			//continue;
			return -1; //-1�� ���ٴ� ����
		}
		else //busy ���°� �ƴ϶��
		{
			
			FreeList.RetrieveItem(blockNum, freeListFound, blockIsBusy, blockIsDelayed, blockISWriting);
			if (freeListFound == true)
			{
				FreeList.DeleteItem(blockNum); //freelist���� ����
				HashQueues.markBusy(blockNum); //busy���·� �ٲ�
			}
			return blockNum;
		}
	}
	else //�ؽ�ť�� ã�� ��ȣ�� ���ٸ�
	{
		if (FreeList.LengthIs() == 0) //��������Ʈ�� �������
		{
			//continue;
			return -1; //-1�� ���ٴ� ����
		}
		else //freelist�� ������� ���� ���
		{
			FreeList.ResetList();
			while (true)
			{
				FreeList.GetNextItem(tempBlockNum);
				FreeList.RetrieveItem(tempBlockNum, freeListFound, blockIsBusy, blockIsDelayed, blockISWriting);
				if (blockIsDelayed == true)
				{
					FreeList.Changedelayed(tempBlockNum); //������ ����
					if (blockISWriting == false) FreeList.ChangeWrite(tempBlockNum); //write���� �ٲ�
				}
				
				else if (blockIsBusy == true)
					continue;
				else if (blockISWriting == true)
					continue;
				else //��������Ʈ�� ������� �ʰ� �����̳� busy�� �ƴѰ��
				{
					FreeList.DeleteItem(tempBlockNum); // ��������Ʈ���� ����
					HashQueues.HAshDeleteItem(tempBlockNum); //�ؽ�ť������ ����
					HashQueues.HashInsertItem(blockNum); //���ο� ��ȣ�� �ؽ�ť�� ����
					cout << "---��������Ʈ�κ��� ";
					return blockNum;
				}
			}
		}
	}
}