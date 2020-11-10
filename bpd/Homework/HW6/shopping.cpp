#include <iostream>
using namespace std;

struct item {
    int id;
    int price;
    bool discount;
    bool buy;
};

// 返回 true 表明 a 先于 b; false 表明 a 后于 b;
bool cmp(item a, item b)
{
    // 如果 a和 b一个打折一个不打
    if(a.discount ^ b.discount)
        return a.discount;
    if(a.discount)
    {
        if(a.price == b.price)
            return (a.id < b.id);
        else
            return (a.price > b.price);
    }
    else
    {
        if(a.price == b.price)
            return (a.id < b.id);
        else 
            return (a.price < b.price);
    }
        
}

void bubbleSort(item *s, item *t){
    if(s >= t) return;
    for(auto i = t-1;i >= s;--i){
        for(auto j = s;j < i;++j){
            if(cmp(*(j+1), *j)) {
                item tmp = *j;
                *j = *(j+1);
                *(j+1) = tmp;
            }
        }
    }
}
void Sort(item *s, item *t)
{
    if (s >= t)
        return;
    for (auto i = t - 1; i >= s; --i)
    {
        for (auto j = s; j < i; ++j)
        {
            if ((*(j + 1)).id < (*j).id)
            {
                item tmp = *j;
                *j = *(j + 1);
                *(j + 1) = tmp;
            }
        }
    }
}

int cnt;
double budget;
item items[1002];

int main()
{
    cin >> budget >> cnt;
    for(int i = 1; i <= cnt; ++i)
    {
        cin >> items[i].price >> items[i].discount;
        items[i].id = i;
        items[i].buy = false;
    }
    bubbleSort(items+1, items+cnt+1);
    int buy_num = 0, cur = 1;
    while(budget >= 0 && cur <= cnt)
    {
        double cost = (double)items[cur].price * ((items[cur].discount) ? 0.5 : 1);
        if(budget >= cost)
        {
            ++buy_num;
            //cout << items[cur].id << " ";
            //最后的结果还要从小到大，淦
            items[cur].buy = true;
            budget -= cost;
        }
        ++cur;
    }
    if(!buy_num) cout << 0;
    else 
    {
        Sort(items+1, items+1+cnt);
        for(int i = 1; i <= cnt; ++i)
            if( items[i].buy)
                cout << items[i].id << " ";
    }
    return 0;
}