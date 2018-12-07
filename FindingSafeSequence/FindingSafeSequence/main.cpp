#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int kindOfResources = 4;
	int numberOfProcesses = 10;
	int numberOfInstances[4] = { 50,60,70,80 }; //인스턴스는 4개가 있으며 각각 초기 Available값을 정해줌
	int MaxnumOfProcesses[4][10];
	int currentAllocation[4][10];
	int currentNeed[4][10];

	int currentAvailable[4]; //비교용
	bool isEnd[10] = { false, false, false, false, false, false, false, false, false, false}; //while문의 조건용. 각 프로세스가 끝났는지 알아봄. 초기값은 모드 false
	int safeSequence[10] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

	int inst1, inst2, inst3, inst4;
	int deadCheck = 0;
	int endNum = 0;

	for (int i = 0; i < 4; i++)
	{
		currentAvailable[i] = numberOfInstances[i]; //초기 Available값 할당
		for (int j = 0; j < 10; j++)
		{
			MaxnumOfProcesses[i][j] = int(rand() % numberOfInstances[i]); //각 인스턴스보다 작거나 같은 값들을 MAX로 정함	
			currentNeed[i][j] = MaxnumOfProcesses[i][j]; //초기에는 인스턴스가 할당되어 있지 않으므로 MAx와 Need가 같음
		}
	}

	int temp; 
	cout << "Process     p0  p1  p2  p3  p4  p5  p6  p7  p8  p9" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "Instance" << i + 1 << " : ";
		for (int j = 0; j < 10; j++)
		{
			temp = int(rand() % (MaxnumOfProcesses[i][j] + 2) / 2); //현재 allocation을 각 인스턴스의 MAX값의 절반이하로 할당-한번에 너무 많이 할당하지 않으려고
			while (temp > currentAvailable[i]) temp = int(rand() % (MaxnumOfProcesses[i][j] + 2) / 2); //가용한 자원보다 많으면 다시 정함

			currentAvailable[i] -= temp; //할당한만큼 뺌
			currentNeed[i][j] -= temp;
			cout << setw(2) <<  temp << "  ";
		}
		cout << endl;
	} 
	
	cout << "==================Initial State=====================" << endl; //처음 자원 할당 끝
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

	//======================= 할당할 프로세스 넘버와 할당할 인스턴스 갯수 정함 ==========================

	bool isAllEnd = false;
	int chkProcessNum = temp;

	if (inst1 <= currentAvailable[0] && inst2 <= currentAvailable[1] && inst3 <= currentAvailable[2] && inst4 <= currentAvailable[3]) //요청하는게 available보다는 같거나 작아야 함
		if (inst1 <= currentNeed[0][chkProcessNum] && inst2 <= currentNeed[1][chkProcessNum] && inst3 <= currentNeed[2][chkProcessNum] && inst4 <= currentNeed[3][chkProcessNum]) //요청하는게 해당 프로세스의 need보다같거나 작아야 함
		{
			
		} //일단 조건에 맞ㅇ면 할당해 줌
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
		currentAvailable[3] += currentAllocation[3][chkProcessNum]; //가지고 있던 자원 반환
		isEnd[chkProcessNum] = true; //해당 프로세스는 끝낸거임
		for (int i = 0; i < 10; i++)
			if (safeSequence[i] == 100)
			{
				safeSequence[i] = chkProcessNum; //safe sequence 순서에 넣음
				break;
			}

		isAllEnd = true;
		for (int i = 0; i < 10; i++)
			if (isEnd[i] == false)
			{
				isAllEnd = false; //하나라도 false면 모두 끝난게 아님
			}

		for (int k = 0; k < 10; k++)
			if (isEnd[k] == false) //끝나지 않은 프로세스에 한해서 검사
			{
				if (currentNeed[0][k] > currentAvailable[0] || currentNeed[1][k] > currentAvailable[1] || currentNeed[2][k] > currentAvailable[2] || currentNeed[3][k] > currentAvailable[3])
				{//끝나지 않은 프로세스 중 available보다 큰 자원을 요구하는 프로세스가 있다면 카운트
					deadCheck++;
				}else chkProcessNum = k;
			}
			else endNum++;

		if (deadCheck + endNum == 10) //끝나지 않은 모든 프로세스중 조건에 맞지 않는 수와 와 끝난 프로세스의 합이 10이라면 죽은것임
		{
			cout << "DEAD..." << endl;
			break;
		}//현재 프로세스 처리 후 끝내지 않은 모든 프로세스에 대해 검사

			 //데드상태가 아니면 다음 번호 정함
		while (isEnd[chkProcessNum] == true || (currentNeed[0][chkProcessNum] > currentAvailable[0] || currentNeed[1][chkProcessNum] > currentAvailable[1] || currentNeed[2][chkProcessNum] > currentAvailable[2] || currentNeed[3][chkProcessNum] > currentAvailable[3]))
			chkProcessNum = int(rand() % 10); //다음에 체크할 프로세스는 랜덤으로 정해봄
	}

	for (int i = 0; i < 10; i++) cout << safeSequence[i] << "  ";
	cin >> temp;
	return 0;
}