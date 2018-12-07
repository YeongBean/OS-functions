#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int kindOfResources = 4;
	int numberOfProcesses = 10;
	int numberOfInstances[4] = { 50,60,70,80 }; //�ν��Ͻ��� 4���� ������ ���� �ʱ� Available���� ������
	int MaxnumOfProcesses[4][10];
	int currentAllocation[4][10];
	int currentNeed[4][10];

	int currentAvailable[4]; //�񱳿�
	bool isEnd[10] = { false, false, false, false, false, false, false, false, false, false}; //while���� ���ǿ�. �� ���μ����� �������� �˾ƺ�. �ʱⰪ�� ��� false
	int safeSequence[10] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

	int inst1, inst2, inst3, inst4;
	int deadCheck = 0;
	int endNum = 0;

	for (int i = 0; i < 4; i++)
	{
		currentAvailable[i] = numberOfInstances[i]; //�ʱ� Available�� �Ҵ�
		for (int j = 0; j < 10; j++)
		{
			MaxnumOfProcesses[i][j] = int(rand() % numberOfInstances[i]); //�� �ν��Ͻ����� �۰ų� ���� ������ MAX�� ����	
			currentNeed[i][j] = MaxnumOfProcesses[i][j]; //�ʱ⿡�� �ν��Ͻ��� �Ҵ�Ǿ� ���� �����Ƿ� MAx�� Need�� ����
		}
	}

	int temp; 
	cout << "Process     p0  p1  p2  p3  p4  p5  p6  p7  p8  p9" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "Instance" << i + 1 << " : ";
		for (int j = 0; j < 10; j++)
		{
			temp = int(rand() % (MaxnumOfProcesses[i][j] + 2) / 2); //���� allocation�� �� �ν��Ͻ��� MAX���� �������Ϸ� �Ҵ�-�ѹ��� �ʹ� ���� �Ҵ����� ��������
			while (temp > currentAvailable[i]) temp = int(rand() % (MaxnumOfProcesses[i][j] + 2) / 2); //������ �ڿ����� ������ �ٽ� ����

			currentAvailable[i] -= temp; //�Ҵ��Ѹ�ŭ ��
			currentNeed[i][j] -= temp;
			cout << setw(2) <<  temp << "  ";
		}
		cout << endl;
	} 
	
	cout << "==================Initial State=====================" << endl; //ó�� �ڿ� �Ҵ� ��
	cout << "Available" << endl << "Instance1 :" << currentAvailable[0] << endl << "Instance2 :" << currentAvailable[1] << endl << "Instance3 :" << currentAvailable[2] << endl << "Instance4 :" << currentAvailable[3] << endl << endl;
	cout << "Need        p0  p1  p2  p3  p4  p5  p6  p7  p8  p9" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "Instance" << i + 1 << " : ";
		for (int j = 0; j < 10; j++) cout << setw(2) << currentNeed[i][j] << "  ";
		cout << endl;
	}
	temp = 10;
	while (temp > 9) {
		cout << "Which process do you want to allocate? : ";
		cin >> temp;
	}
	cout << "How many instances do you want to allocate to process" << temp << "?" << endl << "(inst1 inst2 inst3 inst4) : ";
	cin >> inst1 >> inst2 >> inst3 >> inst4;

	//======================= �Ҵ��� ���μ��� �ѹ��� �Ҵ��� �ν��Ͻ� ���� ���� ==========================

	bool isAllEnd = false;
	int chkProcessNum = temp;

	if (inst1 <= currentAvailable[0] && inst2 <= currentAvailable[1] && inst3 <= currentAvailable[2] && inst4 <= currentAvailable[3]) //��û�ϴ°� available���ٴ� ���ų� �۾ƾ� ��
		if (inst1 <= currentNeed[0][chkProcessNum] && inst2 <= currentNeed[1][chkProcessNum] && inst3 <= currentNeed[2][chkProcessNum] && inst4 <= currentNeed[3][chkProcessNum]) //��û�ϴ°� �ش� ���μ����� need���ٰ��ų� �۾ƾ� ��
		{
			
		} //�ϴ� ���ǿ� �¤��� �Ҵ��� ��
		else
		{
			cout << "incorrect request" << endl;

			cout << "Enter any character to exit program ";
			cin >> temp;
			return 0;
		}
	else
	{
		cout << "incorrect request" << endl;

		cout << "Enter any integer to exit program ";
		cin >> temp;
		return 0;
	}

	while (isAllEnd == false)
	{
		currentAvailable[0] += currentAllocation[0][chkProcessNum];
		currentAvailable[1] += currentAllocation[1][chkProcessNum];
		currentAvailable[2] += currentAllocation[2][chkProcessNum];
		currentAvailable[3] += currentAllocation[3][chkProcessNum]; //������ �ִ� �ڿ� ��ȯ
		isEnd[chkProcessNum] = true; //�ش� ���μ����� ��������
		for (int i = 0; i < 10; i++)
			if (safeSequence[i] == 100)
			{
				safeSequence[i] = chkProcessNum; //safe sequence ������ ����
				break;
			}

		isAllEnd = true;
		for (int i = 0; i < 10; i++)
			if (isEnd[i] == false)
			{
				isAllEnd = false; //�ϳ��� false�� ��� ������ �ƴ�
			}

		for (int k = 0; k < 10; k++)
			if (isEnd[k] == false) //������ ���� ���μ����� ���ؼ� �˻�
			{
				if (currentNeed[0][k] > currentAvailable[0] || currentNeed[1][k] > currentAvailable[1] || currentNeed[2][k] > currentAvailable[2] || currentNeed[3][k] > currentAvailable[3])
				{//������ ���� ���μ��� �� available���� ū �ڿ��� �䱸�ϴ� ���μ����� �ִٸ� ī��Ʈ
					deadCheck++;
				}else chkProcessNum = k;
			}
			else endNum++;

		if (deadCheck + endNum == 10) //������ ���� ��� ���μ����� ���ǿ� ���� �ʴ� ���� �� ���� ���μ����� ���� 10�̶�� ��������
		{
			cout << "DEAD..." << endl;
			break;
		}//���� ���μ��� ó�� �� ������ ���� ��� ���μ����� ���� �˻�

			 //������°� �ƴϸ� ���� ��ȣ ����
		while (isEnd[chkProcessNum] == true || (currentNeed[0][chkProcessNum] > currentAvailable[0] || currentNeed[1][chkProcessNum] > currentAvailable[1] || currentNeed[2][chkProcessNum] > currentAvailable[2] || currentNeed[3][chkProcessNum] > currentAvailable[3]))
			chkProcessNum = int(rand() % 10); //������ üũ�� ���μ����� �������� ���غ�
	}

	for (int i = 0; i < 10; i++) cout << safeSequence[i] << "  ";
	cin >> temp;
	return 0;
}