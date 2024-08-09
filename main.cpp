#include <iostream>#include <string>#include <cmath>#include <sstream>struct test{uint32_t red[5];uint32_t blue[4];uint32_t green[4];uint32_t yellow;};struct test stone = {{0,0,0,0,0},{0,0,0,0},{0,0,0,0},0};struct test stone_1 = {{0,0,0,0,0},{0,0,0,0},{0,0,0,0},0};struct num{uint32_t met [4];uint32_t score;};struct num result{{0,0,0,0},0};void red_type(int x){    switch (x)    {        case 1: case 2: stone.red[x] = stone.red[x-1]*2;break;        case 3: stone.red[x] = ceil(stone.red[x-1]*2.4);break;        case 4: stone.red[x] = stone.red[x-1];break;    }stone.red[x-1] = 0;}void green_type(int x){    switch(x)    {        case 1: stone.green[x] = stone.green[x-1];                stone.yellow+=stone.green[x-1];                break;        case 2: stone.green[x] = ceil(stone.green[x-1]*0.8);                stone.yellow+=stone.green[x] + stone.green[x-1];                break;        case 3: stone.green[x] = ceil(stone.green[x-1]*0.7);                stone.yellow+=stone.green[x] + stone.green[x-1];                break;    }stone.green[x-1] = 0;}void blue_type(int x){    switch(x)    {        case 1: if(stone.blue[x-1]*stone.yellow !=0)                {                stone.blue[x] = ceil((stone.blue[x-1] + stone.yellow)/2);                stone.yellow = 0;stone.blue[x-1] = 0;}                break;        case 2: if(stone.blue[x-1]*stone.green[1] !=0)                {stone.blue[x] = ceil((stone.blue[x-1] + stone.green[1])/2);                stone.green[1] = 0;stone.blue[x-1] = 0;}                break;        case 3: if(stone.blue[x-1]*stone.red[3] !=0)                {stone.blue[x] = ceil((stone.blue[x-1] + stone.red[3])/2);                stone.red[3] = 0;stone.blue[x-1] = 0;}                break;    }}void yellow_type(int x){    switch(x){        case 3: stone.yellow = stone.yellow*5;break;        case 2: stone.yellow = stone.yellow*8;break;        case 1: stone.yellow = stone.yellow*9;break;    }}using namespace std;void caculator(int a,int b, int c, int d){    uint32_t num_score = 0;    num_score += stone.red[3]*35 + stone.red[4]*85    + stone.green[0]*1 + stone.green[1]*5 + stone.green[2]*50 + stone.green[3]*500    + stone.blue[0]*1 + stone.blue[1]*8 + stone.blue[2]*42 + stone.blue[3]*225;    if (c>0)    {num_score += stone.yellow*2;}    else{num_score += stone.yellow;}    cout << num_score << endl;    if (num_score>result.score)    {        result.score = num_score;        result.met[0] = a;        result.met[1] = b;        result.met[2] = c;        result.met[3] = d;    }}void executor(int a,int b, int c, int d){    red_type(1);    red_type(2);    red_type(3);    if(a == 1){red_type(4);}    if(b>0)    {for(int i=1;i<=b;i++)        {            green_type(i);        }    }    if(c>0)    {for(int i=1;i<=c;i++)        {            yellow_type(i);        }    }    if(d>0)    {for(int i=1;i<=d;i++)        {            blue_type(i);        }    }    caculator(a,b,c,d);    cout << stone.yellow <<"x"<< stone.red[3] <<"x"<< stone.blue[1] <<"X"<<stone.blue[0]<< "x"<<stone.green[0]<<endl;    stone = stone_1;}// 生成数组，有对应字母就执行对应函数powerd by FlowingLights// 递归函数，穷举法生成所有可能的情况int creater(int t) {    // 遍历所有可能的总和，从2到6    for (int sum = 2; sum <= t; ++sum) {        cout << "Sum = " << sum << ":" << endl;        // 红色a的范围是0到1（包含）        for (int a = 0; a <= 1; ++a) {            // 剩余三个元素的总和            int RS = sum - a;            // 遍历剩余三个元素的可能值            // 注意：我们不需要显式地遍历所有三个元素，而是可以通过计算来确定它们的组合            // 但为了清晰起见，这里我们采用一个简化的三层循环来模拟            for (int b = 0; b <= 3 && b <= RS; ++b) { // b绿色的最大值是3，且不超过剩余和                for (int c = 0; c <= 3 && b + c <= RS; ++c) { // c黄色的最大值也是3，且b+c不超过剩余和                    int d = RS - b - c; // 最后一个元素d蓝色由剩余和决定                    // 确保d在有效范围内                    if (d >= 0 && d <= 3) {                        // 输出满足条件的数组                        cout << "[" << a << ", " << b << ", " << c << ", " << d << "]" << endl;                        executor(a,b,c,d);                    }                }            }        }        cout << endl; // 总和变化时的分隔符    }    return 0;}int main() {    int r, g, b, y, t; // 声明四个整型变量    result.score = 0;    // 使用cin和空格分隔的输入来接收四个值    cout << "请输入四种石头的数量，顺序为RGBY，和槽位数t：" << endl;    cin >> r >> g >> b >> y >> t;    stone.red[0] = r;    stone.green[0] = g;    stone.blue[0] = b;    stone.yellow = y;    stone_1.red[0] = r;    stone_1.green[0] = g;    stone_1.blue[0] = b;    stone_1.yellow = y;    creater(t);    cout << "最优方法是:顺序为rgyb" << endl;    for (int i=0;i<4;i++)    {        cout <<"x"<< result.met[i] << endl;    }    cout << "最高分数是" << endl;    cout << result.score << endl;    return 0;}