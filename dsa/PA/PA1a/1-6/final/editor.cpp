#include <iostream>
#include <cstring>
#define MAX_LEN 7200002

/*
Author: 刘玉河 2019011560

Honor code:
Discussed with:
关于利用同一数组联系正反方向的单项链表的方法，曾与王之栋同学讨论
关于光标指针的个数，曾与贾启珑同学讨论
Reference:
DSA2020 第一次习题课
*/


using namespace std;

struct CirnosPerfectEditor
{
    char ch[MAX_LEN << 1];
    int ne[MAX_LEN << 1];

    int distance;
    int cur[2];
    int header_fd, header_bd,
        trailer_fd, trailer_bd;
    int new_index;
    
    // 初始化
    inline void init(char s[], int len)
    {
        header_fd = 0, header_bd = MAX_LEN + len + 1;   // 正反序的头哨兵
        trailer_fd = len + 1, trailer_bd = MAX_LEN;     // 正反序的尾哨兵
        for(int i = 1; i < len + 1; ++i)
        {
            ch[i] = ch[i + MAX_LEN] = s[i-1];           // 正反列表中对应同一个字符的节点的字符初始化
            ne[i-1] = i;                                // 正列表的后继
            ne[i + MAX_LEN] = MAX_LEN + i - 1;          // 反列表的后继
        }
        ne[len] = trailer_fd, ne[header_bd] = MAX_LEN + len;    // 补上正列表末节点的后继为尾哨兵、反列表头哨兵的后继为（正向的）末节点
        cur[0] = 1, cur[1] = trailer_fd;           // 光标记录在正列表上
        distance = len;                            // 初始两光标距离为len
        new_index = len + 2;    // 从len+2开始分配新的节点空间
    }
    // 光标向左移动 isRight表示是否为右光标
    inline int move_left(int isRight)
    {
        if(atLeft(isRight)) return 0;   // 如果光标已经处于首节点，移动失败
        cur[isRight] = trans(ne[trans(cur[isRight])]);    // 否则光标的上一个位置，是当前节点在反列表中对应节点的下一个节点，
                                                                // 在正列表中的对应位置
        distance += (isRight) ? -1 : 1;
        return 1;                                               
    }
    // 光标向右移动 isRight表示是否为右光标
    inline int move_right(int isRight)
    {
        if(atRight(isRight)) return 0;  // 如果光标已经处于尾哨兵，移动失败
        cur[isRight] = ne[cur[isRight]];        // 否则光标指向下一个节点

        distance += (isRight) ? 1 : -1;
        return 1;                               
    }
    // 在光标左侧插入节点
    inline void insert(int isRight, const char &c)
    {
        ch[new_index] = ch[trans(new_index)] = c;
        // 正列表插入
        ne[new_index] = cur[isRight];
        ne[trans(ne[trans(cur[isRight])])] = new_index;
        // 反列表插入
        ne[trans(new_index)] = ne[trans(cur[isRight])];
        ne[trans(cur[isRight])] = trans(new_index);
        // 更新光标距离
        if(distance > 0 && isRight) ++distance;
        else if(distance < 0 && !isRight) --distance;
        
        ++new_index;
    }
    inline int remove(int isRight)  // 删除字符
    {
        if(atRight(isRight)) return 0;
        // 正列表删除
        ne[trans(ne[trans(cur[isRight])])] = ne[cur[isRight]];
        // 反列表删除
        ne[trans(ne[cur[isRight]])] = ne[trans(cur[isRight])];
        // 处理光标位置与距离
        cur[isRight] = ne[cur[isRight]];
        if(!distance) cur[!isRight] = cur[isRight];
        else if(distance > 0 && !isRight) --distance;
        else if(distance < 0 && isRight) ++distance;
        
        return 1;
    }
    inline int reverse()        // 翻转区间
    {
        if(distance <= 0) return 0;
        int pos11 = trans(ne[trans(cur[0])]),
            pos12 = trans(ne[trans(cur[1])]),
            pos21 = ne[trans(cur[0])],
            pos22 = ne[trans(cur[1])];
        /*
        pos11->LEFT-------->...->pos12->RIGHT-------->...
                |                        |
        pos21<-trans(LEFT)<-...<-pos22<-trans(RIGHT)<-...
        */
        ne[pos11] = pos22;
        ne[trans(cur[1])] = cur[0];
        ne[pos12] = pos21;
        ne[trans(cur[0])] = cur[1];

        cur[0] = pos22; //更新左光标位置
        return 1;
    }
    inline bool atLeft(int isRight)     // 判断光标是否在最左端
    {
        return cur[isRight] == ne[header_fd];
    }
    inline bool atRight(int isRight)    // 判断光标是否在最右端
    {
        return cur[isRight] == trailer_fd;
    }
    // 给定正（反）向链表的节点，返回反（正）向链表中对应的节点
    inline int trans(int idx)
    {
        return (idx < MAX_LEN) ? idx + MAX_LEN : idx - MAX_LEN;
    }
    inline void show()      // 打印序列
    {
        int idx = ne[header_fd];
        while(idx != trailer_fd)
        {
            putchar(ch[idx]);
            idx = ne[idx];
        }
        putchar('\n');
    }
};

char init_string[3200001];
int N, status;
char op, cursor, ch;
CirnosPerfectEditor editor;

int main()
{
    scanf("%s",init_string);
    editor.init(init_string, strlen(init_string));
    scanf("%d\n",&N);
    for(int i = 0;i < N; ++i)
    {
        op = getchar();
        switch (op)
        {
        case '<':   // 光标左移
        {
            //scanf(" %c\n", &cursor);
            getchar();
            cursor = getchar();
            getchar();

            if(cursor == 'L') status = editor.move_left(0);
            else status = editor.move_left(1);
            if(status) putchar('T');
            else putchar('F');
            putchar('\n');
            break;
        }
        case '>':   // 光标右移
        {
            //scanf(" %c\n", &cursor);
            getchar();
            cursor = getchar();
            getchar();

            if(cursor == 'L') status = editor.move_right(0);
            else status = editor.move_right(1);
            if (status)
                putchar('T');
            else
                putchar('F');
            putchar('\n');
            break;
        }
        case 'I':   // 插入字符
        {
            //scanf(" %c %c\n", &cursor, &ch);
            getchar();
            cursor = getchar();
            getchar();
            ch = getchar();
            getchar();

            editor.insert((cursor=='L')?0:1, ch);
            printf("T\n");
            break;
        }
        case 'D':   // 删除字符
        {
            //scanf(" %c\n", &cursor);
            getchar();
            cursor = getchar();
            getchar();

            status = editor.remove((cursor == 'L') ? 0 : 1);
            if (status)
                putchar('T');
            else
                putchar('F');
            putchar('\n');
            break;
        }
        case 'R':   // 翻转区间
        {
            getchar();

            status = editor.reverse();
            if (status)
                putchar('T');
            else
                putchar('F');
            putchar('\n');
            break;
        }
        case 'S':   // 打印序列
        {
            getchar();

            editor.show();
            break;
        }
        }
    }
    return 0;
}