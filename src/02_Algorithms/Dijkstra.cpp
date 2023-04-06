#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;  // 无穷大表示两个顶点不连通
const int MAXN = 100; // 最大顶点数

int d[MAXN];                        // 存储起点到各个顶点的最短距离
bool used[MAXN];                    // 是否已经确定起点到该顶点的最短距离
vector<pair<int, int>> edges[MAXN]; // 以邻接表形式存储图

// Dijkstra算法求最短路
void dijkstra(int s, int n)
{
    for (int i = 0; i < n; i++)
    {
        d[i] = INF; // 初始化
        used[i] = false;
    }
    d[s] = 0; // 起点到自己的距离（即为0）

    while (true)
    {
        int v = -1;
        for (int u = 0; u < n; u++)
        { // 选择尚未确定最短距离的点中距离最小的点
            if (!used[u] && (v == -1 || d[u] < d[v]))
            {
                v = u;
            }
        }

        if (v == -1)
        { // 如果所有点都已经确定了最短距离，则退出循环
            break;
        }

        used[v] = true;

        for (auto edge : edges[v])
        { // 通过更新与v相邻的点来更新起点到其他点的最短距离
            int u = edge.first;
            int w = edge.second;

            d[u] = min(d[u], d[v] + w);
        }
    }
}

int main111()
{
    int n; // 顶点数
    int m; // 边数
    int s; // 起点
    int t; // 终点

    cin >> n >> m >> s >> t;

    for (int i = 0; i < m; i++)
    { // 输入图的边
        int from, to, weight;
        cin >> from >> to >> weight;
        edges[from].push_back(make_pair(to, weight));
        edges[to].push_back(make_pair(from, weight));
    }

    dijkstra(s, n); // 求出起点到所有点的最短距离

    int ans = d[t]; // 终点的最短距离

    cout << ans << endl;

    return 0;
}