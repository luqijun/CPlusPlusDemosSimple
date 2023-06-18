#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1000; // 最大字符串长度

// 动态规划求解最长公共子序列
int LCS(string A, string B) {
    int dp[MAXN][MAXN];

    int m = A.length();
    int n = B.length();

    cout << m << ' '<< n <<endl; 

    // 边界条件
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }

    // 状态转移方程
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i] == B[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }

    return dp[m][n]; // 返回A和B的最长公共子序列长度
}

int main() {
    string A, B;
    cin >> A >> B; // 输入两个字符串

    int ans = LCS(A, B); // 求最长公共子序列长度

    cout << ans << endl;

    return 0;
}
