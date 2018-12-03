#include <iostream>
#include "List.h"
#include "Que.h"

using namespace std;

int main()
{
	int Memory_Size = 1000;
	int process_number, temp, start = 0, space = 1000, required = 0, entry_point = 0, space_count = 1, inList_process_point;
	int inList_process_size, sum_of_left_space = Memory_Size, compares;
	bool found = true, temp_bool; //compaction���� ���� �����ϴ� �뵵
	int command;
	SortedType<int> process_list;
	SortedType<int> temp_process;
	QueType tempQueue;

	cout << "�޸� ������" << Memory_Size << endl;
	
	while (true)
	{
		
		cout << "������ �Ͻðڽ��ϱ�? (1 �޸� ���� 2 ����) : ";
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
						//cout << "���� ��ȣ�� ���μ����� �ֽ��ϴ�" << endl;
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
						//cout << "�ش� ��ȣ�� ���μ����� �����ϴ�" << endl;
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
						if (required <= inList_process_point - start) //������ ������ ���̸�
						{
							if (inList_process_point - start < space) //����Ʈ ���̽����� Ȯ��
							{										  //������
								entry_point = start;				  //������������ ����
								space = inList_process_point - start; //������ ������������ ���� ������ ����
							}
							found == true;							  //ã����
						}
						else
						{											//�ƴϸ�
							if (inList_process_point - start != 0)	//���� ���μ����� ������ 0�� �ƴϸ�
								space_count++;						//���ҵ� �����̶�� ���̹Ƿ� ����
							start = start + inList_process_size;	//������ ������������ ���� ������ ����
						}
						if (i == process_list.LengthIs() - 1)
						{		//������ ���μ����� �������� ����
							if (start + required <= Memory_Size)
							{			//��Ʈ�Ӹ��� ���� ���� Ȯ��
								if (found == false)					//�������� ������ ������ ��ã������
								{
									found = true;					//�� �������� �Ѵ�
									entry_point = start;			//�������� ����
								}
								else
								{												//������ ������ ������ ã�� ������
									if (1000 - (start + required) < space)		//�� ������ ��(�ռ� if������ ��Ʈ�Ӹ� ������ rquired���� ũ�ų� ������ Ȯ������)
										entry_point = start;					//����Ʈ ���̽��� ����� �������
								}
							}
						}
					}


					if (found == false && process_list.LengthIs() > 1)//������ ��ã������
					{
						process_list.InsertItem(1001, 1001, 1001);
						
						while (process_list.LengthIs() > 0)
						{
							process_list.ResetList();
							process_list.GetNextItem(process_number, inList_process_point, inList_process_size);
							process_list.DeleteItem(process_number);
							tempQueue.Enqueue(process_number, inList_process_size);
						}//���μ������� ť�� ����
						process_list.MakeEmpty();
						entry_point = 0;
						while (tempQueue.lengthIs() > 1)
						{
							tempQueue.Dequeue(process_number, inList_process_size);

							process_list.InsertItem(process_number, entry_point, inList_process_size);
							entry_point += inList_process_size;
						}//ť�� ���μ����� ����� ���� ���μ�������Ʈ�� ����
						tempQueue.MakeEmpty();
						if (1000 - entry_point >= required)
						{
							space_count = 1;
							found = true;
						}//�׷��� ������ ������ Ȯ��
						cout << "���Ѽ� ����Ϸ�" << endl;
					} // compaction ����

					process_number = temp;

					if (found == true) //������ ã������
					{
						process_list.InsertItem(process_number, entry_point, required);//����
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
					else cout << "������ �����մϴ� ���μ����� ������ �ּ���" << endl;
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
						} //���� ���� ���


						process_list.ResetList();
						entry_point = 0;
						space_count = 1;
						for (int h = 0; h < process_list.LengthIs(); h++)
						{											//���� �Ŀ��� ������� ������ ����� ��
							process_list.GetNextItem(process_number, inList_process_point, inList_process_size);
							if (inList_process_point - entry_point != 0)	//������� �پ��ִٸ� �׳� �Ѿ
								space_count++;						//���ҵ� �����̶�� ���̹Ƿ� ����
							entry_point = entry_point + inList_process_size;	//������ ������������ ���� ������ ����
						}

						process_number = temp;

						cout << "FREE REQUEST " << process_number << " : " << required << endl;
						cout << "Best fit : Freed at address " << entry_point << endl;
						cout << "        " << sum_of_left_space << "K free, " << space_count << " block(s) average size = " << sum_of_left_space / space_count << "K" << endl;
					}
					else cout << "���μ����� ã�� �� �����ϴ�" << endl;
					
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
			cout << "�߸��� ����Դϴ�" << endl;
			break;
		}
		
	}




	return 0;
}