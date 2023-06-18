#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
基本思想：左边有节点n个，右边有节点m个，每个节点之间有一条边，每条边有一个权值，求一个匹配，使得匹配的边的权值和最大。

定义visx，visy数组变量，用于记录每次匹配的左边和右边的节点是否被访问过。每一轮都会重置。
定义slack松弛变量，记录右边未匹配节点的最小松弛量，是一个向上递归过程，在递归中获得最小差值。每一轮都会重置。
定义lx，ly数组变量，用于记录每个节点的顶标，lx顶标的初始值为与其相连的边的最大权值, ly初始值为0。
当无法匹配时， lx中已经访问过的节点会减去最小松弛变量， ly中已经匹配过的节点的顶标会加上最小松弛变量。此时，已经意味着腾出一个位置，可以匹配了。匹配到的原始就是那个贡献了最小松弛变量的元素。
重复以上步骤，直到遍历所有n个节点，即可得到最大匹配。

*/

const int N = 510;

int n, m; // n表示左集合的元素个数，m表示右集合的元素个数
int w[N][N], lx[N], ly[N], linky[N], slack[N]; // w表示权值矩阵，lx和ly表示顶标，linky表示右侧元素指向左侧元素的匹配，slack表示松弛量
bool visx[N], visy[N]; // visx和visy表示左侧元素与右侧未匹配元素的连通性

bool dfs(int x) // DFS遍历
{
    visx[x] = true; // 标记从左侧的x开始已访问过
    for (int y = 1; y <= m; y++) // 遍历所有右侧元素
    {
        if (visy[y]) // 如果该元素已匹配，跳过
            continue;
        int t = lx[x] + ly[y] - w[x][y]; // 计算该边的最小权值
        if (t == 0) // 如果该边是相等子图的边，则可以继续匹配
        {
            visy[y] = true; // 右侧元素y已经连通
            if (!linky[y] || dfs(linky[y])) // 如果y元素未匹配，直接匹配；否则，如果可以改进现有匹配，就更新
            {
                linky[y] = x; // 更新y的匹配对象
                return true;
            }
        }
        else if (t > 0) // 如果该边不属于相等子图，且可以优化，更新松弛量
        {
            slack[y] = min(slack[y], t);
        }
    }
    return false; // 无法匹配，返回false
}

int KM() // 匈牙利算法（KM算法）
{
    memset(linky, 0, sizeof(linky)); // 初始化所有右侧元素是否已匹配
    memset(ly, 0, sizeof(ly)); // 右侧元素顶标初始化为0
    // 左侧元素顶标初始化为其相连的最大边权
    for (int i = 1; i <= n; i++)
    {
        lx[i] = -1e9;
        for (int j = 1; j <= m; j++)
        {
            lx[i] = max(lx[i], w[i][j]);
        }
    }
    // 从左边依次匹配右侧元素
    for (int x = 1; x <= n; x++)
    {
        while (true) // 轮流尝试匹配单向边
        {
            memset(visx, false, sizeof(visx)); // 重置访问标记
            memset(visy, false, sizeof(visy));
            memset(slack, 0x3f, sizeof(slack)); // 重置松弛量
            if (dfs(x)) // 如果匹配成功，跳出循环
                break;
            int d = 1e9;
            // 计算松弛量
            for (int i = 1; i <= m; i++)
            {
                if (!visy[i])
                    d = min(d, slack[i]);
            }
            // 更新顶标
            for (int i = 1; i <= n; i++)
            {
                if (visx[i])
                    lx[i] -= d;
            }
            for (int i = 1; i <= m; i++)
            {
                if (visy[i])
                    ly[i] += d;
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= m; i++) // 计算最大匹配的总权值
    {
        if (linky[i])
            res += w[linky[i]][i];
    }
    return res;
}


/*
5 5
3 4 6 4 9
6 4 5 3 8
7 5 3 4 2
6 3 2 2 5
8 4 5 4 7
//执行HungaryMatch (true) ，结果为 29
*/

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> w[i][j]; // 输入权值矩阵
        }
    }
    cout << KM() << endl; // 输出最大权值
}