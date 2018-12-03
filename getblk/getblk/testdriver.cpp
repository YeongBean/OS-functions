//getblk를 테스트하는 테스트 드라이버
#include "queueType.h" //사용이 끝난 프로세스블록 반환을 빨리 하려고 사용
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
	QueType using_blocks(100), waiting_blocks(100); //using + 프로세스가 100개이므로 최악의 경우 100개까지 기다릴수 있음
	//초기 세팅 변수

	float command = 0;
	int startTime = 0, endTime = 0;
	//getblk 시간재는 변수

	while(i < number_of_blocks)
	{
		temp = rand() % 300; //블록넘버 생성
		HashQueues.HashRetrieveItem(temp, found, busy, delayed, writing);
		
		if (found == false) //중복되는 블록넘버가 없으면
		{
			//FreeList.InsertItem(temp);
			HashQueues.HashInsertItem(temp); //삽입
			i++;
		}
	}//해시큐에 100개의 블록 생성 완료

	int k = 0;

	while (true)
	{
		cout << "무엇을 하시겠습니까?" << endl << "1)3초간 getblk실행  2)프로그램 종료  : ";
		cin >> command;
		k = 0;
		if (command == 1)
		{
			cout << "몇초간 실행하시겠습니까?  : ";
			cin >> command;
			startTime = clock();
			while (endTime - startTime < command * 1000)
			{
				if ((endTime - startTime) % 50 == 0)
				{
					if (!using_blocks.IsEmpty()) 
					{
						using_blocks.Dequeue(doneblock,temp);
						if (temp > 3) //적어도 각 블록이 4개 이상의 단계를 거쳤다는 뜻임
						{
							cout << "-----------------------------------------------" << endl;
							cout << doneblock << "번 블록의 작업이 끝나 FreeList에 반환합니다" << endl; //카운터가 4인 블록 반환(instruction cyle이 4단계이므로)
							cout << "-----------------------------------------------" << endl;
							FreeList.InsertItem(doneblock); //프리리스트에 해당번호의 블록 삽입
							HashQueues.HashRetrieveItem(getblkNum, found, busy, delayed, writing);
							if (busy == true) HashQueues.markBusy(doneblock);
							if (writing == true) HashQueues.markWrite(doneblock);
							if (delayed == true) HashQueues.markDelayed(doneblock); //작업이 끝났으므로 busy와 delayed는 해제함
						}//3단계 이상을 거치지 않았다면 = operation cycle을 끝내지 않았다면
						else using_blocks.Enqueue(doneblock, temp); //다시 using blocks에 넣음
					} //작업이 끝난 블록 먼저 처리

					if (!waiting_blocks.IsEmpty() && !FreeList.IsEmpty()) //기다리고 있는 프로세스가 있고 프리리스트가 비어있지 않다면
					{
						waiting_blocks.Dequeue(getblkNum, temp); //먼저 한다
						cout << "--> sleep중이던 블록이 사용할 ";
					}
					else getblkNum = rand() % 300;//필요한 블록넘버 생성

					cout << getblkNum << "번 블록이 필요합니다" << endl; //필요한 블록넘버 요구 + 취득
					temp = getblk(getblkNum, HashQueues, FreeList);

					if (temp != -1)
					{
						cout << temp << "번 블록을 사용합니다" << endl;

						temp = rand() % 2;
						if (temp == 0) HashQueues.markBusy(getblkNum);
						else HashQueues.markDelayed(getblkNum);
						cout << getblkNum << endl;
						using_blocks.Enqueue(getblkNum,0); //사용하는 블록은 instruction cycle 수행중이므로 using_block에 넣음
					}
					else
					{
						cout << "지금은 블록을 사용할 수 없습니다" << endl;
						//cout << FreeList.LengthIs() << "     " << using_blocks.lengthis() << endl;
						waiting_blocks.Enqueue(getblkNum); //현재 가용한 블록이 없을 경우 waiting 시킴

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
		else cout << "잘못된 명령입니다" << endl;

	}

	FreeList.~UnsortedType();
	HashQueues.~Hash();
	return 0;
}