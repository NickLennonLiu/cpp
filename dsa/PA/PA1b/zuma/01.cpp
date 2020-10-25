#include <iostream>
#include <string>

using namespace std;

string a;   // 初始字符串

void play(int rank) {
    int left = rank;
    int right = rank;
    char color = a[rank];                                   // 标定当前颜色
    while (left >= 0 && a[left] == color) --left;
    left += 1;                                              // 向左走直到遇到的颜色不一样
    while (right < a.size() && a[right] == color) ++right;  // 向右走直到遇到的颜色不一样

    int size = right - left;
    if (size >= 3) {
        a.erase(left, size);
        play(left - 1);
    }
}

int main() {
    getline(cin, a);
    int m = 0;
    cin >> m;

    int rank; char color;
    for (int i = 0; i < m; ++i) {
        cin >> rank >> color;
        a.insert(a.cbegin() + rank, color); // 在序列的rank位置插入color
        play(rank);                         // 在rank位置进行游玩
    }

    cout << a << endl;

    return 0;
}
