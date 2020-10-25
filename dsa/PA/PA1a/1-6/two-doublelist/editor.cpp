#include "List.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define Editor CirnosPerfectEditor

class CirnosPerfectEditor
{
    List<char> forward;
    List<char> backward;
    ListNode<char> *cursors[2][2];  // 第一维 0：正序 1：倒序
                                    // 第二维 0: 左光标 1：右光标
    int distance;

public:
    Editor(char *s, int len)
    : distance(len)
    {
        for(int i = 0;i<len;i++)                // 创建初始字符串链表
        {
            forward.insertAsLast(s[i]);
            backward.insertAsLast(s[len-i-1]);
        }
        cursors[0][0] = forward.first();        // 左光标指向第一个元素，表示在第一个元素的左边
        cursors[0][1] = forward.last()->next(); // 右光标指向尾哨兵，表示在最后一个元素的右边
        cursors[1][0] = backward.last();
        cursors[1][1] = backward.first()->prev();
    }
    // 使光标向左移动
    int move_left(int cursor)
    {
        if(cursors[0][cursor] == forward.first() || cursors[0][cursor] == backward.last()) return 0;
        cursors[0][cursor] = cursors[0][cursor]->pre;
        cursors[1][cursor] = cursors[1][cursor]->nex;
        distance += (cursor)? -1:1;

        return 1;
    }
    // 使光标向右移动
    int move_right(int cursor)
    {
        if(cursors[0][cursor]->next() == nullptr) return 0;
        cursors[0][cursor] = cursors[0][cursor]->nex;
        cursors[1][cursor] = cursors[1][cursor]->pre;
        distance += (cursor)? 1:-1;

        return 1;
    }
    void insert(int cursor, char c) // 在光标左边插入一个
    {
        cursors[0][cursor]->insertAsPre(c); 

        cursors[1][cursor]->insertAsNext(c);

        if(distance > 0 && cursor) distance += 1;
        else if(distance < 0 && !(cursor)) distance -= 1; 
    }
    int remove(int cursor)
    {
        if(cursors[0][cursor]->next() == nullptr) return 0;
        
        ListNode<char>* temp = cursors[0][cursor]->next();  // 保存光标下一个位置
        forward.remove(cursors[0][cursor]);
        cursors[0][cursor] = temp;
        if(!distance) cursors[0][!cursor] = temp;

        temp = cursors[1][cursor]->prev();
        backward.remove(cursors[1][cursor]);
        cursors[1][cursor] = temp;
        if(!distance) cursors[1][!cursor] = temp;

        if(distance > 0 && !cursor) distance -= 1;          // 如果原本左光标在右光标左边，此时删除左光标右侧字符，两个光标的距离减一
        else if(distance < 0 && cursor) distance += 1;      // 如果原本右光标在左光标左边，此时删除右光标右侧字符，两个光标的距离加一

        return 1;
    }
    int reverse()
    {
        if(distance <= 0) return 0; // 右光标必须严格在左光标的右侧

        ListNode<char>* temp;
        cursors[0][0]->pre->nex = cursors[1][1]->next();
        temp = cursors[1][1]->next();
        cursors[1][1]->nex->pre = cursors[0][0]->prev();
        cursors[1][1]->nex = cursors[0][0];
        cursors[0][0]->pre = cursors[1][1];
        cursors[0][0] = temp;

        cursors[0][1]->pre->nex = cursors[1][0]->next();
        cursors[1][0]->nex->pre = cursors[0][1]->prev();
        temp = cursors[0][1]->prev();
        cursors[1][0]->nex = cursors[0][1];
        cursors[0][1]->pre = cursors[1][0];
        cursors[1][0] = temp;

        return 1;
    }
    void show()
    {
        ListNode<char> *iter = forward.first();     // 从正向表的首节点开始遍历
        while (iter != forward.first()->prev() &&   // 直到遇到某个哨兵节点
                iter != backward.first()->prev() &&
                iter != forward.last()->next() &&
                iter != backward.last()->next())
        {
            putchar(iter->data());
            iter = iter->next();
        }
        putchar('\n');
    }
};


char init_string[3200001];
int N, status;
char op, cursor, ch;

int main()
{
    scanf("%s",init_string);
    CirnosPerfectEditor editor(init_string, strlen(init_string));
    scanf("%d\n",&N);
    for(int i = 0;i < N; ++i)
    {
        scanf("%c", &op);
        switch (op)
        {
        case '<':
        {
            scanf(" %c\n", &cursor);
            if(cursor == 'L') status = editor.move_left(0);
            else status = editor.move_left(1);
            if(status) putchar('T');
            else putchar('F');
            putchar('\n');
            break;
        }
        case '>':
        {
            scanf(" %c\n", &cursor);
            if(cursor == 'L') status = editor.move_right(0);
            else status = editor.move_right(1);
            if (status)
                putchar('T');
            else
                putchar('F');
            putchar('\n');
            break;
        }
        case 'I':
        {
            scanf(" %c %c\n", &cursor, &ch);
            editor.insert((cursor=='L')?0:1, ch);
            printf("T\n");
            break;
        }
        case 'D':
        {
            scanf(" %c\n", &cursor);
            status = editor.remove((cursor == 'L') ? 0 : 1);
            if (status)
                putchar('T');
            else
                putchar('F');
            putchar('\n');
            break;
        }
        case 'R':
        {
            scanf("\n");
            status = editor.reverse();
            if (status)
                putchar('T');
            else
                putchar('F');
            putchar('\n');
            break;
        }
        case 'S':
        {
            scanf("\n");
            editor.show();
            break;
        }
        }
    }
    return 0;
}