#include<bits/stdc++.h>
using namespace std;

void recursiveSearch(int N, int currentN = 1, string expression = "1");
int getSum(string expressionStr);
int convertOperatorToInt(char opertator);


int main() {
	cin.tie(0)->sync_with_stdio(0);

	int T, N;
	cin >> T;

	while (T--)
	{
		cin >> N;
		recursiveSearch(N);
		cout << "\n";
	}
}

void recursiveSearch(int N, int currentN, string expression) {
	if (N == currentN) {
		if (getSum(expression) == 0) cout << expression << "\n";
		return;
	}
	int nextN = currentN + 1;
	// ASCII : ' ' -> '+' -> '-'
	recursiveSearch(N, nextN, expression + ' ' + to_string(nextN));
	recursiveSearch(N, nextN, expression + '+' + to_string(nextN));
	recursiveSearch(N, nextN, expression + '-' + to_string(nextN));
}

int getSum(string expression) {
	int sum = 0;
	int sign = 1;
	int operand = 1;
	// i : operator index
	for (int i = 1; i < expression.length(); i += 2) {
		char curOperaotor = expression[i];
		int nextOperand = expression[i + 1] - '0';

		if (curOperaotor == '+' || curOperaotor == '-') {
			sum += operand * sign;
			sign = convertOperatorToInt(curOperaotor);
			operand = nextOperand;
		}
		else if (curOperaotor == ' ') {
			operand = operand * 10 + nextOperand;
		}
	}
	sum += operand * sign;
	return sum;
}

int convertOperatorToInt(char opertator)
{
	int sign = 1;
	if (opertator == '+') sign = 1;
	else if (opertator == '-')  sign = -1;
	return sign;
}