#include <iostream>
#include <cstring>
#include <string>
#include <format>
#include <string_view>
using namespace std;

const int MAXN = 1005; // 最大点数
const int INF = 0x3f3f3f3f;

int weight[MAXN][MAXN];  // 二分图的邻接矩阵
int lx[MAXN], ly[MAXN];  // 顶标
bool sx[MAXN], sy[MAXN]; // 是否在匹配中
int match[MAXN];         // 记录右部点的匹配左部点编号，-1 表示未匹配

int n; // 点的总数，左部点编号 0~n-1，右部点编号 n~2n-1

template <typename T>
string GetArrInfo(T &arr)
{
    string res = "";
    for (size_t i = 0; i < n; i++)
    {
        res += to_string(arr[i]);
        if (i != n - 1)
            res += ' ';
    }
    return res;
}

bool dfs(int u, bool isUpSearch = false)
{
    sx[u] = true;
    cout << "sx: " + GetArrInfo(sx) + "  sy: " + GetArrInfo(sy) + "  lx: " + GetArrInfo(lx) + "  ly: " + GetArrInfo(ly) + "  match:" + GetArrInfo(match) + " --change sx u=" + to_string(u) + (isUpSearch ? " --UpSearch" : "") + "\n";
    for (int v = 0; v < n; v++)
        if (!sy[v] && lx[u] + ly[v] == weight[u][v])
        {
            sy[v] = true;
            cout << "sx: " + GetArrInfo(sx) + "  sy: " + GetArrInfo(sy) + "  lx: " + GetArrInfo(lx) + "  ly: " + GetArrInfo(ly) + "  match:" + GetArrInfo(match) +
                        " --change sy " + "lx[" + to_string(u) + "] + ly[" + to_string(v) + "]=" + to_string(weight[u][v]) + " \n";
            if (match[v] == -1 || dfs(match[v], true))
            {
                match[v] = u;
                cout << "sx: " + GetArrInfo(sx) + "  sy: " + GetArrInfo(sy) + "  lx: " + GetArrInfo(lx) + "  ly: " + GetArrInfo(ly) + "  match:" + GetArrInfo(match) + " --change match \n";
                return true;
            }
        }
    return false;
}

int HungaryMatch(bool maxsum = true)
{
    int i, j;
    if (!maxsum)
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                weight[i][j] = -weight[i][j];
    }

    // 初始化标号
    for (i = 0; i < n; i++)
    {
        lx[i] = -0x1FFFFFFF;
        ly[i] = 0;
        for (j = 0; j < n; j++)
            if (lx[i] < weight[i][j])
                lx[i] = weight[i][j];
    }

    memset(match, -1, sizeof(match));
    for (int u = 0; u < n; u++)
    {
        cout << "Left Point Index:" + to_string(u) + "\n";
        while (true)
        {
            // 重置sx,sy状态 都置为未访问
            memset(sx, 0, sizeof(sx));
            memset(sy, 0, sizeof(sy));

            // 深度优先搜索DFS
            bool is_find = dfs(u);
            cout << "sx: " + GetArrInfo(sx) + "  sy: " + GetArrInfo(sy) + "  lx: " + GetArrInfo(lx) + "  ly: " + GetArrInfo(ly) + "  match:" + GetArrInfo(match) + " --After dfs isfind=" + to_string(is_find) + " \n";
            if (is_find)
                break;

            // 修改标号  DFS未能找到可分配项
            // 对已访问的左侧节点，求他们与未访问的右侧节点的权值最小差值
            int dx = 0x7FFFFFFF;
            for (i = 0; i < n; i++)
                if (sx[i])
                    for (j = 0; j < n; j++)
                        if (!sy[j])
                            dx = min(lx[i] + ly[j] - weight[i][j], dx);

            // 对DFS搜索路径中访问过的左侧节点和右侧节点 更新标号 lx, ly  
            // 主要用于便于递归遍历时查找 lx[u] + ly[v] == weight[u][v] 且 ly[v]==0的匹配项
            for (i = 0; i < n; i++)
            {
                if (sx[i])
                    lx[i] -= dx;
                if (sy[i])
                    ly[i] += dx;
            }

            cout << "sx: " + GetArrInfo(sx) + "  sy: " + GetArrInfo(sy) + "  lx: " + GetArrInfo(lx) + "  ly: " + GetArrInfo(ly) + "  match:" + GetArrInfo(match) + " -- change lx and ly, dx = " + to_string(dx) + "\n";
        }
    }

    int sum = 0;
    for (i = 0; i < n; i++)
        sum += weight[match[i]][i];

    if (!maxsum)
    {
        sum = -sum;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                weight[i][j] = -weight[i][j]; // 如果需要保持 weight [ ] [ ] 原来的值，这里需要将其还原
    }
    return sum;
}

/*
5
3 4 6 4 9
6 4 5 3 8
7 5 3 4 2
6 3 2 2 5
8 4 5 4 7
//执行HungaryMatch (true) ，结果为 29
*/

int main()
{
    // 读入二分图
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> weight[i][j];
        }
    }

    int ans = HungaryMatch();
    cout << ans << endl;

    return 0;
}