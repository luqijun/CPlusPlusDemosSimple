#include <iostream>
#include <vector>
#include <utility> // 要包含utility头文件，才能使用pair

using namespace std;

int main() {
    char ceshi[20];
    cin >> ceshi;

    cout << "1111" << endl;

    int n, m; // n是顶点数，m是边数
    cin >> n >> m;

     // 清空输入缓冲区
    cin.ignore();

    vector<vector<pair<int, int>>> adj(n + 1);
    //vector<pair<int, int>> adj[n + 1];

    for (int i = 0; i < m; ++i) {
        int u, v, w; // 从u到v有一条边，边权为w
        cin >> u >> v >> w;
        adj[u].push_back({v, w}); // 存储边的信息
        adj[v].push_back({u, w}); // 因为是无向图，所以要存储两次
    }

    // 输出邻接表
    for (int i = 1; i <= n; ++i) {
        cout << i << ": ";
        for (auto p : adj[i]) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }

    return 0;
}