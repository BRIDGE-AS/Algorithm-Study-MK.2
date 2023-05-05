#include <iostream>
#include <algorithm>
using namespace std;
constexpr int LIMIT = 51;
constexpr int DX[4] = {-1,1, 0, 0};
constexpr int DY[4] = {0, 0, 1, -1};
int N;
int maxLength;
char board[LIMIT][LIMIT];

void Check() {
    int xLength = 0;
    int yLength = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
			// X check
            if (j - 1 < 0 || board[i][j - 1] != board[i][j])
                xLength = 1;
            else
                xLength++;
            if (maxLength < xLength) 
				maxLength = xLength;

			// Y check
            if (j - 1 < 0 || board[j - 1][i] != board[j][i])
                yLength = 1;
            else
                yLength++;
            if (maxLength < yLength)
				maxLength = yLength;

        }
    }
}
void Change() {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
			for(int k=0; k<4; k++)
			{
				int curY = y+DY[k];
				int curX = x+DX[k];
				
				if(curY < 0 || curY >= N || curX < 0 || curY >= N)
					continue;
				swap(board[y][x], board[curY][curX]);
	            Check();
				swap(board[y][x], board[curY][curX]);
			}
        }
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> board[y][x];
        }
    }

    Change();

    cout << maxLength;
}