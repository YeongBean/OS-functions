#include <iostream>
#include "List.h"
#include "Que.h"

using namespace std;

int main()
{
	int Memory_Size = 1000;
	int process_number, temp, start = 0, space = 1000, required = 0, entry_point = 0, space_count = 1, inList_process_point;
	int inList_process_size, sum_of_left_space = Memory_Size, compares;
	bool found = true, temp_bool; //compaction할지 말지 결정하는 용도
	int command;
	SortedType<int> process_list;
	SortedType<int> temp_process;
	QueType tempQueue;

	cout << "메모리 사이즈" << Memory_Size << endl;
	
	while (true)
	{
		
		cout << "무엇을 하시겠습니까? (1 메모리 관리 2 종료) : ";
		cin >> command;

		switch (command)
		{
		case 2:
			return 0;
			break;

		case 1:
			for (int cnt = 0; cnt < 10; cnt++) {
				process_number = rand() % 2;
				if (process_number != 0)
				{
					process_number = rand() % 100 + 1;
					temp = process_number;
					required = rand() % 80 + 60;
					process_list.RetrieveItem(process_number, temp_bool);
					if (temp_bool == true)
					{
						while (temp_bool == true)
						{
							process_number = rand() % 100 + 1;
							process_list.RetrieveItem(process_number, temp_bool);
						}
						//cout << "동일 번호의 프로세스가 있습니다" << endl;
						//break;
					}
				}
				else
				{
					required = 0;
					process_number = rand() % 100 + 1;
					//cin >> process_number;
					temp = process_number;
					process_list.RetrieveItem(process_number, temp_bool);
					if (temp_bool == false)
					{
						while (temp_bool == false)
						{
							process_number = rand() % 100 + 1;
							process_list.RetrieveItem(process_number, temp_bool);
						}
						//cout << "해당 번호의 프로세스가 없습니다" << endl;
						//break;
					}
				}


				process_list.ResetList();

				if (required != 0)
				{
					process_list.RetrieveItem(process_number, temp_bool);
					cout << "REQUEST " << process_number << " : " << required << endl;
					process_list.ResetList();
					if (temp_bool == true)
					{
						while (temp_bool == true)
						{
							process_number = rand() % 100 + 1;
							process_list.RetrieveItem(process_number, temp_bool);
						}
					}

					for (int i = 0; i < process_list.LengthIs(); i++)
					{
						process_list.GetNextItem(process_number, inList_process_point, inList_process_size);
						if (required <= inList_process_point - start) //적절한 공간이 보이면
						{
							if (inList_process_point - start < space) //베스트 케이스인지 확인
							{										  //맞으면
								entry_point = start;				  //진입지점으로 설정
								space = inList_process_point - start; //다음에 진입지점으로 비교할 값으로 설정
							}
							found == true;							  //찾았음
						}
						else
						{											//아니면
							if (inList_process_point - start != 0)	//만약 프로세스간 간격이 0이 아니면
								space_count++;						//분할된 공간이라는 뜻이므로 더함
							start = start + inList_process_size;	//다음에 진입지점으로 비교할 값으로 설정
						}
						if (i == process_list.LengthIs() - 1)
						{		//마지막 프로세스의 끝지점에 오면
							if (start + required <= Memory_Size)
							{			//끄트머리에 남은 공간 확인
								if (found == false)					//아직까지 적합한 공간을 못찾았으면
								{
									found = true;					//이 공간으로 한다
									entry_point = start;			//진입지점 설정
								}
								else
								{												//위에서 적절한 공간을 찾긴 했으면
									if (1000 - (start + required) < space)		//그 공간과 비교(앞선 if문에서 끄트머리 공간이 rquired보다 크거나 같음을 확인했음)
										entry_point = start;					//베스트 케이스면 여기다 집어넣음
								}
							}
						}
					}


					if (found == false && process_list.LengthIs() > 1)//공간을 못찾았으면
					{
						process_list.InsertItem(1001, 1001, 1001);
						
						while (process_list.LengthIs() > 0)
						{
							process_list.ResetList();
							process_list.GetNextItem(process_number, inList_process_point, inList_process_size);
							process_list.DeleteItem(process_number);
							tempQueue.Enqueue(process_number, inList_process_size);
						}//프로세스들을 큐에 넣음
						process_list.MakeEmpty();
						entry_point = 0;
						while (tempQueue.lengthIs() > 1)
						{
							tempQueue.Dequeue(process_number, inList_process_size);

							process_list.InsertItem(process_number, entry_point, inList_process_size);
							entry_point += inList_process_size;
						}//큐의 프로세스를 빈공간 없이 프로세스리스트에 넣음
						tempQueue.MakeEmpty();
						if (1000 - entry_point >= required)
						{
							space_count = 1;
							found = true;
						}//그래도 공간이 없는지 확인
						cout << "컴팩션 진행완료" << endl;
					} // compaction 진행

					process_number = temp;

					if (found == true) //공간을 찾았으면
					{
						process_list.InsertItem(process_number, entry_point, required);//삽입
						process_list.ResetList();
						for (int k = 0; k < process_list.LengthIs(); k++)
						{
							process_list.GetNextItem(process_number, inList_process_point, inList_process_size);
							//cout << process_number << endl;
							sum_of_left_space -= inList_process_size;
						}



						cout << "Best fit : Allocated address " << entry_point << endl;
						cout << "        " << sum_of_left_space << "K free, " << space_count << " block(s) average size = " << sum_of_left_space / space_count << "K" << endl;
					}
					else cout << "공간이 부족합니다 프로세스를 삭제해 주세요" << endl;
				}
				else
				{
					process_number = temp;
					process_list.RetrieveItem(temp, temp_bool);
					/*
					while (temp_bool == false)
					{
						process_number = rand() % 100 + 1;
						process_list.RetrieveItem(process_number, temp_bool);
					}*/
					if (temp_bool == true)
					{
						process_list.DeleteItem(process_number);
						process_list.ResetList();
						for (int k = 0; k < process_list.LengthIs(); k++)
						{
							process_list.GetNextItem(process_number, inList_process_point, inList_process_size);

							sum_of_left_space -= inList_process_size;
						} //남은 공간 계산


						process_list.ResetList();
						entry_point = 0;
						space_count = 1;
						for (int h = 0; h < process_list.LengthIs(); h++)
						{											//삭제 후에도 빈공간의 개수를 세어야 함
							process_list.GetNextItem(process_number, inList_process_point, inList_process_size);
							if (inList_process_point - entry_point != 0)	//빈공간이 붙어있다면 그냥 넘어감
								space_count++;						//분할된 공간이라는 뜻이므로 더함
							entry_point = entry_point + inList_process_size;	//다음에 진입지점으로 비교할 값으로 설정
						}

						process_number = temp;

						cout << "FREE REQUEST " << process_number << " : " << required << endl;
						cout << "Best fit : Freed at address " << entry_point << endl;
						cout << "        " << sum_of_left_space << "K free, " << space_count << " block(s) average size = " << sum_of_left_space / space_count << "K" << endl;
					}
					else cout << "프로세스를 찾을 수 없습니다" << endl;
					
				}
				start = 0;
				space = 1000;
				entry_point = 0;
				space_count = 1;
				found = false;
				sum_of_left_space = Memory_Size;
			}
			break;
			
		default:
			cout << "잘못된 명령입니다" << endl;
			break;
		}
		
	}




	return 0;
}