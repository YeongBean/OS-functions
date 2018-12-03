//getblk�� �׽�Ʈ�ϴ� �׽�Ʈ ����̹�
#include "queueType.h" //����� ���� ���μ������ ��ȯ�� ���� �Ϸ��� ���
#include <time.h>
#include "getblk.h"

using namespace std;



int main()
{
	int number_of_blocks = 100;
	int temp, i = 0;
	int getblkNum = 0, doneblock = 0;
	bool found, busy, delayed,writing;
	Hash<int> HashQueues;
	UnsortedType<int> FreeList;
	QueType using_blocks(100), waiting_blocks(100); //using + ���μ����� 100���̹Ƿ� �־��� ��� 100������ ��ٸ��� ����
	//�ʱ� ���� ����

	float command = 0;
	int startTime = 0, endTime = 0;
	//getblk �ð���� ����

	while(i < number_of_blocks)
	{
		temp = rand() % 300; //��ϳѹ� ����
		HashQueues.HashRetrieveItem(temp, found, busy, delayed, writing);
		
		if (found == false) //�ߺ��Ǵ� ��ϳѹ��� ������
		{
			//FreeList.InsertItem(temp);
			HashQueues.HashInsertItem(temp); //����
			i++;
		}
	}//�ؽ�ť�� 100���� ��� ���� �Ϸ�

	int k = 0;

	while (true)
	{
		cout << "������ �Ͻðڽ��ϱ�?" << endl << "1)3�ʰ� getblk����  2)���α׷� ����  : ";
		cin >> command;
		k = 0;
		if (command == 1)
		{
			cout << "���ʰ� �����Ͻðڽ��ϱ�?  : ";
			cin >> command;
			startTime = clock();
			while (endTime - startTime < command * 1000)
			{
				if ((endTime - startTime) % 50 == 0)
				{
					if (!using_blocks.IsEmpty()) 
					{
						using_blocks.Dequeue(doneblock,temp);
						if (temp > 3) //��� �� ����� 4�� �̻��� �ܰ踦 ���ƴٴ� ����
						{
							cout << "-----------------------------------------------" << endl;
							cout << doneblock << "�� ����� �۾��� ���� FreeList�� ��ȯ�մϴ�" << endl; //ī���Ͱ� 4�� ��� ��ȯ(instruction cyle�� 4�ܰ��̹Ƿ�)
							cout << "-----------------------------------------------" << endl;
							FreeList.InsertItem(doneblock); //��������Ʈ�� �ش��ȣ�� ��� ����
							HashQueues.HashRetrieveItem(getblkNum, found, busy, delayed, writing);
							if (busy == true) HashQueues.markBusy(doneblock);
							if (writing == true) HashQueues.markWrite(doneblock);
							if (delayed == true) HashQueues.markDelayed(doneblock); //�۾��� �������Ƿ� busy�� delayed�� ������
						}//3�ܰ� �̻��� ��ġ�� �ʾҴٸ� = operation cycle�� ������ �ʾҴٸ�
						else using_blocks.Enqueue(doneblock, temp); //�ٽ� using blocks�� ����
					} //�۾��� ���� ��� ���� ó��

					if (!waiting_blocks.IsEmpty() && !FreeList.IsEmpty()) //��ٸ��� �ִ� ���μ����� �ְ� ��������Ʈ�� ������� �ʴٸ�
					{
						waiting_blocks.Dequeue(getblkNum, temp); //���� �Ѵ�
						cout << "--> sleep���̴� ����� ����� ";
					}
					else getblkNum = rand() % 300;//�ʿ��� ��ϳѹ� ����

					cout << getblkNum << "�� ����� �ʿ��մϴ�" << endl; //�ʿ��� ��ϳѹ� �䱸 + ���
					temp = getblk(getblkNum, HashQueues, FreeList);

					if (temp != -1)
					{
						cout << temp << "�� ����� ����մϴ�" << endl;

						temp = rand() % 2;
						if (temp == 0) HashQueues.markBusy(getblkNum);
						else HashQueues.markDelayed(getblkNum);
						cout << getblkNum << endl;
						using_blocks.Enqueue(getblkNum,0); //����ϴ� ����� instruction cycle �������̹Ƿ� using_block�� ����
					}
					else
					{
						cout << "������ ����� ����� �� �����ϴ�" << endl;
						//cout << FreeList.LengthIs() << "     " << using_blocks.lengthis() << endl;
						waiting_blocks.Enqueue(getblkNum); //���� ������ ����� ���� ��� waiting ��Ŵ

					}

					for (i = 0; i < using_blocks.lengthis(); i++)
					{
						using_blocks.Dequeue(doneblock, temp);
						temp++;
						using_blocks.Enqueue(doneblock, temp);
					}
					k++;
				}
				endTime = clock();
			}
			cout << endl << endl;
		}
		else if (command == 2) break;
		else cout << "�߸��� ����Դϴ�" << endl;

	}

	FreeList.~UnsortedType();
	HashQueues.~Hash();
	return 0;
}