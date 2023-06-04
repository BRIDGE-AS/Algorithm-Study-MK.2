#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 연산자 종류
enum class Oper
{
	Space,
	Plus,
	Minus
};

// 연산자들을 보고 수식 출력
void PrintFormula(const vector<Oper>& operVec)
{
	int N = operVec.size() + 1;

	for (int i = 1; i < N; ++i)
	{
		printf("%d", i);

		if (operVec[i - 1] == Oper::Space)
			printf(" ");
		else if (operVec[i - 1] == Oper::Plus)
			printf("+");
		else if (operVec[i - 1] == Oper::Minus)
			printf("-");
	}

	printf("%d\n", N);
}

// 공백으로 이어진 숫자 반환
int getGroupNumber(queue<int>& group)
{
	int num = 0;
	int multi = 1;

	while (!group.empty())
	{
		num += group.front() * multi;
		multi *= 10;

		group.pop();
	}

	return num;
}

// 해당 연산자들이 0을 도출하는지 확인
bool isValidFormula(vector<Oper> operVec)
{
	int N = operVec.size() + 1;

	int total = 0;
	
	queue<int> group;
	group.push(N);

	for (int i = N; i >= 2; --i)
	{
		// 현재 연산자
		Oper oper = operVec[i - 2];

		if (oper == Oper::Space)
		{
			group.push(i - 1);
		}
		else if (oper == Oper::Plus)
		{
			int groupNum = getGroupNumber(group);
			total += groupNum;

			group.push(i - 1);
		}
		else if (oper == Oper::Minus)
		{
			int groupNum = getGroupNumber(group);
			total -= groupNum;

			group.push(i - 1);
		}
	}

	// 1 앞에 있는 건 사실상 '+'
	int groupNum = getGroupNumber(group);
	total += groupNum;

	return (total == 0);
}

// 재귀를 통해 ASCII 순서대로 연산자들 실험
void SimulateFormula(vector<Oper>& operVec, int index, int last)
{
	if (index > last) return;

	operVec[index] = Oper::Space;

	if (index == last)
	{
		if (isValidFormula(operVec))
			PrintFormula(operVec);
	}

	SimulateFormula(operVec, index + 1, last);

	operVec[index] = Oper::Plus;

	if (index == last)
	{
		if (isValidFormula(operVec))
			PrintFormula(operVec);
	}

	SimulateFormula(operVec, index + 1, last);

	operVec[index] = Oper::Minus;

	if (index == last)
	{
		if (isValidFormula(operVec))
			PrintFormula(operVec);
	}

	SimulateFormula(operVec, index + 1, last);
}

// 메인
int main()
{
	int T;
	scanf("%d", &T);

	for (int i = 0; i < T; ++i)
	{
		int N;
		scanf("%d", &N);

		vector<Oper> operVec(N - 1);
		SimulateFormula(operVec, 0, N - 2);

		if(i < T - 1)
			printf("\n");
	}
}
