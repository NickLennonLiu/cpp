#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

char a[1 << 22]; // 不分块的珠子
int realn;       // 珠子总长度

constexpr int cut = 1 << 11; // 分块时每一块的长度
constexpr int sec = 1 << 12; // 每块最大长度

//constexpr int cut = 1 << 3; // 分块时每一块的长度
//constexpr int sec = 1 << 4; // 每块最大长度

char p[1 << 12][sec]; // 分的块
int plen[1 << 12];    // 每一块的长度
int pn;               // 块数

struct Rank {
    int first, second;
};

// a to p：将 a 切分成 p
// p的开头p[0]就是实际的珠子序列，而不是无意义的HEAD
// 复杂度：O(realn)
void a2p() {
    if (realn == 0) {
        pn = 1;
        plen[0] = 0;
        return;
    }
    int i = 0, j = 0;
    for (; j < realn; i++, j += cut) {
        int m = realn - j < cut ? realn - j : cut;
        memcpy(p[i], &a[j], m);
        plen[i] = m;
    }
    pn = i;
}

// p to a：将 p “组装”回 a
// 复杂度 ：O(realn)
void p2a() {
    int old_realn = realn;
    realn = 0;
    for (int i = 0; i < pn; i++) {
        memcpy(&a[realn], p[i], plen[i]);
        realn += plen[i];
    }
}

// 调试用：打印所有块，每块一行
void viewp() {
    for (int i = 0; i < pn; i++) {
        for (int j = 0; j < plen[i]; j++)
            putchar(p[i][j]);
        cout << " " << plen[i];
        putchar('\n');
    }
}

// 返回rank对应的group和位置
// 调用位置： 插入珠子前、块过长而重组后重新确定rank位置
// 如果rank对应的是某个块的长度，则最终rank不会转到下一个块，而是当前块的最后一个位置+1
Rank find(int rank) {
    int group = 0;
    while (group < pn - 1 && rank > plen[group]) {      // 为何这里是 > 而不是 >=
        rank -= plen[group];
        group++;
    }
    return {group, rank};
}

// 获得第pos.first块的第pos.second个字符
inline char &get(Rank pos) {
    return p[pos.first][pos.second];
}

// 在 p 上计算珠子的插入和消除
// 在rank位置即将插入一个ch
void play(int rank, char ch) {
    Rank pos = find(rank);
    char *cur = &get(pos);
    int succ_len = plen[pos.first] - pos.second;    // 这个块里pos后面的珠子数 + 1
    if (succ_len > 0) {                             // 如果后面还有珠子，那么先进行移动
        memmove(cur + 1, cur, succ_len);
    }
    *cur = ch;
    realn++;
    plen[pos.first]++;

    // 块过长，重组
    if (plen[pos.first] >= sec) {
        p2a();
        a2p();
        pos = find(rank);
    }

    Rank l = pos, r = pos;
    Rank lbound, rbound;
    int dis = 0; // 消除序列长度+1
    int decrease = 0;   // 消除的长度？
    while (1) {
        while (l.first >= 0 && get(l) == ch) {
            l.second--;
            dis++;
            while (l.second < 0 && l.first >= 0) {
                l.first--;
                if (l.first >= 0)
                    l.second += plen[l.first];
            }
        }
        while (r.first < pn && get(r) == ch) {
            r.second++;
            dis++;
            while (r.second >= plen[r.first] && r.first < pn) {
                r.second -= plen[r.first];
                r.first++;
            }
        }
        if (dis > 3) {
            cout << "debug: dis: " << dis << endl;
            decrease += dis - 1;
            lbound = l;
            rbound = r;

            ch = get(l);
            dis = 1;
        } else {
            break;
        }
    }

    if (decrease > 0) {
        realn -= decrease;
        l = lbound;
        r = rbound;
        cout << "debug: l:" << l.first << " r:" << r.first << endl;
        if (l.first >= 0) {
            plen[l.first] = l.second + 1;
        }
        if (r.first < pn) {
            int len = plen[r.first] - r.second;
            if (len > 0) {
                memmove(&p[r.first][0], &p[r.first][r.second], len);
            }
            plen[r.first] = len;
        }
        for (int i = l.first + 1; i < r.first; i++)
            plen[i] = 0;
    }
}

int main() {
    int n;
    fgets(a, sizeof(a), stdin);
    realn = strlen(a);
    while (realn > 0 && (a[realn - 1] == '\n' || a[realn - 1] == '\r'))
        realn--;
    a2p();
    // debug
    cout << "debug init -------" << endl;
    viewp();
    cout << "debug init end----" << endl;
    //
    scanf("%d", &n);
    while (n--) {
        char buf[16];
        char &ch = buf[0];
        int rank;
        scanf("%d%s", &rank, &ch);
        cout << "debug ch: "<< ch << endl;
        play(rank, ch);
        // debug
        cout << "debug viewp-----------" << endl;
        viewp();
        cout << "debug viewp end-------" << endl;
    }
    p2a();
    a[realn] = '\0';
    puts(a);
    return 0;
}
