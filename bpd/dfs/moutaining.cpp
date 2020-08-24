#include <iostream>
using namespace std;

const int MAXP = 10;

// SAMPLE

int N = 6, P = 6, E[MAXP] = {0, 1,2,2,2,3,3}, M[MAXP] = {0, 7,8,17,18,22,25};

int need[MAXP] = {0}, take[MAXP] = {0}, who[MAXP] = {0}, H[MAXP] = {0};
int minP = MAXP, minNeed = 10000;
int minWho[MAXP] = {0}, minTake[MAXP] = {0}, minH[MAXP] = {0};

void ReadData(){    // 读入数据
    cout << "Input N & P:";
    cin >> N >> P;

    cout << "Input " << P << " E[i]: " ;
    for(int i = 1;i <= P; i++) cin >>E[i];

    cout << "Input " << P << " M[i]: " ;
    for(int i = 1;i <=P; i++) cin >>M[i];
}

void output_debug_info(int k, int dayUseNow) {         // 搜索到成功结果时输出调试信息
    cout << "Persons Number: " << k << endl << '\t' ;
    for(int i = 1; i<=k;i++) cout << who[i] << '#' ;
    cout << ", Total Need = " << need[k] << ", Total Take = " << take[k]
    << ", DayUseNow = " << dayUseNow << endl;
}

void Search(int k, int dayUse ){
    
    if(k > P) return;

    for(int i = 1; i <= P; i++) {

        bool bSelected = false;             // 检查是否已经被选上
        for( int j = 1;j < k; j++) {
            if ( who[j] == i ) {
                bSelected = true;
                break;
            }
        }
        if ( bSelected ) continue;

        if ( H[k-1] * E[i] > M[i] )         // 检查是否是累赘
            continue;
        
        who[k] = i;

        need[k] = need[k-1] + H[k-1] * E[i] * 2;
        take[k] = take[k-1] + M[i];

        if(need[k] <= take[k]) {
            
            #define PLAN_A
            #if defined(PLAN_A)
                if ((k > minP) || (k == minP && need[k] >= minNeed))
                    continue;
            #else
                if(need[k] >= minNeed)
                    continue;
            #endif

            minP = k;
            minNeed = need[k];
            take[k] = need[k];

            for( int j = 1; j <=k; j++) {
                minWho[j] = who[j];
                minTake[j] = take[j] - take[j-1];
                minH[j] = H[j-1];
            }
            output_debug_info(k, dayUse);
        } 
        else {
            int d = need[k] - take[k];

            int dayUseNow = dayUse + E[i];
             
             int w = d / dayUseNow;
             H[k] = (w * dayUseNow == d) ? w : w+1;

             Search(k+1, dayUseNow);
        }
    }
}

int main()
{
    // 1 Input Data
    // ReadData();

    // 2 Create Team
    H[0] = N;
    Search(1,0);

    // 3 Output Solution
    cout << "\nPerson Num: " << minP << ", Need: " << minNeed << endl;
    for(int k=1; k<=minP; k++) {
        cout << "#" << minWho[k]
            << ", take: " << minTake[k]
            << ", return: " << minH[k] << endl;
    }
    return 0;
}