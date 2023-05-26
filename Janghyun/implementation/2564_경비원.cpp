#include <bits/stdc++.h>
using namespace std;
constexpr int LIMIT = 102;
using pInt = pair<int, int>;

pInt inputPair();
void convertPosition(pInt& pos, pInt& length);
int getMinCost(const pInt& curX, const pInt& target, const pInt& length);
int getClockwiseCost(pInt curX, const pInt& target, const pInt& length, int cost = 0);
bool isWest(const pInt& curX, const pInt& length);
bool isNorth(const pInt& curX, const pInt& length);
bool isEast(const pInt& curX, const pInt& length);
bool isSouth(const pInt& curX, const pInt& length);


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int storeCnt;
    int sum = 0;
    pInt store[LIMIT];
    pInt X;
    pInt length;

    length = inputPair();
    cin >> storeCnt;

    for (int i = 0; i < storeCnt; i++) {
        store[i] = inputPair();
        convertPosition(store[i], length);
    }
    X = inputPair();
    convertPosition(X, length);

    for (int i = 0; i < storeCnt; i++) {
        sum += getMinCost(X, store[i], length);
    }
    cout << sum;
}

pInt inputPair() {
    int x, y;
    cin >> x >> y;
    return make_pair(x, y);
}

// pair<x, y> 형태로 변환
void convertPosition(pInt& pos, pInt& length) {
    switch (pos.first) {
        // North
    case 1:
        pos = make_pair(pos.second, length.second);
        break;
        // South
    case 2:
        pos = make_pair(pos.second, 0);
        break;
        // West
    case 3:
        pos = make_pair(0, length.second - pos.second);
        break;
        // East
    case 4:
        pos = make_pair(length.first, length.second - pos.second);
        break;
    }
}

int getMinCost(const pInt& curX, const pInt& target, const pInt& length) {
    int clockwiseCost = getClockwiseCost(curX, target, length);
    int round = length.first * 2 + length.second * 2;
    int cost = min(clockwiseCost, round - clockwiseCost);
    return cost;
}

int getClockwiseCost(pInt curX, const pInt& target, const pInt& length, int cost) {
    if (curX == target)
        return cost;
    else if (isWest(curX, length))
        curX.second += 1;
    else if (isNorth(curX, length))
        curX.first += 1;
    else if (isEast(curX, length))
        curX.second -= 1;
    else if (isSouth(curX, length))
        curX.first -= 1;
    return getClockwiseCost(curX, target, length, cost + 1);
}

bool isWest(const pInt& curX, const pInt& length) {
    return (curX.first == 0 && curX.second < length.second);
}
bool isNorth(const pInt& curX, const pInt& length) {
    return (curX.first < length.first&& curX.second == length.second);
}
bool isEast(const pInt& curX, const pInt& length) {
    return (curX.first == length.first && curX.second > 0);
}
bool isSouth(const pInt& curX, const pInt& length) {
    return (curX.first > 0 && curX.second == 0);
}